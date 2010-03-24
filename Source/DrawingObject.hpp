/*  Object.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#ifndef OBJGUARD
#define OBJGUARD

#include "globals.hpp"

namespace Sewers
{	
	/* DrawingObject -- parent class of all objects in the game
	 *               -- contains information on drawing the object
	 */
	class DrawingObject
	{
	public:
		// CONSTRUCTORS
		DrawingObject(string type = "");
		DrawingObject(const DrawingObject&);
		// ACCESSORS
		string type() const { return _type; }
		GLint left() const { return _left; }
		GLint bottom() const { return _bottom; }
		GLint right() const { return _left + _width; }
		GLint top() const { return _bottom + _height; }
		GLint width() const { return _width; }
		GLint height() const { return _height; }
        // MUTATORS
        void set_type(string type) { _type = type; }
        void set_left(GLint left) { _left = left; }
        void set_bottom(GLint bottom) { _bottom = bottom; }
        void set_width(GLint width) { _width = width; }
        void set_height(GLint height) { _height = height; }
        // METHODS
        void draw() const;
    private:
        string _type;  // For identification
        GLint _left, _bottom, _width, _height;  // Drawing coordinates
    };

	// OPERATORS
    ostream& operator << (ostream&, const DrawingObject&);
	
	bool intersecting(const DrawingObject&, const DrawingObject&);
	bool next_to(const DrawingObject&, const DrawingObject&);
	bool inside(const DrawingObject&, GLint x, GLint y);
}

#endif
