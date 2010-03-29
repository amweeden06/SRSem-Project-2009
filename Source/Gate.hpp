/*  Gate.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 *
 *  CLASS INVARIANTS:
 *
 */
#ifndef GATEOBJ
#define GATEOBJ

#include "DrawingObject.hpp"
#include "TruthTable.hpp"
#include "Connection.hpp"

namespace Sewers
{	
	class Gate : public DrawingObject
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
		TruthTable _truth_table;
		Connection _connections[MAX_NUM_GATE_INPUTS];
		DrawingObject* _outputs[MAX_NUM_BLUEPRINT_GATES - 1];
    };
}

#endif