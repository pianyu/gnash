// Microphone_as.hx:  ActionScript 3 "Microphone" class, for Gnash.
//
// This test is only valid for Flash v9 and higher.
//
// Generated on: 20090602 by "bnaugle". Remove this
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
import flash.media.Microphone;
import flash.media.SoundTransform;
import flash.display.MovieClip;
#else
import flash.Microphone;
#end
import flash.Lib;
import Type;
import Std;

import DejaGnu;

// Class must be named with the PP prefix, as that's the name the
// file passed to haxe will have after the preprocessing step
class Microphone_as {
    static function typeof(thing:Dynamic) {
        return ("" + untyped __typeof__(thing));
    }
    
    static function main() {
#if flash9
        var x1:Microphone = Microphone.getMicrophone();
#else
		var x1:Microphone = Microphone.get();
#end

        // Make sure we actually get a valid class        
        if (Std.is(x1, Microphone)) {
            DejaGnu.pass("Microphone class exists");
        } else {
            DejaGnu.xfail("Microphone class doesn't exist");
        }
// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (typeof(x1.activityLevel) == "number") {
	    DejaGnu.pass("Microphone.activityLevel property exists");
	} else {
	    DejaGnu.fail("Microphone.activityLevel property doesn't exist");
	}
	
	
	//FIXME: this will need to be implemented if speex codec is supported
	//FIXME: it would be nice if this analyzed the string to see if it is
	//a supported codec
	//if (Type.typeof(x1.codec) == ValueType.TObject)  {
	//	DejaGnu.pass("Microphone::codec property exists");
	//} else {
	//	DejaGnu.fail("Microphone::codec property doesn't exist");
	//}
	//if (Type.typeof(x1.encodeQuality) == ValueType.TInt)  {
	//	DejaGnu.pass("Microphone::encodeQuality (speex) property exists");
	//} else {
	//	DejaGnu.fail("Microphone::encodeQuality (speex) property doesn't exist");
	//}
	//if (Type.typeof(x1.framesPerPacket) == ValueType.TInt) {
	//	DejaGnu.pass("Microphone::framesPerPacket (speex) property exists");
	//} else {
	//	DejaGnu.fail("Microphone::framesPerPacket (speex) property doesn't exist");
	//}
	
	
	if (typeof(x1.gain) == "number") {
	    DejaGnu.pass("Microphone::gain property exists");
	} else {
	    DejaGnu.fail("Microphone::gain property doesn't exist");
	}
	if (typeof(x1.index) == "number") {
	    DejaGnu.pass("Microphone::index property exists");
	} else {
	    DejaGnu.fail("Microphone::index property doesn't exist");
	}
	if (typeof(x1.muted) == "boolean") {
	    DejaGnu.pass("Microphone::muted property exists");
	} else {
	    DejaGnu.fail("Microphone::muted property doesn't exist");
	}
	//FIXME: it would be nice if this parsed and checked the name string
	if (typeof(x1.name) == "string") {
	    DejaGnu.pass("Microphone::name property exists");
	} else {
	    DejaGnu.fail("Microphone::name property doesn't exist");
	}
	if (typeof(x1.rate) == "number") {
	    DejaGnu.pass("Microphone::rate property exists");
	} else {
	    DejaGnu.fail("Microphone::rate property doesn't exist");
	}
	if (typeof(x1.silenceLevel) == "number") {
	    DejaGnu.pass("Microphone::silenceLevel property exists");
	} else {
	    DejaGnu.fail("Microphone::silenceLevel property doesn't exist");
	}
#if flash9
	if (Std.is(x1.soundTransform, SoundTransform)) {
	    DejaGnu.pass("Microphone::soundTransform property exists");
	} else {
	    DejaGnu.xfail("Microphone::soundTransform property doesn't exist");
	}
	if (Type.typeof(x1.silenceTimeout) == ValueType.TInt) {
	    DejaGnu.pass("Microphone::silenceTimeout property exists");
	} else {
	    DejaGnu.xfail("Microphone::silenceTimeout property doesn't exist");
	}
#else
	if (typeof(x1.silenceTimeOut) == "number") {
	    DejaGnu.pass("Microphone::silenceTimeOut property exists");
	} else {
	    DejaGnu.fail("Microphone::silenceTimeOut property doesn't exist");
	}
#end
	if (typeof(x1.useEchoSuppression) == "boolean") {
	    DejaGnu.pass("Microphone::useEchoSuppression property exists");
	} else {
	    DejaGnu.fail("Microphone::useEchoSuppression property doesn't exist");
	}

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
#if flash9
	if (Type.typeof(x1.setLoopBack) == ValueType.TFunction) {
	    DejaGnu.pass("Microphone::setLoopBack() method exists");
	} else {
	    DejaGnu.fail("Microphone::setLoopBack() method doesn't exist");
	}
#else
	if (Type.typeof(x1.setRate) == ValueType.TFunction) {
	    DejaGnu.pass("Microphone::setRate() method exists");
	} else {
	    DejaGnu.xfail("Microphone::setRate() method doesn't exist");
	}
	if (Type.typeof(x1.setGain) == ValueType.TFunction) {
	    DejaGnu.pass("Microphone::setGain() method exists");
	} else {
	    DejaGnu.xfail("Microphone::setGain() method doesn't exist");
	}
#end
	if (Type.typeof(x1.setSilenceLevel) == ValueType.TFunction) {
	    DejaGnu.pass("Microphone::setSilenceLevel() method exists");
	} else {
	    DejaGnu.xfail("Microphone::setSilenceLevel() method doesn't exist");
	}
	if (Type.typeof(x1.setUseEchoSuppression) == ValueType.TFunction) {
	    DejaGnu.pass("Microphone::setUseEchoSuppression() method exists");
	} else {
	    DejaGnu.xfail("Microphone::setUseEchoSuppression() method doesn't exist");
	}

        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
    }
}
