/*  Workbench.hpp
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
	class Workbench : public DrawingObject
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
    };
}