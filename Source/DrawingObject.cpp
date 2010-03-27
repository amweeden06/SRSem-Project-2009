/*
 *
 */
#include "DrawingObject.hpp"

namespace Sewers
{
	/* DEFAULT CONSTRUCTOR */
	DrawingObject::DrawingObject()
	{
		set_type("OBJECT");
		set_left(0);
		set_bottom(0);
		set_width(0);
		set_height(0);
	}
	
	/* COPY CONSTRUCTOR */
	DrawingObject::DrawingObject(const DrawingObject& o)
	{
		set_type(o.type());
		set_left(o.left());
		set_bottom(o.bottom());
		set_width(o.width());
		set_height(o.height());
	}

	/* FUNCTION: draw()
	 * PRECONDITIONS: None
	 * POSTCONDITION: The object has been placed in the drawing queue, to be
	 *                 drawn at the next glFlush()
	 * POSSIBLE RETURN VALUES: SUCCESS
	 */
	int DrawingObject::draw() const
	{
		GLred3.glColor();
		glRecti(left(), bottom(), right(), top());
		return SUCCESS;
    }	
	
	/* FUNCTION: contains(GLint x, GLint y)
	 * PRECONDITIONS: none
	 * POSTCONDITIONS: none
	 * RETURN VALUE: true iff the point (x,y) is contained within the boundaries
	 *  of this object
	 */
	bool DrawingObject::contains(GLint x, GLint y) const
	{
		return(x >= left() &&
			   x <= right() &&
			   y >= bottom() &&
			   y <= top()); 
	}

	/* FUNCTION: is_intersecting(const DrawingObject& o)
	 * PRECONDITIONS: none
	 * POSTCONDITIONS: none
	 * RETURN VALUE: true iff this object is intersecting o
	 */
	bool DrawingObject::is_intersecting(const DrawingObject& o) const
	{
		bool x_intersection = ((left() < o.left() && right() > o.left()) ||
							   (left() < o.right() && right() > o.right()));
		
		bool y_intersection = ((bottom() < o.bottom() && top() > o.top()) ||
							   (bottom() < o.top() && top() > o.top()));
		
		return x_intersection && y_intersection;
	}
}
