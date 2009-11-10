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
			bool load_file(string filename);
			void init_glut(int& argc, char** argv);
			void re_display(void);
			void key_click(unsigned char key, int x, int y);
		private:
			vector <SewersObject> _objs;
			int _player_facing;
			bool _animation_frame;
		};
}


