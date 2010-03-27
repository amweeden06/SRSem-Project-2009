/*  Switch.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "CircuitObject.hpp"

namespace Sewers
{
	/* Switch -- Object to be connected in a circuit
	 *        -- Value is either 0 or 1
	 *        -- Function to draw
	 */
	class Switch : public CircuitObject
	{
	public:
		// CONSTRUCTORS
		Switch(int output_value = 0);
		Switch(const Switch&);
        // ACCESSORS
		CircuitObject output () const { return _output; }
		bool has_button() const { return _has_button; }
		int output_value() const { return _output_value; }
        // MUTATORS
		void set_output(const CircuitObject o) { _output = o; }
		void give_button() { _has_button = true; }
		void set_output_value(const int v) { _output_value = v; }
        // METHODS
        void draw() const;
    private:
		CircuitObject _output;
		bool _has_button;
		int _output_value;
    };
	
    ostream& operator << (ostream&, const Switch&);
}
