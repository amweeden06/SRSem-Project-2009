/*
 *
 */
#include "CircuitObject.hpp"

namespace Sewers
{
	CircuitObject::CircuitObject(string type)
	{
		set_type(type);
		set_left(0);
		set_bottom(0);
		set_width(0);
		set_height(0);
		set_input1(NULL);
		set_input2(NULL);
		set_output(NULL);
		set_output_value(0);
	}
	
	CircuitObject::CircuitObject(const CircuitObject& o)
	{
		set_type(o.type());
		set_left(o.left());
		set_bottom(o.bottom());
		set_width(o.width());
		set_height(o.height());
		set_input1(o.input1());
		set_input2(o.input2());
		set_output(o.output());
		set_output_value(o.output_value());
		if(o.has_button())
			give_button();
	}
	
	int CircuitObject::output_value() const
	{
		if(type() == "SWITCH")
			return _output_value;
		else if(type() == "NOT")
		{
			// Return the logical negation of the input
			if(input1()->output_value() == 0)
				return 1;
			else
				return 0;
		}
		else if(type() == "AND")
		{
			// Return 1 if all of the inputs are 1
			if(input1()->output_value() == 1 &&
			   input2()->output_value() == 1)
				return 1;
			else
				return 0;
		}
		else if(type() == "OR")
		{
			// Return 1 if any of the inputs are 1
			if(input1()->output_value() == 1 ||
			   input2()->output_value() == 1)
				return 1;
			else
				return 0;
		}
		else
		{
			// Just return the input
			return input1()->output_value();
		}
	}
	
	// PRECONDITIONS: none
    // POSTCONDITION: The object has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void CircuitObject::draw() const
	{
		if(type() == "SWITCH")
		{
			// Draw the button if necessary
			if(has_button())
			{
				GLcolor3(0.2, 0.0, 0.0).glColor();
				glRectf(left(), bottom(), left() + BUTTON_WIDTH, bottom() + BUTTON_HEIGHT);
				GLred3.glColor();
				glRectf(left() + BUTTON_WIDTH/4, bottom() + BUTTON_HEIGHT/4, left() + 3*BUTTON_WIDTH/4, top() - BUTTON_HEIGHT/4);			
			}
			// Draw the 1
			ONE_COLOR.glColor();
			glRectf(left() + 2*width()/3, top() - 2*height()/5, 
					left() + 2*width()/3 + width()/9, top());
			
			// Draw the 0
			ZERO_COLOR.glColor();
			glRectf(left() + 2*width()/3 - width()/12, bottom() + 3*height()/8,
					left() + 2*width()/3 + width()/12, bottom() + height()/2);
			glRectf(left() + 2*width()/3 - width()/12, bottom(),			     
					left() + 2*width()/3, bottom() + height()/2);
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
		else if(type() == "NOT")
		{
			GATE_COLOR.glColor();
			// Draw triangle
			glBegin(GL_POLYGON);
			glVertex2f(left(), bottom());
			glVertex2f(left(), top());
			glVertex2f(left()+2*width()/3, bottom() + height()/2);
			glEnd();
			// Draw circle
			glBegin(GL_POLYGON);
			glVertex2f(left()+2*width()/3, bottom() + height()/2);
			glVertex2f(left()+5*width()/6, bottom() + 3*height()/5);
			glVertex2f(left()+6*width()/6, bottom() + height()/2);
			glVertex2f(left()+5*width()/6, bottom() + 2*height()/5);
			glEnd();
		}
		else if(type() == "AND")
		{
			GATE_COLOR.glColor();
			glBegin(GL_POLYGON);
			glVertex2f(left(), bottom());
			glVertex2f(left(), top());
			glVertex2f(left()+width()/2, top());
			glVertex2f(right(), bottom() + 2*height()/3);
			glVertex2f(right(), bottom() + 1*height()/3);
			glVertex2f(left()+width()/2, bottom());
			glEnd();
			// Draw the dot
			GLblack3.glColor();
			glRectf(left()+2*width()/5, bottom()+2*height()/5, left()+3*width()/5, bottom()+3*height()/5);
			glEnd();			
		}
		else if(type() == "OR")
		{
			GATE_COLOR.glColor();
			// Top of the gate
			glBegin(GL_POLYGON);
			glVertex2f(left()+width()/3, bottom()+height()/2);
			glVertex2f(left(), top());
			glVertex2f(left()+2*width()/3, top());
			glVertex2f(right(), bottom() + height()/2);
			glEnd();
			// Bottom of the gate
			glBegin(GL_POLYGON);
			glVertex2f(left()+width()/3, bottom()+height()/2);
			glVertex2f(left(), bottom());
			glVertex2f(left()+2*width()/3, bottom());
			glVertex2f(right(), bottom() + height()/2);
			glEnd();
			// Draw the +
			GLblack3.glColor();
			glBegin(GL_LINES);
			glVertex2f(left()+4*width()/7, top()-height()/4);
			glVertex2f(left()+4*width()/7, bottom()+height()/4);
			glVertex2f(left()+2*width()/5, top()-height()/2);
			glVertex2f(left()+4*width()/5, top()-height()/2);
			glEnd();			
		}	
		else if(type() == "EXIT")
		{
			if(!is_open())
			{
				// Draw the door
				DOOR_COLOR.glColor();
				glBegin(GL_POLYGON);
				glVertex2f(left(), bottom());
				glVertex2f(left(), top() - height()/2);
				glVertex2f(right(), top());
				glVertex2f(right(), top() - height()/2);
				glEnd();
			}
			// Draw the wall
			WALL_COLOR.glColor();
			glBegin(GL_POLYGON);
			glVertex2f(left(), bottom());
			glVertex2f(right(), top() - height()/2);
			glVertex2f(right(), bottom());
			glEnd();			
		}
    }	
	
    ostream& operator << ( ostream& outs, const CircuitObject& o )
    {
        outs << o.type() << endl;
        outs << "\tleft: " << o.left() << endl;
        outs << "\tbottom: " << o.bottom() << endl;
        outs << "\twidth: " << o.width() << endl;
        outs << "\theight: " << o.height() << endl;
		if(o.has_button())
			outs << "\thas a button" << endl;
		outs << "\toutput value: " << o.output_value() << endl;
        return outs;
    }
}
