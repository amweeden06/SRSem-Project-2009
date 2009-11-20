/*
 *  GameEngine.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/8/09.
 *
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "gltypes.1.h"
#include "SewersObject.hpp"

using namespace GLTYPES;
using namespace std;

namespace Sewers
{
	class GameEngine
		{
		public:
			GameEngine();
			// Functions
			bool load_file(string filename);		// Load a room from a file
			void init_glut(int& argc, char** argv);	// Initialize drawing
			// GLUT wrappers
			void re_display(void);					// Draw everything in the current room
			void key_click(unsigned char key, int x, int y);
		private:
			vector <SewersObject> _objs;	// All of the objects in the current room
			int _player_index;				// Player is a sort of special object, so we keep its index
											//  into the _objs vector
			int _player_facing;				// Direction the player is currently facing
			bool _animation_frame;			// 2 possible frames of animation
			
			// Returns true if the player is allowed to exist within the given rectangle
			bool check_player_path(GLint factor, int direction);
		};
}


