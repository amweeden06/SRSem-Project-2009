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
	GameEngine::GameEngine()
	{
		_gates_in_box.push_back(SewersObject(GATE_DISPLAY, 0, 10, 0, WINDOW_HEIGHT/6, NONE, NONE));
		_gates_in_hand.push_back(SewersObject(GATE_DISPLAY, 0, 10, 0, WINDOW_HEIGHT/6, NONE, NONE));
		_table_screen = SewersObject(TABLE_DISPLAY, 3*WINDOW_WIDTH / 5, WINDOW_WIDTH, 0, WINDOW_HEIGHT/2, NONE, NONE);
		_button_screen = SewersObject(BUTTON_DISPLAY, 0, WINDOW_WIDTH/6, 0, WINDOW_HEIGHT/6, NONE, NONE);
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
		
		// Order matters here for drawing
		
		// Floors
		for(int i=0; i < _floors.size(); ++i)
			_floors[i].draw();
		
		// Circuits
		for(int i=0; i < _circuits.size(); ++i)
			_circuits[i].draw();
		
		// Switches
		for(int i=0; i < _switches.size(); ++i)
			_switches[i].draw();
		
		// Switch buttons
		for(int i=0; i < _switch_buttons.size(); ++i)
			_switch_buttons[i].draw();
		
		// Panels
		for(int i=0; i < _panels.size(); ++i)
			_panels[i].draw();
		
		// Gates
		for(int i=0; i < _inverters.size(); ++i)
			_inverters[i].draw();
		for(int i=0; i < _ands.size(); ++i)
			_ands[i].draw();
		for(int i=0; i < _ors.size(); ++i)
			_ors[i].draw();
		
		// Ladder
		_ladder.draw();
		
		// Table
		_table.draw();
		
		// Gate box
		_gate_box.draw();
		
		// Player
		_player.draw();
		
		// Doors
		for(int i=0; i < _doors.size(); ++i)
			_doors[i].draw();
		
		// Gate screen, if needed
		for(int i=0; i<_panels.size(); ++i)
			if(touching_object(_panels[i]))
				for(int i=0; i < _gates_in_hand.size(); ++i)
					_gates_in_hand[i].draw();
		
		// Table screen, if needed
		if(touching_table())
			_table_screen.draw();
		
		// Button screen if needed
		for(int i=0; i<_switch_buttons.size(); ++i)
			if(touching_object(_switch_buttons[i]))
				_button_screen.draw();
				
		glFlush();
	}
	
	// Keyboard event handler
	void GameEngine::key_click(unsigned char key, int x, int y)
	{
		switch(key)
		{
			case 'a':
				_player.change_int(LEFT);
				_player.toggle();
				if(check_player_path(LEFT))
					_player.move(-MOVE_FACTOR, 0);
				re_display();
				break;
			case 'd':  
				_player.change_int(RIGHT);
				_player.toggle();
				if(check_player_path(RIGHT))
					_player.move(MOVE_FACTOR, 0);
				re_display();
				break;
			case 'w':
				_player.change_int(UP);
				_player.toggle();
				if(check_player_path(UP))
					_player.move(0, MOVE_FACTOR);
				re_display();
				break;
			case 's':
				_player.change_int(DOWN);
				_player.toggle();
				if(check_player_path(DOWN))
					_player.move(0, -MOVE_FACTOR);
				re_display();
				break;
		}
	}
	
	// Mouse event handler
	void GameEngine::mouse_click(int button, int state, int x, int y)
	{
		int panel = -1;
		for(int i=0; i < _panels.size(); ++i)
			if(touching_object(_panels[i]))
				panel = i;
		int gate_id = NONE;
		/*if((panel != -1) && (state == GLUT_DOWN))
			{
				// If clicking in the panel, remove all gates from main screen
				if((x >= _panels[panel].left()) && 
				   (x <= _panels[panel].right()) && 
				   (y >= _panels[panel].bottom()) &&
				   (y <= _panels[panel].top()))
				{
					hide_gate();
					update_circuit(panel, NONE);
				}
				
				for(int i=1; i < _gates_in_hand.size(); ++i)
				{
					if(((x >= _gates_in_hand[i].left()) && 
						(x <= _gates_in_hand[i].right()) && 
						(y >= _gates_in_hand[i].bottom()) &&
						(y <= _gates_in_hand[i].top())) &&
					   (_gates_in_hand[i].bool1()))
					{
						hide_gate();
						
						gate_id = _gates_in_hand[i].id();

						// Make the gate display version of the gate to be displayed invisible
						_gates_in_hand[i].toggle();
						// Make the panel version of the gate to be displayed visible
						for(int i=0; i < _inverters.size(); ++i)
							if(_inverters[i].id() == gate_id)
								_inverters[i].toggle();
						
						for(int i=0; i < _ands.size(); ++i)
							if(_ands[i].id() == gate_id)
								_ands[i].toggle();

						for(int i=0; i < _ors.size(); ++i)
							if(_ors[i].id() == gate_id)
								_ors[i].toggle();
						
						update_circuit(panel, gate_id);
					}
				}
				re_display();
			}*/
		
		// Check for switch button
		int switch_button = -1;
		for(int i=0; i < _switch_buttons.size(); ++i)
			if(touching_object(_switch_buttons[i]))
				switch_button = i;
		if((switch_button != -1) && (state == GLUT_DOWN) && ((x >= _button_screen.left()) && 
															 (x <= _button_screen.right()) && 
															 (y >= _button_screen.bottom()) &&
															 (y <= _button_screen.top())))
																				   
		{
			// Change the value of the corresponding switch
			if(_switches[switch_button].int1() == 1)
				_switches[switch_button].change_int(0);
			else
				_switches[switch_button].change_int(1);
			// Update the network of circuits as necessary
			update_circuit();
			re_display();
		}
	}
	
	// Returns true iff the player is currently touching the object
	bool GameEngine::touching_object(SewersObject obj)
	{
		return ((((_player.left() <= obj.right()) &&
				  (_player.right() >= obj.left()) &&
				  (_player.top() >= obj.bottom()) &&
				  (_player.bottom() <= obj.top())) &&
				 (obj.bool1())));
	}
	
	// Returns true iff the player is currently touching the table
	bool GameEngine::touching_table()
	{
		return (((_player.left() <= _table.right() + MOVE_FACTOR) &&
				 (_player.right() >= _table.left() - MOVE_FACTOR) &&
				 (_player.bottom() <= _table.top() + MOVE_FACTOR) &&
				 (_player.top() >= _table.bottom())) &&
				(_table.bool1()));
	}	
		
	// Returns true iff the player is allowed to exist factor pixels in a certain direction
	bool GameEngine::check_player_path(int direction)
	{
		bool is_allowed = false;
		// Check floors
		for(int i=0; i<_floors.size(); ++i)
		{
			switch(direction)
			{
				case LEFT:
					if(!is_allowed)
						is_allowed = (((_player.left() - MOVE_FACTOR) > (_floors[i].left()))
										&&(_player.right() - MOVE_FACTOR) < (_floors[i].right())
										&&(_player.bottom()) < (_floors[i].top())
										&&(_player.bottom()) > (_floors[i].bottom() - MOVE_FACTOR));
					break;
				case DOWN:
					// Find a floor, but only if the player will not already standing on a valid one.
					if(!is_allowed)
						is_allowed = (((_player.left()) > (_floors[i].left()))
									  &&(_player.right()) < (_floors[i].right())
									  &&(_player.bottom()) < (_floors[i].top())
									  &&(_player.bottom()) > (_floors[i].bottom()));
					break;
				case RIGHT:
					// Find a floor, but only if the player will not already standing on a valid one.
					if(!is_allowed)
						is_allowed = (((_player.left() + MOVE_FACTOR) > (_floors[i].left()))
									  &&(_player.right() + MOVE_FACTOR) < (_floors[i].right())
									  &&(_player.bottom()) < (_floors[i].top())
									  &&(_player.bottom()) > (_floors[i].bottom() - MOVE_FACTOR));
					
					break;
				case UP:
					// Find a floor, but only if the player will not already standing on a valid one.
					if(!is_allowed)
						is_allowed = (((_player.left()) > (_floors[i].left()))
									  &&(_player.right()) < (_floors[i].right())
									  &&(_player.bottom() + MOVE_FACTOR) < (_floors[i].top())
									  &&(_player.bottom()) > (_floors[i].bottom() - MOVE_FACTOR));
					break;
			}
		}
		
		// Check doors
		for(int j=0; j < _doors.size(); ++j)
		{
			switch(direction)
			{
				case LEFT:
					// If a left-side door is closed, the player may not walk through it

					if(!(_doors[j].bool1()) && (_doors[j].int1() == LEFT) &&
					   (_player.left() - MOVE_FACTOR <= _doors[j].right()))
						is_allowed = false;
					break;
					
				case RIGHT:
					// If a right-side door is closed, the player may not walk through it
					for(int j=0; j < _doors.size(); ++j)
						if(!(_doors[j].bool1()) && (_doors[j].int1() == RIGHT) &&
						   (_player.right() + MOVE_FACTOR >= _doors[j].left()))
							is_allowed = false;
					break;
			}
		}
		
		// If there is a table, check for it
		if(_table.bool1())
		{
			switch(direction)
			{
				case LEFT:
					// Player may not walk into the right of the table
					if((_player.left() - MOVE_FACTOR <= _table.right()) &&
					   (_player.right() - MOVE_FACTOR >= _table.left()) &&
					   (_player.bottom() >= _table.bottom() - MOVE_FACTOR) &&
					   (_player.bottom() <= _table.top()))
					{
						is_allowed = false;
					}	
					break;
					
				case DOWN:
					// Player may not walk into the top of the table
					if((_player.left() <= _table.right()) &&
					   (_player.right() >= _table.left()) &&
					   (_player.bottom() >= _table.bottom() + MOVE_FACTOR) &&
					   (_player.bottom() <= _table.top() + MOVE_FACTOR))
					{
						is_allowed = false;
					}
					break;
					
				case RIGHT:
					// Player may not walk into the left of the table
					if((_player.left() + MOVE_FACTOR <= _table.right()) &&
					   (_player.right() + MOVE_FACTOR >= _table.left()) &&
					   (_player.bottom() >= _table.bottom() - MOVE_FACTOR) &&
					   (_player.bottom() <= _table.top()))
					{
						is_allowed = false;
					}
					break;
		
				case UP:
					// Player may not walk into the bottom of the table
					if((_player.left() <= _table.right()) &&
					   (_player.right() >= _table.left()) &&
					   (_player.bottom() + MOVE_FACTOR >= _table.bottom() - MOVE_FACTOR) &&
					   (_player.bottom() + MOVE_FACTOR <= _table.top() - MOVE_FACTOR))
					{
						is_allowed = false;
					}
					break;
			}
		}
		
		// See if player has intercepted gate box, if it is visible
		if((_gate_box.bool1()) && (touching_object(_gate_box)))
		{
			_gate_box.toggle(); // Make gate box invisible
			get_gates_from_box();
		}
		
		return is_allowed;
	}
	
	// Transfers all gates in the box into player's inventory
	void GameEngine::get_gates_from_box()
	{
		while(_gates_in_box.size() != 1)
		{
			_gates_in_hand.push_back(_gates_in_box.back());
			_gates_in_box.pop_back();
			
			// Adjust size of the gate screen -- MOVE THIS TO WHEN THE PLAYER GETS THE BOX
			_gates_in_hand[0].set_pos(0, SPACE_BETWEEN_GATES + ((SPACE_BETWEEN_GATES+GATE_WIDTH) * (_gates_in_hand.size()-1)), 0, WINDOW_HEIGHT/6);
		}
	}
	
	// Removes the gate on the main screen and displays all gates on the gate screen
	void GameEngine::hide_gate()
	{
		for(int j=1; j < _gates_in_hand.size(); ++j)
			if(!_gates_in_hand[j].bool1())
			{
				int gate_id = _gates_in_hand[j].id();
				_gates_in_hand[j].toggle();
				for(int k=0; k < _inverters.size(); ++k)
					if(_inverters[k].id() == gate_id)
						_inverters[k].toggle();
				for(int k=0; k < _ands.size(); ++k)
					if(_ands[k].id() == gate_id)
						_ands[k].toggle();
				for(int k=0; k < _ors.size(); ++k)
					if(_ors[k].id() == gate_id)
						_ors[k].toggle();
			}
	}
	
	bool GameEngine::connected(SewersObject circuit, SewersObject source)
	{
		GLint source_width = source.right() - source.left();
		GLint source_height = source.top() - source.bottom();
		
		return (((circuit.left() == source.left() + source_width/2) ||
				 (circuit.right() == source.left() + source_width/2)) &&
				((circuit.bottom() == source.bottom() + source_height/2) ||
				 (circuit.top() == source.bottom() + source_height/2)));
	}
	
	void GameEngine::update_circuit()
	{
		for(int i=0; i<_circuits.size(); ++i)
		{
			// If a switch is powering the circuit, the value of the circuit is the value of the switch
			for(int j=0; j<_switches.size(); ++j)
				if(connected(_circuits[i],_switches[j]))
					_circuits[i].change_int(_switches[j].int1());
		}
		
		/*vector<SewersObject> input_circuit;
		int output_circuit = NONE;
		// Find input circuits
		for(int i=0; i<_circuits.size(); ++i)
			if(// One end will be in the middle of the panel
			   ((_circuits[i].left() == _panels[panel].left() + PANEL_WIDTH/2) ||
				(_circuits[i].right() == _panels[panel].left() + PANEL_WIDTH/2)) &&
			   ((_circuits[i].bottom() == _panels[panel].bottom() + PANEL_HEIGHT/2) ||
				(_circuits[i].top() == _panels[panel].bottom() + PANEL_HEIGHT/2)) &&
			   // One end will be to the left of the panel
			   ((_circuits[i].left() < _panels[panel].left()) ||
				(_circuits[i].right() < _panels[panel].left())))
				input_circuit.push_back(_circuits[i]);
		
		// Find output circuit
		for(int i=0; i<_circuits.size(); ++i)
			if(// One end will be in the middle of the panel
			   ((_circuits[i].left() == _panels[panel].left() + PANEL_WIDTH/2) ||
				(_circuits[i].right() == _panels[panel].left() + PANEL_WIDTH/2)) &&
			   ((_circuits[i].bottom() == _panels[panel].bottom() + PANEL_HEIGHT/2) ||
				(_circuits[i].top() == _panels[panel].bottom() + PANEL_HEIGHT/2)) &&
			   // One end will be to the right of the panel
			   ((_circuits[i].left() > _panels[panel].right()) ||
				(_circuits[i].right() > _panels[panel].right())))
				output_circuit = i;
		
		
		// Update the output circuit given the input circuits and the gate id
		if(gate_id == INVERTER)
		{
			// Inverters can only have 1 input
			if(input_circuit.size() != 1)
				_circuits[output_circuit].change_int(-1);
			else if(input_circuit[0].int1() == 0)
				_circuits[output_circuit].change_int(1);
			else if(input_circuit[0].int1() == 1)
				_circuits[output_circuit].change_int(0);
			else
				_circuits[output_circuit].change_int(-1);
		}
		else if(gate_id == AND)
		{
			bool value = true;
			for(int i=0; i<input_circuit.size(); ++i)
				value = value && input_circuit[i].int1();
			_circuits[output_circuit].change_int(value);
		}
		else if(gate_id == OR)
		{
			bool value = false;
			for(int i=0; i<input_circuit.size(); ++i)
				value = value || input_circuit[i].int1();
			_circuits[output_circuit].change_int(value);
		}
		else
		{
			// If one input, output is just the same as the input
			if(input_circuit.size() == 1)
				_circuits[output_circuit].change_int(input_circuit[0].int1());
			// Otherwise, output is -1
			else
				_circuits[output_circuit].change_int(-1);
		}
		
		// Change door state if necessary (i.e. if the object's bool1 is true because it is
		//  connected to a door)
		if((_circuits[output_circuit].bool1()))
		{
				// If the door and the object have different values, toggle the door
				if(_doors[0].bool1() != _circuits[output_circuit].int1())
					_doors[0].toggle();
		}*/
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
				if(object == "PLAYER")
				{
					int left, bottom, direction;
					string facing;
					ifs >> left >> bottom >> facing;
					if(facing == "LEFT")
						direction = LEFT;
					else if(facing == "RIGHT")
						direction = RIGHT;
					else if(facing == "DOWN")
						direction = DOWN;
					else
						direction = UP;
					_player = SewersObject(PLAYER, left, left+PLAYER_WIDTH, bottom, bottom+PLAYER_HEIGHT, direction, _animation_frame);
				}
				else if(object == "TABLE")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_table = SewersObject(TABLE, left, left+TABLE_WIDTH, bottom, bottom+TABLE_HEIGHT, NONE, VISIBLE);
				}
				else if(object == "DOOR")
				{
					bool open;
					int bottom, left, position;
					string pos, connection, o;
					ifs >> bottom >> pos >> o;
					
					if(pos == "LEFT")
					{
						position = LEFT;
						left = 0;
					}
					else
					{
						position = RIGHT;
						left = WINDOW_WIDTH - DOOR_WIDTH;
					}
					
					open = (o == "OPEN");
					
					_doors.push_back(SewersObject(DOOR, left, left+DOOR_WIDTH, bottom, bottom+DOOR_HEIGHT, position, open));
				}
				else if(object == "INVERTER")
				{
					bool visible;
					int left, bottom;
					string v;
					ifs >> left >> bottom >> v;
					visible = (v == "VISIBLE");
					// Add to the display screen if it is not a fixed gate
					if(!visible)
					{
						_gates_in_box.push_back(SewersObject(INVERTER, SPACE_BETWEEN_GATES + ((_gates_in_box.size()-1) * (GATE_WIDTH+SPACE_BETWEEN_GATES)),
													  _gates_in_box.size() * (GATE_WIDTH+SPACE_BETWEEN_GATES), SPACE_BETWEEN_GATES, GATE_HEIGHT+SPACE_BETWEEN_GATES, NONE, VISIBLE));
					}
					_inverters.push_back(SewersObject(INVERTER, left, left+GATE_WIDTH, bottom, bottom+GATE_HEIGHT, NONE, visible));
				}
				else if(object == "AND")
				{
					bool visible;
					int left, bottom;
					string v;
					ifs >> left >> bottom >> v;
					visible = (v == "VISIBLE");
					// Add to the display screen if it is not a fixed gate
					if(!visible)
					{
						_gates_in_box.push_back(SewersObject(AND, SPACE_BETWEEN_GATES + ((_gates_in_box.size()-1) * (GATE_WIDTH+SPACE_BETWEEN_GATES)),
													  _gates_in_box.size() * (GATE_WIDTH+SPACE_BETWEEN_GATES), SPACE_BETWEEN_GATES, GATE_HEIGHT+SPACE_BETWEEN_GATES, NONE, VISIBLE));
					}
					_ands.push_back(SewersObject(AND, left, left+GATE_WIDTH, bottom, bottom+GATE_HEIGHT, NONE, visible));
				}
				else if(object == "OR")
				{
					bool visible;
					int left, bottom;
					string v;
					ifs >> left >> bottom >> v;
					visible = (v == "VISIBLE");
					// Add to the display screen if it is not a fixed gate
					if(!visible)
					{
						_gates_in_box.push_back(SewersObject(OR, SPACE_BETWEEN_GATES + ((_gates_in_box.size()-1) * (GATE_WIDTH+SPACE_BETWEEN_GATES)),
													  _gates_in_box.size() * (GATE_WIDTH+SPACE_BETWEEN_GATES), SPACE_BETWEEN_GATES, GATE_HEIGHT+SPACE_BETWEEN_GATES, NONE, VISIBLE));
					}
					_ors.push_back(SewersObject(OR, left, left+GATE_WIDTH, bottom, bottom+GATE_HEIGHT, NONE, visible));
				}
				else if(object == "SWITCH")
				{
					int left, bottom, val;
					ifs >> left >> bottom >> val;
					_switches.push_back(SewersObject(SWITCH, left, left+SWITCH_WIDTH, bottom, bottom+SWITCH_HEIGHT, val, NONE));
				}
				else if(object == "SWITCH_BUTTON")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_switch_buttons.push_back(SewersObject(SWITCH_BUTTON, left, left+SWITCH_BUTTON_WIDTH, bottom, bottom+SWITCH_BUTTON_HEIGHT, NONE, NONE));					
				}
				else if(object == "PANEL")
				{
					bool visible;
					int left, bottom;
					string v;
					ifs >> left >> bottom >> v;
					visible = (v == "VISIBLE");
					_panels.push_back(SewersObject(PANEL, left, left+PANEL_WIDTH, bottom, bottom+PANEL_HEIGHT, NONE, visible));
				}
				else if(object == "LADDER")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_ladder = SewersObject(LADDER, left, left+LADDER_WIDTH, bottom, bottom+LADDER_HEIGHT, NONE, NONE);
				}
				else if(object == "CIRCUIT")
				{
					int x1, y1, x2, y2, val, activator;
					ifs >> x1 >> y1 >> x2 >> y2 >> val >> activator;
					_circuits.push_back(SewersObject(CIRCUIT, x1, y1, x2, y2, val, activator));
				}
				else if(object == "FLOOR")
				{
					int left, right, bottom, top;
					ifs >> left >> right >> bottom >> top;
					_floors.push_back(SewersObject(FLOOR, left, right, bottom, top, NONE, NONE));
				}
				else if(object == "GATE_BOX")
				{
					int left, bottom;
					ifs >> left >> bottom;
					_gate_box = SewersObject(GATE_BOX, left, left+GATE_BOX_WIDTH, bottom, bottom+GATE_BOX_HEIGHT, NONE, VISIBLE);
				}
			}
		}
		return true;
	}
}