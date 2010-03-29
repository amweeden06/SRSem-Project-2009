/*  ManufacturersRoom.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 *
 *  CLASS INVARIANTS:
 *
 */
#include "Room.hpp"
#include "Avatar.hpp"
#include "Workbench.hpp"
#include "BlueprintScreen.hpp"

namespace Sewers
{	
	class ManufacturersRoom : public Room
	{
	public:
		/* ACCESSORS */
		/* FUNCTIONS */
        int draw() const;
	private:
		Avatar _manufacturer;
		Workbench _workbench;
		BlueprintScreen _blueprint_screen;
    };
}