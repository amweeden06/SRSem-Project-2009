/*  Computer.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Computer.hpp"

namespace Sewers
{
	Computer::Computer()
	{
		set_type("COMPUTER");
		set_left(COMPUTER_LEFT);
		set_bottom(COMPUTER_BOTTOM);
		set_width(COMPUTER_WIDTH);
		set_height(COMPUTER_HEIGHT);
	}
	
	Computer::Computer(const Computer& c)
	{
		set_type(c.type());
		set_left(c.left());
		set_bottom(c.bottom());
		set_width(c.width());
		set_height(c.height());
	}	
	
	void Computer::draw() const
	{
		GLcolor3(0.4,0.4,0.4).glColor();
		glRectf(left(), bottom(), right(), top());
		// Screen
		GLgreen3.glColor();
		glRectf(left() + width()/6, bottom() + height()/3, right() - width()/6, top() - height()/6);
		// Buttons
		GLred3.glColor();
		glRectf(left() + width()/6, bottom() + height()/8, left() + width()/3, bottom() + height()/5);
		GLyellow3.glColor();
		glRectf(right() - width()/3, bottom() + height()/8, right() - width()/6, bottom() + height()/5);
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Information about the object has been displayed to the user.
	void Computer::help() const
	{
	}	
	
	ostream& operator << (ostream& outs, const Computer& c)
    {
        outs << c.type() << endl;
        outs << "\tleft: " << c.left() << endl;
        outs << "\tbottom: " << c.bottom() << endl;
        outs << "\twidth: " << c.width() << endl;
        outs << "\theight: " << c.height() << endl;
        return outs;
    }		
}
