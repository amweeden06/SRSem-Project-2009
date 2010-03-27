/*
 *  SewersObject.hpp
 *  Sewers
 *
 *  Aaron Weeden, Nov/2009
 *
 *  Collection of methods for referencing objects within the Sewers game.
 *
 */
/*#include "constants.hpp"

using namespace GLTYPES;

namespace SewersOld
{
	class SewersObject
		{
		public:
			// Constructors
			SewersObject();
			SewersObject(string id, GLint l, GLint r, GLint b, GLint t, int i1, bool b1);
			// Accessors
			string id()		const { return _id;		}
			GLint left()	const { return _left;	}
			GLint right()	const { return _right;	}
			GLint bottom()	const { return _bottom; }
			GLint top()		const { return _top;	}
			GLint width()   const { return _right - _left; }
			GLint height()  const { return _top - _bottom; }
			int int1()		const { return _int1;	}
			bool bool1()	const { return _bool1;	}
			// Mutators
			void mutate(int id) { _id = id; }
			void set_pos(GLint l, GLint r, GLint b, GLint t) { _left = l; _right = r; _bottom = b; _top = t; }
			void move(int x_factor, int y_factor) { _left += x_factor; _right += x_factor; _bottom += y_factor; _top += y_factor; }
			void set_int(int i) { _int1 = i; }
			void set_bool(bool b) { _bool1 = b; }
			void toggle() { _bool1 = !_bool1; }
			// Member functions
            bool inside(GLint x, GLint y);
			void draw();
		private:
			string _id;
			// The edges of the object, for drawing purposes
			GLint _left, _right, _bottom, _top;
			// Objects may use an int and bool, which have varying meanings
			//  depending on the object.  See the draw() function in SewersObject.cpp
			int _int1; // meaning depends on _id
			bool _bool1; // meaning depends on _id
		};
}*/
