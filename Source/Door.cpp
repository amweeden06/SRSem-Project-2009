/*
 *  Door.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/29/09.
 *  
 */
#include "Door.hpp"

namespace Sewers
{
	void Door::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		if(!_is_open)
		{
			GLgreen3.glColor();
			glBegin(GL_POLYGON);
			glVertex2f(world().left(), world().bottom());
			glVertex2f(world().left(), w_height()/2);
			glVertex2f(world().right(), world().top());
			glVertex2f(world().right(), w_height()/2);
			glEnd();
		}
		GLblack3.glColor();
		glBegin(GL_POLYGON);
		glVertex2f(world().left(), world().bottom());
		glVertex2f(world().right(), w_height()/2);
		glVertex2f(world().right(), world().bottom());
		glEnd();
		glPopAttrib();
	}
}