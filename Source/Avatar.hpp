/*  Avatar.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{
	/* Drawing constants */
	const GLcolor3 BITTY_HEAD_COLOR = GLgreen3;
	const GLcolor3 BITTY_TORSO_COLOR = GLblue3;
	const GLcolor3 LOGICIAN_HEAD_COLOR = GLyellow3;
	const GLcolor3 LOGICIAN_TORSO_COLOR = GLred3;
	const GLcolor3 AVATAR_HEAD_COLOR = GLcyan3;
	const GLcolor3 AVATAR_TORSO_COLOR = GLmagenta3;
	const GLcolor3 AVATAR_EYE_COLOR = GLblack3;
	const GLcolor3 AVATAR_SHOE_COLOR = GLblack3;	
	
	/* Avatar -- In-game character
	 *        -- functions to draw and animate
	 */
	class Avatar : public DrawingObject
	{		
	public:
		// CONSTRUCTORS
		Avatar(string type = "AVATAR");
		Avatar(const Avatar&);
        // ACCESSORS
		string dialogue() const { return _dialogue; }
        string direction() const { return _direction; }
        bool animation_frame() const { return _animation_frame; }
        // MUTATORS
		void set_dialogue(string d) { _dialogue = d; }
		void set_direction(string direction) { _direction = direction; }
        void set_animation_frame(bool a) { _animation_frame = a; }
        // METHODS
        void draw() const;
		void help() const;
    private:
		string _dialogue; // What a non-player character says to the player
        string _direction; // Direction the avatar is facing
        bool _animation_frame; // toggled to animate the avatar
    };
	
    ostream& operator << (ostream&, const Avatar&);
}
