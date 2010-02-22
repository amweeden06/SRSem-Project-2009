/*  Gate.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Gate.hpp"

namespace Sewers
{
	Gate::Gate(string type)
	{
		set_type(type);
		set_left(0);
		set_bottom(0);
		set_width(GATE_WIDTH);
		set_height(GATE_HEIGHT);
		if(type == "NOT")
			set_expected_num_inputs(1);
		set_output(CircuitObject());
	}
	
	Gate::Gate(const Gate& g)
	{
		set_type(g.type());
		set_left(g.left());
		set_bottom(g.bottom());
		set_width(g.width());
		set_height(g.height());
		for(size_t i = 0; i < g.num_inputs(); ++i)
			add_input(g.inputs(i));
		set_expected_num_inputs(g.expected_num_inputs());
		set_output(g.output());
	}	
	
	// PRECONDITIONS: No inputs are needed
	// POSTCONDITION: Returns the output value of the gate as calculated based on
	//                 the inputs
	int Gate::output_value(const vector<int> inputs) const
	{
		assert(!needs_input());
		if(type() == "NOT")
		{
			if(inputs[0] == 0)
				return 1;
			else
				return 0;
		}
	}
	
	
	void Gate::add_input(const CircuitObject input)
	{
		_inputs.push_back(input);
	}
	
	void Gate::update_input(const CircuitObject input)
	{
		/*for(size_t i = 0; i < num_inputs(); ++i)
		{
			if(input == inputs(i))
				_inputs[i] = input;
		}*/
	}
		
	// PRECONDITIONS: none
    // POSTCONDITION: The gate has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void Gate::draw() const
	{
		if(type() == "NOT")
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
    }	
	
	ostream& operator << ( ostream& outs, const Gate& g )
    {
        outs << g.type() << endl;
        outs << "\tleft: " << g.left() << endl;
        outs << "\tbottom: " << g.bottom() << endl;
        outs << "\twidth: " << g.width() << endl;
        outs << "\theight: " << g.height() << endl;
		outs << "\texpected num inputs: " << g.expected_num_inputs() << endl;
		outs << "\tnum inputs: " << g.num_inputs() << endl;
		if(g.needs_input())
			outs << "\tneeds input" << endl;
		return outs;
    }
}