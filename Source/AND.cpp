/*
 *  AND.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/1/09.
 *
 *  Graphical AND gate object
 */
#include "AND.hpp"

namespace Sewers
{
	void AND::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		if(!_invisible)
		{
			GLred3.glColor();
			glBegin(GL_POLYGON);
			glVertex2f(world().left(), world().bottom());
			glVertex2f(world().left(), world().top());
			glVertex2f(world().left()+w_width()/2, world().top());
			glVertex2f(world().right(), world().bottom() + 2*w_height()/3);
			glVertex2f(world().right(), world().bottom() + 1*w_height()/3);
			glVertex2f(world().left()+w_width()/2, world().bottom());
			glEnd();
			// Draw the dot
			GLblack3.glColor();
			glRectf(world().left()+2*w_width()/5, world().bottom()+2*w_height()/5, world().left()+3*w_width()/5, world().bottom()+3*w_height()/5);
			glEnd();
		}
		glPopAttrib();
	}
}