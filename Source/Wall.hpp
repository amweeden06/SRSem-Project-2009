/*
 *  Wall.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Graphical wall object.  Can optionally be a control panel or door.
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class Wall : public Component
		{
		public:
			// Accessors
			GLcolor3 color() const { return _color; }
			// Mutators
			void set_color(GLcolor3 c) { _color = c; }
			// Functions for GLUT
			void re_display(void);
		private:
			bool _is_panel, _is_door;
			GLcolor3 _color;
		};
}