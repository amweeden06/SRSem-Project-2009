/*
 *  globals.hpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009
 *
 *  Contains the global constants for the game
 */
#ifndef GLOBALS
#define GLOBALS

#include <iostream>
#include "gltypes.1.h"

using namespace std;
using namespace GLTYPES;

namespace Sewers
{
	/* ERROR VALUES */
	const int SUCCESS = 0;
	const int FULL_ARRAY = -1;
	const int INDEX_OUT_OF_BOUNDS = -2;
	
	const int MAX_NUM_GATE_INPUTS = 2;
	const int MAX_NUM_TT_ROWS = 4; // This should be pow(2,MAX_NUM_GATE_INPUTS), but can't use pow in a constant expression
	const int MAX_NUM_HORIZONTAL_BLUEPRINT_GATES = 5;
	const int MAX_NUM_VERTICAL_BLUEPRINT_GATES = 4;
	const int MAX_NUM_BLUEPRINT_GATES = MAX_NUM_HORIZONTAL_BLUEPRINT_GATES * MAX_NUM_VERTICAL_BLUEPRINT_GATES;
	const int MAX_NUM_BLUEPRINT_CONNECTIONS = MAX_NUM_BLUEPRINT_GATES * 2;
	const int NUM_PUZZLES = 6;
	const int PUZZLES_PER_ROOM = 3;
	const int NUM_BUTTONS = 4; // stats, save, load, and quit
	
	/* DRAWING COORDINATES */
	const GLint WALL_WIDTH = 20;
	const GLint WALL_HEIGHT = WALL_WIDTH;
	const GLint HUD_BORDER_WIDTH = 10;
	const GLint HUD_BORDER_HEIGHT = HUD_BORDER_WIDTH;
	const GLint AVATAR_WIDTH = 15;
	const GLint AVATAR_HEIGHT = 2 * AVATAR_WIDTH;
	const GLint BUTTON_WIDTH = (AVATAR_WIDTH > AVATAR_HEIGHT
								? AVATAR_WIDTH
								: AVATAR_HEIGHT);
	const GLint BUTTON_HEIGHT = BUTTON_WIDTH;
	const GLint HUD_BUTTONS_WIDTH = (BUTTON_WIDTH * 2) * NUM_BUTTONS;
	const GLint HUD_BUTTONS_HEIGHT = BUTTON_HEIGHT;	
	const GLint CONNECTION_WIDTH = 10;
	const GLint CONNECTION_HEIGHT = CONNECTION_WIDTH;
	const GLint BIT_WIDTH = 10;
	const GLint BIT_HEIGHT = BIT_WIDTH;
	const GLint SWITCH_WIDTH = 10;
	const GLint SWITCH_HEIGHT = SWITCH_WIDTH;
	const GLint MAX_ROW_HEIGHT = (2 * (BIT_WIDTH > SWITCH_WIDTH ? BIT_WIDTH : SWITCH_WIDTH));
	const GLint MAX_ROW_WIDTH = MAX_ROW_HEIGHT * (MAX_NUM_GATE_INPUTS + 1);
	const GLint MAX_TRUTH_TABLE_WIDTH = MAX_ROW_WIDTH;
	const GLint MAX_TRUTH_TABLE_HEIGHT = MAX_ROW_HEIGHT * (MAX_NUM_TT_ROWS + 1);
	const GLint GATE_WIDTH = 20;
	const GLint GATE_HEIGHT = GATE_WIDTH;
	const GLint WORKBENCH_WIDTH = GATE_WIDTH * 2;
	const GLint WORKBENCH_HEIGHT = GATE_HEIGHT * 2;
	const GLint PUZZLE_WIDTH = (GATE_WIDTH * 3 > AVATAR_WIDTH ? GATE_WIDTH * 3 : AVATAR_WIDTH);
	const GLint PUZZLE_HEIGHT = (AVATAR_HEIGHT * 2 > GATE_HEIGHT ? AVATAR_HEIGHT * 2 : GATE_HEIGHT);
	const GLint MAX_BLUEPRINT_SCREEN_WIDTH = 2 * GATE_WIDTH * MAX_NUM_HORIZONTAL_BLUEPRINT_GATES;
	const GLint MAX_BLUEPRINT_SCREEN_HEIGHT = 2 * GATE_HEIGHT * MAX_NUM_VERTICAL_BLUEPRINT_GATES;
	const GLint MAX_HUD_PUZZLE_WIDTH = 2 * GATE_WIDTH + 2 * MAX_TRUTH_TABLE_WIDTH;
	const GLint MAX_HUD_PUZZLE_HEIGHT = (MAX_TRUTH_TABLE_HEIGHT > GATE_HEIGHT 
										 ? MAX_TRUTH_TABLE_HEIGHT : GATE_HEIGHT);
	const GLint MAX_HUD_WIDTH = HUD_BUTTONS_WIDTH + MAX_HUD_PUZZLE_WIDTH + 2 * HUD_BORDER_WIDTH;
	const GLint MAX_HUD_HEIGHT = HUD_BUTTONS_HEIGHT + MAX_HUD_PUZZLE_HEIGHT + 2 * HUD_BORDER_HEIGHT;
	const GLint WINDOW_HEIGHT = MAX_BLUEPRINT_SCREEN_HEIGHT + MAX_HUD_HEIGHT;
	const GLint WINDOW_WIDTH = ((MAX_BLUEPRINT_SCREEN_WIDTH > MAX_HUD_WIDTH)
								? MAX_BLUEPRINT_SCREEN_WIDTH
								: MAX_HUD_WIDTH);
}
#endif
