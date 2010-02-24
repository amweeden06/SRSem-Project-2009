/*  GameEngine.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, 2009-2010
 */
#include "GameEngine.hpp"

namespace Sewers
{
	GameEngine::GameEngine(string rooms_file)
	{	
		set_num_steps(0);
		set_rooms_file(rooms_file);
		
		_num_switches = _num_gates = 0;
		
		_exit.set_type("EXIT");
		_exit.set_left(EXIT_LEFT);
		_exit.set_bottom(EXIT_BOTTOM);
		_exit.set_width(EXIT_WIDTH);
		_exit.set_height(EXIT_HEIGHT);
		
		_computer.set_exit(&_exit);
		
		_button_screen.set_type("BUTTON_SCREEN");
		_button_screen.set_left(BUTTON_SCREEN_LEFT);
		_button_screen.set_bottom(BUTTON_SCREEN_BOTTOM);
		_button_screen.set_width(BUTTON_SCREEN_WIDTH);
		_button_screen.set_height(BUTTON_SCREEN_HEIGHT);
		
		_computer_screen.set_type("COMPUTER_SCREEN");
		_computer_screen.set_left(COMPUTER_SCREEN_LEFT);
		_computer_screen.set_bottom(COMPUTER_SCREEN_BOTTOM);
		_computer_screen.set_width(COMPUTER_SCREEN_WIDTH);
		_computer_screen.set_height(COMPUTER_SCREEN_HEIGHT);
		
        set_left_key('a');
        set_right_key('d');
        set_down_key('s');
        set_up_key('w');
		set_action_key('f');
		set_save_key('i');
		set_load_key('u');
        set_quit_key('q');
	}
	
    // PRECONDITION: argc and argv have not been modified since main() was
    //                called
    // POSTCONDITION: The GLUT window has been set up for drawing
	void GameEngine::init_glut(int& argc, char** argv)
    {
        glutInit(&argc, argv);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Computer City:  Sewers");
        // Set the clear color to the Sewer's wall color
        glClearColor(0.0, 0.0, 0.0, 0.0);
        gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT); 
    }

    // PRECONDITIONS: none
    // POSTCONDITION: The circuit of the room has been loaded from `filename'
	void GameEngine::load_circuit(string filename)
	{
		// Used for to make insertion easy, via the >> operator
		ifstream ifs;
		// The type of the current object being loaded from the file
		string current_type = "";
		// Switches must specify their initial output value
		int output_value;
		// Dummy variables to pass by reference to drawing prep function
		int w = 0, h = 0;
		
        // Open the file for loading
		ifs.open(filename.c_str());
		// Check that the file opened properly, exit on failure
        if(!ifs)
        {
            cerr << "Fatal error loading room file " << filename << endl;
			cerr << "Could not open file" << endl;
            exit(EXIT_FAILURE);
        }
		
		// Load circuit object
		while(ifs >> current_type)
		{		
			if(current_type == "SWITCH")
			{
				// Import the output value
				ifs >> output_value;
				// Add to this room's list of switches
				_switches[_num_switches++] = (CircuitObject(current_type));
				_switches[num_switches()-1].set_width(SWITCH_WIDTH);
				_switches[num_switches()-1].set_height(SWITCH_HEIGHT);
				_switches[num_switches()-1].set_output_value(output_value);
				// Connect the object to the rest of the circuit
				connect_object(_switches[num_switches()-1]);
			}
			else if(current_type == "BUTTON")
			{
				// The last switch added gets the button
				_switches[num_switches()-1].give_button();
			}			
			else 
			{
				// Add to this room's list of gates
				_gates[_num_gates++] = (CircuitObject(current_type));
				// Update the gate in the room's list
				_gates[num_gates()-1].set_width(GATE_WIDTH);
				_gates[num_gates()-1].set_height(GATE_HEIGHT);
				// Connect the object to the rest of the circuit
				connect_object(_gates[num_gates()-1]);
			}			
		}

		// Set up circuit for drawing
		prepare_circuit_drawing(*(_exit.input1()), 0, 0, w, h);
	}
	
	// PRECONDITIONS: None
	// POSTCONDITION: Saves the game state to a user-specified file
	// 
	// Note:  Only the information that cannot be derived from other information
	//         in the room should be saved.
	// Note:  This function's syntax should match that of the load_game function below
	void GameEngine::save_game() const
	{
		// Used to make extraction easy, via the << operator
		ofstream ofs;
		// User-specified file
		string filename;
		
		// Prompt the user for filename
		cerr << "SAVE GAME:  Enter filename: ";
		cin >> filename;
		
		if(filename == "cancel")
			cerr << "SAVE CANCELLED" << endl;
		
		// Open the file for saving
		ofs.open(filename.c_str());
		if(!ofs)
        {
			cerr << "ERROR:  Could not open file for saving" << endl;
        }
		else 
		{
			ofs << _avatar.left() << " " << _avatar.bottom() << " ";
			ofs << _avatar.direction() << " ";
			ofs << (_avatar.animation_frame() ? "true" : "false") << " ";
			for(size_t i = 0; i < num_switches(); ++i)
			{
				if(_switches[i].has_button())
				{
					ofs << _switches[i].output_value() << " ";
				}
			}
		}
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: The game state from a user-specified file has been loaded.
	void GameEngine::load_game()
	{
		ifstream ifs;
		string filename;
		
		// Prompt the user for filename
		cerr << "LOAD GAME:  Enter filename: ";
		cin >> filename;
				
		// Open the file for saving
		ifs.open(filename.c_str());
		if(!ifs)
        {
			cerr << "ERROR:  Could not open file " << filename << endl;
        }
		else 
		{
			GLint left, bottom;
			string direction, animation_frame;
			int value;
			
			ifs >> left >> bottom >> direction >> animation_frame;
			_avatar.set_left(left);
			_avatar.set_bottom(bottom);
			_avatar.set_direction(direction);
			if(animation_frame == "true")
				_avatar.set_animation_frame(true);
			else
				_avatar.set_animation_frame(false);
			
			for(size_t i = 0; i < num_switches(); ++i)
			{
				if(_switches[i].has_button())
				{
					ifs >> value;
					_switches[i].set_output_value(value);
				}
			}
		}
	}

    // PRECONDITIONS: none
    // POSTCONDITION: All of the objects of the room have been drawn to the
    //                 screen
	void GameEngine::draw() const
	{
		// Walls
        glClear(GL_COLOR_BUFFER_BIT);
		
		// Floor
        FLOOR_COLOR.glColor();
        glRectf(FLOOR_LEFT,FLOOR_BOTTOM,
				FLOOR_WIDTH,FLOOR_HEIGHT);

        // Hallways
        FLOOR_COLOR.glColor();
		glRectf(_entrance.left(), _entrance.bottom(),
				_entrance.right(), 
				_entrance.top()-_entrance.height()/2);
        glRectf(_exit.left(),_exit.bottom(),
                _exit.right(),_exit.top()-_exit.height()/2);
				
        // Computer
        _computer.draw();
		
        // Panels
        // for(size_t i=0; i < _panels.size(); ++i)
        //    _panels[i].draw();
				
		// Circuit
		for(size_t i = 0; i < num_switches(); ++i)
		{
			draw_circuit(_switches[i]);
		}
		
		// Switches
		for(size_t i = 0; i < num_switches(); ++i)
		{
			_switches[i].draw();
		}
		
		// Gates
		for(size_t i = 0; i < num_gates(); ++i)
		{
			_gates[i].draw();
		}
		
        // Ladder
        _entrance.draw();
		
        // Gate box
        //_gate_box.draw();
		
        // Avatar
        _avatar.draw();
		
        // Exit
		_exit.draw();
		
        // Gate screen, if needed
        //for(size_t i=0; i<_panels.size(); ++i)
        //    if(intersecting_object(_panels[i]))
        //        for(size_t i=0; i < _gates_in_hand.size(); ++i)
        //            _gates_in_hand[i].draw();
		
        // Button screen, if needed
		for(size_t i = 0; i < num_switches(); ++i)
			if(intersecting(_avatar, _switches[i]) && _switches[i].has_button())
			   _button_screen.draw();
		
        // Pause screen, if needed
        //if(_pause_screen.bool1())
        //    _pause_screen.draw();
		
        // Computer screen, if needed
       if(intersecting(_avatar, _computer) && _computer.is_on())
            _computer_screen.draw();
		
		glFlush();
	}

    // Keyboard event handler
    // Wrapper for the glutKeyboardFunc
    void GameEngine::key_click(unsigned char key, int x, int y)
    {
        if(key == left_key())
        {
            attempt_avatar_move("LEFT");
			draw();
        }
        else if(key == right_key())
        {
            attempt_avatar_move("RIGHT");
			draw();
		}
        else if(key == down_key())
        {
            attempt_avatar_move("DOWN");
			draw();
		}
        else if(key == up_key())
        {
            attempt_avatar_move("UP");
			draw();
		}
		else if(key == action_key())
		{			
			// See if the avatar is touching a switch button
			for(size_t i = 0; i < num_switches(); ++i)
			{
				// If so, 
				if(intersecting(_avatar, _switches[i]) && _switches[i].has_button())
				   {
					   // Toggle the value of the switch
					   if(_switches[0].output_value() == 0)
						   _switches[0].set_output_value(1);
					   else
						   _switches[0].set_output_value(0);
				   }
			}
			
			// Display the truth table if the player is touching the computer
			//  and it is on
			if(intersecting(_avatar, _computer) && _computer.is_on())
				print_truth_table();
			
			draw();
		}		
		else if(key == save_key())
		{
			save_game();
			draw();
		}
		else if(key == load_key())
		{
			load_game();
			draw();
		}
        else if(key == quit_key())
        {
            exit(EXIT_SUCCESS);
        }
    }
	
	// PRECONDITIONS: none
	// POSTCONITIONS: Truth table for the current room has been drawn, with
	//                 prompts for the user at each row
	void GameEngine::print_truth_table() const
	{
		// Each switch is assigned a unique letter.
		// P is often the standard choice for the initial letter.
		char letter = 'P';
		// For each row in the table, we will be prompting the user to
		//  input the correct answer for that row
		int row_answer;
		
		// Print the column headings.  We want a column
		//  for each switch in the circuit.
		for(size_t i = 0; i < num_switches(); ++i)
		{
			cerr << letter << "\t";
			// Set the letter of the next switch
			letter++;
		}
		
		// Print the final column heading.  This is the boolean
		//  description of the current circuit.
		// Again, the initial letter assignment is "P"
		letter = 'P';
		print_truth_table_result(*(_exit.input1()), letter);
		cerr << endl;
		
		// There will be 2^n rows, where n is the number of switches
		//  in the circuit.
		for(size_t i = 0; i < pow(2.0,(double)num_switches()); ++i)
		{
			// This section is to ensure that we have all combinations of
			//  switches
			for(int j = num_switches() - 1; j >= 0; --j)
			{
				cerr << (int)(i / pow(2.0,(double)j)) % 2 << "\t";
			}
			cin >> row_answer;
			cerr << endl;
		}		
	}

    // PRECONDITIONS: None
    // POSTCONDITION: The avatar is facing `direction' and has been animated.
    //                If the move is a valid one, the avatar will also move in
    //                the indicated direction
    void GameEngine::attempt_avatar_move(string direction)
    {
		// Animate the avatar
        _avatar.set_direction(direction);
        _avatar.set_animation_frame(!_avatar.animation_frame());
		
		// Determine the proposed positioning of the avatar
		Avatar proposed_position = _avatar;
		if(direction == "LEFT")
		{
			proposed_position.set_left(proposed_position.left() - MOVE_FACTOR);
		}
		else if(direction == "RIGHT")
		{
			proposed_position.set_left(proposed_position.left() + MOVE_FACTOR);
		}
		else if(direction == "DOWN")
		{
			proposed_position.set_bottom(proposed_position.bottom() - MOVE_FACTOR);
		}
		else if(direction == "UP")
		{
			proposed_position.set_bottom(proposed_position.bottom() + MOVE_FACTOR);
		}
		
		// Check if the avatar would be in a hallway or on the main floor
		if((!_entrance.is_ladder() &&
			proposed_position.left() <= _entrance.right() &&
			proposed_position.bottom() >= _entrance.bottom() &&
			proposed_position.top() < _entrance.top()) ||
		   (_exit.is_open() &&
			proposed_position.right() >= _exit.left() &&
			proposed_position.bottom() >= _exit.bottom() &&
			proposed_position.top() < _exit.top()) ||
		   (proposed_position.left() > _entrance.right() &&
			proposed_position.right() < _exit.left() &&
			proposed_position.bottom() > WALL_HEIGHT &&
			proposed_position.top() < WINDOW_HEIGHT))
			// If so, allow the avatar to move and record the step
		{
			_avatar = proposed_position;
			set_num_steps(num_steps()+1);
		}
	}
	
	// Find an object to which we can connect the `input' object
	void GameEngine::connect_object(CircuitObject& input)
	{
		// Check the exit first to see if it needs an input.  If it does,
		if(_exit.input1() == NULL)
		{
			// Change the exit's input field,
			_exit.set_input1(&input);
			// And change the input object's output field.
			input.set_output(&_exit);
		}
		// If it doesn't,
		else
		{
			// Look for an object in the gates array that does.
			bool found_obj = false;
			size_t i = 0;
			while(!found_obj && i < num_gates())
			{
				// If we find one,
				if(_gates[i].input1() == NULL)
				{
					// Update the input field of the gate,
					_gates[i].set_input1(&input);
					// And change the input object's output field
					input.set_output(&(_gates[i]));
					found_obj = true;
				}
				else if((_gates[i].input2() == NULL) && (_gates[i].type() != "NOT"))
				{
					_gates[i].set_input2(&input);
					input.set_output(&(_gates[i]));
					found_obj = true;
				}
				++i;
			}
			if(!found_obj)
			{
				cerr << "Fatal error loading room file" << endl;
				cerr << "Invalid circuit:  Too many objects, could not find output for ";
				cerr << input.type() << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	
	// Recursively set up the coordinates of the circuit objects for drawing, starting
	//  at root_obj (which should be the exit's input object at first)
	void GameEngine::prepare_circuit_drawing(CircuitObject& root_obj, int width, 
											 int height, int& circuit_width, int& circuit_height)
	{
		++width;		
		
		if(root_obj.input2() != NULL)
		{
			++circuit_height;
			prepare_circuit_drawing(*(root_obj.input2()), width, height-1, 
									circuit_width, circuit_height);
		}
		
		if(root_obj.input1() != NULL)
		{
			if(root_obj.input2() == NULL)
				prepare_circuit_drawing(*(root_obj.input1()), width, height, 
										circuit_width, circuit_height);
			else
				prepare_circuit_drawing(*(root_obj.input1()), width, height+1, 
										circuit_width, circuit_height);
		}
		else
		{
			// We have reached the switch.  Update the total circuit width if necessary
			if(width > circuit_width)
				circuit_width = width;
			circuit_height++;
		}
		
		// Determine left and bottom coordinates and set them
		root_obj.set_left(FLOOR_LEFT + FLOOR_WIDTH - width*(FLOOR_WIDTH/(circuit_width+1)));
		root_obj.set_bottom(FLOOR_BOTTOM + FLOOR_HEIGHT/2 + height*(FLOOR_HEIGHT)/(circuit_height+1));		
	}
	
	// Draws the wires connecting objects in the circuit
	void GameEngine::draw_circuit(const CircuitObject& input_obj) const
	{
		CircuitObject* output_obj = input_obj.output();
		
		GLint mid_point_x = (input_obj.right() + output_obj->left())/2;
		GLint left_y = input_obj.bottom() + input_obj.height()/2;
		GLint right_y;
		
		// If the output object has only one input,
		if(output_obj->input2() == NULL)
			right_y = left_y;
		else
		{
			// If this is the 1st input of the output object,
			if(&input_obj == output_obj->input1())
				right_y = output_obj->top() - output_obj->height()/3;
			else 
				right_y = output_obj->bottom() + output_obj->height()/3;
		}
		
		if(input_obj.output_value() == 1)
			ONE_COLOR.glColor();
		else
			ZERO_COLOR.glColor();
		
		glBegin(GL_LINES);
		if(input_obj.top() == output_obj->top())
		{
			glVertex2i(input_obj.right(), left_y);
			glVertex2i(output_obj->left(), right_y);
		}
		else
		{			
			glVertex2i(input_obj.right(), left_y);
			glVertex2i(mid_point_x, left_y);
			glVertex2i(mid_point_x, right_y);
			glVertex2i(mid_point_x, left_y);
			glVertex2i(mid_point_x, right_y);
			glVertex2i(output_obj->left(), right_y);
		}		
		glEnd();
		
		if(output_obj->type() != "EXIT")
			draw_circuit(*(output_obj));
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Recursively prints out the circuit as it would be described in a
	//                 truth table
	void GameEngine::print_truth_table_result(const CircuitObject& root_obj, char& letter) const
	{
		if(root_obj.input2() != NULL)
		{
			cerr << "(";
			print_truth_table_result(*(root_obj.input2()), letter);
			cerr << ")";
		}
		
		if(root_obj.type() == "SWITCH")
		{
			cerr << letter;
			letter++;
		}
		else
		{
			cerr << root_obj.type();
		}
		
		if(root_obj.input1() != NULL)
		{
			cerr << "(";
			print_truth_table_result(*(root_obj.input1()),letter);
			cerr << ")";
		}
	}
}
