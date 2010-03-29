#include "Switch.hpp"

namespace Sewers
{	
	/* CONSTRUCTOR */
	Switch::Switch(string type)
	{
		set_type(type);
		for(int i = 0; i < MAX_NUM_OUTPUTS; ++i)
			_outputs[i] = NULL;
	}
	
	/* FUNCTION: num_inputs()
	 * PRECONDITIONS: none
	 * POSTCONDITIONS: none
	 * RETURN VALUE: The number of outputs the switch possesses.
	 */
	int Switch::num_outputs() const
	{
		for(int i = 0; i < MAX_NUM_OUTPUTS; ++i)
		{
			if(_outputs[i] == NULL)
				return i;
		}
		return MAX_NUM_OUTPUTS;
	}
	
	/* FUNCTION: outputs(size_t index)
	 * PRECONDITIONS: index is less than num_inputs()
	 * POSTCONDITIONS: none
	 * RETURN VALUE: the output object at position index if the precondition was met, 
	 *  NULL otherwise
	 */
	DrawingObject* Switch::outputs(size_t index) const
	{
		if(index < num_outputs())
			return _outputs[index];
		else
			return NULL;
	}


	/* FUNCTION: add_output(DrawingObject* o)
	 * PRECONDITIONS: the switch does not already have the maximum number of outputs
	 * POSTCONDITION: o has been added to the array of pointers to outputs
	 * POSSIBLE RETURN VALUES: SUCCESS, FULL_ARRAY
	 */
	int Switch::add_output(DrawingObject* o)
	{
		if(num_outputs() != MAX_NUM_OUTPUTS)
		{
			_outputs[num_outputs()] = o;
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
	int Switch::draw() const
	{
		return SUCCESS;
    }	
}
