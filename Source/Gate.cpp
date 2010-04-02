#include "Gate.hpp"

namespace Sewers
{
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The gate has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Gate::draw() const
	{
		return SUCCESS;
    }	
}
