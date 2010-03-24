/*  Computer.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "CircuitObject.hpp"

namespace Sewers
{
	/* Computer -- in-game object
	 *			-- functions to draw, and display information about the object
	 */
	class Computer : public Object
	{
	public:
		// CONSTRUCTORS
		Computer();
		Computer(const Computer&);
        // ACCESSORS
        // MUTATORS
		// METHODS
        void draw() const;
		void help() const;
    private:
    };
	
    ostream& operator << (ostream&, const Computer&);
}
