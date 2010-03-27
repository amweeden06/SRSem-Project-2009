/*  HudButtons.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "DrawingObject.hpp"
#include "Button.hpp"

namespace Sewers
{		
	class HudButtons : public DrawingObject
	{
	public:
		/* CONSTRUCTOR */
		HudButtons();
		/* ACCESSORS */
		Button stats_button() const { return _stats_button; }
		Button save_button() const { return _save_button; }
		Button load_button() const { return _load_button; }
		Button quit_button() const { return _quit_button; }
		/* FUNCTIONS */
        int draw() const;
	private:
		Button _stats_button, _save_button, _load_button, _quit_button;
    };
}