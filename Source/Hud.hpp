/*  Hud.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 *
 *  CLASS INVARIANTS:
 *
 */
#include "HudButtons.hpp"
#include "HudPuzzle.hpp"

namespace Sewers
{	
	class Hud : public DrawingObject
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
		HudButtons _hud_buttons;
		HudPuzzle _hud_puzzle;
    };
}
