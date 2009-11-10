/*
 *  Inverter.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/1/09.
 *
 *  Graphical NOT gate object
 */
#include "Inverter.hpp"

namespace Sewers
{
	void Inverter::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		if(!_invisible)
		{
			GLred3.glColor();
			// Draw triangle
			glBegin(GL_POLYGON);
			glVertex2f(world().left(), world().bottom());
			glVertex2f(world().left(), world().top());
			glVertex2f(world().left()+2*w_width()/3, world().bottom() + w_height()/2);
			glEnd();
			// Draw circle
			glBegin(GL_POLYGON);
			glVertex2f(world().left()+2*w_width()/3, world().bottom() + w_height()/2);
			glVertex2f(world().left()+5*w_width()/6, world().bottom() + 3*w_height()/5);
			glVertex2f(world().left()+6*w_width()/6, world().bottom() + w_height()/2);
			glVertex2f(world().left()+5*w_width()/6, world().bottom() + 2*w_height()/5);
			glEnd();
		}
		glPopAttrib();
	}
}