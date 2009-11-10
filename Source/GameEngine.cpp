/*
 *  GameEngine.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/8/09.
 *
 */
#include "GameEngine.hpp"

namespace Sewers
{
	const int WINDOW_WIDTH = 400;
	const int WINDOW_HEIGHT = 300;
	
	// Object ids
	const int NONE = -1;
	const int PLAYER = 0;
	const int FLOOR = 1;
	const int LADDER = 2;
	const int PANEL = 3;
	const int SWITCH = 4;
	const int DOOR = 5;
	const int INVERTER = 6;
	const int AND = 7;
	const int OR = 8;
	const int CIRCUIT = 9;
	
	// Values for int1 (see draw)
	const int FACING_LEFT = 0;
	const int FACING_RIGHT = 1;
	const int FACING_DOWN = 2;
	const int FACING_UP = 3;
	
	GameEngine::GameEngine()
	{
		_objs.push_back(SewersObject(PLAYER, 0, 15, 0, 30, FACING_RIGHT, false));
	}
	
	void GameEngine::init_glut(int& argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("Computer City:  Sewers");
		// Set the clear color to white
		glClearColor(0.0, 0.0, 0.0, 0.0);
		// Set the size of a drawing point
		glPointSize(1.0);
		//
		glEnable(GL_COLOR_LOGIC_OP);
		//
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void GameEngine::re_display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT); 
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		
		/*
		 objs.draw(PLAYER, 0, 15, 0, 30, facing, animation_frame);
		 objs.draw(FLOOR, 40, 60, 40, 60, NONE, NONE);
		 objs.draw(LADDER, 0, 20, 40, 100, NONE, NONE);
		 objs.draw(PANEL, 40, 60, 70, 90, NONE, NONE);
		 objs.draw(SWITCH, 40, 50, 100, 110, NONE, true);
		 objs.draw(SWITCH, 60, 70, 100, 110, NONE, false);
		 objs.draw(DOOR, 0, 20, 120, 180, NONE, true);
		 objs.draw(DOOR, 0, 20, 180, 240, NONE, false);
		 objs.draw(INVERTER, 40, 60, 120, 140, NONE, NONE);
		 objs.draw(AND, 70, 90, 120, 140, NONE, false);
		 objs.draw(OR, 110, 130, 120, 140, NONE, false);
		 */
		
		
		// Draw things, making sure the priority is as follows:
		// 1) Floor, hallway, and circuit
		/*objs.push_back(SewersObject(FLOOR, 20, 380, 130, 280, NONE, NONE));
		 objs.push_back(SewersObject(FLOOR, 380, 400, 190, 220, NONE, NONE));
		 //		Switch -> Panel
		 objs.push_back(SewersObject(CIRCUIT, 205, 310, 280, 235, 0, NONE));
		 //		Panel -> Door
		 objs.push_back(SewersObject(CIRCUIT, 380, 310, 220, 235, 1, NONE));
		 // 2) Things the player can walk over
		 objs.push_back(SewersObject(LADDER, 0, 20, 190, 250, NONE, NONE));
		 objs.push_back(SewersObject(PANEL, 300, 320, 225, 245, NONE, NONE));
		 objs.push_back(SewersObject(SWITCH, 200, 210, 285, 295, NONE, false));
		 // 3) Player
		 objs.push_back(SewersObject(PLAYER, 25, 40, 190, 220, facing, animation_frame));
		 // 4) Door
		 objs.push_back(SewersObject(DOOR, 380, 400, 190, 250, NONE, false));*/
		
		for(int i=0; i < _objs.size(); ++i)
			_objs[i].draw();
		
		glFlush();
	}
	
	// Keyboard event handler
	void GameEngine::key_click(unsigned char key, int x, int y)
	{
		switch(key)
		{
			case 'a':
				_objs[0].change_int(FACING_LEFT);
				_objs[0].toggle();
				re_display();
				break;
			case 'd':  
				_objs[0].change_int(FACING_RIGHT);
				_objs[0].toggle();
				re_display();
				break;
			case 'w':
				_objs[0].change_int(FACING_UP);
				_objs[0].toggle();
				re_display();
				break;
			case 's':
				_objs[0].change_int(FACING_DOWN);
				_objs[0].toggle();
				re_display();
				break;
		}
	}
	
	bool GameEngine::load_file(string filename)
	{
		ifstream ifs;
		
		ifs.open(filename.c_str());
		if(!ifs)
		{
			cerr << "Sewers exited:  Error loading room file " << filename << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			string object;
			while(ifs >> object)
			{
				if(object == "FLOOR")
				{
					int left, right, bottom, top;
					ifs >> left >> right >> bottom >> top;
					_objs.push_back(SewersObject(FLOOR, left, right, bottom, top, NONE, NONE));
				}
				else if(object == "CIRCUIT")
				{
					int x1, y1, x2, y2, val;
					ifs >> x1 >> y1 >> x2 >> y2 >> val;
					_objs.push_back(SewersObject(CIRCUIT, x1, y1, x2, y2, val, NONE));
				}
				else if(object == "LADDER")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_objs.push_back(SewersObject(LADDER, left, left+20, bottom, bottom+60, NONE, NONE));
				}
				else if(object == "PANEL")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_objs.push_back(SewersObject(PANEL, left, left+20, bottom, bottom+20, NONE, NONE));
				}
				else if(object == "SWITCH")
				{
					int left, bottom, val;
					ifs >> left >> bottom >> val;
					_objs.push_back(SewersObject(SWITCH, left, left+10, bottom, bottom+10, NONE, val));
				}
				else if(object == "DOOR")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_objs.push_back(SewersObject(DOOR, left, left+20, bottom, bottom+60, NONE, false));
				}
				else if(object == "PLAYER")
				{
					int left, bottom;
					string facing;
					int direction;
					ifs >> left >> bottom >> facing;
					cout << facing << endl;
					if(facing == "LEFT")
						direction = FACING_LEFT;
					else if(facing == "RIGHT")
						direction = FACING_RIGHT;
					else if(facing == "DOWN")
						direction = FACING_DOWN;
					else
						direction = FACING_UP;
					_objs[0].set_pos(left, left+30, bottom, bottom+15);
					//_objs[0].change_int(direction);
				}
			}
		}
		return true;
	}
}