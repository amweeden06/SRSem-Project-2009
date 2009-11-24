/*
 *  constants.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/21/09.
 *
 *  Contains the global constants for the game
 */

namespace Sewers
{
	// Object ids
	const int NONE = -1;
	const int PLAYER = 0;
	const int DOOR = 1;
	const int LADDER = 2;
	const int PANEL = 3;
	const int SWITCH = 4;
	const int FLOOR = 5;
	const int INVERTER = 6;
	const int AND = 7;
	const int OR = 8;
	const int CIRCUIT = 9;
	const int TABLE = 10;
	const int GATE_DISPLAY = 11;
	const int TABLE_DISPLAY = 12;
	const int GATE_BOX = 13;
	const int SWITCH_BUTTON = 14;
	const int BUTTON_DISPLAY = 15;
	
	// Values for int1 (see draw_object)
	const int LEFT = 0;
	const int RIGHT = 1;
	const int DOWN = 2;
	const int UP = 3;	
	
	// Values for bool1 (see draw_object
	const bool VISIBLE = true;
	
	// Window drawing
	const GLint WINDOW_WIDTH = 400;
	const GLint WINDOW_HEIGHT = 300;
	
	// Object drawing
	const GLint PLAYER_WIDTH = 15;
	const GLint PLAYER_HEIGHT = 30;
	const GLint PANEL_WIDTH = 20;
	const GLint PANEL_HEIGHT = 20;
	const GLint TABLE_WIDTH = 40;
	const GLint TABLE_HEIGHT = 25;
	const GLint DOOR_WIDTH = 20;
	const GLint DOOR_HEIGHT = 60;
	const GLint LADDER_WIDTH = DOOR_WIDTH;
	const GLint LADDER_HEIGHT = DOOR_HEIGHT;
	const GLint SWITCH_WIDTH = 10;
	const GLint SWITCH_HEIGHT = 10;
	const GLint SWITCH_BUTTON_WIDTH = 20;
	const GLint SWITCH_BUTTON_HEIGHT = 20;
	const GLint GATE_WIDTH = PANEL_WIDTH;
	const GLint GATE_HEIGHT = PANEL_HEIGHT;
	const GLint SPACE_BETWEEN_GATES = 10;
	const GLint GATE_BOX_WIDTH = 15;
	const GLint GATE_BOX_HEIGHT = 15;
	
	// # of pixels the player can move at once
	const GLint MOVE_FACTOR = 7;
	
}