/*
 *  Display.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Display class for the Sewers game
 */
#include "Display.hpp"

const int MOVE_FACTOR = 7;

namespace Sewers
{
	// Constructor
	Display::Display(GLint width, GLint height)
	{
		_main_window = 0;
		_screen_width = width;
		_screen_height = height;
		// Map viewport and world coordinates
		reMap(IntRect(0, _screen_width, 0, _screen_height));
		reFrame(RealRect(0, _screen_width, 0, _screen_height));
		
		// Initialize the gates and gate display
		_gate_display.reMap(IntRect(0, _screen_width/3, 0, _screen_height/6));
		_inverter.reMap(IntRect(3*_screen_width/4, 3*_screen_width/4+20, 3*_screen_height/4, 3*_screen_height/4+20));
		_inverter.hide();
		_and.reMap(IntRect(3*_screen_width/4, 3*_screen_width/4+20, 3*_screen_height/4, 3*_screen_height/4+20));
		_and.hide();
		_or.reMap(IntRect(3*_screen_width/4, 3*_screen_width/4+20, 3*_screen_height/4, 3*_screen_height/4+20));
		_or.hide();
		
		// Initialize the player, panel, and switch
		_player.reMap(IntRect(25,40,_screen_height/2+40,_screen_height/2+70));
		_panel.reMap(IntRect(3*_screen_width/4, 3*_screen_width/4+20, 3*_screen_height/4, 3*_screen_height/4+20));
		_switch.reMap(IntRect(_screen_width/2, _screen_width/2+10, _screen_height - 15, _screen_height - 5));
		
		// Initialize walls
		_left_wall.reMap(IntRect(0, 20, 0, _screen_height));
		_upper_right_wall.reMap(IntRect(_screen_width - 20, _screen_width, _screen_height/2 + 70, _screen_height));
		_lower_right_wall.reMap(IntRect(_screen_width - 20, _screen_width, 0, _screen_height/2 + 40));
		_top_wall.reMap(IntRect(0, _screen_width, _screen_height - 20, _screen_height));
		_bottom_wall.reMap(IntRect(0, _screen_width, _screen_height/2 - 40, _screen_height/2));
		_ladder.reMap(IntRect(0, 20, _screen_height/2+40, _screen_height/2+100));
		_door.reMap(IntRect(_screen_width - 20, _screen_width, _screen_height/2+40, _screen_height/2+100));
	}
	
	// True if the player is standing on the panel
	bool Display::on_panel()
	{
		return ( _player.inside((GLintPoint(_panel.viewport().left(), _panel.viewport().top()))) ||
				 _player.inside((GLintPoint(_panel.viewport().left(), _panel.viewport().bottom()))) ||
				 _player.inside((GLintPoint(_panel.viewport().right(), _panel.viewport().top()))) ||
			 	 _player.inside((GLintPoint(_panel.viewport().right(), _panel.viewport().bottom())))
				);
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
	
	// Redraw the screen
	void Display::re_display(void)
	{
		// Initialize
		glClear(GL_COLOR_BUFFER_BIT);
		initDraw();
		
		// Draw the floor
		(GLcolor3(0.2, 0.2, 0.2)).glColor();
		glRecti(viewport().left(), viewport().bottom(), viewport().right(), viewport().top());
		
		// Draw the circuit
		//   Between switch and gate
		GLblue3.glColor();
		glBegin(GL_LINE_STRIP);
		glVertex2i(_switch.viewport().right() - _switch.v_width()/2, _switch.viewport().bottom());
		glVertex2i(_switch.viewport().right() - _switch.v_width()/2, _panel.viewport().top() - _panel.v_height()/2);
		glVertex2i(_panel.viewport().left() + _panel.v_width()/2, _panel.viewport().top() - _panel.v_height()/2);
		glEnd();
		//   Between gate and door
		if(_door.is_open())
			GLgreen3.glColor();
		else
			GLblue3.glColor();
		glBegin(GL_LINE_STRIP);
		glVertex2i(_panel.viewport().left() + _panel.v_width()/2, _panel.viewport().top() - _panel.v_height()/2);
		glVertex2i(_upper_right_wall.viewport().left()-1, _panel.viewport().top() - _panel.v_height()/2);
		glVertex2i(_upper_right_wall.viewport().left()-1, _door.viewport().top() - _door.v_height()/2);
		glEnd();		
		
		// Draw walls
		_left_wall.re_display();
		_upper_right_wall.re_display();
		_lower_right_wall.re_display();
		_top_wall.re_display();
		_bottom_wall.re_display();
		_ladder.re_display();
		_switch.re_display();
		_panel.re_display();
		_inverter.re_display();
		_and.re_display();
		_or.re_display();
		_player.re_display();
		_door.re_display(); // Door has to be drawn on top of player to give illusion of walking through the door.
		
		// Draw gate screen if player is on the panel
		if(on_panel())
		{
			_gate_display.re_display();
		}
		
		// Flush the display
		glFlush();
	}
	
	// Keyboard event handler
	void Display::key_click(unsigned char key, int x, int y)
	{
		switch(key)
		{
			case 'a':
				if( (_player.viewport().left() - MOVE_FACTOR ) >= _left_wall.viewport().right() )
					_player.move_left(MOVE_FACTOR);
				else
					_player.move_left(0);
				re_display();
				break;
			case 'd':  
				if( ( ( _door.is_open() ) && ( _player.viewport().bottom() + MOVE_FACTOR < _upper_right_wall.viewport().bottom()) && ( _player.viewport().bottom() > _door.viewport().bottom() - MOVE_FACTOR ) )
				   ||( ( _player.viewport().right() + MOVE_FACTOR ) < _upper_right_wall.viewport().left() ) )
					_player.move_right(MOVE_FACTOR);
				else
					_player.move_right(0);
				re_display();
				break;
			case 'w':
				if( ( ( _player.viewport().bottom() < _upper_right_wall.viewport().bottom() - 10 ) && ( viewport().right() > _upper_right_wall.viewport().left() ) )
				   ||( !( _player.viewport().right() > _upper_right_wall.viewport().left() ) && ( _player.viewport().top() + MOVE_FACTOR ) < _screen_height ) )
					_player.move_up(MOVE_FACTOR);
				else
					_player.move_up(0);
				re_display();
				break;
			case 's':
				if( ( ( _player.viewport().bottom() > _lower_right_wall.viewport().top() ) && ( _player.viewport().right() > _upper_right_wall.viewport().left() ) )
				   ||( !(_player.viewport().right() > _upper_right_wall.viewport().left()) && ( _player.viewport().bottom() - MOVE_FACTOR ) >= _bottom_wall.viewport().top()) )
					_player.move_down(MOVE_FACTOR);
				else
					_player.move_down(0);
				re_display();
				break;
		}
	}

	// Mouse event handler
	void Display::mouse_click(int button, int state, int x, int y)
	{
		if( on_panel() )
		{
			if( _gate_display.inverter().inside( GLintPoint(x,y) ) )
			{
				_inverter.show();
				_gate_display.hide_inverter();
				_and.hide();
				_gate_display.show_AND();
				_or.hide();
				_gate_display.show_OR();
				_door.open();
				re_display();
			}
			else if( _gate_display.And().inside( GLintPoint(x,y) ) )
			{
				_inverter.hide();
				_gate_display.show_inverter();
				_and.show();
				_gate_display.hide_AND();
				_or.hide();
				_gate_display.show_OR();
				_door.close();
				re_display();
			}
			else if( _gate_display.Or().inside( GLintPoint(x,y) ) )
			{
				_inverter.hide();
				_gate_display.show_inverter();
				_and.hide();
				_gate_display.show_AND();
				_or.show();
				_gate_display.hide_OR();
				_door.close();
				re_display();
			}
			else if( _panel.inside( GLintPoint(x,y) ) )
			{
				_inverter.hide();
				_gate_display.show_inverter();
				_and.hide();
				_gate_display.show_AND();
				_or.hide();
				_gate_display.show_OR();
				_door.close();
				re_display();
			}
		}
	}
}