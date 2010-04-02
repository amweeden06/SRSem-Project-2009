/*  Connection.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{	
	class Connection : public DrawingObject
	{
	public:
		/* CONSTRUCTOR */
		Connection();
		/* ACCESSOR */
		DrawingObject* input() const { return _input; }
		DrawingObject* output() const { return _output; }
		/* MUTATOR */
		void set_input(DrawingObject* p) { _input = p; }
		void set_output(DrawingObject* p) { _output = p; }
		/* FUNCTIONS */
        int draw() const;
	private:
		DrawingObject* _input;
		DrawingObject* _output;
    };
}