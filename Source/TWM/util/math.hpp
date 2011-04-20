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
#ifndef __TWM_UTIL_MATH__
#define __TWM_UTIL_MATH__

#define _USE_MATH_DEFINES
#include <cmath>
#include "twm/core/types.hpp"

namespace twm
{
  Vector Cross( const Vector&, const Vector& );
  float  Dot( const Vector&, const Vector& );
  float  Length( const Vector& );
  Vector Unit( const Vector& );

  Vector Standardize( const HVector& );
  Vector Truncate( const HVector& );

  Matrix Inverse( const Matrix& );
  Matrix Transpose( const Matrix& );

  namespace operators
  {
    Vector operator-( const Vector& );
    Vector operator+( const Vector&, const Vector& );
    Vector operator-( const Vector&, const Vector& );
    Vector operator*( float, const Vector& );
    Vector operator*( const Vector&, float );
    Vector operator/( const Vector&, float );

    const Vector& operator+=( Vector&, const Vector& );
    const Vector& operator-=( Vector&, const Vector& );
    const Vector& operator*=( Vector&, float );
    const Vector& operator/=( Vector&, float );

    HVector operator* ( const HVector&, const Matrix& );
    HVector operator* ( const Matrix&, const HVector& );

    const Matrix& operator*=( Matrix&, const Matrix& );
    const Matrix& operator+=( Matrix&, const Matrix& );
    const Matrix& operator-=( Matrix&, const Matrix& );
    const Matrix& operator*=( Matrix&, float );

    Matrix operator*( const Matrix&, const Matrix& );
    Matrix operator*( const Matrix&, float );
    Matrix operator*( float, const Matrix& );
    Matrix operator+( const Matrix&, const Matrix& );
    Matrix operator-( const Matrix&, const Matrix& );

    Colour operator-( const Colour& );
    Colour operator+( const Colour&, const Colour& );
    Colour operator-( const Colour&, const Colour& );
    Colour operator*( const Colour&, const Colour& );
    Colour operator*( float, const Colour& );
    Colour operator*( const Colour&, float );
    Colour operator/( const Colour&, float );

    const Colour& operator+=( Colour&, const Colour& );
    const Colour& operator-=( Colour&, const Colour& );
    const Colour& operator*=( Colour&, const Colour& );
    const Colour& operator*=( Colour&, float );
    const Colour& operator/=( Colour&, float );
  }
}

#endif
