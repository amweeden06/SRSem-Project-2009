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
			if(_rows[i].num_columns() == 0)
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
	
	/* FUNCTION: set_up_rows()
	 * PRECONDITIONS: none
	 * POSTCONDITION: All rows have been filled in with the appropriate 1's and 0's, execpt
	 *  for the last column, which is empty.
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int TruthTable::set_up_rows()
	{
		/* Each row can be thought of as representing a binary number:
		 * 0001, 0010, 0011, etc.  So, the table is constructed by constructing
		 * these numbers.  We know a binary number is of the form:
		 * C1(2)^E + C2(2)^(E-1) + C3(2)^(E-2) + ... + Cn(2)^(0),
		 * where C1..n are coefficients and E is an exponent representing the number of digits
		 * in the number.  Note that in this case, E is the number of rows in the table.
		 */
		int decimal = -1; // The decimal representation of the number
		int factor = -1; // 2^(current exponent)
		int coefficient = -1; // The current coefficient
		
		/* There will be one decimal number for each row, 2^(num inputs) rows total */
		for(int i = 0; i < (int)pow(2.0,num_inputs()); ++i)
		{
			_rows[i].clear();
			decimal = i;
			for(factor = (int)pow(2.0,num_inputs())/2; factor >= 1; factor /= 2)
			{
				/* Find the coefficient via integer division; this becomes the value of the
			     * bit in the current row
				 */
				coefficient = decimal/factor;
				_rows[i].add_column(Bit(coefficient));

				/* The remainder becomes the new decimal */
				decimal = decimal % factor;
			}
		}
		return SUCCESS;
	}
	
	/* FUNCTION: add_input(Switch s)
	 * PRECONDITIONS: the table does not already have the maximum number of inputs
	 * POSTCONDITION: s has been added as an input in the table.
	 * POSSIBLE RETURN VALUES: SUCCESS, FULL_ARRAY
	 */
	int TruthTable::add_input(Switch s)
	{
		if(num_inputs() != MAX_NUM_INPUTS)
		{
			/* Add s as an input */
			_inputs[num_inputs()] = s;
			
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