#include "Room.hpp"

namespace Sewers
{
	/* CONSTRUCTOR */
	Room::Room()
	{
		_left_neighbor = NULL;
		_right_neighbor = NULL;
		_bottom_neighbor = NULL;
		_top_neighbor = NULL;
		_left_doorway.set_type("FLOOR");
		_right_doorway.set_type("FLOOR");
		_bottom_doorway.set_type("FLOOR");
		_top_doorway.set_type("FLOOR");
	}
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: none
	 * POSTCONDITION: The room has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * RETURN VALUE: SUCCESS
	 */
	int Room::draw() const
	{
		_main_floor.draw(FLOOR_COLOR);
		if(_left_neighbor != NULL)
			_left_doorway.draw(FLOOR_COLOR);
		if(_right_neighbor != NULL)
			_right_doorway.draw(FLOOR_COLOR);
		if(_bottom_neighbor != NULL)
			_bottom_doorway.draw(FLOOR_COLOR);
		if(_top_neighbor != NULL)
			_top_doorway.draw(FLOOR_COLOR);
		return SUCCESS;
    }	
}
