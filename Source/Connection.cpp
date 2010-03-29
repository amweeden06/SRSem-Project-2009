/*
 *
 */
#include "Connection.hpp"

namespace Sewers
{	
	Connection::Connection()
	{
		set_width(CONNECTION_WIDTH);
		set_height(CONNECTION_HEIGHT);
	}
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The connection has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Connection::draw() const
	{
		return SUCCESS;
    }
}