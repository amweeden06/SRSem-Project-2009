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
		
		_main_floor.set_left(MAIN_FLOOR_LEFT);
		_main_floor.set_bottom(MAIN_FLOOR_BOTTOM);
		_main_floor.set_width(MAIN_FLOOR_WIDTH);
		_main_floor.set_height(MAIN_FLOOR_HEIGHT);
		
		_left_doorway.set_left(LEFT_DOORWAY_LEFT);
		_left_doorway.set_bottom(LEFT_DOORWAY_BOTTOM);
		_left_doorway.set_width(LEFT_DOORWAY_WIDTH);
		_left_doorway.set_height(LEFT_DOORWAY_HEIGHT);
		
		_right_doorway.set_left(RIGHT_DOORWAY_LEFT);
		_right_doorway.set_bottom(RIGHT_DOORWAY_BOTTOM);
		_right_doorway.set_width(RIGHT_DOORWAY_WIDTH);
		_right_doorway.set_height(RIGHT_DOORWAY_HEIGHT);
		
		_bottom_doorway.set_left(BOTTOM_DOORWAY_LEFT);
		_bottom_doorway.set_bottom(BOTTOM_DOORWAY_BOTTOM);
		_bottom_doorway.set_width(BOTTOM_DOORWAY_WIDTH);
		_bottom_doorway.set_height(BOTTOM_DOORWAY_HEIGHT);
		
		_top_doorway.set_left(TOP_DOORWAY_LEFT);
		_top_doorway.set_bottom(TOP_DOORWAY_BOTTOM);
		_top_doorway.set_width(TOP_DOORWAY_WIDTH);
		_top_doorway.set_height(TOP_DOORWAY_HEIGHT);			
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
