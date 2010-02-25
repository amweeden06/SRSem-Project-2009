/*  Object.hpp
 *  Part of the Sewers project
 *     Aaron Weeden, Earlham College, 2009-2010
 */
#include "constants.hpp"

#ifndef OBJGUARD
#define OBJGUARD

namespace Sewers
{
	/* Object -- parent class of all objects in the game
	 *        -- contains information on drawing the object
	 *        -- also contains help function, which describes the object
	 */
	class Object
	{
	public:
		// CONSTRUCTORS
		Object(const string type = "");
		Object(const Object&);
		// ACCESSORS
		string type() const { return _type; }
		GLint left() const { return _left; }
		GLint bottom() const { return _bottom; }
		GLint right() const { return _left + _width; }
		GLint top() const { return _bottom + _height; }
		GLint width() const { return _width; }
		GLint height() const { return _height; }
        // MUTATORS
        void set_type(const string type) { _type = type; }
        void set_left(const GLint left) { _left = left; }
        void set_bottom(const GLint bottom) { _bottom = bottom; }
        void set_width(const GLint width) { _width = width; }
        void set_height(const GLint height) { _height = height; }
        // METHODS
        void draw() const;
		void help() const;
    private:
        string _type;  // For identification
        GLint _left, _bottom, _width, _height;  // Drawing coordinates
    };

    ostream& operator << (ostream&, const Object&);
	bool intersecting(const Object&, const Object&);
	bool next_to(const Object&, const Object&);
}

#endif
