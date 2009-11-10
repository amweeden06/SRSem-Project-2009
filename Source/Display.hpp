/*
 *  Display.hpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Display class for the Sewers game
 */
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include "Player.hpp"
#include "Wall.hpp"
#include "Panel.hpp"
#include "Ladder.hpp"
#include "Door.hpp"
#include "Switch.hpp"
#include "GateDisplay.hpp"

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
		bool on_panel(); // True if the player is standing on the panel
		// Drawing methods
		void init_glut(int& argc, char** argv);  // Initialize the display window for drawing
		// Functions to be wrapped by GLUT wrappers
		void re_display(void);  // Redraw everything in the display window
		void key_click(unsigned char key, int x, int y);
		void mouse_click(int button, int state, int x, int y);
	private:
		GLint _main_window; // glut ID of main window
		GLint _screen_width; // width of the program's screen, in pixels
		GLint _screen_height; // height of the program's screen, in pixels
		Player _player; // Graphical player object
		Panel _panel; // Graphical control panel object
		Wall _left_wall, _upper_right_wall, _lower_right_wall, _top_wall, _bottom_wall;
		Ladder _ladder;
		Door _door;
		Switch _switch;
		GateDisplay _gate_display; // Gate display screen, appears when the player is on the panel
		Inverter _inverter;
		AND _and;
		OR _or;
	};
}