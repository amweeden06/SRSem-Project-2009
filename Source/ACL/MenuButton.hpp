/*
 *  MenuButton.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/27/09.
 *
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class MenuButton : public Component
		{
		public:
			// Mutators
			void set_color(GLcolor3 c) { _color = c; }
			// Functions for GLUT
			void re_display(void);
		private:
			GLcolor3 _color; // The background color of the button
		};
}