// NativeDragEvent_as.h:  ActionScript 3 "NativeDragEvent" class, for Gnash.
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
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
//

#ifndef GNASH_ASOBJ3_NATIVEDRAGEVENT_H
#define GNASH_ASOBJ3_NATIVEDRAGEVENT_H

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "fn_call.h"

namespace gnash {

// Forward declarations
class as_object;
namespace {
    as_object* getNativeDragEventInterface();
}

class NativeDragEvent_as: public as_object
{

public:

    NativeDragEvent_as()
        :
        as_object(getNativeDragEventInterface())
    {}

};

/// Initialize the global NativeDragEvent class
void nativedragevent_class_init(as_object& global);

} // gnash namespace

// GNASH_ASOBJ3_NATIVEDRAGEVENT_H
#endif

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
