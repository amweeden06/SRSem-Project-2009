#include "Row.hpp"

namespace Sewers
{			
	/* FUNCTION: num_columns()
	 * PRECONDITIONS: none
	 * POSTCONDITIONS: none
	 * RETURN VALUE: The number of columns in the row.
	 */
	int Row::num_columns() const
	{
		for(int i = 0; i < MAX_NUM_COLUMNS; ++i)
		{
			if(_columns[i].type() == Bit().type())
				return i;
		}
		return MAX_NUM_COLUMNS;
	}
	
	/* FUNCTION: columns(size_t index)
	 * PRECONDITIONS: index is less than num_columns()
	 * POSTCONDITIONS: none
	 * RETURN VALUE: the bit at position index if the precondition was met, a default Bit
	 *  otherwise
	 */
	Bit Row::columns(size_t index) const
	{
		if(index < num_columns())
			return _columns[index];
		else
			return Bit();
	}
	
	/* FUNCTION: clear()
	 * PRECONDITIONS: none
	 * POSTCONDITION: the row no longer contains any bits
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int Row::clear()
	{
		for(int i = 0; i < num_columns(); ++i)
			_columns[i] = Bit();
		return SUCCESS;
	}
	
	/* FUNCTION: add_column(Bit b)
	 * PRECONDITIONS: the row does not already have the maximum number of columns
	 * POSTCONDITION: b has been added to the array of bits
	 * POSSIBLE RETURN VALUES: SUCCESS, FULL_ARRAY
	 */
	int Row::add_column(Bit b)
	{
		if(num_columns() < MAX_NUM_COLUMNS)
		{
			_columns[num_columns()] = b;
			return SUCCESS;
		}
		else
			return FULL_ARRAY;
	}	
		
	/* FUNCTION: draw()
	 * PRECONDITIONS: none
	 * POSTCONDITION: The object has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * RETURN VALUE: SUCCESS
	 */
	int Row::draw() const
	{
		return SUCCESS;
    }	
}
