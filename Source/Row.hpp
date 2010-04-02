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
		Bit columns(size_t) const;
		/* FUNCTIONS */
		int clear();
		int add_column(Bit);
        int draw() const;
	private:
		Bit _columns[MAX_NUM_COLUMNS];
    };
	
	/* A TESTING FUNCTION FOR THE ROW CLASS */
	static void RowTest()
	{
		Row r;
		Bit b(0);
		int i;
		
		r.clear();
		
		for(i = 0; i < r.MAX_NUM_COLUMNS; ++i)
		{
			if(r.num_columns() != i)
			{
				cerr << "ERROR:  Row should have had " << i << " columns but instead had ";
				cerr << r.num_columns() << "." << endl;
			}
			
			if(r.add_column(b) == FULL_ARRAY)
			{
				cerr << "ERROR: Row has " << r.num_columns() << " columns but it claims to have ";
				cerr << "a full array, but a full array is " << r.MAX_NUM_COLUMNS << "." << endl;
			}
		}
		
		if(r.add_column(b) != FULL_ARRAY)
		{
			cerr << "ERROR: Row has " << r.num_columns() << " columns but it claims to have ";
			cerr << "a non-full array, but a full array is " << r.MAX_NUM_COLUMNS << "." << endl;
		}
		
		r.clear();
		if(r.num_columns() != 0)
		{
			cerr << "ERROR: Clearing the row should have given it 0 columns, instead it has ";
			cerr << r.num_columns() << endl;
		}
	}	
}