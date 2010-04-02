/*  Bit.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{	
	class Bit : public DrawingObject
	{
	public:
		/* CONSTRUCTOR */
		Bit(int value = -1);
		/* DRAWING FUNCTION */
        int draw() const;
    };
	
	/* A TESTING FUNCTION FOR THE BIT CLASS */
	static void BitTest()
	{
		Bit b1;
		if(b1.type() != "BIT")
		{
			cerr << "ERROR: Bit should have type BIT but instead has type " << b1.type() << endl;
		}
		Bit b2(0);
		if(b2.type() != "0")
		{
			cerr << "ERROR: Bit should have type 0 but instead has type " << b2.type() << endl;
		}
		Bit b3(1);
		if(b3.type() != "1")
		{
			cerr << "ERROR: Bit should have type 1 but instead has type " << b3.type() << endl;
		}
	}
}