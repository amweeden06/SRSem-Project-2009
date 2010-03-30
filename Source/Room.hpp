/*  Room.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#ifndef ROOMOBJ
#define ROOMOBJ

#include "DrawingObject.hpp"
#include "Floor.hpp"

namespace Sewers
{	
	class Room : public DrawingObject
	{
	public:
		/* CONSTRUCTOR */
		Room();
		/* ACCESSORS */
		Room* left_neighbor() const { return _left_neighbor; }
		Room* right_neighbor() const { return _right_neighbor; }
		Room* bottom_neighbor() const { return _bottom_neighbor; }
		Room* top_neighbor() const { return _top_neighbor; }
		Floor main_floor() const { return _main_floor; }
		Floor left_doorway() const { return _left_doorway; }
		Floor right_doorway() const { return _right_doorway; }
		Floor bottom_doorway() const { return _bottom_doorway; }
		Floor top_doorway() const { return _top_doorway; }
		/* MUTATORS */
		void set_main_floor(Floor f) { _main_floor = f; }
		void set_left_neighbor(Room* r) { _left_neighbor = r; }
		void set_right_neighbor(Room* r) { _right_neighbor = r; }
		void set_bottom_neighbor(Room* r) { _bottom_neighbor = r; }
		void set_top_neighbor(Room* r) { _top_neighbor = r; }
		/* FUNCTIONS */
        int draw() const;
	private:
		Room* _left_neighbor;
		Room* _right_neighbor;
		Room* _bottom_neighbor;
		Room* _top_neighbor;
		Floor _main_floor, _left_doorway, _right_doorway, _bottom_doorway, _top_doorway;
    };
}

#endif