/*  Entrance.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Entrance.hpp"

namespace Sewers
{
	Entrance::Entrance()
	{
		set_type("ENTRANCE");
		set_left(ENTRANCE_LEFT);
		set_bottom(ENTRANCE_BOTTOM);
		set_width(ENTRANCE_WIDTH);
		set_height(ENTRANCE_HEIGHT);
		set_as_ladder();
	}
	
	Entrance::Entrance(const Entrance& e)
	{
		set_type(e.type());
		set_left(e.left());
		set_bottom(e.bottom());
		set_width(e.width());
		set_height(e.height());
		if(e.is_ladder())
			set_as_ladder();
		else 
			set_as_door();
	}	
	
	void Entrance::draw() const
	{
		if(is_ladder())
		{
			WALL_COLOR.glColor();
			glRectf(left(), bottom(), right(), top());
			LADDER_COLOR.glColor();
			glBegin(GL_POLYGON);
			// Top Rung 
			glVertex2f(left(), bottom() + 3*height()/5);
			glVertex2f(left(), top());
			glVertex2f(left() + width()/5, top() - height()/5);
			glVertex2f(left() + width()/5, bottom() + 2*height()/5);
			glEnd();
			glBegin(GL_POLYGON);
			// Middle Rung
			glVertex2f(left() + 2*width()/5, bottom() + height()/3);
			glVertex2f(left() + 2*width()/5, top() - height()/4);
			glVertex2f(left() + 3*width()/5, top() - 2*height()/5);
			glVertex2f(left() + 3*width()/5, bottom() + height()/5);
			glEnd();
			glBegin(GL_POLYGON);
			// Bottom Rung
			glVertex2f(left() + 4*width()/5, bottom() + height()/5);
			glVertex2f(left() + 4*width()/5, bottom() + 3*height()/5);
			glVertex2f(right(), top() - 3*height()/5);
			glVertex2f(right(), bottom());
			glEnd();
		}
		else 
		{
			// Draw the wall
			WALL_COLOR.glColor();
			glBegin(GL_POLYGON);
			glVertex2f(left(), bottom());
			glVertex2f(left(), top() - height()/2);
			glVertex2f(right(), bottom());
			glEnd();
		}
	}
	
	ostream& operator << (ostream& outs, const Entrance& e)
    {
        outs << e.type() << endl;
        outs << "\tleft: " << e.left() << endl;
        outs << "\tbottom: " << e.bottom() << endl;
        outs << "\twidth: " << e.width() << endl;
        outs << "\theight: " << e.height() << endl;
		outs << "\tis ladder?: " << ((e.is_ladder()) ? "true" : "false") << endl;
        return outs;
    }		
}
