/*
 *
 */
#include "TruthTable.hpp"

namespace Sewers
{	
	/* FUNCTION: num_inputs()
	 * PRECONDITIONS: none
	 * POSTCONDITIONS: none
	 * RETURN VALUE: The number of inputs (switches) in the truth table.  This is also the
	 *  number of column headings.
	 */
	int TruthTable::num_inputs() const
	{
		for(int i = 0; i < MAX_NUM_INPUTS; ++i)
		{
			if(_inputs[i].type() == Switch().type())
				return i;
		}
		return MAX_NUM_INPUTS;
	}
	
	/* FUNCTION: inputs(size_t index)
	 * PRECONDITIONS: index is less than num_inputs()
	 * POSTCONDITIONS: none
	 * RETURN VALUE: the switch at position index if the precondition was met, a default Switch
	 *  otherwise
	 */
	Switch TruthTable::inputs(size_t index) const
	{
		if(index < num_inputs())
			return _inputs[index];
		else
			return Switch();
	}
	
	/* FUNCTION: num_rows()
	 * PRECONDITIONS: none
	 * POSTCONDITIONS: none
	 * RETURN VALUE: The number of rows in the truth table.
	 */
	int TruthTable::num_rows() const
	{
		for(int i = 0; i < MAX_NUM_ROWS; ++i)
		{
			if(_rows[i].type() == Row().type())
				return i;
		}
		return MAX_NUM_ROWS;
	}
	
	/* FUNCTION: rows(size_t index)
	 * PRECONDITIONS: index is less than num_rows()
	 * POSTCONDITIONS: none
	 * RETURN VALUE: the row at position index if the precondition was met, a default row
	 *  otherwise
	 */
	Row TruthTable::rows(size_t index) const
	{
		if(index < num_rows())
			return _rows[index];
		else
			return Row();
	}
	
	/* FUNCTION: add_input(Switch s)
	 * PRECONDITIONS: the table does not already have the maximum number of inputs
	 * POSTCONDITION: s has been added as an input in the table.  2 rows have been added for
	 *  that input, and each row in the table has also been given an extra column for that input.
	 * POSSIBLE RETURN VALUES: SUCCESS, FULL_ARRAY
	 */
	int TruthTable::add_input(Switch s)
	{
		if(num_inputs() != MAX_NUM_INPUTS)
		{
			_inputs[num_inputs()] = s;
			
			// TODO:  add 2 rows
			
			// TODO:  Give a new column to each row in the table 
			
			// TODO:  Fill out the rows again with their correct values
			
			return SUCCESS;
		}
		else
			return FULL_ARRAY;
	}		
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The object has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int TruthTable::draw() const
	{
		return SUCCESS;
    }
}