// GC.h: Garbage Collector for Gnash
// 
//   Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef GNASH_GC_H
#define GNASH_GC_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <list>
#include <algorithm> //for std::find

#ifndef NDEBUG
# include <boost/thread.hpp>
#endif

// Define the following macro to enable GC verbosity 
// Define to > 1 to have info printed about scan of already reachable objects
//#define GNASH_GC_DEBUG 1

#ifdef GNASH_GC_DEBUG
# include "log.h"
# include <typeinfo>
#endif

namespace gnash {

class GC;

/// Abstract class to allow the GC to store "roots" into a container
//
/// Any class expected to act as a "root" for the garbage collection 
/// should derive from this class, and implement the markReachableResources()
/// method.
///
///
class GcRoot
{

public:

	/// Scan all GC resources reachable by this instance.
	//
	/// This function is invoked on roots registered to
	/// the collector.
	///
	/// Use setReachable() on the resources stored in this
	/// container.
	///
	virtual void markReachableResources() const=0;

	virtual ~GcRoot() {}
};

/// Collectable resource
//
/// Instances of this class can be managed by a GC object.
///
class GcResource
{

public:

	friend class GC;

	/// Create a Garbage-collected resource.
	//
	/// The resource will be automatically registered with
	/// the garbage collector singleton.
	///
	GcResource();

	/// \brief
	/// Mark this resource as being reachable, possibly triggering
	/// further marking of all resources reachable by this object.
	//
	/// If the object wasn't reachable before, this call triggers
	/// scan of all contained objects too...
	///
	void setReachable() const
	{

		if ( _reachable )
		{
#if GNASH_GC_DEBUG > 1
			log_debug(_("Instance %p of class %s already reachable, setReachable doing nothing"),
					(void*)this, typeid(*this).name());
#endif
			return;
		}

#if GNASH_GC_DEBUG  > 1
		log_debug(_("Instance %p of class %s set to reachable, scanning reachable resources from it"),
				(void*)this, typeid(*this).name());
#endif

		_reachable = true;
		markReachableResources();
	}

	/// Return true if this object is marked as reachable
	bool isReachable() const { return _reachable; }

	/// Clear the reachable flag
	void clearReachable() const { _reachable = false; }

protected:

	/// Scan all GC resources reachable by this instance.
	//
	/// This function is invoked everytime this object
	/// switches from unreachable to reachable, and is
	/// used to recursively mark all contained resources
	/// as reachable.
	///
	/// See setReachable(), which is the function to invoke
	/// against all reachable methods.
	///
	/// Feel free to assert(_reachable) in your implementation.
	///
	/// The default implementation doesn't mark anything.
	///
	virtual void markReachableResources() const
	{
		assert(_reachable);
#if GNASH_GC_DEBUG > 1
		log_debug(_("Class %s didn't override the markReachableResources() method"), typeid(*this).name());
#endif
	}

	/// Delete this resource.
	//
	/// This is protected to allow subclassing, but ideally it
	/// sould be private, so only the GC is allowed to delete us.
	///
	virtual ~GcResource()
	{
	}

private:

	mutable bool _reachable;

};

/// Garbage collector singleton
//
/// Instances of this class ( you' only use one, the singleton )
/// manage a list of heap pointers (collectables) deleting them
/// when no more needed/reachable.
///
/// Reachability of them is detected starting from a list
/// of "root" containers each one expected to provide a
/// function to return all reachable object.
///
/// Each "collectable" objects is also expected to be a container
/// itself.
///
///
class GC
{

public:

	/// Init the singleton instance using the given GcRoot
	//
	static GC& init(GcRoot& r);

	/// Delete the singleton. You'll need to call init() again
	/// after this call, if you want to use the singleton.
	//
	/// See init(GcRoot&)
	///
	static void cleanup();

	/// Get the singleton 
	//
	/// An assertion will fail if the GC has not been initialized yet.
	/// See init(GcRoot&).
	///
	static GC& get();

	/// Add an heap object to the list of managed collectables
	//
	/// The given object is expected not to be already in the
	/// list. Failing to do so would just decrease performances
	/// but might not be a problem. Anyway, an assertion will fail
	/// if adding an object twice.
	///
	/// PRECONDITIONS:
	///	- the object isn't already in this GC list.
	///	- the object isn't marked as reachable.
	///	- the object isn't managed by another GC (UNCHECKED)
	///
	/// @param item
	///	The item to be managed by this collector.
	///	Can't be NULL. The caller gives up ownerhip
	///	of it, which will only be deleted by this GC.
	///
	void addCollectable(const GcResource* item)
	{
#ifndef NDEBUG
		boost::thread self;
		assert(self == mainThread);
		assert(item);
		assert(! item->isReachable());
		assert(std::find(_resList.begin(), _resList.end(), item) == _resList.end());
#endif

		_resList.push_back(item);
#if GNASH_GC_DEBUG > 1
		log_debug(_("GC %p: collectable %p added, num collectables: " SIZET_FMT), (void*)this, (void*)item, _resList.size());
#endif
	}


	/// Run the collector
	//
	/// Find all reachable collectables, destroy all the others.
	///
	void collect()
	{
#ifdef GNASH_GC_DEBUG 
		log_debug(_("Starting collector: " SIZET_FMT " collectables"), _resList.size());
#endif // GNASH_GC_DEBUG

#ifndef NDEBUG
		boost::thread self;
		assert(self == mainThread);
#endif

		// Mark all resources as reachable
		markReachable();

		// clean unreachable resources, and mark them others as reachable again
		cleanUnreachable();

	}

private:

	/// Create a garbage collector, using the given root
	GC(GcRoot& root)
		:
		_root(root)
	{
#ifdef GNASH_GC_DEBUG 
		log_debug(_("GC %p created"), (void*)this);
#endif
	}

	/// Destroy the collector, releasing all collectables.
	~GC();

	/// List of collectables
	typedef std::list<const GcResource *> ResList;

	/// Mark all reachable resources
	void markReachable()
	{
#ifdef GNASH_GC_DEBUG 
		log_debug(_("GC %p: MARK SCAN"), (void*)this);
#endif
		_root.markReachableResources();
	}

	/// Delete all unreachable objects, and mark the others unreachable again
	void cleanUnreachable();

	ResList _resList;

	GcRoot& _root;

	static GC* _singleton;

#ifndef NDEBUG
	/// The thread that initialized the GC is 
	/// the only one allowed to run the collector
	/// and to register collectable objects
	boost::thread mainThread;
#endif
};


inline GcResource::GcResource()
	:
	_reachable(false)
{
	GC::get().addCollectable(this);
}

} // namespace gnash

#endif // GNASH_GC_H
