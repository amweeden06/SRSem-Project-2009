/****************************************************************************
 * gltypes.1.cpp                                                            *
 *  Additional GL defined types                                             *
 *   Partly from Hill                                                       *
 *   JRogers, Aug/2002, Sept/2002                                           *
 *   JRogers, Jan/2005 --- extracted inlines operators to compile-time      *
 *                         implementation portion                           *
 *                                                                          *
 * For detailed documentation see gltypes.1.h                               *
 *                                                                          *
 * Methods implemented here:                                                *
 *                                                                          *
 *   GLintPoint --- pair of GLint                                           *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, const GLintPoint& p )       *
 *        istream& operator >> ( istream& ins, GLintPoint& p )              *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 *   Point2 --- real valued coordinate pair                                 *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, const Point2& p )           *
 *        istream& operator >> ( istream& ins, Point2& p )                  *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 *   IntRect --- GLint aligned rectangle                                    *
 *     Operators:                                                           *
 *       ostream& operator << ( ostream& outs, const IntRect& r );          *
 *       istream& operator >> ( istream& ins, IntRect& r );                 *
 *                                                                          *
 *   RealRect --- real aligned rectangle                                    *
 *     Operators:                                                           *
 *       ostream& operator << ( ostream& outs, const RealRect& r );         *
 *       istream& operator >> ( istream& ins, RealRect& r );                *
 *                                                                          *
 *   GLcolor3 --- triple of GLfloat                                         *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, GLcolor3& const  c )        *
 *        istream& operator >> ( istream& ins, GLcolor3&  p )               *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 *   GLcolor4 --- quadruple of GLfloat                                      *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, GLcolor4& const  c )        *
 *        istream& operator >> ( istream& ins, GLcolor4&  p )               *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 * Namespace: GLTYPES                                                       *
 ****************************************************************************/
#include "gltypes.1.h"

using namespace std;

namespace GLTYPES
{
/****************************************************************************
 *  GLintPoint                                                              *
 ****************************************************************************/

  ostream& operator << ( ostream& outs, const GLTYPES::GLintPoint& p )
  {
    outs << p.x() << " " << p.y();
    return outs;
  }
  
  istream& operator >> ( istream& ins, GLintPoint& p )
  {
    GLint x, y;
    ins >> x >> y;
    p = GLintPoint(x, y);
    return ins;
  }

/****************************************************************************
 *  Point2                                                                   *
 ****************************************************************************/

  ostream& operator << ( ostream& outs, const Point2& p )
  {
    outs << p.x() << " " << p.y();
    return outs;
  }
  
  istream& operator >> ( istream& ins, Point2& p )
  {
    GLdouble x, y;
    ins >> x >> y;
    p = Point2(x, y);
    return ins;
  }

/****************************************************************************
 *  IntRect                                                                 *
 ****************************************************************************/

  ostream& operator << ( ostream& outs, const IntRect& p )
  {
    outs << p.left() << " " << p.right()
         << " " << p.bottom() << " " << p.top();
    return outs;
  }
  
  istream& operator >> ( istream& ins, IntRect& p )
  {
    GLint l, r, b, t;
    ins >> l >> r >> b >> t;
    p = IntRect(l, r, b, t);
    return ins;
  }

  // IntRect * GLdouble --- scales size of rect, origin unchanged 
  IntRect operator * ( const IntRect& r, GLdouble scale )
  {
    GLintPoint orig( r.left(),r.bottom() );
    return ( (r-orig)*Point2(scale,scale)+orig );
  }

  IntRect operator * ( GLdouble scale, const IntRect& r )
  {
    GLintPoint orig( r.left(),r.bottom() );
    return ( (r-orig)*Point2(scale,scale)+orig );
  }

  IntRect operator / ( const IntRect& r, GLdouble scale )
  {
    GLintPoint orig( r.left(),r.bottom() );
    return ( (r-orig)/Point2(scale,scale)+orig );
  }


/****************************************************************************
 *  RealRect                                                                *
 ****************************************************************************/

  ostream& operator << ( ostream& outs, const RealRect& p )
  {
    outs << p.left() << " " << p.right()
         << " " << p.bottom() << " " << p.top();
    return outs;
  }
  
  istream& operator >> ( istream& ins, RealRect& p )
  {
    GLdouble l, r, b, t;
    ins >> l >> r >> b >> t;
    p = RealRect(l, r, b, t);
    return ins;
  }

  // RealRect * GLdouble --- scales size of rect, origin unchanged 
  RealRect operator * ( const RealRect& r, GLdouble scale )
  {
    Point2 orig(r.left(), r.bottom());
    return ( (r-orig)*Point2(scale,scale)+orig );
  }

  RealRect operator * ( GLdouble scale, const RealRect& r )
  {
    Point2 orig(r.left(), r.bottom());
    return ( (r-orig)*Point2(scale,scale)+orig );
  }

  RealRect operator / ( const RealRect& r, GLdouble scale )
  {
    Point2 orig(r.left(), r.bottom());
    return ( (r-orig)/Point2(scale,scale)+orig );
  }


/****************************************************************************
 *  GLcolor3                                                                *
 ****************************************************************************/

  istream& operator >> ( istream& ins, GLcolor3& c )
  {
    GLfloat red, green, blue;
    ins >> red >> green >> blue;
    c = GLcolor3( red, green, blue );
    return ins;
  }

  ostream& operator << ( ostream& outs, const GLcolor3& c )
  {
    outs << c.red() << " " << c.green() << " " << c.blue();
    return outs;
  }

/****************************************************************************
 *  GLcolor4                                                                *
 ****************************************************************************/

  istream& operator >> ( istream& ins, GLcolor4& c )
  {
    GLfloat red, green, blue, alpha;
    ins >> red >> green >> blue >> alpha;
    c = GLcolor4( red, green, blue, alpha );
    return ins;
  }

  ostream& operator << ( ostream& outs, const GLcolor4& c )
  {
    outs << c.red() << " " << c.green() << " " << c.blue() << " " 
         << c.alpha();
    return outs;
  }

}
// End of gltypes.1.cpp
