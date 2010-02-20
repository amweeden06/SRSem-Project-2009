/*  GameScreen.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "Object.hpp"

namespace Sewers
{
	/* Game Screen -- appears during specific game situations
	 *             -- method to draw
	 */
	class GameScreen : public Object
	{
	public:
		// CONSTRUCTORS
		GameScreen(const string type = "");
		GameScreen(const GameScreen&);
		// ACCESSORS
        // MUTATORS
        // METHODS
        void draw() const;
    private:
    };
	
    ostream& operator << (ostream&, const GameScreen&);
}
