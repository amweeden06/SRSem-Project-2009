/*
 *  GameEngine.hpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009.
 *
 */
/*#include "Circuit.hpp"

namespace SewersOld
{
    class GameEngine
    {
	public:
		GameEngine();
		// Load a room from a file
		void load_file(string filename);
		void load_line_numbers();
		void load_avatar();
		void load_circuit();
		void load_door();
		void load_gate();
		void load_input_circuit();
		void load_switch();
		void load_switch_button();
		void load_fail(string expected_obj);
		// Initialize drawing
		void init_glut(int& argc, char** argv);	
		// Check for collision (walking over object)
		bool intersecting_object(SewersObject obj); 
		// Check for collision (next to object)
		bool touching_object(SewersObject obj);	
		// Check if avatar can move in a direction
		void attempt_move(int direction);
		// Swap gate off of main screen
		void hide_gate();
		void stats(); 
		void help(); 
		void options();
		void truth_table();
		void pause_game();
		void unpause_game();
		// GLUT wrappers
		void re_display(void);	// Draw everything in the current room
		void key_click(unsigned char key, int x, int y);
		void mouse_click(int button, int state, int x, int y);
	private:
		SewersObject _avatar; // The avatar object
		SewersObject _ladder; // A ladder
		SewersObject _table_screen;	// The table screen, shows a truth table
		SewersObject _button_screen; // Shows a button to click
		SewersObject _computer_screen; // Shows a comptuter to click
		SewersObject _pause_screen;	// Indicates whether the game is paused
		SewersObject _gate_box; // A box of gates for the avatar to pick up
		SewersObject _computer;     // A computer terminal
		vector <SewersObject*> _doors;	// Each of the doors (which are in the circuit class)
		vector <SewersObject> _floors;	// Each of the floors
		vector <SewersObject> _panels;	// Each of the panels
		vector <SewersObject> _switches; // Each of the switches
		vector <SewersObject> _switch_buttons; // Control switches
		vector <SewersObject> _wires;		// Each of the wires
		vector <SewersObject> _NOTs;	// Each of the NOTs
		vector <SewersObject> _ands;		// Each of the AND gates
		vector <SewersObject> _ors;			// Each of the OR gates
		vector <Circuit> _circuits;			// Each of the circuits
		int _avatar_facing;	// Direction the avatar is currently facing
		bool _animation_frame;		// 2 possible frames of animation
		// The gates the player owns and their display screen
		vector <SewersObject> _gates_in_hand; 
		// The gates a player can pick up via the box
		vector <SewersObject> _gates_in_box;
		int _rooms_completed, _rooms_left, _blueprints; // Game statistics
		// Changeable settings
		int _move_factor;
		char _left_char, _right_char, _up_char, _down_char, _help_char, _stats_char, _options_char, _quit_char;
		// For loading files
		string _filename;
		ifstream _ifs;
		string _current_object;
		int _line_num;
	};
}


*/