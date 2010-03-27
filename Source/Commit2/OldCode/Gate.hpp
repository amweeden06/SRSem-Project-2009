/*  Gate.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "CircuitObject.hpp"

namespace Sewers
{
	/* Gate   -- Object to be connected in a circuit
	 *        -- Has multiple inputs and a single output
	 *        -- Output is determined based on the type of the gate
	 *            and the inputs
	 *        -- Functions to draw and determine output
	 */
	class Gate : public CircuitObject
	{
	public:
		// CONSTRUCTORS
		Gate(string type = "GATE");
		Gate(const Gate&);
        // ACCESSORS
		CircuitObject inputs(const size_t i) const { return _inputs[i]; }
		size_t expected_num_inputs() const { return _expected_num_inputs; }
		size_t num_inputs() const { return _inputs.size(); }
		bool needs_input() const { return (expected_num_inputs() != num_inputs()); }
		CircuitObject output() const { return _output; }
		int output_value(const vector<int>) const;
        // MUTATORS
		void add_input(const CircuitObject);
		void update_input(const CircuitObject);
		void set_expected_num_inputs(size_t n) { _expected_num_inputs = n; }
		void set_output(const CircuitObject o) { _output = o; }
        // METHODS
        void draw() const;
    private:
		vector<CircuitObject> _inputs;
		size_t _expected_num_inputs;
		CircuitObject _output;
    };
	
    ostream& operator << (ostream&, const Gate&);
}
