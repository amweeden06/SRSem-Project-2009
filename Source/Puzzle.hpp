/*  Puzzle.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 *
 *  CLASS INVARIANTS:
 *
 */
#ifndef PUZZLEOBJ
#define PUZZLEOBJ

#include "Avatar.hpp"
#include "Gate.hpp"

namespace Sewers
{	
	class Puzzle : public DrawingObject
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
		Avatar _engineer;
		Gate _gate;
    };
}

#endif