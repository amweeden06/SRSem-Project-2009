/*  Door.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, 2009-2010
 */

#include "Door.hpp"

namespace Sewers 
{
	Door::Door(string type)
	{
		set_type(type);
		set_left(0);
		set_bottom(0);
		set_width(0);
		set_height(0);
		
		set_is_open(false);
	}
	
	Door::Door(const Door& d)
	{
		set_type(d.type());
		set_left(d.left());
		set_bottom(d.bottom());
		set_width(d.width());
		set_height(d.height());
		
		set_is_open(d.is_open());
	}
	
	// PRECONDITIONS: none
    // POSTCONDITION: The Door has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void Door::draw() const
	{
		if(is_open())
			FLOOR_COLOR.glColor();
		else
			DOOR_COLOR.glColor();

		glRecti(left(), bottom(), right(), top());
    }	
	
    ostream& operator << (ostream& outs, const Door& d)
    {
        outs << d.type() << endl;
        outs << "\tleft: " << d.left() << endl;
        outs << "\tbottom: " << d.bottom() << endl;
        outs << "\twidth: " << d.width() << endl;
        outs << "\theight: " << d.height() << endl;
        return outs;
    }	
}
