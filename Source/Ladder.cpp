/*
 *  Ladder.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/29/09.
 *
 */
#include "Ladder.hpp"

namespace Sewers
{
	void Ladder::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		GLwhite3.glColor();
		glBegin(GL_POLYGON);
		// Rung 1 
		glVertex2f(world().left(), world().bottom()+0.5);
		glVertex2f(world().left(), world().top()-0.1);
		glVertex2f(world().left()+0.2, world().top()-0.2);
		glVertex2f(world().left()+0.2, world().bottom()+0.4);
		glEnd();
		glBegin(GL_POLYGON);
		// Rung 2
		glVertex2f(world().left()+0.4, world().bottom()+0.3);
		glVertex2f(world().left()+0.4, world().top()-0.3);
		glVertex2f(world().left()+0.6, world().top()-0.4);
		glVertex2f(world().left()+0.6, world().bottom()+0.2);
		glEnd();
		glBegin(GL_POLYGON);
		// Rung 3
		glVertex2f(world().left()+0.8, world().bottom()+0.1);
		glVertex2f(world().left()+0.8, world().top()-0.5);
		glVertex2f(world().right(), world().top()-0.6);
		glVertex2f(world().right(), world().bottom());
		glEnd();
		glPopAttrib();
	}
}