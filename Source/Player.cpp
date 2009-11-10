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
	const int WINDOW_WIDTH = 400;
	const int WINDOW_HEIGHT = 300;
	
	void Player::move_left(int move_factor)
	{
		// Player is now only facing left
		_facing_left = true;
		_facing_right = _facing_down = _facing_up = false;
		// Remap the player move_factor pixels to the left
		reMap(IntRect(viewport().left() - move_factor, viewport().right() - move_factor, viewport().bottom(), viewport().top()));
		// Animate the player
		_animation_frame = !_animation_frame;
	}
	void Player::move_right(int move_factor)
	{
		_can_leave = true;
		// Player is now only facing right
		_facing_right = true;
		_facing_left = _facing_down = _facing_up = false;
		// Remap the player move_factor pixels to the right
		reMap(IntRect(viewport().left() + move_factor, viewport().right() + move_factor, viewport().bottom(), viewport().top()));
		
		if(viewport().left() > WINDOW_WIDTH)
			exit(0);
		
		// Animate the player
		_animation_frame = !_animation_frame; // Animate the player
	}
	void Player::move_down(int move_factor)
	{
		// Player is now only facing down
		_facing_down = true;
		_facing_left = _facing_right = _facing_up = false;
		// Remap the player move_factor pixels to the down
		reMap(IntRect(viewport().left(), viewport().right(), viewport().bottom() - move_factor, viewport().top() - move_factor));
		// Animate the player
		_animation_frame = !_animation_frame;
	}
	void Player::move_up(int move_factor)
	{
		// Player is now only facing up
		_facing_up = true;
		_facing_left = _facing_right = _facing_down = false;
		// Remap the player move_factor pixels to the up
		reMap(IntRect(viewport().left(), viewport().right(), viewport().bottom() + move_factor, viewport().top() + move_factor));
		// Animate the player
		_animation_frame = !_animation_frame;
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