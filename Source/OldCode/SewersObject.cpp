/*
 *  SewersObject.cpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009
 *
 *  Collection of methods for drawing objects within the Sewers game.
 */
/*#include "SewersObject.hpp"

namespace SewersOld
{
    // A NONE object
    SewersObject::SewersObject()
    {
        _id = "NONE";
        _int1 = -1;
        _bool1 = false;
        _left = _right = _bottom = _top = 0;
    }

    SewersObject::SewersObject(string id, GLint left, GLint right, GLint bottom, GLint top, int int1, bool bool1)
    {
        _id = id;
        _left = left;
        _right = right;
        _bottom = bottom;
        _top = top;
        _int1 = int1;
        _bool1 = bool1;
    }

    // Returns true iff the point at (x,y) is inside the object
    bool SewersObject::inside(GLint x, GLint y)
    {
        return (( x >= _left ) &&
                ( x <= _right ) &&
                ( y >= _bottom ) &&
                ( y <= _top ));
    }

    void SewersObject::draw()
    {		
        GLint height = _top - _bottom;

        // AVATAR object :  int1 refers to the direction the avatar is facing.
        //					bool1 refers to the current animation frame.
        if(_id == "AVATAR")
        {
            // Avatar's coordinates
            GLint eye_l, eye_r, eye_b, eye_t;
            // Avatar's shoe coordinates
            GLint shoe_l = _left + width()/6, shoe_r = _right - width()/6, shoe_b = _bottom, shoe_t = _bottom + height/6; // Both shoes together
            GLint lshoe_l = _left + 2*width()/3, lshoe_r = _right, rshoe_l = _left, rshoe_r = _left + width()/3; // Individual shoes
            // For avatar, int1 refers to the direction the avatar is facing.
            switch(_int1)
            {
                case LEFT:
                    eye_l = _left;
                    eye_r = _left + width()/6;
                    eye_b = _top - height/4;
                    eye_t = _top - height/8;
                    break;
                case RIGHT:
                    eye_l = _right - width()/6;
                    eye_r = _right;
                    eye_b = _top - height/4;
                    eye_t = _top - height/8;
                    break;
                case DOWN:
                    eye_l = _left + width()/8;
                    eye_r = _left + width()/3;
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
            if(_int1 != UP)
                glRectf(eye_l, eye_b, eye_r, eye_t);
            if(_int1 == DOWN)
                // Draw right eye
                glRectf(_left + 2*width()/3, _top - 3*height/8, _right - width()/8, _top - height/4);

            // Draw torso
            GLblue3.glColor();
            glRectf(_left,  _bottom + height/6, _right, _top - height/2);

            // Draw shoes
            GLblack3.glColor();
            if(( _int1 == LEFT ) || ( _int1 == RIGHT ))
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
        }
        // FLOOR object : int1 and bool1 have no specified meanings
        else if(_id == "FLOOR")
        {
            (GLcolor3(0.2,0.2,0.2)).glColor();
            glRectf(_left, _bottom, _right, _top);
        }
        // LADDER object : int1 and bool1 have no specified meanings
        else if(_id == "LADDER")
        {
            GLblack3.glColor();
            glRectf(_left, _bottom, _right, _top);
            GLwhite3.glColor();
            glBegin(GL_POLYGON);
            // Top Rung 
            glVertex2f(_left, _bottom + 3*height/5);
            glVertex2f(_left, _top);
            glVertex2f(_left + width()/5, _top - height/5);
            glVertex2f(_left + width()/5, _bottom + 2*height/5);
            glEnd();
            glBegin(GL_POLYGON);
            // Middle Rung
            glVertex2f(_left + 2*width()/5, _bottom + height/3);
            glVertex2f(_left + 2*width()/5, _top - height/4);
            glVertex2f(_left + 3*width()/5, _top - 2*height/5);
            glVertex2f(_left + 3*width()/5, _bottom + height/5);
            glEnd();
            glBegin(GL_POLYGON);
            // Bottom Rung
            glVertex2f(_left + 4*width()/5, _bottom + height/5);
            glVertex2f(_left + 4*width()/5, _bottom + 3*height/5);
            glVertex2f(_right, _top - 3*height/5);
            glVertex2f(_right, _bottom);
            glEnd();
        }

        // PANEL object : bool1 and int1 have no specified meanings
        else if(_id == "PANEL")
        {
            GLblack3.glColor();
            glBegin(GL_LINE_LOOP);
            glVertex2f(_left, _top);
            glVertex2f(_left, _bottom);
            glVertex2f(_right, _bottom);
            glVertex2f(_right, _top);
            glEnd();
        }
        // SWITCH object : int1 refers to the switch's value
        //				   bool1 has no specified meaning
        else if(_id == "SWITCH")
        {
            // Draw the 1
            GLgreen3.glColor();
            glRectf(_left + width()/8, _top - 2*height/5, 
                    _left + width()/3, _top);

            // Draw the 0
            GLblue3.glColor();
            glRectf(_left, _bottom + 3*height/8,
                    _left + width()/4, _bottom + height/2);
            glRectf(_left, _bottom,			     
                    _left + width()/8, _bottom + height/2);
            glRectf(_left + width()/4, _bottom,				
                    _left + 3*width()/8, _bottom + height/2);
            glRectf(_left, _bottom, 
                    _left + width()/4, _bottom + height/8);

            if(_int1 == 1)
            {
                // Draw wire from the one
                GLgreen3.glColor();
                glBegin(GL_LINES);
                glVertex2f(_left + width()/2, _top - height/4);
                glVertex2f(_left + width(), _bottom + height/2);
                glEnd();
            }
            else if(_int1 == 0)
            {
                // Draw wire from the zero
                GLblue3.glColor();
                glBegin(GL_LINES);
                glVertex2f(_left + width()/2, _bottom + height/4);
                glVertex2f(_left + width(), _bottom + height/2);
                glEnd();
            }
        }
        // DOOR object : int1 refers to the orientation of the door
        //               bool1 is true iff the door is open
        else if(_id == "DOOR")
        {
            switch(_int1)
            {
                case LEFT:
                    if(!_bool1) // If closed
                    {
                        GLgreen3.glColor();
                        glBegin(GL_POLYGON);
                        glVertex2f(_right, _bottom);
                        glVertex2f(_right, _top - height/2);
                        glVertex2f(_left, _top);
                        glVertex2f(_left, _top - height/2);
                        glEnd();
                    }
                    GLblack3.glColor();
                    glBegin(GL_POLYGON);
                    glVertex2f(_right, _bottom);
                    glVertex2f(_left, _top - height/2);
                    glVertex2f(_left, _bottom);
                    glEnd();
                    break;
                    break;
                case RIGHT:
 if(!_bool1) // If closed
 {
 GLgreen3.glColor();
 glBegin(GL_POLYGON);
 glVertex2f(_right, _bottom);
 glVertex2f(_right, _top - height/2);
 glVertex2f(_left, _top);
 glVertex2f(_left, _top - height/2);
 glEnd();
 }
 GLblack3.glColor();
 glBegin(GL_POLYGON);
 glVertex2f(_right, _bottom);
 glVertex2f(_left, _top - height/2);
 glVertex2f(_left, _bottom);
 glEnd();
 break;
            }
        }

        // NOT object : bool1 is true iff the gate is visible
        //					 int1 has no specified meanings
        else if(_id == "NOT")
        {
            if(_bool1)
            {
                GLred3.glColor();
                // Draw triangle
                glBegin(GL_POLYGON);
                glVertex2f(_left, _bottom);
                glVertex2f(_left, _top);
                glVertex2f(_left+2*width()/3, _bottom + height/2);
                glEnd();
                // Draw circle
                glBegin(GL_POLYGON);
                glVertex2f(_left+2*width()/3, _bottom + height/2);
                glVertex2f(_left+5*width()/6, _bottom + 3*height/5);
                glVertex2f(_left+6*width()/6, _bottom + height/2);
                glVertex2f(_left+5*width()/6, _bottom + 2*height/5);
                glEnd();
            }
        }
        // OR object : bool1 is true iff the gate is visible
        //             int1 has no specified meanings
        else if(_id == "OR")
        {
            if(_bool1)
            {
                GLred3.glColor();
                // Top of the gate
                glBegin(GL_POLYGON);
                glVertex2f(_left+width()/3, _bottom+height/2);
                glVertex2f(_left, _top);
                glVertex2f(_left+2*width()/3, _top);
                glVertex2f(_right, _bottom + height/2);
                glEnd();
                // Bottom of the gate
                glBegin(GL_POLYGON);
                glVertex2f(_left+width()/3, _bottom+height/2);
                glVertex2f(_left, _bottom);
                glVertex2f(_left+2*width()/3, _bottom);
                glVertex2f(_right, _bottom + height/2);
                glEnd();
                // Draw the +
                GLblack3.glColor();
                glBegin(GL_LINES);
                glVertex2f(_left+4*width()/7, _top-height/4);
                glVertex2f(_left+4*width()/7, _bottom+height/4);
                glVertex2f(_left+2*width()/5, _top-height/2);
                glVertex2f(_left+4*width()/5, _top-height/2);
                glEnd();
            }
        }
        // AND object : bool1 is true iff the gate is visible
        //              int1 has no specified meanings
        else if(_id == "AND")
        {
            if(_bool1)
            {
                GLred3.glColor();
                glBegin(GL_POLYGON);
                glVertex2f(_left, _bottom);
                glVertex2f(_left, _top);
                glVertex2f(_left+width()/2, _top);
                glVertex2f(_right, _bottom + 2*height/3);
                glVertex2f(_right, _bottom + 1*height/3);
                glVertex2f(_left+width()/2, _bottom);
                glEnd();
                // Draw the dot
                GLblack3.glColor();
                glRectf(_left+2*width()/5, _bottom+2*height/5, _left+3*width()/5, _bottom+3*height/5);
                glEnd();
            }
        }
        // WIRE object : int1 indicates the charge of the wire
        //				bool1 is true iff the wire powers a door
        else if(_id == "WIRE")
        {
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
            glVertex2f(_right, _top);
            glEnd();
        }
        // PAUSE button : bool1 indicates the game is paused and the pause button is visible
        //				  int1 has no specified meaning
        else if(_id == "PAUSE_BUTTON")
        {
            if(_bool1)
            {
                GLyellow3.glColor();
                glRectf(_left, _bottom, _right, _top);
                GLred3.glColor();
                glRectf(_left + width()/5, _bottom + height/5, _left + 2*width()/5, _top - height/5);
                glRectf(_left + 3*width()/5, _bottom + height/5, _left + 4*width()/5, _top - height/5);
            }
        }
        // GATE_DISPLAY object : int1 is the number of gates on the screen
        //						 bool1 has no specified meanings
        else if(_id == "GATE_DISPLAY")
        {
            GLyellow3.glColor();
            glRectf(_left, _bottom, _right, _top);
        }
        // TABLE_DISPLAY object : int1 and bool1 have no specified meanings
        else if(_id == "TABLE_DISPLAY")
        {
            GLyellow3.glColor();
            glRectf(_left, _bottom, _right, _top);
        }
        // GATE_BOX object : bool1 is true iff the gate box is visible
        //					 int1 has no specified meaning
        else if(_id == "GATE_BOX")
        {
            if(_bool1)
            {
                GLred3.glColor();
                glRecti(_left, _bottom, _right, _top);
                // Outline
                glBegin(GL_LINE_LOOP);
                GLblack3.glColor();
                glVertex2i(_left, _bottom);
                glVertex2i(_right, _bottom);
                glVertex2i(_right, _top);
                glVertex2i(_left, _top);
                glEnd();
                // G
                glBegin(GL_LINE_STRIP);
                GLyellow3.glColor();
                glVertex2i(_right - width()/4, _top - height/3);
                glVertex2i(_right - width()/3, _top - height/4);
                glVertex2i(_left + width()/3, _top - height/4);
                glVertex2i(_left + width()/4, _top - height/3);
                glVertex2i(_left + width()/4, _bottom + height/3);
                glVertex2i(_left + width()/3, _bottom + height/5);
                glVertex2i(_right - width()/3, _bottom + height/5);
                glVertex2i(_right - width()/4, _bottom + height/3);
                glVertex2i(_right - width()/2, _bottom + height/2);
                glEnd();
            }
        }
        // SWITCH_BUTTON object : bool1 has no specified meaning
        //						  int1 is the index of the circuit that contains 
        //							the switch to which the button is connected
        else if(_id == "SWITCH_BUTTON")
        {
            GLcolor3(0.2, 0.0, 0.0).glColor();
            glRectf(_left, _bottom, _right, _top);
            GLred3.glColor();
            glRectf(_left + width()/4, _bottom + height/4, _right - width()/4, _top - height/4);
        }
        // BUTTON_DISPLAY object : bool1 and int1 have no specified meanings
        else if(_id == "BUTTON_DISPLAY")
        {
            GLyellow3.glColor();
            glRectf(_left, _bottom, _right, _top);
            // Draw button
            GLcolor3(0.2, 0.0, 0.0).glColor();
            glRectf(_left + width()/2 - OBJECT_WIDTH/2, _bottom + height/2 - OBJECT_HEIGHT/2,
                    _left + width()/2 + OBJECT_WIDTH/2, _bottom + height/2 + OBJECT_HEIGHT/2);
            GLred3.glColor();
            glRectf(_left + width()/2 - OBJECT_WIDTH/4, _bottom + height/2 - OBJECT_HEIGHT/4,
                    _left + width()/2 + OBJECT_WIDTH/4, _bottom + height/2 + OBJECT_HEIGHT/4);
        }
        // COMPUTER object : bool1 is true iff the computer is on
        //                   int1 has no specified meanings
        else if(_id == "COMPUTER")
        {
            GLcolor3(0.4,0.4,0.4).glColor();
            glRectf(_left, _bottom, _right, _top);
            // Screen
            if(_bool1)
                GLgreen3.glColor();
            else
                GLcolor3(0.0,0.3,0.0).glColor();
            glRectf(_left + width()/6, _bottom + height/3, _right - width()/6, _top - height/6);
            // Buttons
            GLred3.glColor();
            glRectf(_left + width()/6, _bottom + height/8, _left + width()/3, _bottom + height/5);
            GLyellow3.glColor();
            glRectf(_right - width()/3, _bottom + height/8, _right - width()/6, _bottom + height/5);
        }
        // COMPUTER_DISPLAY object : bool1 and int1 have no specified meanings
        else if(_id == "COMPUTER_DISPLAY")
        {
            GLyellow3.glColor();
            glRectf(_left, _bottom, _right, _top);
            GLcolor3(0.4,0.4,0.4).glColor();
            glRectf(_left + width()/2 - OBJECT_WIDTH/2, 
                    _bottom + height/2 - OBJECT_HEIGHT/2,
                    _right - width()/2 + OBJECT_WIDTH/2,
                    _top - height/2 + OBJECT_HEIGHT/2);
            // Screen
            GLgreen3.glColor();
            glRectf(_left + width()/2 - OBJECT_WIDTH/2 + OBJECT_WIDTH/6,
                    _bottom + height/2 - OBJECT_HEIGHT/2 + OBJECT_HEIGHT/3, 
                    _right - width()/2 + OBJECT_WIDTH/2 - OBJECT_WIDTH/6,
                    _top - height/2 + OBJECT_HEIGHT/2 - OBJECT_HEIGHT/6);
            // Buttons
            GLred3.glColor();
            glRectf(_left + width()/2 - OBJECT_WIDTH/2 + OBJECT_WIDTH/6,
                    _bottom + height/2 - OBJECT_HEIGHT/2 + OBJECT_HEIGHT/8, 
                    _left + width()/2 - OBJECT_WIDTH/2 + OBJECT_WIDTH/3,
                    _bottom + height/2 - OBJECT_HEIGHT/2 + OBJECT_HEIGHT/5);
            GLyellow3.glColor();
            glRectf(_right - width()/2 + OBJECT_WIDTH/2 - OBJECT_WIDTH/3, 
                    _bottom + height/2 - OBJECT_HEIGHT/2 + OBJECT_HEIGHT/8, 
                    _right - width()/2 + OBJECT_WIDTH/2 - OBJECT_WIDTH/6,
                    _bottom + height/2 - OBJECT_HEIGHT/2 + OBJECT_HEIGHT/5);
        }
    }
}
*/