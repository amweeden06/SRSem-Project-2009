/*
 *
 */
#include "GameScreen.hpp"

namespace Sewers
{
	GameScreen::GameScreen(string type)
	{
		set_type(type);
		set_left(0);
		set_bottom(0);
		set_width(0);
		set_height(0);
	}
	
	GameScreen::GameScreen(const GameScreen& g)
	{
		set_type(g.type());
		set_left(g.left());
		set_bottom(g.bottom());
		set_width(g.width());
		set_height(g.height());
	}
	
	// PRECONDITIONS: none
    // POSTCONDITION: The screen has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void GameScreen::draw() const
	{
		SCREEN_COLOR.glColor();
		glRectf(left(), bottom(), right(), top());
		if(type() == "BUTTON_SCREEN")
		{
            // Draw button
            GLcolor3(0.2, 0.0, 0.0).glColor();
            glRectf(left() + width()/2 - width()/2, bottom() + height()/2 - BUTTON_HEIGHT/2,
                    left() + width()/2 + BUTTON_WIDTH/2, bottom() + height()/2 + BUTTON_HEIGHT/2);
            GLred3.glColor();
            glRectf(left() + width()/2 - BUTTON_WIDTH/4, bottom() + height()/2 - BUTTON_HEIGHT/4,
                    left() + width()/2 + BUTTON_WIDTH/4, bottom() + height()/2 + BUTTON_HEIGHT/4);			
		}
    }	
	
    ostream& operator << ( ostream& outs, const GameScreen& g )
    {
        outs << g.type() << endl;
        outs << "\tleft: " << g.left() << endl;
        outs << "\tbottom: " << g.bottom() << endl;
        outs << "\twidth: " << g.width() << endl;
        outs << "\theight: " << g.height() << endl;
        return outs;
    }
}
