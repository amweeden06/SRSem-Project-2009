/*
 *  OR.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/2/09.
 *
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class OR : public Component
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


