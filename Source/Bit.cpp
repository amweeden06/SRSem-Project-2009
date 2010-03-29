#include "Bit.hpp"

namespace Sewers
{
	/* CONSTRUCTOR */
	Bit::Bit(int value)
	{
		if(value == 0)
			set_type("0");
		else if(value == 1)
			set_type("1");
		else
			set_type("BIT");
		
		set_width(BIT_WIDTH);
		set_height(BIT_HEIGHT);
	}
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The bit has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Bit::draw() const
	{
		return SUCCESS;
    }	
}
