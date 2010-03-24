/*  Entrance.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Object.hpp"

namespace Sewers
{	
	/* Drawing colors */
	const GLcolor3 LADDER_COLOR = GLwhite3;
	
	/* Entrance -- in-game object
	 *          -- appears on the left side of the screen
	 *          -- either a ladder (first room) or an
	 *                open door (all other rooms)
	 */
	class Entrance : public Object
	{
	public:
		// CONSTRUCTORS
		Entrance();
		Entrance(const Entrance&);
        // ACCESSORS
        bool is_ladder() const { return _is_ladder; }
		// MUTATORS
		void set_as_ladder() { _is_ladder = true; }
		void set_as_door() { _is_ladder = false; }
        // METHODS
        void draw() const;
		void help() const;
    private:
        bool _is_ladder;
    };
	
    ostream& operator << (ostream&, const Entrance&);
}
