/*
 *
 */
#include "Object.hpp"

namespace Sewers
{
	Object::Object(string type)
	{
		set_type(type);
		set_left(0);
		set_bottom(0);
		set_width(0);
		set_height(0);
	}
	
	Object::Object(const Object& o)
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
	void Object::draw() const
	{
    }	
	
	// PRECONDITIONS: none
	// POSTCONDITION: Information about the object has been displayed to the user.
	void Object::help() const
	{
	}
	
    ostream& operator << ( ostream& outs, const Object& o )
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
	bool intersecting(const Object& o1, const Object& o2)
	{
		return ((o1.left() <= o2.right()) &&
				(o1.right() >= o2.left()) &&
				(o1.top() >= o2.bottom()) &&
				(o1.bottom() <= o2.top()));
	}
	
	// PRECONDITIONS: none
	// POSTCONDITION: returns true if an object is within a movement factor
	//  of another (this will usually only be used with avatar as one of the objects)
	bool next_to(const Object& o1, const Object& o2)
	{
		return((o1.left() - MOVE_FACTOR <= o2.right()) &&
			   (o1.right() + MOVE_FACTOR >= o2.left()) &&
			   (o1.bottom() - MOVE_FACTOR <= o2.top()) &&
			   (o1.top() + MOVE_FACTOR >= o2.bottom()));
	}
}
