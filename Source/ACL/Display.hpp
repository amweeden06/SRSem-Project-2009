/*
 *  Display.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Display class for the Sewers game
 */
#include <GL/glut.h>
#include <GL/gl.h>
#include "glui.h"
#include "Player.hpp"
#include "Wall.hpp"
#include "MenuBar.hpp"

namespace Sewers
{
	class Display : public Component
	{
	public:
		// Constructor
		Display(GLint width, GLint height);
		// Accessors
		GLint main_window()   const { return _main_window;  }
		GLint screen_width()  const { return _screen_width; }
		GLint screen_height() const { return _screen_width; }
		// Drawing methods
		void init_glut(int& argc, char** argv);  // Initialize the display window for drawing
		void init_GLUI(); // Initialize the GLUI
		// Functions to be wrapped by GLUT wrappers
		void re_display(void);  // Redraw everything in the display window
		void key_click(unsigned char key, int x, int y);
	private:
		GLint _main_window; // glut ID of main window
		GLUI* _glui;
		GLint _screen_width; // width of the program's screen, in pixels
		GLint _screen_height; // height of the program's screen, in pixels
		Player _player; // Graphical player object
		Wall _panel; // Graphical control panel object
		MenuBar _menu; // Menu that appears at the top of the screen
	};
}
