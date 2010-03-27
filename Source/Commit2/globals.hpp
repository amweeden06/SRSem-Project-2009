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
	
	const int MAX_NUM_GATE_INPUTS = 2;
	const int MAX_NUM_HORIZONTAL_BLUEPRINT_GATES = 5;
	const int MAX_NUM_VERTICAL_BLUEPRINT_GATES = 4;
	const int MAX_NUM_BLUEPRINT_GATES = MAX_NUM_HORIZONTAL_BLUEPRINT_GATES * MAX_NUM_VERTICAL_BLUEPRINT_GATES;
	const int MAX_NUM_BLUEPRINT_CONNECTIONS = MAX_NUM_BLUEPRINT_GATES * 2;
}
#endif
