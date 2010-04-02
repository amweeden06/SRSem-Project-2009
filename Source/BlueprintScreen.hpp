/*  BlueprintScreen.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 *
 *  CLASS INVARIANTS:
 *
 */
#include "DrawingObject.hpp"
#include "Gate.hpp"

namespace Sewers
{	
	class BlueprintScreen : public DrawingObject
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
		Switch _switches[MAX_NUM_GATE_INPUTS];
		Gate _selected_gate;
		Gate _available_gates[NUM_PUZZLES];
		Connection _selected_connection;
		Gate _gates_in_play[MAX_NUM_BLUEPRINT_GATES];
		Row _row;
    };
}