/*  Floor.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{	
	class Floor : public DrawingObject
	{
	public:
		/* DRAWING FUNCTION */
        int draw(GLcolor3) const;
    };
}