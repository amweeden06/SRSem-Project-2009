/*  Button.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"
#include "Avatar.hpp"

namespace Sewers
{	
	class Button : public DrawingObject
	{
	public:
        int draw() const;
    };
}