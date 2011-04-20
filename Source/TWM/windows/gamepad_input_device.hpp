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
#ifndef __TWM_WINDOWS_GAMEPAD_INPUT_DEVICE__
#define __TWM_WINDOWS_GAMEPAD_INPUT_DEVICE__

#include "input_device.hpp"

namespace twm
{
  class GamepadInputDevice : public IInputDevice
  {
  public:
    enum Axes {
      kLeftThumbX,
      kLeftThumbY,
      kRightThumbX,
      kRightThumbY,
      kLeftTrigger,
      kRightTrigger
    };
    enum Buttons {
      kButtonA,
      kButtonB,
      kButtonX,
      kButtonY,
      kLeftShoulder,
      kRightShoulder,
      kLeftThumb,
      kRightThumb,
      kStart,
      kBack,
      kDPadUp,
      kDPadDown,
      kDPadLeft,
      kDPadRight
    };
  public:
    bool GetButtonStatus( unsigned int i ) const;
    float GetAxisStatus( unsigned int i ) const;
  public:
    void SetVibration( float low_freq_amplitude, float high_freq_amplitude );
  private:
    GamepadInputDevice( int id );
    ~GamepadInputDevice();
  public:
    bool IsConnected() const { return _connected; }
  private:
    bool _buttons[14];
    float _axes[6];
    bool _connected;
    int _id;
  
  public: // singleton device dictionary
    static GamepadInputDevice* GetDevice( unsigned int i );
    static void Init();
    static void Deinit();
    static void Update();
  private:
    static GamepadInputDevice* _devices[4];
  };
}

#endif
