/*
 *  MenuBar.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/27/09.
 *
 */
#include "MenuBar.hpp"

namespace Sewers
{	
	void MenuBar::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		_color.glColor();
		glRecti(world().left(), world().top(), world().right(), world().bottom());
		
		// Set colors
		_new.set_color(GLgreen3);
		_save.set_color(GLblue3);
		_load.set_color(GLyellow3);
		_quit.set_color(GLred3);
				
		// Draw buttons
		_new.reMap(IntRect(viewport().left(), viewport().left() + v_width()/4, viewport().bottom(), viewport().top()));
		_new.re_display();
		_save.reMap(IntRect(viewport().left() + v_width()/4, viewport().left() + v_width()/2, viewport().bottom(), viewport().top()));
		_save.re_display();
		_load.reMap(IntRect(viewport().left() + v_width()/2, viewport().right() - v_width()/4, viewport().bottom(), viewport().top()));
		_load.re_display();
		_quit.reMap(IntRect(viewport().left() + 3*v_width()/4, viewport().right(), viewport().bottom(), viewport().top()));
		_quit.re_display();
		
		glPopAttrib();
	}
}