/*
 *  SewersObject.cpp
 *  Sewers
 *
 *  Created by Aaron Weeden on 11/6/09.
 *
 *  Collection of methods for drawing objects within the Sewers game.
 */
#include "gltypes.1.h"

using namespace GLTYPES;

namespace Sewers
{
	
	class SewersObject
		{
		public:
			// Constructors
			SewersObject();
			SewersObject(int id, GLint l, GLint r, GLint b, GLint t, int i1, bool b1);
			// Accessors
			int id()		const { return _id;		}
			GLint left()	const { return _left;	}
			GLint right()	const { return _right;	}
			GLint bottom()	const { return _bottom; }
			GLint top()		const { return _top;	}
			int int1()		const { return _int1;	}
			bool bool1()	const { return _bool1;	}
			// Mutators
			void mutate(int id) { _id = id; }
			void set_pos(GLint l, GLint r, GLint b, GLint t) { _left = l; _right = r; _bottom = b; _top = t; }
			void move(int x_factor, int y_factor) { _left += x_factor; _right += x_factor; _bottom += y_factor; _top += y_factor; }
			void change_int(int i) { _int1 = i; }
			void toggle() { _bool1 = !_bool1; }
			// Member functions
			void draw();
		private:
			int _id;
			GLint _left, _right, _bottom, _top; // for drawing
			int _int1; // meaning depends on _id
			bool _bool1; // meaning depends on _id
		};
}