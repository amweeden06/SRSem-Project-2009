/*
 *  Circuit.hpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009
 *
 *  A circuit object, which contains objects and the wires that connect them
 *
 */
/*
#include "SewersObject.hpp"

using namespace GLTYPES;
using namespace std;

namespace SewersOld
{
	class Circuit
		{
		public:
			Circuit();
			// Accessors
			int switch_charge() const { return _objects[0].int1(); }
			SewersObject last_obj() const { return _objects.back(); }
			// Mutators
			void set_switch_charge(int charge);
			// Member Functions
			int invert_charge(int charge);
			int andify_charge(int charge);
			// Draw everything
			void draw();
			void connect(SewersObject obj1, SewersObject obj2);
			void add_object(SewersObject obj);
			void update(size_t pos, int charge);
		private:
			// Objects and the wires that connect them
			vector<SewersObject> _objects;
		};
}
*/