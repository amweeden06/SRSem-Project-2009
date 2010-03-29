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
		int set_up_rows();
		int add_input(Switch);
        int draw() const;
	private:
		Row _rows[MAX_NUM_ROWS];
		Switch _inputs[MAX_NUM_INPUTS];
    };
	
	/* A TESTING FUNCTION FOR THE TRUTHTABLE CLASS */
	static void TruthTableTest()
	{
		TruthTable t;
		Switch s("A");
		
		for(int i = 0; i < t.MAX_NUM_INPUTS; ++i)
		{
			/* Test the num_inputs() function */
			if(t.num_inputs() != i)
			{
				cerr << "ERROR:  Truth Table should have " << i << " inputs but instead ";
				cerr << "has " << t.num_inputs() << "." << endl;
			}
			
			/* Test the add_input() function */
			int num_inputs = t.num_inputs();
			if(t.add_input(s) == FULL_ARRAY)
			{
				cerr << "ERROR: Truth Table has " << t.num_inputs() << " inputs but it ";
				cerr << "claims to have a full array, but a full array is ";
				cerr << t.MAX_NUM_INPUTS << "." << endl;
			}
			if(t.num_inputs() != num_inputs + 1)
			{
				cerr << "ERROR: Adding an input to a Truth Table does not increase the ";
				cerr << "number of inputs.  Should be " << num_inputs + 1 << ", is instead ";
				cerr << t.num_inputs() << endl;
			}
			
			/* Test the set_up_rows() function */
			if(t.set_up_rows() != SUCCESS)
			{
				cerr << "ERROR: Setting up rows with " << t.num_inputs() << " inputs and ";
				cerr << t.num_rows() << " rows failed." << endl;
			}
			if(t.num_rows() != pow(2.0, t.num_inputs()))
			{
				cerr << "ERROR: After setting up rows, there are " << t.num_inputs();
				cerr << " inputs but only " << t.num_rows() << " rows." << endl;
			}
						
			/* Output the table */
			for(int j = 0; j < t.num_rows(); ++j)
			{
				for(int k = 0; k < t.rows(j).num_columns(); ++k)
					cerr << t.rows(j).columns(k).type()
					<< " ";
				cerr << endl;
			}
			cerr << endl;			
		}
		
		/* Test the add_input() function on a full array */
		if(t.add_input(s) != FULL_ARRAY)
		{
			cerr << "ERROR: Table has " << t.num_inputs() << " outputs but it claims to have ";
			cerr << "a non-full array, but a full array is " << t.MAX_NUM_INPUTS << "." << endl;
		}
	}
}