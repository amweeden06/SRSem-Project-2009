/*
 *  Switch.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Switch that appears on the floor.  Represents a 0 or 1.
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class Switch : public Component
		{
		public:
			// Mutators
			void set(bool val) { _is_1 = val; }
			// Accessors
			bool is_1() const { return _is_1; }
			// Functions for GLUT
			void re_display(void);
		private:
			bool _is_1; // Switch is 0 or 1
		};
}