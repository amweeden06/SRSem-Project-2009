/****************************************************************************
 *  component.h   Version 1                                                 *
 *   Component class --- base class for OpenGL components                   * 
 *   JRogers, Sept/2002                                                     *
 *   JRogers, Oct/2002 --- changed to gltypes.h (v1)                        *
 *                                                                          *
 *   Each component has its own world window (real coordinates) and         *
 *    viewport (GLint coordinates).                                         *
 *                                                                          *
 *   Constructor:                                                           *
 *                                                                          *
 *     Component( IntRect viewport = IntRect(0, 100, 0, 100),               *
 *                RealRect world = RealRect(0, 1, 0, 1) )                   *
 *                                                                          *
 *   Selectors:                                                             *
 *                                                                          *
 *     RealRect world( void ) const                                         *
 *     IntRect viewport( void ) const                                       *
 *     GLdouble w_width( void ) const                                       *
 *     GLdouble w_height( void ) const                                      *
 *     GLint v_width( void ) const                                          *
 *     GLint v_height( void ) const                                         *
 *     GLdouble w_aspect( void ) const                                      *
 *     GLdouble v_aspect( void ) const                                      *
 *                                                                          *
 *   Constant methods:                                                      *
 *                                                                          *
 *   void initDraw( void ) const                                            *
 *    Sets Projection matrix and viewport for this component's world window *
 *      and viewport. (This neither saves nor restores prior context.)      *
 *                                                                          *
 *   bool inside( GLintPoint p )                                            *
 *    true iff p is inside viewport                                         *
 *                                                                          *
 *   Mutators:                                                              *
 *                                                                          *
 *     void reMap( IntRect viewport )                                       *
 *       Remaps component into viewport                                     *
 *                                                                          *
 *     void reFrame( RealRect world )                                       *
 *       Resets component's world window to world                           *
 *                                                                          *
 *   Protected member functions:                                            *
 *                                                                          *
 *    Point2 vtow( GLintPoint p )                                           *
 *      Inverse world-->viewport mapping                                    *
 *                                                                          *
 *    GLintPoint wtov( Point2 )                                             *
 *      Explicit world-->viewport mapping                                   *
 *                                                                          *
 *                                                                          *
 * To use as base class:                                                    *
 *                                                                          *
 *  #include "component.h"                                                  *
 *                                                                          *
 *  class AComponent : public Component                                     *
 *  {                                                                       *
 *  public:                                                                 *
 *    AComponent( GLTYPES::IntRect viewport,// Add defaults                 *
 *                ---additional paramaters--- )                             *
 *    : Component( viewport, RealRect(world) ),  // Call base constructor   *
 *      ---other member initializations---                                  *
 *    // Typically, components will set their own world window              *
 *    //   but world could be a parameter of the constructor as well        *
 *    {                                     // If only the base constructor *
 *      ---body of constructor---           //  is needed, you may omit     *
 *    }                                     //  declaration of constructors *
 *                                          //  for the derived class       *
 *    ---Expose event handler---                                            *
 *    reDisplay()                                                           *
 *    {                                                                     *
 *      initDraw();                                                         *
 *      // Draw component                                                   *
 *    }                                                                     *
 *                                                                          *
 *    ---input events---                                                    *
 *    eventHandler( ..., int x, int y )                                     *
 *    {                                                                     *
 *      // Precondition: y is in viewport coordinates (origin@lower left)   *
 *      //  world position will be  vtow(GLintPoint(x,y))                   *
 *    }                                                                     *
 *                                                                          *
 *    ---additional member functions---     // Base class's functions are   *
 *                                          //  inherited, but may be       *
 *                                          //  overridden by declaring     *
 *                                          //  functions with same         *
 *                                          //  signature.  These may       *
 *                                          //  call base class's function  *
 *                                          //   as Component::fname()      *
 *  private:                                                                *
 *    ---additional member variables---     // Base class's variables are   *
 *                                          //   inherited                  *
 *  };                                                                      *
 *                                                                          *
 *  Libraries:                                                              *
 *   <cassert> --- for assert()                                             *
 *   <cmath> --- for rint()                                                 *
 *   "gltypes.h" --- version >= 1                                           *
 ****************************************************************************/
#ifndef COMPONENT_H
#define COMPONENT_H

#include <cassert>
#include <cmath>
#include "gltypes.1.h"

class Component
{
public:
  // Constructor
  Component( GLTYPES::IntRect viewport=GLTYPES::IntRect(0, 100, 0, 100),
             GLTYPES::RealRect world=GLTYPES::RealRect(0, 1, 0, 1)       )
  {
    _w = world;
    reMap(viewport);
  }

  // Selectors
  GLTYPES::RealRect world( void ) const { return _w; }

  GLTYPES::IntRect viewport( void ) const { return _v; }
  
  GLdouble w_width( void ) const { return _w.right()-_w.left();}

  GLdouble w_height( void ) const { return _w.top()-_w.bottom(); }
  
  GLint v_width( void ) const { return _v.right()-_v.left(); }

  GLint v_height( void ) const { return _v.top()-_v.bottom(); }

  GLdouble w_aspect( void ) const
  {
    return ( w_width()/w_height() );
  }

  GLdouble v_aspect( void ) const
  {
    return ( static_cast<GLdouble>(v_width()) / v_height() );
  }

  bool inside( GLTYPES::GLintPoint p ) const { return viewport().inside( p ); }

  // Constant methods
  void initDraw( void ) const
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(_w.left(), _w.right(), _w.bottom(), _w.top()); 
    glViewport(_v.left(), _v.bottom(), 
               _v.right()-_v.left(), _v.top()-_v.bottom() );
  }

  // Mutators
  void reMap( GLTYPES::IntRect viewport )
  {
    assert( viewport.right() >= viewport.left() );
    assert( viewport.top() >= viewport.bottom() );

    _v = viewport;
    if (_v.right() == _v.left() )
      _xScl = 0;
    else
      _xScl = (_w.right()-_w.left())/(_v.right()-_v.left());
    _xOff = _w.left()- _xScl*_v.left();
    if (_v.top() == _v.bottom() )
      _yScl = 0;
    else
      _yScl = (_w.top()-_w.bottom())/(_v.top()-_v.bottom());
    _yOff = _w.bottom()- _yScl*_v.bottom();
  }

  void reFrame( GLTYPES::RealRect world )
  {
    _w = world;
    reMap( _v );
  }

protected:
  // Protected member functions
  
  // vtow( p ) --- does inverse world->viewport map on point p
  GLTYPES::Point2 vtow( GLTYPES::GLintPoint p ) const
  {
    return ( GLTYPES::Point2( p.x()*_xScl + _xOff, p.y()*_yScl + _yOff ) );
  }

  // wtov( p ) ---  Explicit world-->viewport mapping 
  GLTYPES::GLintPoint wtov( GLTYPES::Point2 p ) const
  {
    return (GLTYPES::GLintPoint(static_cast<GLint>(rint((p.x()-_xOff)/_xScl)),
                                static_cast<GLint>(rint((p.y()-_yOff)/_yScl)))
            );
  }


private:
  // Member variables
  GLTYPES::RealRect _w;             // World window --- world coordinates
  GLTYPES::IntRect _v;              // Viewport --- screen coordinates
  GLdouble _xScl, _xOff;   // X scale and offset V->W mapping
  GLdouble _yScl, _yOff;   // Y scale and offset V->W mapping

}; 

#endif
