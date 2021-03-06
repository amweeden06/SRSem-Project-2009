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
		set_exit(NULL);
	}
	
	Computer::Computer(const Computer& c)
	{
		set_type(c.type());
		set_left(c.left());
		set_bottom(c.bottom());
		set_width(c.width());
		set_height(c.height());
		set_exit(c.exit());
	}	
	
	void Computer::draw() const
	{
		GLcolor3(0.4,0.4,0.4).glColor();
		glRectf(left(), bottom(), right(), top());
		// Screen
		if(is_on())
			GLgreen3.glColor();
		else
			GLcolor3(0.0,0.3,0.0).glColor();
		glRectf(left() + width()/6, bottom() + height()/3, right() - width()/6, top() - height()/6);
		// Buttons
		GLred3.glColor();
		glRectf(left() + width()/6, bottom() + height()/8, left() + width()/3, bottom() + height()/5);
		GLyellow3.glColor();
		glRectf(right() - width()/3, bottom() + height()/8, right() - width()/6, bottom() + height()/5);
	}
	
	ostream& operator << ( ostream& outs, const Computer& c )
    {
        outs << c.type() << endl;
        outs << "\tleft: " << c.left() << endl;
        outs << "\tbottom: " << c.bottom() << endl;
        outs << "\twidth: " << c.width() << endl;
        outs << "\theight: " << c.height() << endl;
		outs << "\tis on?: " << ((c.is_on()) ? "true" : "false") << endl;
        return outs;
    }		
}