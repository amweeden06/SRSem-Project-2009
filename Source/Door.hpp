/*
 *  Door.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/29/09.
 *
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class Door : public Component
		{
		public:
			// Mutators
			void open()  { _is_open = true; }
			void close() { _is_open = false; }
			// Accessors
			bool is_open() const { return _is_open; }
			// Functions for GLUT
			void re_display(void);
		private:
			bool _is_open;
		};
}


