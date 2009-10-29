/*
 *  Display.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Display class for the Sewers game
 */
#include "Display.hpp"

namespace Sewers
{
	// Constructor
	Display::Display(GLint width, GLint height)
	{
		_main_window = 0;
		_screen_width = width;
		_screen_height = height;
		reMap(IntRect(0, _screen_width, 0, _screen_height));
		// Initialize the player and panel
		_player.reMap(IntRect(0,15,0,30));
		_panel.reMap(IntRect(500, 520, 460, 480));
		_menu.reMap(IntRect(0,640,440,480));
	}

	// Set up glut with display mode, window size and position, coloration, and drawing point size
	void Display::init_glut(int& argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(_screen_width, _screen_height);
		glutInitWindowPosition(0, 0);
		_main_window = glutCreateWindow("Computer City:  Sewers");
		// Set the clear color to white
		glClearColor(1.0, 1.0, 1.0, 0.0);
		// Set the size of a drawing point
		glPointSize(1.0);
		//
		glEnable(GL_COLOR_LOGIC_OP);
		//
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Display::init_GLUI()
	{
		_glui = GLUI_Master.create_glui((char*)"GLUI");
	}
	
	// Redraw the screen
	void Display::re_display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		initDraw();
		(GLcolor3(0.2, 0.2, 0.2)).glColor();
		glRectf(viewport().left(), viewport().bottom(), viewport().right(), viewport().top());
		
		_panel.re_display();
		_menu.re_display();
		_player.re_display();
		
		// Flush the display
		glFlush();
	}
	
	// Keyboard event handler
	void Display::key_click(unsigned char key, int x, int y)
	{
		switch(key)
		{
			case 'a':  _player.move_left();  re_display();  break;
			case 'd':  _player.move_right(); re_display();  break;
			case 'w':  _player.move_up();    re_display();  break;
			case 's':  _player.move_down();  re_display();  break;
		}
	}

}