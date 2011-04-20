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
#ifndef __TWM_UTIL_USER_CONTROL__
#define __TWM_UTIL_USER_CONTROL__

#include "twm/core/entity.hpp"
#include "timer.hpp"

namespace twm
{
  class IInputDevice;

  class InspectionUserControl
  {
  public:
    InspectionUserControl();
    ~InspectionUserControl();
  public:
    enum Axis { kAxisY, kAxisZ };
  public:
    void Init( Entity entity, Axis up );
    void Init( Entity entity, Axis up, const Vector& initial_interest_point, float initial_orbit_x, float initial_orbit_y, float initial_dolly_z );
    void SetOrbitXInput( IInputDevice*, unsigned int axis, bool invert );
    void SetOrbitYInput( IInputDevice*, unsigned int axis, bool invert );
    void SetDollyInput( IInputDevice*, unsigned int axis, bool invert );
    void SetMoveXInput( IInputDevice*, unsigned int axis, bool invert );
    void SetMoveYInput( IInputDevice*, unsigned int axis, bool invert );
    void SetOrbitSpeed( float s );
    void SetMoveSpeed( float s );
    void SetDollySpeed( float s );
    Entity GetEntity();
    void DoUpdate(); // TODO
  private:
    void RecomputeXform( float, float );
  private:
    struct Input
    {
      IInputDevice* device;
      unsigned int axis;
      bool invert;

      Input() : device(0), axis(kAxisZ), invert(false) {}
    };
  private:
    Input _input_orbit_x;
    Input _input_orbit_y;
    Input _input_dolly_z;
    Input _input_move_x;
    Input _input_move_y;
    Entity _entity;
    float _heading;
    float _inclination;
    float _distance;
    float _rotate_speed;
    float _dolly_speed;
    float _move_speed;
    Vector _pos;
    bool _z_up;
    Timer _timer;
  };
}

#endif
