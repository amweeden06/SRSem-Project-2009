/*  Switch.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Switch.hpp"

namespace Sewers
{
	Switch::Switch(int output_value)
	{
		set_type("SWITCH");
		set_left(0);
		set_bottom(0);
		set_width(SWITCH_WIDTH);
		set_height(SWITCH_HEIGHT);
		set_output(CircuitObject());
		set_output_value(output_value);
	}
	
	Switch::Switch(const Switch& s)
	{
		set_type(s.type());
		set_left(s.left());
		set_bottom(s.bottom());
		set_width(s.width());
		set_height(s.height());
		set_output(s.output());
		if(s.has_button())
			give_button();
		set_output_value(s.output_value());
	}	
		
	// PRECONDITIONS: none
    // POSTCONDITION: The switch has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void Switch::draw() const
	{
		// Draw the button if necessary
		if(has_button())
		{
			GLcolor3(0.2, 0.0, 0.0).glColor();
            glRectf(left(), bottom(), left() + width()/3, top());
            GLred3.glColor();
            glRectf(left() + width()/12, bottom() + height()/4, left() + width()/4, top() - height()/4);			
		}
		// Draw the 1
		ONE_COLOR.glColor();
		glRectf(left() + 2*width()/3 + width()/24, top() - 2*height()/5, 
				left() + 2*width()/3 + width()/9, top());
		
		// Draw the 0
		ZERO_COLOR.glColor();
		glRectf(left() + 2*width()/3, bottom() + 3*height()/8,
				left() + 2*width()/3 + width()/12, bottom() + height()/2);
		glRectf(left() + 2*width()/3, bottom(),			     
				left() + 2*width()/3 + width()/24, bottom() + height()/2);
		glRectf(left() + 2*width()/3 + width()/12, bottom(),				
				left() + 2*width()/3 + 3*width()/24, bottom() + height()/2);
		glRectf(left() + 2*width()/3, bottom(), 
				left() + 2*width()/3 + width()/12, bottom() + height()/8);
		
		if(output_value() == 1)
		{
			// Draw wire from the one
			ONE_COLOR.glColor();
			glBegin(GL_LINES);
			glVertex2f(left() + 2*width()/3 + width()/6, top() - height()/4);
			glVertex2f(left() + width(), bottom() + height()/2);
			glEnd();
		}
		else
		{
			// Draw wire from the zero
			ZERO_COLOR.glColor();
			glBegin(GL_LINES);
			glVertex2f(left() + 2*width()/3 + width()/6, bottom() + height()/4);
			glVertex2f(left() + width(), bottom() + height()/2);
			glEnd();
		}			
    }	
	
	ostream& operator << ( ostream& outs, const Switch& s )
    {
        outs << s.type() << endl;
        outs << "\tleft: " << s.left() << endl;
        outs << "\tbottom: " << s.bottom() << endl;
        outs << "\twidth: " << s.width() << endl;
        outs << "\theight: " << s.height() << endl;
		outs << "\t" << (s.has_button() ? "has button" : "has no button") << endl;
		outs << "\toutput value: " << s.output_value() << endl;
        return outs;
    }
	
}