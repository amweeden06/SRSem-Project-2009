#include "Floor.hpp"

namespace Sewers
{
	/* FUNCTION: draw(GLcolor3 color)
	 * PRECONDITIONS: None
	 * POSTCONDITION: The object has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush() with the specified color
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Floor::draw(GLcolor3 color) const
	{
		color.glColor();
		glRecti(left(), bottom(), right(), top());
		return SUCCESS;
    }	
}
