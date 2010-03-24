/*
 *
 */
#include "DrawingObject.hpp"

namespace Sewers
{
	DrawingObject::DrawingObject(string type)
	{
		set_type(type);
		set_left(0);
		set_bottom(0);
		set_width(0);
		set_height(0);
	}
	
	DrawingObject::DrawingObject(const DrawingObject& o)
	{
		set_type(o.type());
		set_left(o.left());
		set_bottom(o.bottom());
		set_width(o.width());
		set_height(o.height());
	}

	// PRECONDITIONS: none
    // POSTCONDITION: The object has been placed in the drawing queue, to be
    //                 drawn at the next glFlush()
	void DrawingObject::draw() const
	{
		GLred3.glColor();
		glRecti(left(), bottom(), right(), top());
    }	
	
    ostream& operator << (ostream& outs, const DrawingObject& o)
    {
        outs << o.type() << endl;
        outs << "\tleft: " << o.left() << endl;
        outs << "\tbottom: " << o.bottom() << endl;
        outs << "\twidth: " << o.width() << endl;
        outs << "\theight: " << o.height() << endl;
        return outs;
    }
		
	// PRECONDITIONS: none
	// POSTCONDITION: returns true if an object is intersecting a
	//  another (this will usually only be used with avatar as one of the objects)
	bool intersecting(const DrawingObject& o1, const DrawingObject& o2)
	{
		return ((o1.left() <= o2.right()) &&
				(o1.right() >= o2.left()) &&
				(o1.top() >= o2.bottom()) &&
				(o1.bottom() <= o2.top()));
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: returns true if an object is within a movement factor
	//  of another (this will usually only be used with avatar as one of the objects)
	bool next_to(const DrawingObject& o1, const DrawingObject& o2)
	{
		return((o1.left() - MOVE_FACTOR <= o2.right()) &&
			   (o1.right() + MOVE_FACTOR >= o2.left()) &&
			   (o1.bottom() - MOVE_FACTOR <= o2.top()) &&
			   (o1.top() + MOVE_FACTOR >= o2.bottom()));
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: returns true if the point at x,y is inside the drawing object
	bool inside(const DrawingObject& d, GLint x, GLint y)
	{ 
		return (x >= d.left() &&
				x <= d.right() &&
				y >= d.bottom() &&
				y <= d.top()); 
	}	
}
