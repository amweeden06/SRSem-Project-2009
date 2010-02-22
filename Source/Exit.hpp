/*  Exit.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "CircuitObject.hpp"

namespace Sewers
{
	/* Exit   -- Object to be connected in a circuit
	 *        -- Has a single input and no output
	 *        -- If input is 1, door is open
	 *        -- Functions to draw
	 */
	class Exit : public CircuitObject
	{
	public:
		// CONSTRUCTORS
		Exit();
		Exit(const Exit&);
        // ACCESSORS
		CircuitObject input() const { return _input; }
		bool is_open() const { return _is_open; }
		bool needs_input() const { return (_input.type() == ""); }
        // MUTATORS
		void add_input(const CircuitObject input) { _input = input; }
		void open() { _is_open = true; }
		void close() { _is_open = false; }
        // METHODS
        void draw() const;
    private:
		CircuitObject _input;
		bool _is_open;
    };
	
    ostream& operator << (ostream&, const Exit&);
}
