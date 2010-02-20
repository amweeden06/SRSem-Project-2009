/*
 *  constants.hpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009
 *
 *  Contains the global constants for the game
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include "gltypes.1.h"

using namespace std;
using namespace GLTYPES;

#ifndef SEWERS
#define SEWERS
namespace Sewers
{
	const bool OPEN = true;
	const bool CLOSED = false;

    typedef int GLint;

    // Window drawing
    const GLint WINDOW_WIDTH = 400;
    const GLint WINDOW_HEIGHT = 300;
	const GLint WALL_WIDTH = 20;
    const GLint WALL_HEIGHT = 20;

    // Object colors
	const GLcolor3 WALL_COLOR = GLblack3;
	const GLcolor3 DOOR_COLOR = GLgreen3;
	const GLcolor3 AVATAR_HEAD_COLOR = GLgreen3;
	const GLcolor3 AVATAR_TORSO_COLOR = GLblue3;
	const GLcolor3 AVATAR_EYE_COLOR = GLblack3;
	const GLcolor3 AVATAR_SHOE_COLOR = GLblack3;
	const GLcolor3 ZERO_COLOR = GLblue3;
	const GLcolor3 ONE_COLOR = GLgreen3;
	const GLcolor3 FLOOR_COLOR = GLcolor3(0.2,0.2,0.2);
	const GLcolor3 LADDER_COLOR = GLwhite3;
    const GLcolor3 GATE_COLOR = GLred3;
	const GLcolor3 SCREEN_COLOR = GLyellow3;
	
	// Object coordinates
	const GLint FLOOR_LEFT = 20;
	const GLint FLOOR_BOTTOM = 20;
	const GLint FLOOR_WIDTH = WINDOW_WIDTH - 20;
	const GLint FLOOR_HEIGHT = WINDOW_HEIGHT - 20;
    const GLint PANEL_WIDTH = 20;
    const GLint PANEL_HEIGHT = 20;
	const GLint EXIT_LEFT = WINDOW_WIDTH - WALL_WIDTH;
	const GLint EXIT_BOTTOM = WINDOW_HEIGHT / 2;
	const GLint EXIT_WIDTH = WALL_WIDTH;
    const GLint EXIT_HEIGHT = 60;
	const GLint ENTRANCE_LEFT = 0;
	const GLint ENTRANCE_BOTTOM = EXIT_BOTTOM;
    const GLint ENTRANCE_WIDTH = EXIT_WIDTH;
    const GLint ENTRANCE_HEIGHT = EXIT_HEIGHT;
	const GLint AVATAR_LEFT = FLOOR_LEFT + 5;
	const GLint AVATAR_BOTTOM = ENTRANCE_BOTTOM;
    const GLint AVATAR_WIDTH = 15;
    const GLint AVATAR_HEIGHT = 30;	
    const GLint SWITCH_WIDTH = 40;
    const GLint SWITCH_HEIGHT = 20;
    const GLint SWITCH_BUTTON_WIDTH = 20;
    const GLint SWITCH_BUTTON_HEIGHT = 20;
    const GLint GATE_WIDTH = PANEL_WIDTH;
    const GLint GATE_HEIGHT = PANEL_HEIGHT;
	const GLint BUTTON_WIDTH = GATE_WIDTH;
	const GLint BUTTON_HEIGHT = GATE_HEIGHT;
    const GLint SPACE_BETWEEN_GATES = 10;
    const GLint GATE_BOX_WIDTH = 15;
    const GLint GATE_BOX_HEIGHT = 15;
	const GLint COMPUTER_LEFT = 280;
	const GLint COMPUTER_BOTTOM = 280;
    const GLint COMPUTER_WIDTH = 20;
    const GLint COMPUTER_HEIGHT = 20;
	const GLint BUTTON_SCREEN_LEFT = 0;
	const GLint BUTTON_SCREEN_BOTTOM = 0;
	const GLint BUTTON_SCREEN_WIDTH = BUTTON_WIDTH*2;
	const GLint BUTTON_SCREEN_HEIGHT = BUTTON_HEIGHT*2;
	const GLint COMPUTER_SCREEN_LEFT = 0;
	const GLint COMPUTER_SCREEN_BOTTOM = 0;
	const GLint COMPUTER_SCREEN_WIDTH = COMPUTER_WIDTH*2;
	const GLint COMPUTER_SCREEN_HEIGHT = COMPUTER_HEIGHT*2;

	// Array bounds
	const size_t MAX_NUM_SWITCHES = 10;
	const size_t MAX_NUM_GATES = 20;
	
    // # of pixels the avatar can move at once
    const GLint MOVE_FACTOR = 5;
	
	// The string that begins a line in a room file
	const string LINE_BEGIN = "\\";
}
#endif
