/*
 *  Player.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 10/25/09.
 *
 *  Graphical player object.  Represents the player's avatar.
 */
#include "Player.hpp"
#include <iostream>

using namespace std;

namespace Sewers
{		
	const GLint MOVE_FACTOR = 7;
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 440;
	
	void Player::move_left()
	{
		_facing_left = true;
		_facing_right = _facing_down = _facing_up = false;
		if( ( viewport().left() - MOVE_FACTOR ) >= 0 )
			reMap(IntRect(viewport().left() - MOVE_FACTOR, viewport().right() - MOVE_FACTOR, viewport().bottom(), viewport().top()));
		
		_animation_frame = !_animation_frame; // Animate the player
	}
	void Player::move_right()
	{
		_facing_right = true;
		_facing_left = _facing_down = _facing_up = false;
		if( ( viewport().right() + MOVE_FACTOR ) < WINDOW_WIDTH )
			reMap(IntRect(viewport().left() + MOVE_FACTOR, viewport().right() + MOVE_FACTOR, viewport().bottom(), viewport().top()));
		
		_animation_frame = !_animation_frame; // Animate the player
	}
	void Player::move_down()
	{
		_facing_down = true;
		_facing_left = _facing_right = _facing_up = false;
		if( ( viewport().bottom() - MOVE_FACTOR ) >= 0 )
			 reMap(IntRect(viewport().left(), viewport().right(), viewport().bottom() - MOVE_FACTOR, viewport().top() - MOVE_FACTOR));
		
		_animation_frame = !_animation_frame; // Animate the player
	}
	void Player::move_up()
	{
		_facing_up = true;
		_facing_left = _facing_right = _facing_down = false;
		if( ( viewport().top() + MOVE_FACTOR ) < WINDOW_HEIGHT )
			reMap(IntRect(viewport().left(), viewport().right(), viewport().bottom() + MOVE_FACTOR, viewport().top() + MOVE_FACTOR));
		
		// Check if the player is in front of the panel
		else if( ( ( viewport().right() > 500 ) && ( viewport().left() < 520 ) ) ||
		    ( ( viewport().left() > 500 ) && ( viewport().left() < 520 ) ) )
		{
			cout << "Panel activated." << endl;
		}
		
		_animation_frame = !_animation_frame; // Animate the player
	}
	
	void Player::re_display(void)
	{
		// For testing only
		set_skin_color(GLgreen3);
		set_shirt_color(GLblue3);
		set_shoe_color(GLblack3);
		// End testing
		
		glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT);
		initDraw();
		draw_head();
		draw_torso();
		draw_arms();
		draw_feet();
		glPopAttrib();
	}
	
	void Player::draw_head()
	{
		_skin_color.glColor();
		glRectf(world().left(),					// Left
				world().top(),					// Top
				world().right(),				// Right
				world().top() - w_height()/2);	// Bottom
		
		// Draw eye(s)
		if( _facing_left )
		{
			GLblack3.glColor();
			glRectf(world().left(),					// Left
					world().top() - w_height()/8,	// Top
					world().left() + w_width()/6,	// Right
					world().top() - w_height()/4);	// Bottom
		}
		else if( _facing_right )
		{
			GLblack3.glColor();
			glRectf(world().right() - w_width()/6,	// Left
					world().top() - w_height()/8,	// Top
					world().right(),				// Right
					world().top() - w_width()/4);	// Bottom
		}
		else if( _facing_down )
		{
			// Left eye
			GLblack3.glColor();
			glRectf(world().left() + w_height()/8,	// Left
					world().top() - w_height()/4,	// Top
					world().left() + w_width()/3,	// Right
					world().top() - 3*w_width()/8);	// Bottom
			
			// Right eye
			GLblack3.glColor();
			glRectf(world().left() + 2*w_width()/3,	// Left
					world().top() - w_height()/4,	// Top
					world().right() - w_width()/8,	// Right
					world().top() - 3*w_width()/8);	// Bottom
		}
	}	
	void Player::draw_torso()
	{
		_shirt_color.glColor();
		glRectf(world().left(),						// Left
				world().top() - w_height()/2,		// Top
				world().right(),					// Right
				world().bottom() + w_height()/6);	// Bottom
	}
	void Player::draw_arms()
	{
	}
	void Player::draw_feet()
	{
		_shoe_color.glColor();
		if( _facing_left )
		{
			if( !_animation_frame )
			{
				// Right shoe
				glRectf(world().left(),						// Left
						world().bottom() + w_height()/6,	// Top
						world().left() + w_width()/3,		// Right
						world().bottom());					// Bottom
				// Left shoe
				glRectf(world().left() + 2*w_width()/3,		// Left
						world().bottom() + w_height()/6,	// Top
						world().right(),					// Right
						world().bottom());					// Bottom
			}
			else
				// Just left shoe
				glRectf(world().left() + w_width()/6,		// Left
						world().bottom() + w_height()/6,	// Top
						world().left() + 5*w_width()/6,		// Right
						world().bottom());					// Bottom
		}
		else if ( _facing_right )
		{
			if( !_animation_frame )
			{
				// Right shoe
				glRectf(world().left(),						// Left
						world().bottom() + w_height()/6,	// Top
						world().left() + w_width()/3,		// Right
						world().bottom());					// Bottom
				// Left shoe
				glRectf(world().left() + 2*w_width()/3,		// Left
						world().bottom() + w_height()/6,	// Top
						world().right(),					// Right
						world().bottom());					// Bottom
			}
			else
			{	
			// Just right shoe
				glRectf(world().left() + w_width()/6,		// Left
						world().bottom() + w_height()/6,	// Top
						world().left() + 5*w_width()/6,		// Right
						world().bottom());					// Bottom
			}
		}
		else
		{
			if( _animation_frame )
				// Right shoe
				glRectf(world().left(),						// Left
						world().bottom() + w_height()/6,	// Top
						world().left() + w_width()/3,		// Right
						world().bottom());					// Bottom
			else
				// Left shoe
				glRectf(world().left() + 2*w_width()/3,		// Left
						world().bottom() + w_height()/6,	// Top
						world().right(),					// Right
					world().bottom());					// Bottom
		}
	}
}