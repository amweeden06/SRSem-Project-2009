/*
 *
 */
#include "Connection.hpp"

namespace Sewers
{
	class Circuit
		{
		public:
			// CONSTRUCTOR
			Circuit();
			// ACCESSORS
			size_t num_connections() const { return _connections.size(); }
			Connection connections(size_t index) const { return _connections[index]; }
			// METHODS
			void connect(Object& input_obj, Object& output_obj);
			void draw();
		private:
			vector<Connection> _connections;
		};
	
	ostream& operator << ( ostream& outs, const Circuit& c );
}