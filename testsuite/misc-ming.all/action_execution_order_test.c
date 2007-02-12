/*
 *   Copyright (C) 2005, 2006 Free Software Foundation, Inc.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */ 

/*
 * Zou Lunkai, zoulunkai@gmail.com
 *
 * Test the execution order of actions within different movieClips
 *
 * set a variable with a new value under _root, then set it again under anther movieClip.
 *   the variable will only record the later assignment. Checking the final result of the
 *   variable will tell us which action(assignment) is executed first.
 *
 * Expected result is:
 *   In the frame placing mc_red,  actions in mc_red is executed *after* actions in _root
 *   In subsequent frames, actions in mc_red is executed *before* actions in _root
 */

#include <stdlib.h>
#include <stdio.h>
#include <ming.h>

#include "ming_utils.h"

#define OUTPUT_VERSION 6
#define OUTPUT_FILENAME "action_execution_order_test.swf"


int
main(int argc, char** argv)
{
  SWFMovie mo;
  SWFMovieClip  mc_red, dejagnuclip;
  SWFShape  sh_red;

  const char *srcdir=".";
  if ( argc>1 ) 
    srcdir=argv[1];
  else
  {
      fprintf(stderr, "Usage: %s <mediadir>\n", argv[0]);
      return 1;
  }

  Ming_init();
  mo = newSWFMovieWithVersion(OUTPUT_VERSION);
  SWFMovie_setDimension(mo, 800, 600);
  SWFMovie_setRate (mo, 1.0);

  dejagnuclip = get_dejagnu_clip((SWFBlock)get_default_font(srcdir), 10, 0, 0, 800, 600);
  SWFMovie_add(mo, (SWFBlock)dejagnuclip);
  SWFMovie_nextFrame(mo);

  
  mc_red = newSWFMovieClip();
  sh_red = make_fill_square (0, 300, 60, 60, 255, 0, 0, 255, 0, 0);
  SWFMovieClip_add(mc_red, (SWFBlock)sh_red);  
  add_clip_actions(mc_red, " _root.xtrace('as in frame1 of mc_red'); _root.x1 = \"as_in_mc_red\"; ");
  SWFMovieClip_nextFrame(mc_red); /* 1st frame */
  add_clip_actions(mc_red, " _root.xtrace('as in frame2 of mc_red'); _root.x2 = \"as_in_mc_red\"; stop(); ");
  SWFMovieClip_nextFrame(mc_red); /* 2nd frame */
  
  /* Add mc_red to _root and name it as "mc_red" */
  SWFDisplayItem it_red;
  it_red = SWFMovie_add(mo, (SWFBlock)mc_red);  
  SWFDisplayItem_setDepth(it_red, 3); 
  SWFDisplayItem_setName(it_red, "mc_red");
  
  add_actions(mo, " xtrace('as in frame1 of root'); var x1 = \"as_in_root\"; ");
  SWFMovie_nextFrame(mo); /* 1st frame */
  add_actions(mo, " xtrace('as in frame2 of root'); _root.x2 = \"as_in_root\"; ");
  SWFMovie_nextFrame(mo); /* 2nd frame */

  /* In the frame placing mc_red,  actions in mc_red is executed *after* actions in _root */
  check_equals(mo, "_root.x1", "'as_in_mc_red'");
  /* In subsequent frames, actions in mc_red is executed *before* actions in _root */
  xcheck_equals(mo, "_root.x2", "'as_in_root'");
  add_actions(mo, " _root.totals(); stop(); ");
  SWFMovie_nextFrame(mo); /* 3rd frame */

  /* Output movie */
  puts("Saving " OUTPUT_FILENAME );
  SWFMovie_save(mo, OUTPUT_FILENAME);

  return 0;
}



