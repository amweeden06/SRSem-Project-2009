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
            glRectf(left() + width()/2 - BUTTON_WIDTH/2, bottom() + height()/2 - BUTTON_HEIGHT/2,
                    left() + width()/2 + BUTTON_WIDTH/2, bottom() + height()/2 + BUTTON_HEIGHT/2);
            GLred3.glColor();
            glRectf(left() + width()/2 - BUTTON_WIDTH/4, bottom() + height()/2 - BUTTON_HEIGHT/4,
                    left() + width()/2 + BUTTON_WIDTH/4, bottom() + height()/2 + BUTTON_HEIGHT/4);			
		}
		else if(type() == "COMPUTER_SCREEN")
		{
			GLint computer_left = left() + width()/2 - COMPUTER_WIDTH/2;
			GLint computer_right = computer_left + COMPUTER_WIDTH;
			GLint computer_bottom = bottom() + height()/2 - COMPUTER_HEIGHT/2;
			GLint computer_top = computer_bottom + COMPUTER_HEIGHT;
			
			// Draw computer
			GLcolor3(0.4,0.4,0.4).glColor();
			glRectf(computer_left, computer_bottom, 
					computer_right, computer_top);
			// Screen
			GLgreen3.glColor();
			glRectf(computer_left + COMPUTER_WIDTH/6, 
					computer_bottom + COMPUTER_HEIGHT/3, 
					computer_right - COMPUTER_WIDTH/6, 
					computer_top - COMPUTER_HEIGHT/6);
			// Buttons
			GLred3.glColor();
			glRectf(computer_left + COMPUTER_WIDTH/6, 
					computer_bottom + COMPUTER_HEIGHT/8, 
					computer_left + COMPUTER_WIDTH/3, 
					computer_bottom + COMPUTER_HEIGHT/5);
			GLyellow3.glColor();
			glRectf(computer_right - COMPUTER_WIDTH/3, 
					computer_bottom + COMPUTER_HEIGHT/8, 
					computer_right - COMPUTER_WIDTH/6, 
					computer_bottom + COMPUTER_HEIGHT/5);			
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
