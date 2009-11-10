/*#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>
#include "Display.hpp"

using namespace std;
using namespace Sewers;

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 300;

Display display(WINDOW_WIDTH, WINDOW_HEIGHT);

// GLUT wrappers
void wrap_display(void) { display.re_display(); }
void wrap_key(unsigned char k, int x, int y)    { display.key_click(k, x, WINDOW_HEIGHT-y); }
void wrap_mouse(int b, int state, int x, int y)	{ display.mouse_click(b, state, x, WINDOW_HEIGHT-y); }

int main (int argc, char ** argv)
{
	// Initialize display and GLUI
	display.init_glut(argc, argv);
	
	// Set GLUT callbacks
	glutDisplayFunc(wrap_display);
	glutKeyboardFunc(wrap_key);
	glutMouseFunc(wrap_mouse);
	
	// Enter the GLUT main loop
	glutMainLoop();
}
*/