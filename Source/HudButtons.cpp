#include "HudButtons.hpp"

namespace Sewers
{	
	/* CONSTRUCTOR */
	HudButtons::HudButtons()
	{
		_stats_button.set_type("STATS_BUTTON");
		_save_button.set_type("SAVE_BUTTON");
		_load_button.set_type("LOAD_BUTTON");
		_quit_button.set_type("QUIT_BUTTON");
	}
	
	/* FUNCTION: draw()
	 * PRECONDITIONS: none
	 * POSTCONDITION: The HUD has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * RETURN VALUE: SUCCESS
	 */
	int HudButtons::draw() const
	{
		_stats_button.draw();
		_save_button.draw();
		_load_button.draw();
		_quit_button.draw();
		
		return SUCCESS;
    }	
}
