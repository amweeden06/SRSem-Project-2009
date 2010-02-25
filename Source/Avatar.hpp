/*  Avatar.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Object.hpp"

namespace Sewers
{
	/* Avatar -- player-controlled object ("Bitty")
	 *        -- functions to draw and animate
	 */
	class Avatar : public Object
	{
	public:
		// CONSTRUCTORS
		Avatar();
		Avatar(const Avatar&);
        // ACCESSORS
        string direction() const { return _direction; }
        bool animation_frame() const { return _animation_frame; }
        // MUTATORS
        void set_direction(const string direction) { _direction = direction; }
        void set_animation_frame(bool a) { _animation_frame = a; }
        // METHODS
        void draw() const;
		void help() const;
    private:
        string _direction; // Direction the avatar is facing
        bool _animation_frame; // toggled to animate the avatar
    };
	
    ostream& operator << (ostream&, const Avatar&);
}
