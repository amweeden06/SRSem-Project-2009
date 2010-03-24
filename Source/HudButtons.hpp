/*
 *  HudButtons.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 3/23/10.
 *  Copyright 2010 Earlham College. All rights reserved.
 *
 */
#include "DrawingObject.hpp"

namespace Sewers
{
	class HudButtons : public DrawingObject
	{
	public:
		DrawingObject quit_button() const { return _quit_button; }
		void set_button(DrawingObject b) { _quit_button = b; }
		void draw() const;
	private:
		DrawingObject _quit_button;
	};
}