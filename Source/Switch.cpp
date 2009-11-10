/*
 *  Switch.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/1/09.
 *
 *  Switch that appears on the floor.  Represents a 0 or 1.
 */
#include "Switch.hpp"

namespace Sewers
{
	void Switch::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		
		if(_is_1)
		{
			// Draw the 1
			GLgreen3.glColor();
			glRectf(w_width()/4, 0, 3*w_width()/4, w_height());
		}
		else
		{
			// Draw the 0
			GLblue3.glColor();
			//   Top Line
			glRectf(world().left() + 1*w_width()/8,	world().bottom(),					3*world().right()/8,	world().top());		// Left Line
			glRectf(world().left() + 1*w_width()/8,	world().bottom(),					7*world().right()/8,	world().top()/4);	// Bottom Line
			glRectf(world().left() + 5*w_width()/8, world().bottom(),					7*world().right()/8,	world().top());		// Right Line
			glRectf(world().left() + 1*w_width()/8,	world().bottom() + 3*w_height()/4,	7*world().right()/8,	world().top());		// Top Line
		}
		glPopAttrib();
	}
}