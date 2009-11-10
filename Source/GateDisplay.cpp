/*
 *  GateDisplay.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/29/09.
 *  
 */
#include "GateDisplay.hpp"

namespace Sewers
{	
	void GateDisplay::re_display(void)
	{
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		(GLcolor3(0.8, 0.9, 0)).glColor();
		glRectf(world().left(), world().bottom(), world().right(), world().top());
		glPopAttrib();
		_inverter.reMap(IntRect(viewport().left() + v_width()/6, viewport().left() + v_width()/6 + 20, viewport().bottom() + v_height()/4, viewport().bottom() + v_height()/4 + 20));
		_inverter.re_display();
		_AND.reMap(IntRect(viewport().left() + 2*v_width()/5, viewport().left() + 2*v_width()/5 + 20, viewport().bottom() + v_height()/4, viewport().bottom() + v_height()/4 + 20));
		_AND.re_display();
		_OR.reMap(IntRect(viewport().left() + 2*v_width()/3, viewport().left() + 2*v_width()/3 + 20, viewport().bottom() + v_height()/4, viewport().bottom() + v_height()/4 + 20));
		_OR.re_display();
	}
}