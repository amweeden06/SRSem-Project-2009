/*
 *  Inverter.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/29/09.
 *
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class Inverter : public Component
		{
		public:
			// Mutators
			void hide() { _invisible = true; }
			void show() { _invisible = false; }
			// Functions for GLUT
			void re_display(void);
		private:
			bool _invisible;
		};
}


