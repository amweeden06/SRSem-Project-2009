#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include "Display.hpp"

using namespace std;
using namespace Sewers;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Display display(WINDOW_WIDTH, WINDOW_HEIGHT);

// GLUT wrappers
void wrap_display(void) { display.re_display(); }
void wrap_key(unsigned char k, int x, int y)     { display.key_click(k, x, display.screen_height()-y);  }

int main (int argc, char ** argv)
{
	// Initialize display and GLUI
	display.init_glut(argc, argv);
	
	// Set GLUT callbacks
	glutDisplayFunc(wrap_display);
	glutKeyboardFunc(wrap_key);
	
	// Enter the GLUT main loop
	glutMainLoop();
}
