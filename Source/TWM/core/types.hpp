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
#ifndef __TWM_CORE_TYPES__
#define __TWM_CORE_TYPES__

namespace twm
{
  typedef unsigned int EntityId;
  typedef unsigned int ComponentId;
  typedef unsigned int ComponentType;
  typedef unsigned int CacheId;

  extern const EntityId kNullEntity;
  extern const ComponentId kNullComponent;
  extern const ComponentType kNullType;

  class Vector
  {
  public:
    float x, y, z;
  public:
    Vector() : x(0), y(0), z(0) {}
    Vector( float X, float Y, float Z ) : x(X), y(Y), z(Z) {}
  };

  class HVector
  {
  public:
    float x, y, z, w;
  public:
    HVector() : x(0), y(0), z(0), w(1) {}
    HVector( float X, float Y, float Z, float W ) : x(X), y(Y), z(Z), w(W) {}
    HVector( const Vector& v, float W ) : x(v.x), y(v.y), z(v.z), w(W) {}
  };

  class Matrix
  {
  public:
    float m00, m10, m20, m30;
    float m01, m11, m21, m31;
    float m02, m12, m22, m32;
    float m03, m13, m23, m33;
  public:
    Matrix() : m00(1), m10(0), m20(0), m30(0), m01(0), m11(1), m21(0), m31(0), m02(0), m12(0), m22(1), m32(0), m03(0), m13(0), m23(0), m33(1) {}
    Matrix( float M00, float M01, float M02, float M03, float M10, float M11, float M12, float M13, float M20, float M21, float M22, float M23, float M30, float M31, float M32, float M33 ) : m00(M00), m10(M10), m20(M20), m30(M30), m01(M01), m11(M11), m21(M21), m31(M31), m02(M02), m12(M12), m22(M22), m32(M32), m03(M03), m13(M13), m23(M23), m33(M33) {}
  };

  class Colour
  {
  public:
    float r, g, b;
  public:
    Colour() : r(1), g(1), b(1) {}
    Colour( float R, float G, float B ) : r(R), g(G), b(B) {}
  };

  class ColourAlpha
  {
  public:
    float r, g, b, a;
  public:
    ColourAlpha() : r(1), g(1), b(1), a(1) {}
    ColourAlpha( float R, float G, float B, float A ) : r(R), g(G), b(B), a(A) {}
    ColourAlpha( const Colour& c, float A ) : r(c.r), g(c.g), b(c.b), a(A) {}
  };
}

#endif
