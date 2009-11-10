/*
 *  Panel.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Panel that appears on the floor.  The player can place a gate on the panel.
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class Panel : public Component
		{
		public:
			// Functions for GLUT
			void re_display(void);
		private:
		};
}