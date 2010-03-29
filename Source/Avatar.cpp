/*  Avatar.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Avatar.hpp"

namespace Sewers
{
	/* CONSTRUCTOR */
	Avatar::Avatar()
	{
		set_width(AVATAR_WIDTH);
		set_height(AVATAR_HEIGHT);
	}
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The avatar has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush() wearing the specified shirt color
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */	
	int Avatar::draw(GLcolor3 shirt_color) const
	{
		// Avatar's eye coordinates
		GLint eye_l, eye_r, eye_b, eye_t;
		// Avatar's shoe coordinates
		GLint shoe_l = left() + width()/6, shoe_r = right() - width()/6, shoe_b = bottom(), shoe_t = bottom() + height()/6; // Both shoes together
		GLint lshoe_l = left() + 2*width()/3, lshoe_r = right(), rshoe_l = left(), rshoe_r = left() + width()/3; // Individual shoes
		if(direction() == "LEFT")
		{
			eye_l = left();
			eye_r = left() + width()/6;
			eye_b = top() - height()/4;
			eye_t = top() - height()/8;
		}
		else if(direction() == "RIGHT")
		{
			eye_l = right() - width()/6;
			eye_r = right();
			eye_b = top() - height()/4;
			eye_t = top() - height()/8;
		}
		else if(direction() == "DOWN")
		{
			eye_l = left() + width()/8;
			eye_r = left() + width()/3;
			eye_b = top() - 3*height()/8;
			eye_t = top() - height()/4;
		}
		
		// Set head color
		HEAD_COLOR.glColor();
		// Draw head
		glRectf(left(), bottom() + height()/2, right(), top());
		
		// Draw eye
		EYE_COLOR.glColor();
		if(direction() != "UP")
			glRectf(eye_l, eye_b, eye_r, eye_t);
		if(direction() == "DOWN")
			// Draw right eye
			glRectf(left() + 2*width()/3, top() - 3*height()/8, right() - width()/8, top() - height()/4);
		
		// Draw torso
		shirt_color.glColor();
		glRectf(left(),  bottom() + height()/6, right(), top() - height()/2);
		
		// Draw shoes
		SHOE_COLOR.glColor();
		if(( direction() == "LEFT" ) || ( direction() == "RIGHT" ))
		{
			if( animation_frame() )
			{
				// Right shoe
				glRectf(rshoe_l, shoe_b, rshoe_r, shoe_t);
				// Left shoe
				glRectf(lshoe_l, shoe_b, lshoe_r, shoe_t);
			}
			else
				// Both shoes together
				glRectf(shoe_l,	shoe_b,	shoe_r,	shoe_t);
		}
		else
		{
			if( animation_frame() )
				// Right shoe
				glRectf(rshoe_l, shoe_b, rshoe_r, shoe_t);
			else
				// Left shoe
				glRectf(lshoe_l, shoe_b, lshoe_r, shoe_t);
		}
		return SUCCESS;
	}
}
