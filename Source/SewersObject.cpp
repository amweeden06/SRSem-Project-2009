/*
 *  SewersObject.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/6/09.
 *
 *  Collection of methods for drawing objects within the Sewers game.
 */
#include "SewersObject.hpp"

namespace Sewers
{
	// Object ids
	const int NONE = -1;
	const int PLAYER = 0;
	const int DOOR = 1;
	const int LADDER = 2;
	const int PANEL = 3;
	const int SWITCH = 4;
	const int FLOOR = 5;
	const int INVERTER = 6;
	const int AND = 7;
	const int OR = 8;
	const int CIRCUIT = 9;
	
	// Values for int1 (see draw_object)
	const int FACING_LEFT = 0;
	const int FACING_RIGHT = 1;
	const int FACING_DOWN = 2;
	const int FACING_UP = 3;
	
	SewersObject::SewersObject(int id, GLint left, GLint right, GLint bottom, GLint top, int int1, bool bool1)
	{
		_id = id;
		_left = left;
		_right = right;
		_bottom = bottom;
		_top = top;
		_int1 = int1;
		_bool1 = bool1;
	}
	
	// Depending on object_id, int1 and bool1 will have special meaning; see the comments for each case of the switch statement for these meanings
	void SewersObject::draw()
	{		
		GLint height = _top - _bottom;
		GLint width = _right - _left;
		
		switch(_id)
		{
			// PLAYER object :  int1 refers to the direction the player is facing.
			//					bool1 refers to the current animation frame.
			case PLAYER:
				// Player's coordinates
				GLint eye_l, eye_r, eye_b, eye_t;
				// Player's shoe coordinates
				GLint shoe_l = _left + width/6, shoe_r = _right - width/6, shoe_b = _bottom, shoe_t = _bottom + height/6; // Both shoes together
				GLint lshoe_l = _left + 2*width/3, lshoe_r = _right, rshoe_l = _left, rshoe_r = _left + width/3; // Individual shoes
				// For player, int1 refers to the direction the player is facing.
				switch(_int1)
				{
					case FACING_LEFT:
						eye_l = _left;
						eye_r = _left + width/6;
						eye_b = _top - height/4;
						eye_t = _top - height/8;
						break;
					case FACING_RIGHT:
						eye_l = _right - width/6;
						eye_r = _right;
						eye_b = _top - height/4;
						eye_t = _top - height/8;
						break;
					case FACING_DOWN:
						eye_l = _left + width/8;
						eye_r = _left + width/3;
						eye_b = _top - 3*height/8;
						eye_t = _top - height/4;
						break;
				}
				// Set head color
				GLgreen3.glColor();
				// Draw head
				glRectf(_left, _bottom + height/2, _right, _top);
				
				// Draw eye
				GLblack3.glColor();
				if(_int1 != FACING_UP)
					glRectf(eye_l, eye_b, eye_r, eye_t);
				if(_int1 == FACING_DOWN)
					// Draw right eye
					glRectf(_left + 2*width/3, _top - 3*height/8, _right - width/8, _top - height/4);
				
				// Draw torso
				GLblue3.glColor();
				glRectf(_left,  _bottom + height/6, _right, _top - height/2);
				
				// Draw shoes
				GLblack3.glColor();
				if(( _int1 == FACING_LEFT ) || ( _int1 == FACING_RIGHT ))
				{
					if( _bool1 )
					{
						// Right shoe
						glRectf(rshoe_l, shoe_b, rshoe_r, shoe_t);
						// Left shoe
						glRectf(lshoe_l, shoe_b, lshoe_r, shoe_t);
					}
					else
						// Both shoes together
						glRectf(shoe_l,	shoe_b,	shoe_r,	shoe_t);
				}
				else
				{
					if( _bool1 )
						// Right shoe
						glRectf(rshoe_l, shoe_b, rshoe_r, shoe_t);
					else
						// Left shoe
						glRectf(lshoe_l, shoe_b, lshoe_r, shoe_t);
				}
				break;
				
			// FLOOR object : int1 and bool1 have no specified meanings
			case FLOOR:
				(GLcolor3(0.2,0.2,0.2)).glColor();
				glRectf(_left, _bottom, _right, _top);
				break;
				
			// LADDER object : int1 and bool1 have no specified meanings
			case LADDER:
				GLblack3.glColor();
				glRectf(_left, _bottom, _right, _top);
				GLwhite3.glColor();
				glBegin(GL_POLYGON);
				// Top Rung 
				glVertex2f(_left, _bottom + 3*height/5);
				glVertex2f(_left, _top);
				glVertex2f(_left + width/5, _top - height/5);
				glVertex2f(_left + width/5, _bottom + 2*height/5);
				glEnd();
				glBegin(GL_POLYGON);
				// Middle Rung
				glVertex2f(_left + 2*width/5, _bottom + height/3);
				glVertex2f(_left + 2*width/5, _top - height/4);
				glVertex2f(_left + 3*width/5, _top - 2*height/5);
				glVertex2f(_left + 3*width/5, _bottom + height/5);
				glEnd();
				glBegin(GL_POLYGON);
				// Bottom Rung
				glVertex2f(_left + 4*width/5, _bottom + height/5);
				glVertex2f(_left + 4*width/5, _bottom + 3*height/5);
				glVertex2f(_right, _top - 3*height/5);
				glVertex2f(_right, _bottom);
				glEnd();
				break;
				
			// PANEL object : int1 and bool1 have no specified meanings
			case PANEL:
				GLblack3.glColor();
				glBegin(GL_LINE_LOOP);
				glVertex2f(_left, _top);
				glVertex2f(_left, _bottom);
				glVertex2f(_right, _bottom);
				glVertex2f(_right, _top);
				glEnd();
				break;
				
			// SWITCH object : bool1 refers to the switch's value (0 or 1)
			//				   int1 has no specified meaning
			case SWITCH:
				if(_bool1)
				{
					// Draw the 1
					GLgreen3.glColor();
					glRectf(_left + width/3, _bottom, _right - width/3, _top);
				}
				else
				{
					// Draw the 0
					GLblue3.glColor();
					//   Top Line
					glRectf(_left + 1*width/8,	_bottom,				 _left + 3*width/8,	_top);
					glRectf(_left + 1*width/8,	_bottom,			     _left + 7*width/8,	_top - 3*height/4);
					glRectf(_left + 5*width/8,	_bottom,				 _left + 7*width/8,	_top);
					glRectf(_left + 1*width/8,	_bottom + 3*height/4, _left + 7*width/8,	_top);
				}
				break;
				
			// DOOR object : int1 refers to the orientation of the door
			//               bool1 is true iff the door is open
			case DOOR:
				if(!_bool1)
				{
					GLgreen3.glColor();
					glBegin(GL_POLYGON);
					glVertex2f(_left, _bottom);
					glVertex2f(_left, _top - height/2);
					glVertex2f(_right, _top);
					glVertex2f(_right, _top - height/2);
					glEnd();
				}
				GLblack3.glColor();
				glBegin(GL_POLYGON);
				glVertex2f(_left, _bottom);
				glVertex2f(_right, _top - height/2);
				glVertex2f(_right, _bottom);
				glEnd();
				break;
				
			// INVERTER object : int1 and bool1 have no specified meanings
			case INVERTER:
				GLred3.glColor();
				// Draw triangle
				glBegin(GL_POLYGON);
				glVertex2f(_left, _bottom);
				glVertex2f(_left, _top);
				glVertex2f(_left+2*width/3, _bottom + height/2);
				glEnd();
				// Draw circle
				glBegin(GL_POLYGON);
				glVertex2f(_left+2*width/3, _bottom + height/2);
				glVertex2f(_left+5*width/6, _bottom + 3*height/5);
				glVertex2f(_left+6*width/6, _bottom + height/2);
				glVertex2f(_left+5*width/6, _bottom + 2*height/5);
				glEnd();
				break;
				
			// OR object : int1 and bool1 have no specified meanings
			case OR:
				GLred3.glColor();
				// Top of the gate
				glBegin(GL_POLYGON);
				glVertex2f(_left+width/3, _bottom+height/2);
				glVertex2f(_left, _top);
				glVertex2f(_left+2*width/3, _top);
				glVertex2f(_right, _bottom + height/2);
				glEnd();
				// Bottom of the gate
				glBegin(GL_POLYGON);
				glVertex2f(_left+width/3, _bottom+height/2);
				glVertex2f(_left, _bottom);
				glVertex2f(_left+2*width/3, _bottom);
				glVertex2f(_right, _bottom + height/2);
				glEnd();
				// Draw the +
				GLblack3.glColor();
				glBegin(GL_LINES);
				glVertex2f(_left+4*width/7, _top-height/4);
				glVertex2f(_left+4*width/7, _bottom+height/4);
				glVertex2f(_left+2*width/5, _top-height/2);
				glVertex2f(_left+4*width/5, _top-height/2);
				glEnd();
				break;
				
			// AND object : int1 and bool1 have no specified meanings
			case AND:
				GLred3.glColor();
				glBegin(GL_POLYGON);
				glVertex2f(_left, _bottom);
				glVertex2f(_left, _top);
				glVertex2f(_left+width/2, _top);
				glVertex2f(_right, _bottom + 2*height/3);
				glVertex2f(_right, _bottom + 1*height/3);
				glVertex2f(_left+width/2, _bottom);
				glEnd();
				// Draw the dot
				GLblack3.glColor();
				glRectf(_left+2*width/5, _bottom+2*height/5, _left+3*width/5, _bottom+3*height/5);
				glEnd();
				break;
				
			// CIRCUIT object : int1 indicates the charge of the circuit
			//					bool1 has no specified meanings
			case CIRCUIT:
				switch(_int1)
				{
					case 0:
						GLblue3.glColor();
						break;
					case 1:
						GLgreen3.glColor();
						break;
					default:
						GLblack3.glColor();
						break;
				}
				glBegin(GL_LINES);
				glVertex2f(_left, _bottom);
				glVertex2f(_left, _top);
				glVertex2f(_left, _top);
				glVertex2f(_right, _top);
				glEnd();
		}
	}
}