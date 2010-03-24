/****************************************************************************
 * gltypes.1.h                                                              *
 *  Additional GL defined types                                             *
 *   Partly from Hill                                                       *
 *   JRogers, Aug/2002, Sept/2002                                           *
 *   JRogers, Oct/2002 --- added inside(p), translation and additional      *
 *                         scaling operators for Rects                      *
 *   JRogers, Jan/2005 --- extracted inlines operators to compile-time      *
 *                         implementation portion                           *
 *                                                                          *
 * Classes provided:                                                        *
 *                                                                          *
 *   GLintPoint --- pair of GLint                                           *
 *     Constructor:                                                         *
 *       GLintPoint( GLint x, GLint y )                                     *
 *     Selectors:                                                           *
 *       x();                                                               *
 *       y();                                                               *
 *       void glVertex() const                                              *
 *          --- calls glVertex2i with coordinates as arguments              *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, const GLintPoint& p )       *
 *        istream& operator >> ( istream& ins, GLintPoint& p )              *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 *        bool operator == ( GLintPoint p1, GLintPoint p2 )                 *
 *        bool operator != ( GLintPoint p1, GLintPoint p2 )                 *
 *        GLintPoint operator + ( GLintPoint p1, GLintPoint p2 )            *
 *        GLintPoint operator - ( GLintPoint p1, GLintPoint p2 )            *
 *        GLintPoint operator * ( GLdouble scale, GLintPoint c )            *
 *        GLintPoint operator * ( GLintPoint c, GLdouble scale )            *
 *        GLintPoint operator += ( GLintPoint p2 )                          *
 *        GLintPoint operator -= ( GLintPoint p2 )                          *
 *        GLintPoint operator *= ( GLdouble scale )                         *
 *        GLintPoint operator /= ( GLdouble scale )                         *
 *                                                                          *
 *                                                                          *
 *   Point2 --- real valued coordinate pair                                 *
 *     Constructor:                                                         *
 *       Point2( GLdouble x, GLdouble y )                                   *
 *     Selectors:                                                           *
 *       x();                                                               *
 *       y();                                                               *
 *       void glVertex() const                                              *
 *          --- calls glVertex2f with coordinates as arguments              *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, const Point2& p )           *
 *        istream& operator >> ( istream& ins, Point2& p )                  *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 *        bool operator == ( Point2 p1, Point2 p2 )                         *
 *        bool operator != ( Point2 p1, Point2 p2 )                         *
 *        Point2 operator + ( Point2 p1, Point2 p2 )                        *
 *        Point2 operator - ( Point2 p1, Point2 p2 )                        *
 *        Point2 operator * ( GLdouble scale, Point2 c )                    *
 *        Point2 operator * ( Point2 c, GLdouble scale )                    *
 *        Point2 operator += ( Point2 p2 )                                  *
 *        Point2 operator -= ( Point2 p2 )                                  *
 *        Point2 operator *= ( GLdouble scale )                             *
 *        Point2 operator /= ( GLdouble scale )                             *
 *                                                                          *
 *                                                                          *
 *   IntRect --- GLint aligned rectangle                                    *
 *     Constructor:                                                         *
 *       IntRect( GLint l=0, GLint r=0, GLint b=0; GLint t=0 );             *
 *     Selectors:                                                           *
 *       GLint left() const;                                                *
 *       GLint right() const;                                               *
 *       GLint bottom() const;                                              *
 *       GLint top() const;                                                 *
 *     Constant methods:                                                    *
 *       bool inside( GLintPoint p );                                       *
 *       void draw();                                                       *
 *     Operators:                                                           *
 *       ostream& operator << ( ostream& outs, const IntRect& r );          *
 *       istream& operator >> ( istream& ins, IntRect& r );                 *
 *                                                                          *
 *       bool operator == ( const IntRect& r1, const IntRect& r2 );         *
 *       bool operator != ( const IntRect& r1, const IntRect& r2 );         *
 *      Translation                                                         *
 *         IntRect + GLintPoint translates rect by p.x() and p.y()          *
 *       IntRect operator + ( const IntRect& r, GLintPoint p )              *
 *       IntRect operator + ( GLintPoint p, const IntRect& r )              *
 *       IntRect operator - ( const IntRect& r, GLintPoint p )              *
 *       IntRect operator += (GLintPoint p )                                *
 *       IntRect operator -= (GLintPoint p )                                *
 *      Scaling                                                             *
 *         IntRect * Point2 ---                                             *
 *                    scales size and position in x and y independently     *
 *       IntRect operator * ( const IntRect& r, Point2 scale )              *
 *       IntRect operator * ( Point2 scale, const IntRect& r )              *
 *       IntRect operator *= (Point2 scale )                                *
 *       IntRect operator /= (Point2 scale )                                *
 *         IntRect * GLdouble --- scales size of rect, origin unchanged     *
 *       IntRect operator * ( const IntRect& r, GLdouble scale )            *
 *       IntRect operator * ( GLdouble scale, const IntRect& r )            *
 *       IntRect operator / ( const IntRect& r, GLdouble scale )            *
 *       IntRect operator *= (GLdouble scale )                              *
 *       IntRect operator /= (GLdouble scale )                              *
 *                                                                          *
 *                                                                          *
 *   RealRect --- real aligned rectangle                                    *
 *     Constructor:                                                         *
 *       RealRect( GLdouble l=0, GLdouble r=0, GLdouble b=0; GLdouble t=0 ) *
 *     Selectors:                                                           *
 *       GLdouble left() const;                                             *
 *       GLdouble right() const;                                            *
 *       GLdouble bottom() const;                                           *
 *       GLdouble top() const;                                              *
 *     Constant methods:                                                    *
 *       bool inside( Point2 p );                                           *
 *       void draw();                                                       *
 *     Operators:                                                           *
 *       ostream& operator << ( ostream& outs, const RealRect& r );         *
 *       istream& operator >> ( istream& ins, RealRect& r );                *
 *                                                                          *
 *       bool operator == ( const RealRect& r1, const RealRect& r2 );       *
 *       bool operator != ( const RealRect& r1, const RealRect& r2 );       *
 *      Translation                                                         *
 *         RealRect + Point2 translates rect by p.x() and p.y()             *
 *       RealRect operator + ( const RealRect& r, Point2 p )                *
 *       RealRect operator + ( Point2 p, const RealRect& r )                *
 *       RealRect operator - ( const RealRect& r, Point2 p )                *
 *       RealRect operator += ( Point2 p )                                  *
 *       RealRect operator -= ( Point2 p )                                  *
 *      Scaling                                                             *
 *         RealRect * Point2 ---                                            *
 *                    scales size and position in x and y independently     *
 *       RealRect operator * ( const RealRect& r, Point2 scale )            *
 *       RealRect operator * ( Point2 scale, const RealRect& r )            *
 *       RealRect operator *= ( Point2 scale )                              *
 *       RealRect operator /= ( Point2 scale )                              *
 *         RealRect * GLdouble --- scales size of rect, origin unchanged    *
 *       RealRect operator * ( const RealRect& r, GLdouble scale )          *
 *       RealRect operator * ( GLdouble scale, const RealRect& r )          *
 *       RealRect operator / ( const RealRect& r, GLdouble scale )          *
 *       RealRect operator *= ( GLdouble scale )                            *
 *       RealRect operator /= ( GLdouble scale )                            *
 *                                                                          *
 *                                                                          *
 *   GLcolor3 --- triple of GLfloat                                         *
 *     Constructor:                                                         *
 *       GLcolor3( GLfloat red, GLfloat green, GLfloat blue )               *
 *     Selectors:                                                           *
 *       red();                                                             *
 *       green();                                                           *
 *       blue();                                                            *
 *       void glColor() const                                               *
 *         --- calls glColor3f with components                              *
 *      Operators:                                                          *
 *          -- insertion and extraction operators                           *
 *        ostream& operator << ( ostream& outs, GLcolor3& const  c )        *
 *        istream& operator >> ( istream& ins, GLcolor3&  p )               *
 *                                                                          *
 *        bool operator == ( GLcolor3 c1, GLcolor3 c2 )                     *
 *        bool operator != ( GLcolor3 c1, GLcolor3 c2 )                     *
 *        GLcolor3 operator + ( GLcolor3 c1, GLcolor3 c2 )                  *
 *        GLcolor3 operator - ( GLcolor3 c1, GLcolor3 c2 )                  *
 *        GLcolor3 operator * ( GLdouble scale, GLcolor3 c )                *
 *        GLcolor3 operator * ( GLcolor3 c, GLdouble scale )                *
 *        GLcolor3 operator / ( GLcolor3 c, GLdouble scale )                *
 *                                                                          *
 *      Constants:                                                          *
 *       GLcolor3 GLblack3                                                  *
 *       GLcolor3 GLwhite3                                                  *
 *       GLcolor3 GLred3                                                    *
 *       GLcolor3 GLyellow3                                                 *
 *       GLcolor3 GLgreen3                                                  *
 *       GLcolor3 GLcyan3                                                   *
 *       GLcolor3 GLblue3                                                   *
 *       GLcolor3 GLmagenta3                                                *
 *                                                                          *
 *                                                                          *
 *   GLcolor4 --- quadruple of GLfloat                                      *
 *       GLcolor3( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )*
 *     Selectors:                                                           *
 *       red();                                                             *
 *       green();                                                           *
 *       blue();                                                            *
 *       alpha();                                                           *
 *       void glColor() const                                               *
 *         --- calls glColor4f with components                              *
 *      Operators:                                                          *
 *          -- insertion and extraction operators                           *
 *        ostream& operator << ( ostream& outs, GLcolor4& const  c )        *
 *        istream& operator >> ( istream& ins, GLcolor4&  p )               *
 *                                                                          *
 *        bool operator == ( GLcolor4 c1, GLcolor4 c2 )                     *
 *        bool operator != ( GLcolor4 c1, GLcolor4 c2 )                     *
 *        GLcolor4 operator + ( GLcolor4 c1, GLcolor4 c2 )                  *
 *        GLcolor4 operator - ( GLcolor4 c1, GLcolor4 c2 )                  *
 *        GLcolor4 operator * ( GLdouble scale, GLcolor4 c )                *
 *        GLcolor4 operator * ( GLcolor4 c, GLdouble scale )                *
 *        GLcolor4 operator / ( GLcolor4 c, GLdouble scale )                *
 *                                                                          *
 *      Constants:                                                          *
 *       GLcolor4 GLblack4                                                  *
 *       GLcolor4 GLwhite4                                                  *
 *       GLcolor4 GLred4                                                    *
 *       GLcolor4 GLyellow4                                                 *
 *       GLcolor4 GLgreen4                                                  *
 *       GLcolor4 GLcyan4                                                   *
 *       GLcolor4 GLblue4                                                   *
 *       GLcolor4 GLmagenta4                                                *
 *                                                                          *
 *                                                                          *
 *    GLpointV --- GLpoint vectors                                          *
 *    template <class PointType, class ColorType>                           *
 *    class GLpointV                                                        *
 *      --- Vector of zero or more points of PointType along with a         *
 *          color of ColorType                                              *
 *     Constructors:                                                        *
 *       GLpointV(ColorType c = ColorType() )                               *
 *       GLpointV( PointType p, ColorType c = ColorType() )                 *
 *     Selectors:                                                           *
 *       ColorType color( void ) const                                      *
 *       PointType operator []( size_t i ) const                            *
 *       bool empty( void ) const                                           *
 *       size_t size( void ) const                                          *
 *       void draw() const                                                  *
 *         --- generates sequence of GL calls to generate sequence of       *
 *             colored vertices                                             *
 *     Mutators:                                                            *
 *       void setColor( ColorType c )                                       *
 *       void clear( void )                                                 *
 *       void addPoint( PointType p )                                       *
 *         --- adds point to end of sequence                                *
 *       PointType& operator []( size_t i )                                 *
 *         --- index operator                                               *
 *      Operators:                                                          *
 *        ostream& operator << ( ostream& outs, const GLpointV& v )         *
 *        istream& operator >> ( istream& ins, GLpointV& v )                *
 *          -- insertion and extraction operators                           *
 *                                                                          *
 *                                                                          *
 * Namespace: GLTYPES                                                       *
 * Link with gltypes.o                                                      *
 ****************************************************************************/
#ifndef GLTYPES_H
#define GLTYPES_H

#include <X11/X.h>    // Basic X library
#include "glheaders.OSX.hpp"

#include <cmath>    // For sqrt
#include <vector>
#include <cassert>
#include <iostream>

namespace GLTYPES
{
/****************************************************************************
 *  GLintPoint --- Integer valued 2-dimensional point                       *
 ****************************************************************************/
  class GLintPoint
  {
  public:
    // Constructor
    GLintPoint( GLint x= 0, GLint y=0 )
    {
      _x = x;
      _y = y;
    }
      
    // Selectors
    GLint x() const { return _x; }
    GLint y() const { return _y; }
    void glVertex() const { glVertex2i( _x, _y ); }

    // Operators
    inline GLintPoint operator += ( GLintPoint p2 );
    inline GLintPoint operator -= ( GLintPoint p2 );
    inline GLintPoint operator *= ( GLdouble scale );
    inline GLintPoint operator /= ( GLdouble scale );
    
  private:
    GLint _x, _y;
  };

  // Operators:
  
  // I/O
  std::ostream& operator << ( std::ostream& outs, const GLintPoint& p );
  
  std::istream& operator >> ( std::istream& ins, GLintPoint& p );

  // Equality
  inline bool operator == ( GLintPoint p1, GLintPoint p2 );
  inline bool operator != ( GLintPoint p1, GLintPoint p2 );

  // Componentwise addition and subtraction
  inline GLintPoint operator + ( GLintPoint p1, GLintPoint p2 );
  inline GLintPoint operator - ( GLintPoint p1, GLintPoint p2 );

  // Scalar multiplication
  inline GLintPoint operator * ( GLdouble scale, GLintPoint c );
  inline GLintPoint operator * ( GLintPoint c, GLdouble scale );
  inline GLintPoint operator / ( GLintPoint c, GLdouble scale );

/****************************************************************************
 *  Point2 --- Real valued 2-dimensional point                              *
 ****************************************************************************/
  class Point2
  {
  public:
    // Constructor
    Point2( GLdouble x= 0, GLdouble y=0 )
    {
      _x = x;
      _y = y;
    }
      
    // Selectors
    GLdouble x() const { return _x; }
    GLdouble y() const { return _y; }
    void glVertex() const { glVertex2f( _x, _y ); }

    // Operators
    inline Point2 operator += ( Point2 p2 );
    inline Point2 operator -= ( Point2 p2 );
    inline Point2 operator *= ( GLdouble scale );
    inline Point2 operator /= ( GLdouble scale );
  

  private:
    GLdouble _x, _y;
  };

  // Operators:
  
  // I/O
  std::ostream& operator << ( std::ostream& outs, const Point2& p );
  
  std::istream& operator >> ( std::istream& ins, Point2& p );

  // Equality
  inline bool operator == ( Point2 p1, Point2 p2 );
  inline bool operator != ( Point2 p1, Point2 p2 );

  // Componentwise addition and subtraction
  inline Point2 operator + ( Point2 p1, Point2 p2 );
  inline Point2 operator - ( Point2 p1, Point2 p2 );

  // Scalar multiplication
  inline Point2 operator * ( GLdouble scale, Point2 c );
  inline Point2 operator * ( Point2 c, GLdouble scale );
  inline Point2 operator / ( Point2 c, GLdouble scale );


  
/****************************************************************************
 *   IntRect --- GLint aligned rectangle                                    *
 ****************************************************************************/
  class IntRect
  {
  public:
    // Constructor:
    IntRect( GLint l=0, GLint r=0, GLint b=0, GLint t=0 )
    {
      _left = l;
      _right = r;
      _bottom = b;
      _top = t;
    }

    // Selectors:
    GLint left() const { return _left; }
    GLint right() const { return _right; }
    GLint bottom() const { return _bottom; }
    GLint top() const { return _top; }

    //Constant methods:
    inline bool inside( GLintPoint p ) const;
    inline void draw();

    // Operators:
    inline IntRect operator += (GLintPoint p );
    inline IntRect operator -= (GLintPoint p );
    inline IntRect operator *= (Point2 scale );
    inline IntRect operator *= ( GLdouble scale );
    inline IntRect operator /= (Point2 scale );
    inline IntRect operator /= ( GLdouble scale );

  private:
    // Member variables
    GLint _left, _right, _bottom, _top;
  };

  // Operators:
  
  // I/O
  std::ostream& operator << ( std::ostream& outs, const IntRect& r );
  std::istream& operator >> ( std::istream& ins, IntRect& r );
  
  // Equality
  inline bool operator == ( const IntRect& r1, const IntRect& r2 );
  inline bool operator != ( const IntRect& r1, const IntRect& r2 );
  
  // Translation 
  //  IntRect + GLintPoint translates rect by p.x() and p.y()
  inline IntRect operator + ( const IntRect& r, GLintPoint p );
  inline IntRect operator + ( GLintPoint p, const IntRect& r );
  inline IntRect operator - ( const IntRect& r, GLintPoint p );
  
  // IntRect * Point2 --- scales size and position in x and y independently
  inline IntRect operator * ( const IntRect& r, Point2 scale );
  inline IntRect operator * ( Point2 scale, const IntRect& r );

  // IntRect * GLdouble --- scales size of rect, origin unchanged 
  IntRect operator * ( const IntRect& r, GLdouble scale );
  IntRect operator * ( GLdouble scale, const IntRect& r );
  IntRect operator / ( const IntRect& r, GLdouble scale );


/****************************************************************************
 *   RealRect --- real aligned rectangle                                    *
 ****************************************************************************/
  class RealRect
  {
  public:
    // Constructor:
    RealRect( GLdouble l=0, GLdouble r=0, GLdouble b=0, GLdouble t=0 )
    {
      _left = l;
      _right = r;
      _bottom = b;
      _top = t;
    }

    // Selectors:
    GLdouble left() const { return _left; }
    GLdouble right() const { return _right; }
    GLdouble bottom() const { return _bottom; }
    GLdouble top() const { return _top; }

    //Constant methods:
    inline bool inside( Point2 p ) const;
    inline void draw();

    // Operators:
    inline RealRect operator += ( Point2 p );
    inline RealRect operator -= ( Point2 p );
    inline RealRect operator *= ( Point2 scale );
    inline RealRect operator /= ( Point2 scale );
    inline RealRect operator *= ( GLdouble scale );
    inline RealRect operator /= ( GLdouble scale );

  private:
    // Member variables
    GLdouble _left, _right, _bottom, _top;
  };

  std::ostream& operator << ( std::ostream& outs, const RealRect& r );
  std::istream& operator >> ( std::istream& ins, RealRect& r );
  
  inline bool operator == ( const RealRect& r1, const RealRect& r2 );
  inline bool operator != ( const RealRect& r1, const RealRect& r2 );

  inline RealRect operator + ( const RealRect& r, Point2 p );
  inline RealRect operator + ( Point2 p, const RealRect& r );
  inline RealRect operator - ( const RealRect& r, Point2 p );

  // RealRect * Point2 --- scales size and position in x and y independently
  inline RealRect operator * ( const RealRect& r, Point2 scale );
  inline RealRect operator * ( Point2 scale, const RealRect& r );
  inline RealRect operator / ( Point2 scale, const RealRect& r );

  // RealRect * GLdouble --- scales size of rect, origin unchanged 
  RealRect operator * ( const RealRect& r, GLdouble scale );
  RealRect operator * ( GLdouble scale, const RealRect& r );
  RealRect operator / ( const RealRect& r, GLdouble scale );


/****************************************************************************
 *  GLcolor3                                                                *
 ****************************************************************************/
  class GLcolor3
  {
  public:
    // Constructor
    GLcolor3 ( GLfloat red = 0.0 , GLfloat green = 0.0, 
               GLfloat blue = 0.0 )
    {
      _r = red;
      _g = green;
      _b = blue;
    }
    // Selectors
    GLfloat red() const { return _r; }
    GLfloat green() const { return _g; }
    GLfloat blue() const { return _b; }

    void glColor() const { glColor3f( _r, _g, _b ); }

  private:
    GLfloat _r, _g, _b;
  };

  std::istream& operator >> ( std::istream& ins, GLcolor3& c );

  std::ostream& operator << ( std::ostream& outs, const GLcolor3& c );

  inline bool operator == ( GLcolor3 c1, GLcolor3 c2 );
  inline bool operator != ( GLcolor3 c1, GLcolor3 c2 );

  inline GLcolor3 operator + ( GLcolor3 c1, GLcolor3 c2 );
  inline GLcolor3 operator - ( GLcolor3 c1, GLcolor3 c2 );
  inline GLcolor3 operator * ( GLdouble scale, GLcolor3 c );
  inline GLcolor3 operator * ( GLcolor3 c, GLdouble scale );
  inline GLcolor3 operator / ( GLcolor3 c, GLdouble scale );
  // Constants
  const GLcolor3 GLblack3 = GLcolor3( 0.0, 0.0, 0.0 );
  const GLcolor3 GLwhite3 = GLcolor3( 1.0, 1.0, 1.0 );
  const GLcolor3 GLred3 = GLcolor3( 1.0, 0.0, 0.0 );
  const GLcolor3 GLyellow3 = GLcolor3( 1.0, 1.0, 0.0 );
  const GLcolor3 GLgreen3 = GLcolor3( 0.0, 1.0, 0.0 );
  const GLcolor3 GLcyan3 = GLcolor3( 0.0, 1.0, 1.0 );
  const GLcolor3 GLblue3 = GLcolor3( 0.0, 0.0, 1.0 );
  const GLcolor3 GLmagenta3 = GLcolor3( 1.0, 0.0, 1.0 );

/****************************************************************************
 *  GLcolor4                                                                *
 ****************************************************************************/
  class GLcolor4
  {
  public:
    // Constructor
    GLcolor4 ( GLfloat red = 0.0, 
               GLfloat green = 0.0, 
               GLfloat blue = 0.0, 
               GLfloat alpha = 1.0)
    {
      _r = red;
      _g = green;
      _b = blue;
    }
    // Selectors
    GLfloat red() const { return _r; }
    GLfloat green() const { return _g; }
    GLfloat blue() const { return _b; }
    GLfloat alpha() const { return _a; }

    void glColor() const { glColor4f( _r, _g, _b, _a ); }

  private:
    GLfloat _r, _g, _b, _a;
  };

  std::istream& operator >> ( std::istream& ins, GLcolor4& c );

  std::ostream& operator << ( std::ostream& outs, const GLcolor4& c );

  inline bool operator == ( GLcolor4 c1, GLcolor4 c2 );
  inline bool operator != ( GLcolor4 c1, GLcolor4 c2 );

  inline GLcolor4 operator + ( GLcolor4 c1, GLcolor4 c2 );
  inline GLcolor4 operator - ( GLcolor4 c1, GLcolor4 c2 );
  inline GLcolor4 operator * ( GLdouble scale, GLcolor4 c );
  inline GLcolor4 operator * ( GLcolor4 c, GLdouble scale );
  inline GLcolor4 operator / ( GLcolor4 c, GLdouble scale );

  // Constants
  const GLcolor4 GLblack4 = GLcolor4( 0.0, 0.0, 0.0, 1.0 );
  const GLcolor4 GLwhite4 = GLcolor4( 1.0, 1.0, 1.0, 1.0 );
  const GLcolor4 GLred4 = GLcolor4( 1.0, 0.0, 0.0, 1.0 );
  const GLcolor4 GLyellow4 = GLcolor4( 1.0, 1.0, 0.0, 1.0 );
  const GLcolor4 GLgreen4 = GLcolor4( 0.0, 1.0, 0.0, 1.0 );
  const GLcolor4 GLcyan4 = GLcolor4( 0.0, 1.0, 1.0, 1.0 );
  const GLcolor4 GLblue4 = GLcolor4( 0.0, 0.0, 1.0, 1.0 );
  const GLcolor4 GLmagenta4 = GLcolor4( 1.0, 0.0, 1.0, 1.0 );




/****************************************************************************
 * GLpointV                                                                 *
 ****************************************************************************/
  template <class PointType, class ColorType>
  class GLpointV
  {
  public:

    GLpointV(ColorType c = ColorType() )
    {
      _color = c;
    }

    GLpointV( PointType p, ColorType c = ColorType() )
    {
      _color = c;
      _points.push_back( p );
    }

    // Selectors
    bool empty( void ) const { return _points.empty(); }

    size_t size( void ) const { return _points.size(); } 

    ColorType color( void ) const { return _color; }

    const PointType& operator []( size_t i ) const { return _points[i]; }

    void draw() const;

    // Mutators
    PointType& operator []( size_t i ) { return _points[i]; }
  
    void addPoint( PointType p ) { _points.push_back( p ); }

    void clear( void ) { _points.clear(); }

    void setColor( ColorType c ) { _color = c; }

  private:
    ColorType _color;
    std::vector<PointType> _points;
  };

/****************************************************************************
 ****************************************************************************
 ** Compile-time implementation                                            **
 **   inline and template functions                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 *  GLintPoint --- Integer valued 2-dimensional point                       *
 ****************************************************************************/
  // Equality
  inline bool operator == ( GLintPoint p1, GLintPoint p2 )
  {
    return ( p1.x() == p2.x() && p1.y() == p2.y() );
  }

  inline bool operator != ( GLintPoint p1, GLintPoint p2 )
  {
    return ( ! (p1 == p2) );
  }

  // Componentwise addition and subtraction
  inline GLintPoint operator + ( GLintPoint p1, GLintPoint p2 )
  {
    return GLintPoint( p1.x()+p2.x(), p1.y()+p2.y() );
  }

  inline GLintPoint operator - ( GLintPoint p1, GLintPoint p2 )
  {
    return GLintPoint( p1.x()-p2.x(), p1.y()-p2.y() );
  }

  inline GLintPoint GLintPoint::operator += ( GLintPoint p2 )
  {
    _x += p2.x();
    _y += p2.y();
    return *this;
  }

  inline GLintPoint GLintPoint::operator -= ( GLintPoint p2 )
  {
    _x -= p2.x();
    _y -= p2.y();
    return *this;
  }

  // Scalar multiplication
  inline GLintPoint operator * ( GLdouble scale, GLintPoint c )
  {
    return GLintPoint( static_cast<GLint>(rint( c.x()*scale)), 
                       static_cast<GLint>(rint( c.y()*scale)) );
  }

  inline GLintPoint operator * ( GLintPoint c, GLdouble scale )
  {
    return GLintPoint( static_cast<GLint>(rint( c.x()*scale)), 
                       static_cast<GLint>(rint( c.y()*scale)) );
  }

  inline GLintPoint operator / ( GLintPoint c, GLdouble scale )
  {
    return GLintPoint( static_cast<GLint>(rint( c.x()/scale)), 
                       static_cast<GLint>(rint( c.y()/scale)) );
  }

  inline GLintPoint GLintPoint::operator *= ( GLdouble scale )
  {
    _x = static_cast<GLint>(rint( _x * scale ));
    _y = static_cast<GLint>(rint( _y * scale ));
    return *this;
  }

  inline GLintPoint GLintPoint::operator /= ( GLdouble scale )
  {
    _x = static_cast<GLint>(rint( _x / scale ));
    _y = static_cast<GLint>(rint( _x / scale ));
    return *this;
  }

/****************************************************************************
 *  Point2 --- Real valued 2-dimensional point                              *
 ****************************************************************************/
  // Equality
  inline bool operator == ( Point2 p1, Point2 p2 )
  {
    return ( p1.x() == p2.x() && p1.y() == p2.y() );
  }

  inline bool operator != ( Point2 p1, Point2 p2 )
  {
    return ( ! (p1 == p2) );
  }

  // Componentwise addition and subtraction
  inline Point2 operator + ( Point2 p1, Point2 p2 )
  {
    return Point2( p1.x()+p2.x(), p1.y()+p2.y() );
  }
  
  inline Point2 operator - ( Point2 p1, Point2 p2 )
  {
    return Point2( p1.x()-p2.x(), p1.y()-p2.y() );
  }
  
  inline Point2 Point2::operator += ( Point2 p2 )
  {
    _x += p2.x();
    _y += p2.y();
    return *this;
  }
  
  inline Point2 Point2::operator -= ( Point2 p2 )
  {
    _x -= p2.x();
    _y -= p2.y();
    return *this;
  }
  
  // Scalar multiplication
  inline Point2 operator * ( GLdouble scale, Point2 c )
  {
    return Point2( c.x()*scale, c.y()*scale );
  }

  inline Point2 operator * ( Point2 c, GLdouble scale )
  {
    return Point2( c.x()*scale, c.y()*scale );
  }

  
  inline Point2 operator / ( Point2 c, GLdouble scale )
  {
    return Point2( c.x()/scale, c.y()/scale );
  }

  
  inline Point2 Point2::operator *= ( GLdouble scale )
  {
    _x *= scale;
    _y *= scale;
    return *this;
  }

  inline Point2 Point2::operator /= ( GLdouble scale )
  {
    _x /= scale;
    _y /= scale;
    return *this;
  }


/****************************************************************************
 *   IntRect --- GLint aligned rectangle                                    *
 ****************************************************************************/
  inline bool IntRect::inside( GLintPoint p ) const
  {
    GLintPoint d0 = p - GLintPoint(left(), bottom()); // deltas point to orig
    GLintPoint d1 = GLintPoint(right(), top()) - p;   // deltas diag to point
    // In block if both components of deltas agree in sign
    return ( d0.x()*d1.x() >= 0 && d0.y()*d1.y() >= 0 );
  }

    // Operators:
  inline void IntRect::draw()
  {
    glBegin(GL_LINE_LOOP);
    glVertex2i( _left, _bottom );
    glVertex2i( _left, _top );
    glVertex2i( _right, _top );
    glVertex2i( _right, _bottom );
    glEnd();
  }      

  // Equality
  inline bool operator == ( const IntRect& r1, const IntRect& r2 )
  { 
    return ( r1.left() == r2.left() && r1.right() == r2.right() &&
             r1.bottom() == r2.bottom() && r1.top() == r2.top()   );
  }
  
  inline bool operator != ( const IntRect& r1, const IntRect& r2 )
  {
    return ( ! (r1 == r2) );
  }
  
  // Translation 
  //  IntRect + GLintPoint translates rect by p.x() and p.y()
  inline IntRect operator + ( const IntRect& r, GLintPoint p )
  {
    return ( IntRect ( r.left() + p.x(), r.right() + p.x(),
                       r.bottom() + p.y(), r.top() + p.y() ) );
  }
  
  inline IntRect operator + ( GLintPoint p, const IntRect& r )
  {
    return ( IntRect( r.left() + p.x(), r.right() + p.x(),
                      r.bottom() + p.y(), r.top() + p.y() ) );
  }
  
  inline IntRect operator - ( const IntRect& r, GLintPoint p )
  {
    return ( IntRect ( r.left() - p.x(), r.right() - p.x(),
                       r.bottom() - p.y(), r.top() - p.y() ) );
  }
  
  inline IntRect IntRect::operator += (GLintPoint p )
  {
    _left += p.x();
    _right += p.x();
    _bottom += p.y();
    _top += p.y();
    return *this;
  }

  inline IntRect IntRect::operator -= (GLintPoint p )
  {
     _left -= p.x();
    _right -= p.x();
    _bottom -= p.y();
    _top -= p.y();
    return *this;
 }

  // IntRect * Point2 --- scales size and position in x and y independently
  inline IntRect operator * ( const IntRect& r, Point2 scale )
  {
    return ( IntRect( static_cast<GLint>(rint( r.left()* scale.x())), 
                      static_cast<GLint>(rint( r.right() * scale.x())),
                      static_cast<GLint>(rint( r.bottom() * scale.y())), 
                      static_cast<GLint>(rint( r.top() * scale.y())) ) );
  }
  
  inline IntRect operator * ( Point2 scale, const IntRect& r )
  {
    return ( IntRect( static_cast<GLint>(rint( r.left()* scale.x())), 
                      static_cast<GLint>(rint( r.right() * scale.x())),
                      static_cast<GLint>(rint( r.bottom() * scale.y())), 
                      static_cast<GLint>(rint( r.top() * scale.y())) ) );
  }

  inline IntRect operator / ( const IntRect& r, Point2 scale )
  {
    return ( IntRect( static_cast<GLint>(rint( r.left()/ scale.x())), 
                      static_cast<GLint>(rint( r.right() / scale.x())),
                      static_cast<GLint>(rint( r.bottom() / scale.y())), 
                      static_cast<GLint>(rint( r.top() / scale.y())) ) );
  }
  
  inline IntRect IntRect::operator *= (Point2 scale )
   {
    _left = static_cast<GLint>(rint( _left * scale.x()));
    _right = static_cast<GLint>(rint( _right * scale.x()));
    _bottom = static_cast<GLint>(rint( _bottom * scale.y()));
    _top = static_cast<GLint>(rint( _top * scale.y()));
    return *this;
  }

  inline IntRect IntRect::operator *= ( GLdouble scale )
  {
    return *this = *this * scale;
  }

  inline IntRect IntRect::operator /= (Point2 scale )
  {
    _left = static_cast<GLint>(rint( _left * scale.x()));
    _right = static_cast<GLint>(rint( _right * scale.x()));
    _bottom = static_cast<GLint>(rint( _bottom * scale.y()));
    _top = static_cast<GLint>(rint( _top * scale.y()));
    return *this;
  }

  inline IntRect IntRect::operator /= ( GLdouble scale )
  {
    return *this = *this / scale;
  }

/****************************************************************************
 *   RealRect --- real aligned rectangle                                    *
 ****************************************************************************/
  inline bool RealRect::inside( Point2 p ) const
  {
    Point2 d0 = p - Point2(left(), bottom()); // deltas point to orig
    Point2 d1 = Point2(right(), top()) - p;   // deltas diag to point
    // In block if both components of deltas agree in sign
    return ( d0.x()*d1.x() >= 0 && d0.y()*d1.y() >= 0 );
  }

  // Operators:
  inline void RealRect::draw()
  {
    glBegin(GL_LINE_LOOP);
    glVertex2d( _left, _bottom );
    glVertex2d( _left, _top );
    glVertex2d( _right, _top );
    glVertex2d( _right, _bottom );
    glEnd();
  }      

  inline bool operator == ( const RealRect& r1, const RealRect& r2 )
  { 
    return ( r1.left() == r2.left() && r1.right() == r2.right() &&
             r1.bottom() == r2.bottom() && r1.top() == r2.top()   );
  }

  inline bool operator != ( const RealRect& r1, const RealRect& r2 )
  {
    return ( ! (r1 == r2) );
  }

  inline RealRect operator + ( const RealRect& r, Point2 p )
  {
    return ( RealRect ( r.left() + p.x(), r.right() + p.x(),
                        r.bottom() + p.y(), r.top() + p.y() ) );
  }

  inline RealRect operator + ( Point2 p, const RealRect& r )
  {
    return ( RealRect( r.left() + p.x(), r.right() + p.x(),
                       r.bottom() + p.y(), r.top() + p.y() ) );
  }

  inline RealRect operator - ( const RealRect& r, Point2 p )
  {
    return ( RealRect ( r.left() - p.x(), r.right() - p.x(),
                        r.bottom() - p.y(), r.top() - p.y() ) );
  }

  inline RealRect RealRect::operator += ( Point2 p )
  {
    _left += p.x();
    _right += p.x();
    _bottom += p.y();
    _top += p.y();
    return *this;
  }

  inline RealRect RealRect::operator -= ( Point2 p )
  {
    _left -= p.x();
    _right -= p.x();
    _bottom -= p.y();
    _top -= p.y();
    return *this;
  }
 

// RealRect * Point2 --- scales size and position in x and y independently
  inline RealRect operator * ( const RealRect& r, Point2 scale )
  {
    return ( RealRect( r.left()* scale.x(), r.right() * scale.x(),
                       r.bottom() * scale.y(), r.top() * scale.y()) );
  }
  
  inline RealRect operator * ( Point2 scale, const RealRect& r )
  {
    return ( RealRect( r.left()* scale.x(), r.right() * scale.x(),
                       r.bottom() * scale.y(), r.top() * scale.y()) );
  }

  inline RealRect operator / ( const RealRect& r, Point2 scale )
  {
    return ( RealRect( r.left()/ scale.x(), r.right() / scale.x(),
                       r.bottom() / scale.y(), r.top() / scale.y()) );
  }
  
  inline RealRect RealRect::operator *= ( Point2 scale )
  {
    _left *= scale.x();
    _right *= scale.x();
    _bottom *= scale.y();
    _top *= scale.y();
    return *this;
  }
  
  inline RealRect RealRect::operator /= ( Point2 scale )
  {
    _left /= scale.x();
    _right /= scale.x();
    _bottom /= scale.y();
    _top /= scale.y();
    return *this;
  }

  inline RealRect RealRect::operator *= ( GLdouble scale )
  {
    return *this = *this * scale;
  }

  inline RealRect RealRect::operator /= ( GLdouble scale )
  {
    return *this = *this / scale;
  }

/****************************************************************************
 *  GLcolor3                                                                *
 ****************************************************************************/
  inline bool operator == ( GLcolor3 c1, GLcolor3 c2 )
  {
    return ( c1.red() == c2.red() && 
             c1.green() == c2.green() && 
             c1.blue() == c2.blue() );
  }

  inline bool operator != ( GLcolor3 c1, GLcolor3 c2 )
  {
    return ( ! (c1 == c2) );
  }

  inline GLcolor3 operator + ( GLcolor3 c1, GLcolor3 c2 )
  {
    return GLcolor3( c1.red()+c2.red(), 
                     c1.green()+c2.green(), 
                     c1.blue()+c2.blue()  );
  }

  inline GLcolor3 operator - ( GLcolor3 c1, GLcolor3 c2 )
  {
    return GLcolor3( c1.red()-c2.red(), 
                     c1.green()-c2.green(), 
                     c1.blue()-c2.blue() );
  }

  inline GLcolor3 operator * ( GLdouble scale, GLcolor3 c )
  {
    return GLcolor3( c.red()*scale, c.green()*scale, c.blue()*scale );
  }

  inline GLcolor3 operator * ( GLcolor3 c, GLdouble scale )
  {
    return GLcolor3( c.red()*scale, c.green()*scale, c.blue()*scale );
  }

  inline GLcolor3 operator / ( GLcolor3 c, GLdouble scale )
  {
    return GLcolor3( c.red()/scale, c.green()/scale, c.blue()/scale );
  }

/****************************************************************************
 *  GLcolor4                                                                *
 ****************************************************************************/
  inline bool operator == ( GLcolor4 c1, GLcolor4 c2 )
  {
    return ( c1.red() == c2.red() && 
             c1.green() == c2.green() && 
             c1.blue() == c2.blue() && 
             c1.alpha() == c2.alpha() );
  }

  inline bool operator != ( GLcolor4 c1, GLcolor4 c2 )
  {
    return ( ! (c1 == c2) );
  }

  inline GLcolor4 operator + ( GLcolor4 c1, GLcolor4 c2 )
  {
    return GLcolor4( c1.red()+c2.red(), 
                     c1.green()+c2.green(),
                     c1.blue()+c2.blue(), 
                     c1.alpha() );
  }

  inline GLcolor4 operator - ( GLcolor4 c1, GLcolor4 c2 )
  {
    return GLcolor4( c1.red()-c2.red(), 
                     c1.green()-c2.green(),
                     c1.blue()-c2.blue(), 
                     c1.alpha() );
  }

  inline GLcolor4 operator * ( GLdouble scale, GLcolor4 c )
  {
    return GLcolor4( c.red()*scale, c.green()*scale, c.blue()*scale, 
                     c.alpha() );
  }

  inline GLcolor4 operator * ( GLcolor4 c, GLdouble scale )
  {
    return GLcolor4( c.red()*scale, c.green()*scale, c.blue()*scale,
                     c.alpha() );
  }

  inline GLcolor4 operator / ( GLcolor4 c, GLdouble scale )
  {
    return GLcolor4( c.red()/scale, c.green()/scale, c.blue()/scale,
                     c.alpha() );
  }

/****************************************************************************
 * GLpointV                                                                 *
 ****************************************************************************/
  template <class PointType, class ColorType>
  std::istream& operator >> (std::istream& ins, GLpointV<PointType, ColorType>& v )
  {
    GLfloat red, green, blue;

    ins >> red >> green >> blue;
  
    v.setColor( ColorType( red, green, blue) );
    v.clear();

    size_t nPoints;

    ins >> nPoints;

    PointType p;

    while ( nPoints != 0 )
      {
        ins >> p;
        v.addPoint( p );
        nPoints -= 1;
      }
  
    return ins;
  }

  template <class PointType, class ColorType>
  std::ostream& operator << ( std::ostream& outs, 
                              const GLpointV<PointType, ColorType>& v)
  {
    outs << v.color() << "\n";
    size_t i = v.size();
    outs << i << "\n";
    while (i != 0 )
      {
        outs << v[v.size()-i] << "\n";
        i -= 1;
      }
    return outs;
  }

  template <class PointType, class ColorType>
  void GLpointV<PointType, ColorType>::draw() const
  {
    if ( _points.size() > 0 )
      {
        _color.glColor();
        if ( _points.size() == 1 )
          {
            glBegin(GL_POINTS);
          }
        else
          {
            glBegin(GL_LINE_STRIP);
          }
        for ( size_t i = 0; i < _points.size(); ++i )
          {
            _points[i].glVertex();
          }
        glEnd();
      }
  }

}
#endif


