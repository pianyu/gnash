// PrintJob_as.hx:  ActionScript 3 "PrintJob" class, for Gnash.
//
// Generated by gen-as3.sh on: 20090515 by "rob". Remove this
// after any hand editing loosing changes.
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

// This test case must be processed by CPP before compiling to include the
//  DejaGnu.hx header file for the testing framework support.

#if flash9
import flash.printing.PrintJob;
import flash.printing.PrintJobOrientation;
import flash.display.MovieClip;
#else
import flash.PrintJob;
import flash.MovieClip;
#end
import flash.Lib;
import Type;
import Std;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class PrintJob_as {
    static function main() {
        var x1:PrintJob = new PrintJob();

        // Make sure we actually get a valid class        
        if (x1 != null) {
            DejaGnu.pass("PrintJob class exists");
        } else {
            DejaGnu.fail("PrintJob class doesn't exist");
        }
		

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (Type.typeof(x1.addPage) == ValueType.TFunction) {
	    DejaGnu.pass("PrintJob::addPage() method exists");
	} else {
	    DejaGnu.fail("PrintJob::addPage() method doesn't exist");
	}
	if (Type.typeof(x1.send) == ValueType.TFunction) {
	    DejaGnu.pass("PrintJob::send() method exists");
	} else {
	    DejaGnu.fail("PrintJob::send() method doesn't exist");
	}
	
 	if (Type.typeof(x1.start) == ValueType.TFunction) {
 	    DejaGnu.pass("PrintJob::start() method exists");
		//need to run x1.start() to populate the properties
		x1.start();
 	} else {
 	    DejaGnu.fail("PrintJob::start() method doesn't exist");	 	
	}



// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.

// These properties don't exist until after a call to PrintJob.start in flash9	

	DejaGnu.note("Orientation type: " + Type.typeof(x1.orientation));
	DejaGnu.note("x1.orientation: " + Std.string(x1.orientation));
	DejaGnu.note("Orientation class: " + Type.getClass(x1.orientation));
	//DejaGnu.note("Orientation type" + Type.getClassName(x1.orientation));

#if flash9
	//not sure why this is returning type TNull test may be incorrect
	if ( Type.typeof(x1.orientation) == ValueType.TNull) {
	    DejaGnu.pass("PrintJob.orientation property exists");
	} else {
	    DejaGnu.fail("PrintJob.orientation property doesn't exist");
	}
#else
	if ( (x1.orientation == "portrait") || x1.orientation == "landscape") {
	    DejaGnu.pass("PrintJob.orientation property exists");
	} else {
	    DejaGnu.fail("PrintJob.orientation property doesn't exist");
	}
#end

	if (Type.typeof(x1.pageHeight) == ValueType.TInt) {
	    DejaGnu.pass("PrintJob.pageHeight property exists");
	} else {
	    DejaGnu.fail("PrintJob.pageHeight property doesn't exist");
	}
	if (Type.typeof(x1.pageWidth) == ValueType.TInt) {
	    DejaGnu.pass("PrintJob.pageWidth property exists");
	} else {
	    DejaGnu.fail("PrintJob.pageWidth property doesn't exist");
	}
	if (Type.typeof(x1.paperHeight) == ValueType.TInt) {
	    DejaGnu.pass("PrintJob.paperHeight property exists");
	} else {
	    DejaGnu.fail("PrintJob.paperHeight property doesn't exist");
	}
	if (Type.typeof(x1.paperWidth) == ValueType.TInt) {
	    DejaGnu.pass("PrintJob.paperWidth property exists");
	} else {
	    DejaGnu.fail("PrintJob.paperWidth property doesn't exist");
	}


        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
    }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

