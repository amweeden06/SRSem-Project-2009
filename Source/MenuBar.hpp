/*
 *  MenuBar.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/27/09.
 *
 */
#include "component.h"
#include "MenuButton.hpp"

using namespace GLTYPES;

namespace Sewers
{
	class MenuBar : public Component
	{
	public:
		// Functions for GLUT
		void re_display(void);
	private:
		MenuButton _new, _save, _load, _quit;
		GLcolor3 _color;
	};
}