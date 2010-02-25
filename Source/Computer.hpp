/*  Computer.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "CircuitObject.hpp"

namespace Sewers
{
	/* Computer -- in-game object
	 *          -- turns on if the room's exit is open
	 *          -- allows the player to enter a truth table
	 */
	class Computer : public Object
	{
	public:
		// CONSTRUCTORS
		Computer();
		Computer(const Computer&);
        // ACCESSORS
		CircuitObject* exit() const { return _exit; }
		bool is_on() const { return _exit->is_open(); }
        // MUTATORS
        void set_exit(CircuitObject* e) { _exit = e; }
		// METHODS
        void draw() const;
		void help() const;
    private:
        CircuitObject* _exit;
    };
	
    ostream& operator << (ostream&, const Computer&);
}
