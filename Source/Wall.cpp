/*
 *  Wall.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Graphical wall object.  Can optionally be a control panel or door.
 */
#include "Wall.hpp"

namespace Sewers
{
	void Wall::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		_color.glColor();
		glRecti(world().left(), world().top(), world().right(), world().bottom());
		glPopAttrib();
	}
}