/*
 *  OR.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/1/09.
 *
 *  Graphical OR gate object
 */
#include "OR.hpp"

namespace Sewers
{
	void OR::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		if(!_invisible)
		{
			GLred3.glColor();
			// Top of the gate
			glBegin(GL_POLYGON);
			glVertex2f(world().left()+w_width()/3, world().bottom()+w_height()/2);
			glVertex2f(world().left(), world().top());
			glVertex2f(world().left()+2*w_width()/3, world().top());
			glVertex2f(world().right(), world().bottom() + w_height()/2);
			glEnd();
			// Bottom of the gate
			glBegin(GL_POLYGON);
			glVertex2f(world().left()+w_width()/3, world().bottom()+w_height()/2);
			glVertex2f(world().left(), world().bottom());
			glVertex2f(world().left()+2*w_width()/3, world().bottom());
			glVertex2f(world().right(), world().bottom() + w_height()/2);
			glEnd();
			// Draw the +
			GLblack3.glColor();
			glBegin(GL_LINES);
			glVertex2f(world().left()+4*w_width()/7, world().top()-w_height()/4);
			glVertex2f(world().left()+4*w_width()/7, world().bottom()+w_height()/4);
			glVertex2f(world().left()+2*w_width()/5, world().top()-w_height()/2);
			glVertex2f(world().left()+4*w_width()/5, world().top()-w_height()/2);
			glEnd();
		}
		glPopAttrib();
	}
}