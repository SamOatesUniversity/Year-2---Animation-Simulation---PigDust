/*
Copyright (c) 2010 Tyrone Davison, Teesside University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#ifndef __TWM_UTIL_GEOMETRY__
#define __TWM_UTIL_GEOMETRY__

#include "math.hpp"

namespace twm
{
  class Point {
  public:
    Point() : _point(0, 0, 0) {
    }

    Point( Vector v ) : _point(v) {
    }

    Point( float x, float y, float z ) : _point(x, y, z) {
    }

    Vector DisplacementFromOrigin() const {
      return _point;
    }

    float DistanceToPoint( Point ) const;
    Vector DisplacementToPoint( Point ) const;

  private:
    Vector _point;
  };

  class Plane {
  public:
    Plane() : _plane(0, 0, 1, 0) {
    }

    static Plane CreateFromPointAndNormal( Point point, Vector normal );

    Vector Normal() const {
      return Truncate(_plane);
    }

    float PerpendicularDistanceToPoint( Point point ) const;

  private:
    Plane( HVector hv ) : _plane(hv) {
    }

  private:
    HVector _plane;
  };

  class Sphere {
  public:
    Sphere() : _radius(0), _centre(0, 0, 0) {
    }

    static Sphere CreateFromPointAndRadius( Point centre, float radius ) {
      return Sphere(centre, radius);
    }

    Point Centre() const {
      return _centre;
    }

    float Radius() const {
      return _radius;
    }

    float PerpendicularDistanceToPoint( Point ) const;

  private:
    Sphere( Point centre, float radius ) : _centre(centre), _radius(radius) {
    }

  private:
    float _radius;
    Point _centre;
  };

  class Box {
  public:
    Box() : _dims(0, 0, 0) {
    }

    static Box CreateFromMatrixAndDims( Matrix xform, float sizeX, float sizeY, float sizeZ );

    static Box CreateFromDims( float sizeX, float sizeY, float sizeZ ) {
      return Box(Matrix(), Vector(sizeX, sizeY, sizeZ));
    }

    float SizeX() const {
      return _dims.x;
    }

    float SizeY() const {
      return _dims.y;
    }

    float SizeZ() const {
      return _dims.z;
    }

    Point Centre() const {
      return Point(_xform.m30, _xform.m31, _xform.m32);
    }

    Plane PlaneX() const;
    Plane PlaneY() const;
    Plane PlaneZ() const;
    float ProjectedSizeInDirection( Vector ) const;

  private:
    Box( const Matrix& xform, Vector dims ) : _xform(xform), _dims(dims) {
    }

  private:
    Matrix _xform;
    Vector _dims;
  };
}

#endif
