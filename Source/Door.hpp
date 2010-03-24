/*  Door.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, 2009-2010
 */
#include "DrawingObject.hpp"

namespace Sewers
{
	const GLcolor3 DOOR_COLOR = GLgreen3;
	
	/* Door
	 */
	class Door : public DrawingObject
	{
	public:
		// CONSTRUCTORS
		Door(string type = "");
		Door(const Door&);
		// ACCESSORS
		bool is_open() const { return _is_open; }
		// MUTATORS
		void set_is_open(bool b) { _is_open = b; }
		// METHODS
        void draw() const;
	private:
		bool _is_open;
	};
	
	// OPERATORS
    ostream& operator << (ostream&, const Door&);
}
