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
			bool touching_object(SewersObject obj); // Check for collision (walking over object)
			bool touching_table();					// Check for collision (next to object)
			bool check_player_path(int direction);  // Check if player can move in a direction
			void hide_gate();						// Swap gate off of main screen
			void get_gates_from_box();				// Transfer gates to player's inventory
			bool connected(SewersObject circuit, SewersObject source);
			void update_circuit();
			
			// GLUT wrappers
			void re_display(void);					// Draw everything in the current room
			void key_click(unsigned char key, int x, int y);
			void mouse_click(int button, int state, int x, int y);
		private:
			SewersObject _player;					// The player object
			SewersObject _table;					// A truth table
			SewersObject _ladder;					// A ladder
			SewersObject _table_screen;				// The table screen, shows a truth table
			SewersObject _button_screen;			// Shows a button to click
			SewersObject _gate_box;					// A box of gates for the player to pick up
			vector <SewersObject> _doors;			// Each of the doors
			vector <SewersObject> _floors;			// Each of the floors
			vector <SewersObject> _panels;			// Each of the panels
			vector <SewersObject> _switches;		// Each of the switches
			vector <SewersObject> _switch_buttons;	// Each of the buttons to control the switches
			vector <SewersObject> _circuits;		// Each of the circuits
			vector <SewersObject> _inverters;		// Each of the inverters
			vector <SewersObject> _ands;			// Each of the AND gates
			vector <SewersObject> _ors;				// Each of the OR gates
			int _player_facing;						// Direction the player is currently facing
			bool _animation_frame;					// 2 possible frames of animation
			vector <SewersObject> _gates_in_hand;	// The gates the player owns and their display screen
			vector <SewersObject> _gates_in_box;	// The gates a player can pick up via the box
		};
}


