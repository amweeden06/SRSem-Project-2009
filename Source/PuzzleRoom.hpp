/*  PuzzleRoom.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 *
 *  CLASS INVARIANTS:
 *
 */
#include "Room.hpp"
#include "Puzzle.hpp"

namespace Sewers
{	
	class PuzzleRoom : public Room
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
		Puzzle _puzzles[PUZZLES_PER_ROOM];
    };
}