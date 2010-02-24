/*
 *
 */
#include "Circuit.hpp"

namespace Sewers
{
	Circuit::Circuit()
	{
	}
	
	void Circuit::connect(Object& input_obj, Object& output_obj)
	{
		_connections.push_back(Connection(input_obj, output_obj));
		output_obj.set_input_val(input_obj.output_val());
	}
	
	void Circuit::draw()
	{
		cerr << "Num connections: " << num_connections() << endl;
		for(size_t i = 0; i < num_connections(); ++i)
		{
			_connections[i].draw();
		}
	}
	
	ostream& operator << ( ostream& outs, const Circuit& c )
	{
		for(size_t i = 0; i < c.num_connections(); ++i)
		{
			outs << c.connections(i) << endl;
		}
		return outs;
	}
}