/*  Avatar.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{	
	/* CONSTANTS FOR DRAWING */
	const GLcolor3 HEAD_COLOR = GLblue3;
	const GLcolor3 EYE_COLOR = GLblack3;
	const GLcolor3 SHOE_COLOR = GLblack3;
	
	class Avatar : public DrawingObject
	{		
	public:
        /* ACCESSORS */
        string direction() const { return _direction; }
        bool animation_frame() const { return _animation_frame; }
        /* MUTATORS */
		void set_direction(string direction) { _direction = direction; }
        void set_animation_frame(bool a) { _animation_frame = a; }
        /* DRAWING METHOD */
        int draw(GLcolor3) const;
	private:
		string _direction; /* Direction in which the avatar is currently facing */
		bool _animation_frame; /* 2-frame animator */
    };
}
