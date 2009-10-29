/*
 *  MenuButton.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/27/09.
 *
 */
#include "MenuButton.hpp"

namespace Sewers
{
	void MenuButton::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		_color.glColor();
		glRectf(world().left(), world().top(), world().right(), world().bottom());
		glPopAttrib();
	}
}