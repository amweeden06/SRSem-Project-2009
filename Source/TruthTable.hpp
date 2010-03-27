/*  TruthTable.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"
#include "Switch.hpp"
#include "Row.hpp"

namespace Sewers
{	
	class TruthTable : public DrawingObject
	{
	public:
		static const int MAX_NUM_INPUTS = MAX_NUM_GATE_INPUTS;
		static const int MAX_NUM_ROWS = MAX_NUM_TT_ROWS;
		/* ACCESSORS */
		int num_inputs() const;
		Switch inputs(size_t index) const;
		int num_rows() const;
		Row rows(size_t index) const;
		/* FUNCTIONS */
		int add_input(Switch);
        int draw() const;
	private:
		Row _rows[MAX_NUM_ROWS];
		Switch _inputs[MAX_NUM_INPUTS];
    };
}