/*  GameEngine.cpp
 *  Part of the Sewers project
 *     Aaron Weeden, 2009-2010
 */
#include "GameEngine.hpp"

namespace Sewers
{
	GameEngine::GameEngine()
	{	
		set_num_steps(0);
		set_blueprints_collected(0);
		set_already_solved(false);
		
		// Initialize solutions array
		for(size_t i = 0; i <= MAX_NUM_SOLUTIONS; ++i)
		{
			_solutions[i] = "";
		}
		
		_avatar.set_type("BITTY");
		
		_exit.set_type("EXIT");
		_exit.set_left(EXIT_LEFT);
		_exit.set_bottom(EXIT_BOTTOM);
		_exit.set_width(EXIT_WIDTH);
		_exit.set_height(EXIT_HEIGHT);
						
		set_left_key('a');
        set_right_key('d');
        set_down_key('s');
        set_up_key('w');
		set_action_key('f');
		set_stats_key('g');
		set_options_key('o');
		set_save_key('i');
		set_load_key('u');
		set_help_key('h');
        set_quit_key('q');
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Returns the number of switches in the current circuit
	size_t GameEngine::num_switches() const
	{
		size_t i;
		for(i = 0; i <= MAX_NUM_SWITCHES && _switches[i].type() != ""; ++i)
		{
		}
		return i;
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Returns the number of gates in the current circuit
	size_t GameEngine::num_gates() const
	{
		size_t i;
		for(i = 0; i <= MAX_NUM_GATES && _switches[i].type() != ""; ++i)
		{
		}
		return i;
	}
	
	// PRECONDITION: The current room index is not out of bounds
	// POSTCONDITION: The filename at the current room index has been returned
	string GameEngine::current_room() const
	{
		assert(current_room_index() < _room_files.size());
		return _room_files[current_room_index()];
	}
	
	// PRECONDITION: i is not an out-of-bounds index
	// POSTCONDITION: The new current room is that at index i of the room
	//                 files vector
	void GameEngine::set_current_room_index(size_t i)
	{
		assert(i < _room_files.size());
		_current_room_index = i;
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
	
	// PRECONDITIONS: rooms_file is an existing file
	// POSTCONDITIONS: The filenames for each of the rooms have been stored (each
	//  whitespace separated string in the file is considered a filename).  Order
	//  matters here, so files earlier in the rooms_file will be added first
	void GameEngine::load_room_filenames(string rooms_file)
	{
		// Used to make insertion easy, via the >> operator
		ifstream ifs;
		// The next filename being loaded
		string current_filename = "";
		
		// Open the file for loading
		ifs.open(rooms_file.c_str());
		// Check that the file opened properly, exit on failure
        if(!ifs)
        {
            cerr << "SEWERS:  Fatal error loading rooms file " << rooms_file << endl;
			cerr << "Could not open file" << endl;
            exit(EXIT_FAILURE);
        }
		
		// Load filenames and add them to the list
		while(ifs >> current_filename)
		{
			_room_files.push_back(current_filename);
		}
		
		// Set the first filename in the rooms_file as the current room
		set_current_room_index(0);
	}

    // PRECONDITIONS: There is a file to load
    // POSTCONDITION: The circuit of the current room has been loaded and the
	//  avatar has been reset to its original position
	void GameEngine::load_circuit()
	{
		// Make sure the gates and switches arrays aren't full
		assert(num_gates() < MAX_NUM_GATES);
		assert(num_switches() < MAX_NUM_SWITCHES);
		// Used to make insertion easy, via the >> operator
		ifstream ifs;
		// The type of the current object being loaded from the file
		string current_type = "";
		// Switches must specify their initial output value
		int output_value = 0;
		// If the avatar is entering from the right, we want to load the _solution_
		//  to the room.  This is specified in the file, the following variable
		//  indicates we have reached that point in the file.
		bool checking_solution = false;
		
		// Clear the last room
		_exit.set_input1(NULL);
		// Reset avatar position
		if(already_solved())
			_avatar.set_left(WINDOW_WIDTH);
		else
		{
			if(current_room_index() == 0)
				_avatar.set_left(AVATAR_LEFT);
			else
				_avatar.set_left(0 - AVATAR_WIDTH);
		}
		// Set entrance as either ladder (first room) or doorway
		if(current_room_index() == 0)
			_entrance.set_as_ladder();
		else
			_entrance.set_as_door();
		
		
        // Open the file for loading
		ifs.open(current_room().c_str());
		// Check that the file opened properly, exit on failure
        if(!ifs)
        {
            cerr << "Fatal error loading room file " << current_room() << endl;
			cerr << "Could not open file" << endl;
            exit(EXIT_FAILURE);
        }
		
		// Load circuit object
		while(ifs >> current_type)
		{		
			if(current_type == "SOLUTION")
				checking_solution = true;
			else if((already_solved() && checking_solution) || (!already_solved() && !checking_solution))
			{
				if(current_type == "SWITCH")
				{
					// Make sure the switches array isn't full
					if(num_switches() == MAX_NUM_SWITCHES)
					{
						cerr << "Fatal error loading room file " << current_room() << endl;
						cerr << "Too many switches, cannot have more than ";
						cerr << MAX_NUM_SWITCHES << " switches." << endl;
						exit(EXIT_FAILURE);
					}
					// Import the output value
					ifs >> output_value;
					// Add to this room's list of switches
					_switches[num_switches()] = (CircuitObject(current_type));
					_switches[num_switches()-1].set_width(SWITCH_WIDTH);
					_switches[num_switches()-1].set_height(SWITCH_HEIGHT);
					_switches[num_switches()-1].set_output_value(output_value);
					// Connect the object to the rest of the circuit
					_connect_object(_switches[num_switches()-1]);
				}
				else if(current_type == "BUTTON")
				{
					// The last switch added gets the button
					_switches[num_switches()-1].set_has_button(true);
				}			
				else 
				{
					// Make sure the gates array isn't full
					if(num_gates() == MAX_NUM_GATES)
					{
						cerr << "Fatal error loading room file " << current_room() << endl;
						cerr << "Too many gates, cannot have more than ";
						cerr << MAX_NUM_GATES << " gates." << endl;
						exit(EXIT_FAILURE);
					}
					// Add to this room's list of gates
					_gates[num_gates()] = (CircuitObject(current_type));
					// Update the gate in the room's list
					_gates[num_gates()-1].set_width(GATE_WIDTH);
					_gates[num_gates()-1].set_height(GATE_HEIGHT);
					// Connect the object to the rest of the circuit
					_connect_object(_gates[num_gates()-1]);
				}			
			}
		}

		// Set up circuit for drawing
		_set_circuit_obj_coords();
		
		// Determine solutions for the room
		_determine_solutions();
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
	// POSTCONITIONS: Truth table for the current room has been drawn, with
	//                 prompts for the user at each row
	/*void GameEngine::print_truth_table() const
	{
		// Each switch is assigned a unique letter.
		// P is often the standard choice for the initial letter.
		char letter = 'P';
		// For each row in the table, we will be prompting the user to
		//  input the correct answer for that row
		int row_answer = 0;
		
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
		_print_truth_table_result(*(_exit.input1()), letter);
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
	}*/
	
	// PRECONDITIONS: none
	// POSTCONDITION: If the avatar is next to an object, display
	//  information about that object
	void GameEngine::help() const
	{
		if(intersecting(_avatar, _computer))
		   _computer.help();
		
		if(next_to(_avatar, _entrance))
			_entrance.help();
		
		if(next_to(_avatar, _exit))
			_exit.help();
		
		for(size_t i = 0; i < num_switches(); ++i)
			if(intersecting(_avatar, _switches[i]))
				_switches[i].help();
		
		for(size_t i = 0; i < num_gates(); ++i)
			if(intersecting(_avatar, _gates[i]))
				_gates[i].help();
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Print the player's current game statistics
	void GameEngine::print_stats() const
	{
		cerr << endl;
		cerr << "STATISTICS" << endl;
		cerr << "----------" << endl;
		cerr << "Rooms completed: " << current_room_index() << "/" << num_rooms() << endl;
		cerr << "Blueprints collected: " << blueprints_collected() << "/" << num_rooms() << endl;
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Prompts the user for the key to change and its newly assigned value
	void GameEngine::change_key()
	{
		unsigned char old_key;
		unsigned char new_key;
		bool valid_key = false;
		
		// Print out the list of keys
		cerr << endl;
		cerr << "KEY LISTING:" << endl;
		cerr << left_key() << " - move left" << endl;
		cerr << right_key() << " - move right" << endl;
		cerr << down_key() << " - move down" << endl;
		cerr << up_key() << " - move up" << endl;
		cerr << action_key() << " - action button" << endl;
		cerr << help_key() << " - help" << endl;
		cerr << stats_key() << " - print statistics" << endl;
		cerr << options_key() << " - change key commands" << endl;
		cerr << save_key() << " - save game" << endl;
		cerr << load_key() << " - load game" << endl;
		cerr << quit_key() << " - quit" << endl;
		cerr << endl;
		
		// Get the key to be changed
		cerr << "Please enter the key to change: ";
		
		while(!valid_key)
		{
			cin >> old_key;
		
			// Check to make sure key is valid
			if(old_key != left_key() && old_key != right_key() && old_key != down_key() &&
			   old_key != up_key() && old_key != action_key() && old_key != help_key() &&
			   old_key != stats_key() && old_key != options_key() && old_key != save_key() &&
			   old_key != load_key() && old_key != quit_key())
			{
				cerr << "That key is not currently assigned.  Please choose another: ";
			}
			else
			{
				valid_key = true;
			}
		}
		
		valid_key = false;
		
		// Get the new key value
		cerr << "Please enter the new key: ";
		
		while(!valid_key)
		{
			cin >> new_key;
		
			// Check to make sure that key isn't already in use
			if((new_key == left_key() || new_key == right_key() || new_key == down_key() ||
			   new_key == up_key() || new_key == action_key() || new_key == help_key() ||
			   new_key == stats_key() || new_key == options_key() || new_key == save_key() ||
			   new_key == load_key() || new_key == quit_key()) && (new_key != old_key))
			{
				cerr << "That key is already in use.  Please choose another: ";
			}
			else
			{
				valid_key = true;
			}
		}
		
		cerr << "New key: " << new_key << endl;
		
		// Set the new key
		if(old_key == left_key())
			set_left_key(new_key);
		else if(old_key == right_key())
			set_right_key(new_key);
		else if(old_key == down_key())
			set_down_key(new_key);
		else if(old_key == up_key())
			set_up_key(new_key);
		else if(old_key == action_key())
			set_action_key(new_key);
		else if(old_key == help_key())
			set_help_key(new_key);
		else if(old_key == stats_key())
			set_stats_key(new_key);
		else if(old_key == options_key())
			set_options_key(new_key);
		else if(old_key == save_key())
			set_save_key(new_key);
		else if(old_key == load_key())
			set_load_key(new_key);
		else if(old_key == quit_key())
			set_quit_key(new_key);
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: The solutions of the room have been listed to the user
	void GameEngine::list_solutions() const
	{
		size_t i = 0;
		for(i = 0; _solutions[i] != ""; ++i)
		{
			cerr << _solutions[i] << endl;
		}
		cerr << "There are " << i << " solutions" << endl;
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
			_draw_circuit(_switches[i]);
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
				
        // Gate box
        //_gate_box.draw();
		
        // Avatar
        _avatar.draw();
		
		// Entrance
		_entrance.draw();
		
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
       if(intersecting(_avatar, _computer))
            _computer_screen.draw();
		
		glFlush();
	}

    // Keyboard event handler
    // Wrapper for the glutKeyboardFunc
    void GameEngine::key_click(unsigned char key, int x, int y)
    {
        if(key == left_key())
        {
            _attempt_avatar_move("LEFT");
			// If the avatar has left the room via the exit, load the next room
			if(_avatar.right() <= 0)
			{
				set_current_room_index(current_room_index() - 1);
				set_already_solved(true);
				load_circuit();
			}
			draw();
        }
        else if(key == right_key())
        {
            _attempt_avatar_move("RIGHT");
			// If the avatar has left the room via the entrance, load the previous room
			if(_avatar.left() >= WINDOW_WIDTH)
			{
				// Exit if player has completed all the rooms
				if(current_room_index() == _room_files.size() - 1)
				   exit(EXIT_SUCCESS);
				else 
				{
					set_current_room_index(current_room_index() + 1);
					set_already_solved(false);
					load_circuit();
				}
			}
			draw();
		}
        else if(key == down_key())
        {
            _attempt_avatar_move("DOWN");
			draw();
		}
        else if(key == up_key())
        {
            _attempt_avatar_move("UP");
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
					   if(_switches[i].output_value() == 0)
						   _switches[i].set_output_value(1);
					   else
						   _switches[i].set_output_value(0);
				   }
			}
			
			// Display the truth table if the player is touching the computer
			//  and it is on
			if(intersecting(_avatar, _computer))
				list_solutions();
			
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
		else if(key == help_key())
		{
			help();
		}
		else if(key == stats_key())
		{
			print_stats();
		}
		else if(key == options_key())
		{
			change_key();
		}
        else if(key == quit_key())
        {
            exit(EXIT_SUCCESS);
        }
    }
	
	// PRECONDITIONS: None
    // POSTCONDITION: The avatar is facing `direction' and has been animated.
    //                If the move is a valid one, the avatar will also move in
    //                the indicated direction
    void GameEngine::_attempt_avatar_move(string direction)
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
	void GameEngine::_connect_object(CircuitObject& input)
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
				if((_gates[i].input2() == NULL) && (_gates[i].type() != "NOT"))
				{
					_gates[i].set_input2(&input);
					input.set_output(&(_gates[i]));
					found_obj = true;
				}
				else if(_gates[i].input1() == NULL)
				{
					// Update the input field of the gate,
					_gates[i].set_input1(&input);
					// And change the input object's output field
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
	
	// Set up the x (i.e. left()) and y (i.e. bottom()) coordinates for
	//  each of the circuit objects
	void GameEngine::_set_circuit_obj_coords()
	{
		// This function uses the lengths of sub-circuits to determine object x values.
		// A sub-circuit is a path from a switch to the exit.
		// The x values of the objects in a sub-circuit are spaced evenly over the width
		//  of the sub-circuit, and the y values of the objects are spaced evenly over
		//  the height of the floor.
		
		// A count of the number of objects for the current sub-circuit
		size_t sc_width = 0;
		// x and y value for the middle of an object
		GLint x_value = 0;
		GLint y_value = 0;
		// x and y value for the left and bottom of the object
		GLint left = 0;
		GLint bottom = 0;
		// The spaces between the x values of objects and the y values of objects,
		//  spaced evenly over the floor
		GLint x_spacing_amount = 0;
		GLint y_spacing_amount = 0;
		// The current object in question
		CircuitObject* current_obj = NULL;
		
		// Divide the floor height into equal chunks
		y_spacing_amount = FLOOR_HEIGHT/(num_switches()+1);
				
		for(size_t i = 0; i <= num_switches(); ++i)
		{		
			// Calculate `sc_width' by counting number of objects along the circuit
			current_obj = &(_switches[i]);
			sc_width = 0;
			while(current_obj->output() != NULL)
			{
				current_obj = current_obj->output();
				++sc_width;
			}
			
			// Divide the floor width into equal chunks
			x_spacing_amount = FLOOR_WIDTH/(sc_width+1);
			
			// Assign x and y values, separated by a certain spacing
			current_obj = &(_switches[i]);
			x_value = WALL_WIDTH;
			y_value = WALL_HEIGHT + (i+1) * y_spacing_amount;
			while(current_obj->output() != NULL)
			{
				x_value += x_spacing_amount;
				
				// Determine `left' and `bottom' based on the current object's
				//  width and height
				if(current_obj->type() == "SWITCH")
				{
					left = x_value - SWITCH_WIDTH/2;
					bottom = y_value - SWITCH_HEIGHT/2;
				}
				// Note: for now `else' only catches gates
				else
				{
					left = x_value - GATE_WIDTH/2;
					bottom = y_value - GATE_WIDTH/2;
				}

				// Only give the object an x value if it doesn't already has one
				if(current_obj->left() == 0)
				{
					current_obj->set_left(left);
				}
				
				// Only give the object a y value if it doesn't already has one
				if(current_obj->bottom() == 0)
				{
					// Make a slight adjustment if the object takes 2 inputs
					if(current_obj->input2() != NULL)
					{
						bottom += y_spacing_amount/2;
					}					
					current_obj->set_bottom(bottom);
				}
				
				current_obj = current_obj->output();
			}
		}
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: The solutions array has been populated with the solutions
	//                 for the given room
	void GameEngine::_determine_solutions() const
	{
		cerr << "_determine_solutions() was called but is just a stub." << endl;
	}
		
	// Draws the wires connecting objects in the circuit
	void GameEngine::_draw_circuit(const CircuitObject& input_obj) const
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
			_draw_circuit(*(output_obj));
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: Recursively prints out the circuit as it would be described in a
	//                 truth table
	/*void GameEngine::_print_truth_table_result(const CircuitObject& root_obj, char& letter) const
	{
		if(root_obj.input2() != NULL)
		{
			cerr << "(";
			_print_truth_table_result(*(root_obj.input2()), letter);
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
			_print_truth_table_result(*(root_obj.input1()),letter);
			cerr << ")";
		}
	}*/
}
