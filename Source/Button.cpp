/*
 *
 */
#include "Button.hpp"

namespace Sewers
{	
	/* CONSTRUCTOR */
	Button::Button()
	{
		set_width(AVATAR_WIDTH);
		set_height(AVATAR_HEIGHT);
	}
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The button has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Button::draw() const
	{
		return SUCCESS;
    }
}