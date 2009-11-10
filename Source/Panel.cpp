/*
 *  Panel.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/1/09.
 *
 *  Panel that appears on the floor.  The player can place a gate on the panel.
 */
#include "Panel.hpp"

namespace Sewers
{
	void Panel::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		GLblack3.glColor();
		glBegin(GL_LINE_LOOP);
		glVertex2f(world().left(), world().top());
		glVertex2f(world().left(), world().bottom());
		glVertex2f(world().right(), world().bottom());
		glVertex2f(world().right(), world().top());
		glEnd();
		glPopAttrib();
	}
}