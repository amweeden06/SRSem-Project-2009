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
		/* DRAWING FUNCTION */
        int draw() const;
    };
}