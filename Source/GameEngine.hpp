/*  GameEngine.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, 2009-2010
 */
#include "Avatar.hpp"
#include "Computer.hpp"
#include "Entrance.hpp"
#include "GameScreen.hpp"
#include "CircuitObject.hpp"

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
			GameEngine();
			// ACCESSORS
			size_t num_steps() const { return _num_steps; }
			size_t num_rooms() const { return _room_files.size(); }
			size_t blueprints_collected() const { return _blueprints_collected; }
			size_t current_room_index() const { return _current_room_index; }
			string current_room() const;
			bool already_solved() const { return _already_solved; }
			size_t num_switches() const;
			size_t num_gates() const;
            unsigned char left_key() const { return _left_key; }
            unsigned char right_key() const { return _right_key; }
            unsigned char down_key() const { return _down_key; }
            unsigned char up_key() const { return _up_key; }
			unsigned char action_key() const { return _action_key; }
			unsigned char help_key() const { return _help_key; }
			unsigned char stats_key() const { return _stats_key; }
			unsigned char options_key() const { return _options_key; }
			unsigned char save_key() const { return _save_key; }
			unsigned char load_key() const { return _load_key; }
            unsigned char quit_key() const { return _quit_key; }
            // MUTATORS
			void set_num_steps(size_t num_steps) { _num_steps = num_steps; }
			void set_blueprints_collected(size_t b) { _blueprints_collected = b; }
			void set_current_room_index(size_t i);
			void set_already_solved(bool b) { _already_solved = b; }
            void set_left_key(unsigned char key) { _left_key = key; }
            void set_right_key(unsigned char key) { _right_key = key; }
            void set_down_key(unsigned char key) { _down_key = key; }
            void set_up_key(unsigned char key) { _up_key = key; }
			void set_action_key(unsigned char key) { _action_key = key; }
			void set_help_key(unsigned char key) { _help_key = key; }
			void set_stats_key(unsigned char key) { _stats_key = key; }
			void set_options_key(unsigned char key) { _options_key = key; }
			void set_save_key(unsigned char key) { _save_key = key; }
			void set_load_key(unsigned char key) { _load_key = key; }
            void set_quit_key(unsigned char key) { _quit_key = key; }
			// METHODS
			void init_glut(int& argc, char** argv);
			void load_room_filenames(string rooms_file);
			void load_circuit();
			void save_game() const;
			void load_game();
			void help() const;
			void print_stats() const;
			void list_solutions() const;
			void change_key();
			// GLUT WRAPPERS
			void draw() const;
            void key_click(unsigned char key, int x, int y);
		private:
			// Data collection
			size_t _num_steps; // Number of steps user has taken in this room
			size_t _blueprints_collected; // Number of blueprints the user has collected
			// Room information
			vector<string> _room_files;  // Ordered list of files from which to load circuits
			size_t _current_room_index; // Index of the current room
			bool _already_solved; // True if the avatar has just entered from the entrance of the next room
			string _solutions[MAX_NUM_SOLUTIONS];
			// Object List
			Avatar _avatar;
			Computer _computer;
			Entrance _entrance;
			CircuitObject _exit;
			CircuitObject _switches[MAX_NUM_SWITCHES+1];
			CircuitObject _gates[MAX_NUM_GATES+1];
			GameScreen _button_screen;
			GameScreen _computer_screen;
            // Keyboard event list
            unsigned char _left_key, _right_key, _down_key, _up_key;
			unsigned char _action_key, _help_key, _stats_key, _options_key;
			unsigned char _save_key, _load_key, _quit_key;
            // PRIVATE MEMBER FUNCTIONS
            void _attempt_avatar_move(string direction);
			void _connect_object(CircuitObject& input);
			void _set_circuit_obj_coords();
			void _prepare_circuit_drawing(CircuitObject&, int, int, int&, int&);
			void _determine_solutions() const;
			void _draw_circuit(const CircuitObject&) const;
		};
}
