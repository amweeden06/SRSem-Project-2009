/*
 *  GameEngine.cpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009.
 *
 */
/*#include "GameEngine.hpp"

namespace SewersOld
{	
    GameEngine::GameEngine()
    {
		// According to , The gate display screen needs to be the first item
        //  of the vectors that contain gates.
        // TODO:  why is the gate screen only 10 pixels wide?
        _gates_in_box.push_back(SewersObject("GATE_DISPLAY", 0, 10, 0, 
                    WINDOW_HEIGHT/6, -1, false));
        _gates_in_hand.push_back(SewersObject("GATE_DISPLAY", 0, 10, 0,
                    WINDOW_HEIGHT/6, -1, false));
        // Prepare the screen that displays switch buttons, put it in the bottom
        //  left corner of the screen
        _button_screen = SewersObject("BUTTON_DISPLAY", 0, WINDOW_WIDTH/6, 0, 
                WINDOW_HEIGHT/6, -1, false);
        // Prepare the screen that comes up when the game is paused
        _pause_screen = SewersObject("PAUSE_BUTTON", WINDOW_WIDTH/2 - 40, 
                WINDOW_WIDTH/2 + 40, WINDOW_HEIGHT/2 - 40, WINDOW_HEIGHT/2 + 40,
                -1, false);
        // Prepare the screen that displays the computer, put it in the bottom-
        //  left corner of the screen
        _computer_screen = SewersObject("COMPUTER_DISPLAY", 0, WINDOW_WIDTH/6, 0,
                WINDOW_HEIGHT/6, -1, false);

        // Set default values for the member variables
        _move_factor = MOVE_FACTOR;
        _rooms_left = 1;
        _left_char = 'a';
        _right_char = 'd';
        _up_char = 'w';
        _down_char = 's';
        _help_char = 'h';
        _stats_char = 'g';
        _options_char = 'o';
        _quit_char = 'q';
    }

    void GameEngine::init_glut(int& argc, char** argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Computer City:  Sewers");
        // Set the clear color to the underground's wall color
        glClearColor(0.0, 0.0, 0.0, 0.0);
        // Set the size of a drawing point
        glPointSize(1.0);
        glEnable(GL_COLOR_LOGIC_OP);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT); 
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Redraw all of the objects
    // Order matters here for drawing
    void GameEngine::re_display(void)
    {
        // Walls
        glClear(GL_COLOR_BUFFER_BIT);

        // Floors
        for(size_t i=0; i < _floors.size(); ++i)
            _floors[i].draw();

        // Switches
        for(size_t i=0; i < _switches.size(); ++i)
            _switches[i].draw();

        // Switch buttons
        for(size_t i=0; i < _switch_buttons.size(); ++i)
            _switch_buttons[i].draw();

        // Computer
        _computer.draw();

        // Panels
        for(size_t i=0; i < _panels.size(); ++i)
            _panels[i].draw();

		// Circuits
		for(size_t i=0; i < _circuits.size(); ++i)
			_circuits[i].draw();
			
        // Gates
        for(size_t i=0; i < _NOTs.size(); ++i)
            _NOTs[i].draw();
        for(size_t i=0; i < _ands.size(); ++i)
            _ands[i].draw();
        for(size_t i=0; i < _ors.size(); ++i)
            _ors[i].draw();

        // Ladder
        _ladder.draw();

        // Gate box
        _gate_box.draw();

        // Avatar
        _avatar.draw();

        // Doors

        // Gate screen, if needed
        for(size_t i=0; i<_panels.size(); ++i)
            if(intersecting_object(_panels[i]))
                for(size_t i=0; i < _gates_in_hand.size(); ++i)
                    _gates_in_hand[i].draw();

        // Button screen, if needed
        for(size_t i=0; i<_switch_buttons.size(); ++i)
            if(intersecting_object(_switch_buttons[i]))
                _button_screen.draw();

        // Pause screen, if needed
        if(_pause_screen.bool1())
            _pause_screen.draw();

        // Computer screen, if needed
        if(intersecting_object(_computer))
            _computer_screen.draw();

        glFlush();
    }

    // Animates the avatar 
    // Moves the avatar in the specified direction if it
	//  will not intersect an object illegally or walk off the floor
	// Checks if a gate box has been intercepted
	// Calls redisplay
    void GameEngine::attempt_move(int direction)
    {
		// Turn the avatar to face the correct direction
        _avatar.set_int(direction);
		// Animate the avatar
        _avatar.toggle();
		
		// Move avatar in direction if possible
		bool is_allowed = false;
		
        //  Check each floor to see if the avatar will be standing on them
        for(size_t i=0; i<_floors.size(); ++i)
        {
            // Check to see if the avatar would be off the floor
            bool not_past_left = _avatar.left() > _floors[i].left();
            bool not_past_right = _avatar.right() < _floors[i].right();
            bool not_above = _avatar.bottom() < _floors[i].top();
            bool not_below = 
			(_avatar.bottom() + _move_factor) > _floors[i].bottom();
			
            // Make direction-specific checks
            switch(direction)
            {
                case LEFT:
                    not_past_left = 
					(_avatar.left() - _move_factor) > _floors[i].left();
                    break;
					
                case DOWN:
                    not_below =
					_avatar.bottom() > _floors[i].bottom();
                    break;
					
                case RIGHT:
                    not_past_right =
					(_avatar.right() + _move_factor) < _floors[i].right();
                    break;
					
                case UP:
                    not_above =
					(_avatar.bottom() + _move_factor) < _floors[i].top();
                    break;
            }
			
            // If we haven't yet found a floor that works, check this one
            if(!is_allowed)
                is_allowed = not_past_left && not_past_right && not_above &&
				not_below;
        }
		
        //  Check if the avatar would walk through a door
        bool through_door = false;
        for(size_t j=0; j < _doors.size(); ++j)
        {
            switch(direction)
            {
					// Is the avatar's left edge going to be past the door's
					//  right edge?
                case LEFT:
                    through_door =
					(_avatar.left() - _move_factor) <= _doors[j]->right();
                    break;
					// Is the avatar's right edge going to be past the door's
					//  left edge?
                case RIGHT:
                    through_door =
					(_avatar.right() + _move_factor) >= _doors[j]->left();
                    break;
            }
			
            // If the current door is closed, and it is facing the same
            //  direction of the avatar's potential movement, and the avatar 
            //  would be through the door if that move were to be made, 
            //  the avatar is not allowed to make the move.
            if(!_doors[j]->bool1() && _doors[j]->int1() == direction && 
			   through_door)
                is_allowed = false;
        }
		
        // See if avatar has intercepted gate box, if it is visible
        if((_gate_box.bool1()) && (intersecting_object(_gate_box)))
        {
            _gate_box.toggle(); // Make gate box invisible
            cout << endl << "You picked up a gate box." << endl
			<< "Inside is an NOT and an AND gate." << endl;
			
			// Get gates from box
			while(_gates_in_box.size() != 1)
			{
				_gates_in_hand.push_back(_gates_in_box.back());
				_gates_in_box.pop_back();
				
				// Adjust size of the gate screE_WIDTHen -- MOVE THIS TO WHEN THE PLAYER GETS THE BOX
				_gates_in_hand[0].set_pos(0, SPACE_BETWEEN_GATES + ((SPACE_BETWEEN_GATES+GATE_WIDTH) * (_gates_in_hand.size()-1)), 0, WINDOW_HEIGHT/6);
			}
        }
		
		// Tell object to move
        if(is_allowed)
        {
            switch(direction)
            {
                case LEFT:
                    _avatar.move(-_move_factor, 0);
                    break;
                case RIGHT:
                    _avatar.move(_move_factor, 0);
                    break;
                case UP:
                    _avatar.move(0, _move_factor);
                    break;
                case DOWN:
                    _avatar.move(0, -_move_factor);
                    break;
            }
        }
		
		// Call redisplay
        re_display();
    }

    // Keyboard event handler
	// Relevant keys:   left movement
	//					right movement
	//					downward movement
	//					upward movement
	//					display stats
	//					display help
	//					display options
    void GameEngine::key_click(unsigned char key, int x, int y)
    {
		// Left movement
        if(key == _left_char)
        {
            attempt_move(LEFT);
        }
		// Right movement
        else if(key == _right_char)
        {
            attempt_move(RIGHT);
        }
		// Upward movement
        else if(key == _up_char)
        {
            attempt_move(UP);
        }
		// Downward movement
        else if(key == _down_char)
        {
            attempt_move(DOWN);
        }
		// Display stats
        else if(key == _stats_char)
        {
            stats();
        }
		// Display help
        else if(key == _help_char)
        {
            help();
        }
		// Display options
        else if(key == _options_char)
        {
            pause_game();
            options();
            unpause_game();
        }
		// Quit
        else if(key == _quit_char)
        {
            exit(EXIT_SUCCESS);
        }
    }

    // Mouse event handler
    void GameEngine::mouse_click(int button, int state, int x, int y)
    {
		/*
        // The following only works for Room1.sew
        if(intersecting_object(_panels[0]) && (state == GLUT_DOWN))
        {
            for(size_t i=1; i < _gates_in_hand.size(); ++i)
            {

                if(_gates_in_hand[i].bool1() && _gates_in_hand[i].inside(x,y))
                {
                    if(_gates_in_hand[i].id() == NOT)
                    {
                        // Give text feedback
                        cout << endl << "You placed the NOT.  Press the help button to learn more about it." << endl;
                        cout << "This opened the door." << endl;
                        if(!_computer.bool1())
                            cout << "You also turned on the computer." << endl;
                        // Put AND back in inventory if necessary
                        _gates_in_hand[1].set_bool(true);
                        _ands[0].set_bool(false);
                        // Remove NOT from inventory
                        _gates_in_hand[i].toggle();
                        // Place NOT on panel
                        _NOTs[0].toggle();
                        // Charge wires
                        _wires[1].set_int(1);
                        // Open door
                        _doors[0].set_bool(true);
                        // Turn on computer
                        _computer.set_bool(true);
                        // Redisplay
                        re_display();
                    }
                    else if(_gates_in_hand[i].id() == AND)
                    {
                        // Give textual feedback
                        cout << endl << "You placed the AND gate.  Press the help button to learn more about it." << endl;
                        if(_doors[0].bool1())
                            cout << "This closed the door." << endl;
                        // Put NOT back in inventory if necessary
                        _gates_in_hand[2].set_bool(true);
                        _NOTs[0].set_bool(false);
                        // Remove AND from inventory
                        _gates_in_hand[i].toggle();
                        // Place AND on panel
                        _ands[0].toggle();
                        // Charge wire
                        _wires[1].set_int(0);
                        // Close door
                        _doors[0].set_bool(false);
                        // Redisplay
                        re_display();
                    }
                }
            }
            if(_panels[0].inside(x,y))
            {
                // Remove NOT from panel
                if(_NOTs[0].bool1())
                {
                    _NOTs[0].set_bool(false);
                    _gates_in_hand[2].set_bool(true);
                    cout << endl << "You removed the NOT." << endl;
                    cout << "This closed the door." << endl;
                    _wires[1].set_int(0);
                    _doors[0].toggle();
                }
                // Remove AND gate from panel
                if(_ands[0].bool1())
                { 
                    _ands[0].set_bool(false);
                    _gates_in_hand[0].set_bool(true);
                    // Give textual feedback
                    cout << endl << "You removed the AND gate." << endl;
                }
                // Redisplay
                re_display();
            }

        }

        if((intersecting_object(_computer) && (state == GLUT_DOWN)) &&
                _computer.bool1() && _computer_screen.inside(x,y))
        {
            truth_table();
        }

        // End part that only works for Room1.sew
		 */
/*
        // Check for switch button
        int index = -1;
        for(size_t i=0; i < _switch_buttons.size(); ++i)
            if(intersecting_object(_switch_buttons[i]))
                index = _switch_buttons[i].int1();

        if((index != -1) && (state == GLUT_DOWN) && 
                (_button_screen.inside(x,y)))
        {
            // Change the value of the corresponding switch,
			//  this assumes the switch is at position 0.
			int oldval = _circuits[index].switch_charge();
			int newval = _circuits[index].invert_charge(oldval);
			_circuits[index].update(0,newval);

			// Print status message
            cout << endl << "Switch value changed to " << _circuits[index].switch_charge() << endl;

            re_display();
        }
    }

    // Returns true iff the avatar is currently on top of or under the object
    bool GameEngine::intersecting_object(SewersObject obj)
    {
        return ((((_avatar.left() <= obj.right()) &&
                        (_avatar.right() >= obj.left()) &&
                        (_avatar.top() >= obj.bottom()) &&
                        (_avatar.bottom() <= obj.top())) &&
                    (obj.bool1())));
    }

    // Returns true iff the avatar is currently touching an object
    bool GameEngine::touching_object(SewersObject obj)
    {
        return (((_avatar.left() <= obj.right() + _move_factor) &&
                    (_avatar.right() >= obj.left() - _move_factor) &&
                    (_avatar.bottom() <= obj.top() + _move_factor) &&
                    (_avatar.top() >= obj.bottom())));
    }	

    // Prompts the user to enter values of a truth table for NOTs
    void GameEngine::truth_table()
    {
        pause_game();

        int first_val, second_val;
        cout << endl << "Enter the correct values (0 or 1) in the following truth table to generate" << endl << "a blueprint:" << endl;
        cout << "P | ~P" << endl;
        cout << "------" << endl;
        cout << "0 | ";
        cin >> first_val;
        cout << "1 | ";
        cin >> second_val;

        if(first_val == 1 && second_val == 0)
        {
            cout << endl << "Truth table correct.  Collected blueprint!" << endl;
            _blueprints++;
            cout << "Blueprints collected so far: " << _blueprints << endl;
        }
        else
        {
            cout << endl << "Truth table incorrect." << endl;
        }

        unpause_game();
    }

    void GameEngine::pause_game()
    {
        _pause_screen.set_bool(true);
        re_display();
    }

    void GameEngine::unpause_game()
    {
        _pause_screen.set_bool(false);
        re_display();
    }

    // Removes the gate on the main screen and displays all gates on the
    //  gate screen
    void GameEngine::hide_gate()
    {
        for(size_t j=1; j < _gates_in_hand.size(); ++j)
            if(!_gates_in_hand[j].bool1())
            {
                string gate_id = _gates_in_hand[j].id();
                _gates_in_hand[j].toggle();
                for(size_t k=0; k < _NOTs.size(); ++k)
                    if(_NOTs[k].id() == gate_id)
                        _NOTs[k].toggle();
                for(size_t k=0; k < _ands.size(); ++k)
                    if(_ands[k].id() == gate_id)
                        _ands[k].toggle();
                for(size_t k=0; k < _ors.size(); ++k)
                    if(_ors[k].id() == gate_id)
                        _ors[k].toggle();
            }
    }

    // Display game stats on standard out
    void GameEngine::stats()
    {
        cout << endl << "STATS:" << endl << "Rooms completed: " 
             << _rooms_completed << endl << "Rooms left: " << _rooms_left 
             << endl << "Blueprints collected: " << _blueprints << endl;
    }

    // Display any current relevant help information
    void GameEngine::help()
    {
        bool touching_nothing = true;
        if(touching_object(_panels[0]) && (!_NOTs[0].bool1()) && 
                (!_ands[0].bool1()))
        {
            touching_nothing = false;
            cout << endl << "This is a panel." << endl;
            cout << "Place a gate on this panel to change the wire running through it." << endl;
        }
        for(size_t i=0; i<_doors.size(); ++i)
        {
            if(touching_object(*_doors[i]))
            {
                touching_nothing = false;
                cout << endl << "This is a door." << endl;
                if(_doors[i]->bool1())
                {
                    cout << "It is open." << endl;
                }
                else
                {
                    cout << "It is closed." << endl;
                    cout << "To open the door, the wire running into it must have a value of 1." << endl;
                }
            }
        }
        for(size_t i=0; i<_switches.size(); ++i)
        {
            if(touching_object(_switches[i]))
            {
                touching_nothing = false;
                cout << endl << "This is a switch." << endl;
                cout << "It outputs a charge, either 0 or 1." << endl;
                cout << "This particular switch has charge " << _switches[i].int1() << "." << endl;
            }
        }
        for(size_t i=0; i<_switch_buttons.size(); ++i)
        {
            if(touching_object(_switch_buttons[i]))
            {
                touching_nothing = false;
                cout << endl << "This is a switch button" << endl;
                cout << "If you click the button in the bottom-left corner of the screen," << endl;
                cout << "it flips the value of the switch next to the button." << endl;
            }
        }
        for(size_t i=0; i<_NOTs.size(); ++i)
        {
            if(_NOTs[i].bool1() && intersecting_object(_NOTs[i]))
            {
                touching_nothing = false;
                cout << endl << "This is an NOT." << endl;
                cout << "The symbols that can represent it are: ~ , ! , NOT" << endl;
                cout << "The output of an NOT is the negation of its input." << endl;
            }
        }
        for(size_t i=0; i<_ands.size(); ++i)
        {
            if(_ands[i].bool1() && intersecting_object(_ands[i]))
            {
                touching_nothing = false;
                cout << endl << "This is an AND Gate." << endl;
                cout << "The symbols that can represent it are: AND , ^" << endl;
                cout << "The output of an AND gate is the conjunction of its inputs." << endl;
            }
        }
        for(size_t i=0; i<_ors.size(); ++i)
        {
            if(_ors[i].bool1() && intersecting_object(_ors[i]))
            {
                touching_nothing = false;
                cout << endl << "This is an OR Gate." << endl;
                cout << "The symbols that can represent it are: + , OR" << endl;
                cout << "The output of an OR gate is the disjunction of its inputs." << endl;
            }
        }
        if(touching_object(_ladder))
        {
            touching_nothing = false;
            cout << endl << "You are standing next to the ladder from which you entered the sewer." << endl;
        }

        if(touching_nothing)
            cout << endl << "Still in the sewer.  It looks like a sewer." << endl;
    }

    // Display the options screen, allow the player to choose different options.
    void GameEngine::options()
    {
        string input;
        cout << endl << "OPTIONS" << endl;
        cout << "\t1 - Change keyboard commands" << endl;
        cout << "\t2 - Adjust avatar speed" << endl;
        cout << "Choice: ";
        cin >> input;

        if(input == "1")
        {
            char oldkey;
            char newkey;
            cout << endl << "Enter old key: ";
            cin >> oldkey;

            if(oldkey == _left_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _left_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }
            else if(oldkey == _right_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _right_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }
            else if(oldkey == _up_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _up_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }			
            else if(oldkey == _down_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _down_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }
            else if(oldkey == _help_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _help_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }			
            else if(oldkey == _stats_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _stats_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }		
            else if(oldkey == _options_char)
            {
                cout << "Enter new key: ";
                cin >> newkey;
                if((newkey == _left_char) || (newkey == _right_char) || (newkey == _up_char) || 
                        (newkey == _down_char) || (newkey == _help_char) || 
                        (newkey == _stats_char) || (newkey == _options_char) || (newkey == _quit_char))
                {
                    cout << "That key is already in use." << endl;
                }
                else
                {
                    _options_char = newkey;
                    cout << "Key changed from '" << oldkey << "' to '" << newkey << "'." << endl;
                }
            }
            else
            {
                cout << "Key '" << oldkey << "' is not currently in use." << endl;
            }
        }
        else if(input == "2")
        {
            cout << endl << "Current movement speed: " << _move_factor << " pixels per button click" << endl;
            cout << "New speed (pixels per button click): ";
            cin >> _move_factor;
        }
    }
	
	// When reading an input file, read in any number of LINE_BEGINs.
	// LINE_BEGIN is a string used to denote the beginning of a line in an input file.
	// This allows error messages to specify the line in the input file at which the
	//  error occurs.
	void GameEngine::load_line_numbers()
	{
		while(_current_object == LINE_BEGIN)
		{
			++_line_num;
			_ifs >> _current_object;
		}
	}
	
	void GameEngine::load_avatar()
	{
		if(_current_object != "AVATAR")
		{
			load_fail("AVATAR");
		}
		
		int left, bottom, direction;
		string facing;
		_ifs >> left >> bottom >> facing;
		if(facing == "LEFT")
			direction = LEFT;
		else if(facing == "RIGHT")
			direction = RIGHT;
		else if(facing == "DOWN")
			direction = DOWN;
		else
			direction = UP;
		_avatar = SewersObject("AVATAR", left, left+AVATAR_WIDTH, bottom, bottom+AVATAR_HEIGHT, direction, _animation_frame);
	}
	
	// Load the circuit's door, intermediate objects, and switch
	void GameEngine::load_circuit()
	{
		if(_current_object != "CIRCUIT")
		{
			load_fail("CIRCUIT");
		}
		
		_circuits.push_back(Circuit());
		
		_ifs >> _current_object;
		load_line_numbers();
		load_door();
	}
	
	void GameEngine::load_door()
	{
		if(_current_object != "DOOR")
		{
			load_fail("DOOR");
		}
			
		int left, bottom, position;
		string pos;
		_ifs >> bottom >> pos;
		
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
		
		_circuits.back().add_object(SewersObject("DOOR", left, left+DOOR_WIDTH, bottom, bottom+DOOR_HEIGHT, position, false));								
	}
	
	void GameEngine::load_gate()
	{
		if(_current_object != "NOT" && _current_object != "AND" && _current_object != "OR" &&
		  _current_object != "PANEL")
		{
			load_fail("NOT, AND, OR, or PANEL");
		}
		
		// Load drawing coordinates
		int left, bottom;
		_ifs >> left >> bottom;

		int num_inputs;
		// NOTs have 1 input
		if(_current_object == "NOT")
			num_inputs = 1;
		else
			_ifs >> num_inputs;
				
		// Load input circuits
		for(size_t i = 0; i < num_inputs; ++i)
		{
			_ifs >> _current_object;
			load_line_numbers();
			load_input_circuit();
		}			
		
		_circuits.back().add_object(SewersObject(_current_object, left, left+GATE_WIDTH, bottom, bottom+GATE_HEIGHT, -1, VISIBLE));
	}
	
	void GameEngine::load_input_circuit()
	{
		if(_current_object != "INPUT_BEGIN")
		{
			load_fail("INPUT_BEGIN");
		}
		
		while(_current_object != "SWITCH")
		{
			_ifs >> _current_object;
			load_line_numbers();
			load_gate();
		}
		
		_ifs >> _current_object;
		load_line_numbers();
		load_switch();
		load_switch_button();
		
		if(_current_object != "INPUT_END")
		{
			load_fail("INPUT_END");
		}
	}
	
	void GameEngine::load_switch()
	{
		if(_current_object != "SWITCH")
		{
			load_fail("SWITCH");
		}
		
		int left, bottom, val;
		_ifs >> left >> bottom >> val;
		_circuits.back().add_object(SewersObject(_current_object, left, 
													left+SWITCH_WIDTH, bottom, 
													bottom+SWITCH_HEIGHT, val, 
													false));
	}
	
	void GameEngine::load_switch_button()
	{
		if(_current_object == "SWITCH_BUTTON")
		{
			int left, bottom;
			_ifs >> left >> bottom;
			
			_switch_buttons.push_back(SewersObject(_current_object, left, 
												   left+SWITCH_BUTTON_WIDTH, 
												   bottom, 
												   bottom+SWITCH_BUTTON_HEIGHT, 
												   _circuits.size()-1, false));							
		}
	}
	
	void GameEngine::load_fail(string expected_obj)
	{
		cerr << "Fatal error loading room file " << _filename;
		cerr << endl << "File not properly formatted:" << endl;
		cerr << "Line " << _line_num << ": Expected " << expected_obj;
		cerr << " but got " << _current_object << endl;
		exit(EXIT_FAILURE);
	}
		
    void GameEngine::load_file(string filename)
    {
		_filename = filename;
		_line_num = 0;
		
		// Open the file for loading
        _ifs.open(_filename.c_str());
        if(!_ifs)
        {
            cerr << "Fatal error loading room file " << _filename << endl;
            exit(EXIT_FAILURE);
        }
     
		_ifs >> _current_object;
		load_line_numbers();
		load_avatar();
				
		_ifs >> _current_object;
		load_line_numbers();
		load_circuit();
				
		while(_ifs >> _current_object)
		{			
			if(_current_object == "LADDER")
			{
				int left, bottom;
				_ifs >> left >> bottom;
				_ladder = SewersObject("LADDER", left, left+LADDER_WIDTH, bottom, bottom+LADDER_HEIGHT, -1, false);
			}
			else if(_current_object == "FLOOR")
			{
				int left, right, bottom, top;
				_ifs >> left >> right >> bottom >> top;
				_floors.push_back(SewersObject("FLOOR", left, right, bottom, top, -1, false));
			}
			else if(_current_object == "GATE_BOX")
			{
				int left, bottom;
				_ifs >> left >> bottom;
				_gate_box = SewersObject("GATE_BOX", left, left+GATE_BOX_WIDTH, bottom, bottom+GATE_BOX_HEIGHT, -1, VISIBLE);
			}
			else if(_current_object == "COMPUTER")
			{
				int left, bottom;
				_ifs >> left >> bottom;
				_computer = SewersObject("COMPUTER", left, left+COMPUTER_WIDTH, bottom, bottom+COMPUTER_HEIGHT, -1, false);
			}
		}
	}
}
*/