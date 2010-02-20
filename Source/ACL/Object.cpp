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
	
    ostream& operator << ( ostream& outs, const Object& o )
    {
        outs << o.type() << endl;
        outs << "\tleft: " << o.left() << endl;
        outs << "\tbottom: " << o.bottom() << endl;
        outs << "\twidth: " << o.width() << endl;
        outs << "\theight: " << o.height() << endl;
        return outs;
    }
	
	bool intersecting(const Object& o1, const Object& o2)
	{
		// Top left corner
		return((o1.left() >= o2.left() &&
				o1.left() <= o2.right() &&
				o1.top() <= o2.top() &&
				o1.top() >= o2.bottom()) ||
			   // Top right corner
			   (o1.right() >= o2.left() &&
				o1.right() <= o2.right() &&
				o1.top() <= o2.top() &&
				o1.top() >= o2.bottom()) ||
			   // Bottom left corner
			   (o1.left() >= o2.left() &&
				o1.left() <= o2.right() &&
				o1.bottom() <= o2.top() &&
				o1.bottom() >= o2.bottom()) ||
			   // Bottom right corner
			   (o1.right() >= o2.left() &&
				o1.right() <= o2.right() &&
				o1.bottom() <= o2.top() &&
				o1.bottom() >= o2.bottom()) ||
			   // Left edge
			   (o1.left() >= o2.left() &&
				o1.left() <= o2.right() &&
				o1.bottom() <= o2.bottom() &&
				o1.top() >= o2.top()) ||	
			   // Right edge
			   (o1.right() >= o2.left() &&
				o1.right() <= o2.right() &&
				o1.bottom() <= o2.bottom() &&
				o1.top() >= o2.top()) ||			   
			   // Bottom edge
			   (o1.left() <= o2.left() &&
				o1.right() >= o2.right() &&
				o1.bottom() <= o2.top() &&
				o1.bottom() >= o2.bottom()) ||
			   // Top edge
			   (o1.left() >= o2.left() &&
				o1.left() <= o2.right() &&
				o1.top() <= o2.top() &&
				o1.top() >= o2.bottom()) ||
			   // Superimposed
			   (o1.left() <= o2.left() &&
				o1.left() >= o2.right() &&
				o1.bottom() <= o2.bottom() &&
				o1.top() >= o2.top()));
	}
}
