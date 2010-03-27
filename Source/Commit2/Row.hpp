/*  Row.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"
#include "Bit.hpp"

namespace Sewers
{	
	class Row : public DrawingObject
	{
	public:
		static const int MAX_NUM_COLUMNS = MAX_NUM_GATE_INPUTS + 1;
		/* ACCESSORS */
		int num_columns() const;
		Bit columns(int index) const;
		/* FUNCTIONS */
		int add_column(Bit);
        int draw() const;
	private:
		Bit _columns[MAX_NUM_COLUMNS];
    };
	
	/* A TESTING FUNCTION FOR THE ROW CLASS */
	static void RowTest()
	{
		Row r;
		Bit b;
		b.set_type("BIT");
		int i;
		
		for(i = 0; i < r.MAX_NUM_COLUMNS; ++i)
		{
			if(r.num_columns() != i)
			{
				cerr << "ERROR:  Row should have had " << i << " columns but instead had ";
				cerr << r.num_columns() << "." << endl;
				exit(EXIT_FAILURE);
			}
			
			if(r.add_column(b) == FULL_ARRAY)
			{
				cerr << "ERROR: Row has " << r.num_columns() << " columns but it claims to have ";
				cerr << "a full array, but a full array is " << r.MAX_NUM_COLUMNS << "." << endl;
				exit(EXIT_FAILURE);
			}
		}
		
		if(r.add_column(b) != FULL_ARRAY)
		{
			cerr << "ERROR: Row has " << r.num_columns() << " columns but it claims to have ";
			cerr << "a non-full array, but a full array is " << r.MAX_NUM_COLUMNS << "." << endl;
			exit(EXIT_FAILURE);			
		}
	}	
}