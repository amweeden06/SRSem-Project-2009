/*  GameEngine.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, 2009-2010
 */
#include "Avatar.hpp"
#include "Computer.hpp"
#include "Entrance.hpp"
#include "Exit.hpp"
#include "GameScreen.hpp"

namespace Sewers
{
	/* Game Engine -- holds information about the game's current room.
	 *             -- also holds information about the game interface,
	 *             -- including how to load objects from files,
	 *             -- as well as how to draw the current room.
	 */
	class GameEngine
		{
		public:
			// CONSTRUCTORS
			GameEngine(string rooms_file = "Room1.sew");
			// ACCESSORS
			string rooms_file() const { return _rooms_file; }
			size_t num_switches() const { return _num_switches; }
			size_t num_gates() const { return _num_gates; }
            unsigned char left_key() const { return _left_key; }
            unsigned char right_key() const { return _right_key; }
            unsigned char down_key() const { return _down_key; }
            unsigned char up_key() const { return _up_key; }
			unsigned char action_key() const { return _action_key; }
            unsigned char quit_key() const { return _quit_key; }
            // MUTATORS
			void set_rooms_file(const string rooms_file) { _rooms_file = rooms_file; }
            void set_left_key(const unsigned char key) { _left_key = key; }
            void set_right_key(const unsigned char key) { _right_key = key; }
            void set_down_key(const unsigned char key) { _down_key = key; }
            void set_up_key(const unsigned char key) { _up_key = key; }
			void set_action_key(const unsigned char key) { _action_key = key; }
            void set_quit_key(const unsigned char key) { _quit_key = key; }
			// METHODS
			void init_glut(int& argc, char** argv);
			void load_circuit(const string filename);
			// GLUT WRAPPERS
			void draw() const;
            void key_click(const unsigned char key, const int x, const int y);
			void print_truth_table() const;
		private:
			// Room information
			int _current_room; // ID of the current room
			string _rooms_file; // Filename of the rooms file
			// Object List
			Avatar _avatar;
			Computer _computer;
			Entrance _entrance;
			CircuitObject _exit;
			CircuitObject _switches[MAX_NUM_SWITCHES];
			size_t _num_switches;
			CircuitObject _gates[MAX_NUM_GATES];
			size_t _num_gates;
			GameScreen _button_screen;
			GameScreen _computer_screen;
            // Keyboard event list
            unsigned char _left_key, _right_key, _down_key, _up_key, _action_key, _quit_key;
            // PRIVATE MEMBER FUNCTIONS
            void attempt_avatar_move(const string direction);
			void connect_object(CircuitObject& input);
			void prepare_circuit_drawing(CircuitObject&, int, int, int&, int&);
			void draw_circuit(const CircuitObject&) const;
			void print_truth_table_result(const CircuitObject&, char&) const;
		};
}
