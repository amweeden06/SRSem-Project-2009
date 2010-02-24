/*  Exit.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Exit.hpp"

namespace Sewers
{
	Exit::Exit()
	{
		set_type("EXIT");
		set_left(EXIT_LEFT);
		set_bottom(EXIT_BOTTOM);
		set_width(EXIT_WIDTH);
		set_height(EXIT_HEIGHT);
		add_input(CircuitObject());
		close();
	}
	
	Exit::Exit(const Exit& e)
	{
		set_type(e.type());
		set_left(e.left());
		set_bottom(e.bottom());
		set_width(e.width());
		set_height(e.height());
		add_input(e.input());
		if(e.is_open())
			open();
		else
			close();
	}	
	
	// PRECONDITIONS: none
    // POSTCONDITION: The exit has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void Exit::draw() const
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
	
	ostream& operator << ( ostream& outs, const Exit& e )
    {
        outs << e.type() << endl;
        outs << "\tleft: " << e.left() << endl;
        outs << "\tbottom: " << e.bottom() << endl;
        outs << "\twidth: " << e.width() << endl;
        outs << "\theight: " << e.height() << endl;
		outs << "\t" << (e.is_open() ? "open" : "closed") << endl;
		outs << "\t" << (e.needs_input() ? "needs input" : "needs no input") << endl;
        return outs;
    }
	
}