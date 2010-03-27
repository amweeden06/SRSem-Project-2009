/*
 *
 */
#include "Connection.hpp"

namespace Sewers
{	
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The object has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Connection::draw() const
	{
		return SUCCESS;
    }
}