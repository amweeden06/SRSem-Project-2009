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
#include <fstream>
#include <cassert>
#include <vector>
#include "gltypes.1.h"

using namespace std;
using namespace GLTYPES;

namespace Sewers
{
	/* ERROR HANDLING */
	/* Function returned as expected */
	const int SUCCESS = 0;
	/* An array access was attempted at an out-of-bounds index */
	const int ARRAY_INDEX_OUT_OF_BOUNDS = -1;
	/* Circuit object was expected to have an initialized object value but didn't */
	const int UNINITIALIZED_OUTPUT_VALUE = -2;
	/* A circuit object's input1 is NULL when it shouldn't be */
	const int NULL_INPUT_1 = -3;
	/* A circuit object's input2 is NULL when it shouldn't be */
	const int NULL_INPUT_2 = -4;
	
	/* PRECONDITIONS: None
	 * POSTCONDITIONS:
	 *  - returns name of the error associated with error_value
	 *  - returns "UNCLASSIFIED_ERROR" if error_value is not recognized
	 */
	static string error_string(const int error_value)
	{
		switch (error_value)
		{
			case SUCCESS:
				return "SUCCESS";
				break;
			case ARRAY_INDEX_OUT_OF_BOUNDS:
				return "ARRAY_INDEX_OUT_OF_BOUNDS";
				break;
			case UNINITIALIZED_OUTPUT_VALUE:
				return "UNINITIALIZED_OUTPUT_VALUE";
				break;
			case NULL_INPUT_1:
				return "NULL_INPUT_1";
				break;
			case NULL_INPUT_2:
				return "NULL_INPUT_2";
				break;
			default:
				break;
		}
		return "UNCLASSIFIED_ERROR";
	}	
	
	/* FUNCTION:  check_error
	 * PARAMETERS:
	 *   function is the name of the function being tested
	 *   scenario is a description of the condition being tested
	 *   expected_error is the error value that is expected to be returned by the function
	 *                   in the given scenario.
	 *   actual_error is the actual error value returned by the function.
	 * POSTCONDITION:
	 *   checks if actual_error == expected_error, if not prints an error message to stderr.
	 */
	static void check_error(string function, string scenario, int expected_error, int actual_error)
	{
		if(actual_error != expected_error)
		{
			cerr << endl << "TESTER FOUND ERROR: " << function;
			cerr << " does not return the correct error value" << endl;
			cerr << "for " << scenario << ".  Expected " << error_string(expected_error);
			cerr << " but got " << error_string(actual_error) << "." << endl;
		}
	}	
	
    // Window drawing
    const GLint WINDOW_WIDTH = 1000;
    const GLint WINDOW_HEIGHT = 300;
	const GLint WALL_WIDTH = 20;
    const GLint WALL_HEIGHT = 20;

    /* Drawing colors */
	const GLcolor3 WALL_COLOR = GLblack3;
	const GLcolor3 ZERO_COLOR = GLblue3;
	const GLcolor3 ONE_COLOR = GLgreen3;
	const GLcolor3 FLOOR_COLOR = GLcolor3(0.2,0.2,0.2);
	const GLcolor3 SCREEN_COLOR = GLyellow3;
	
	/* Drawing coordinates */
	const GLint FLOOR_LEFT = 20;
	const GLint FLOOR_BOTTOM = 20;
	const GLint FLOOR_WIDTH = WINDOW_WIDTH - 20;
	const GLint FLOOR_HEIGHT = WINDOW_HEIGHT - 20;
	
    // # of pixels the avatar can move at once
    const GLint MOVE_FACTOR = 5;
}
#endif
