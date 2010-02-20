/*  CircuitObject.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Object.hpp"

#ifndef CIRCOBJGUARD
#define CIRCOBJGUARD

namespace Sewers
{
	/* CircuitObject -- Object to be connected in a circuit
	 *               -- 2 possible inputs and 1 possible output
	 *               -- Function to draw
	 * Types:
	 *		Switch	 -- 0 inputs, 1 output
	 *				 -- Value of 0 or 1
	 *				 -- Contains an optional button, which allows the user to
	 *                   change the switch's value
	 *      NOT -- 1 input, 1 output
	 *               -- Value is logical negation of input's value
	 *                   so 0 becomes 1, and vice versa
	 *      AND	gate -- 2 inputs, 1 output
	 *				 -- Value is logical conjunction of inputs' values
	 *                   so if any of the input values are 0, the gate's value is 0,
	 *                   otherwise the gate's value is 1
	 *      OR gate	 -- 2 inputs, 1 output
	 *               -- Value is logical disjunction of inputs' values
	 *                   so if any of the input values are 1, the gate's value is 1,
	 *                   otherwise the gate's value is 0
	 *      Exit     -- 1 input, 0 outputs
	 *               -- Door is open if and only input is 1
	 */
	class CircuitObject : public Object
	{
	public:
		// CONSTRUCTORS
		CircuitObject(const string type = "");
		CircuitObject(const CircuitObject&);
        // ACCESSORS
		CircuitObject* input1() const { return _input1; }
		CircuitObject* input2() const { return _input2; }
		CircuitObject* output() const { return _output; }
		int output_value() const;
		bool has_button() const { return _has_button; }
		bool is_open() const { return (input1()->output_value() == 1); }
        // MUTATORS
		void set_input1(CircuitObject* i1) { _input1 = i1; }
		void set_input2(CircuitObject* i2) { _input2 = i2; }
		void set_output(CircuitObject* o) { _output = o; }
		void set_output_value(const int v) { _output_value = v; }
		void give_button() { _has_button = true; }
        // METHODS
        void draw() const;
    private:
		CircuitObject* _input1;
		CircuitObject* _input2;
		CircuitObject* _output;
		int _output_value;
		bool _has_button;
	};
	
    ostream& operator << (ostream&, const CircuitObject&);
}

#endif
