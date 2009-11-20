/*
 *  ObjectDriver.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/6/09.
 *
 */
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "GameEngine.hpp"

using namespace std;
using namespace Sewers;

GameEngine g;

// GLUT wrappers
void wrap_display(void) { g.re_display(); }
void wrap_key(unsigned char k, int x, int y) { g.key_click(k, x, y); }
void wrap_mouse(int b, int state, int x, int y);

int main (int argc, char ** argv)
{
	g.load_file("Room1.sew");
	// Initialize display and GLUI
	g.init_glut(argc, argv);
	
	// Set GLUT callbacks
	glutDisplayFunc(wrap_display);
	glutKeyboardFunc(wrap_key);
	//glutMouseFunc(wrap_mouse);
	
	// Enter the GLUT main loop
	glutMainLoop();
}
