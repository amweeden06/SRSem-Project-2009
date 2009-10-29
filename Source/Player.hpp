/*
 *  Player.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Graphical player object.  Represents the player's avatar.
 */
#include "component.h"

using namespace GLTYPES;

namespace Sewers
{
	class Player : public Component
		{
		public:
			// Movement
			void move_left(), move_right(), move_down(), move_up();
			// Color Mutators
			void set_skin_color(GLcolor3 c)  { _skin_color  = c; }
			void set_shirt_color(GLcolor3 c) { _shirt_color = c; }
			void set_shoe_color(GLcolor3 c)  { _shoe_color = c;  }
			// Functions for GLUT
			void re_display(void);
		private:
			GLcolor3 _skin_color, _shirt_color, _shoe_color;
			bool _facing_left, _facing_right, _facing_up, _facing_down;
			bool _animation_frame; // simply toggles between frames when walking
			void draw_head(), draw_torso(), draw_arms(), draw_feet();  // Drawing functions
		};
}


