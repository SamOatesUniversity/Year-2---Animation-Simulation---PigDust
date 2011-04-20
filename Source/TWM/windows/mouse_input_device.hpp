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
#ifndef __TWM_WINDOWS_MOUSE_INPUT_DEVICE__
#define __TWM_WINDOWS_MOUSE_INPUT_DEVICE__

#include "input_device.hpp"
#include <string>
#include <boost/unordered_map.hpp>

namespace twm
{
  class MouseInputDevice : public IInputDevice
  {
  public: // IInputDevice implementation
    enum {
      kAxisX,
      kAxisY,
      kWheel,
      kLeftButton,
      kMiddleButton,
      kRightButton
    };
  public:
    bool GetButtonStatus( unsigned int i ) const;
    float GetAxisStatus( unsigned int i ) const;

  private:
    MouseInputDevice();
    ~MouseInputDevice();
  public:
    void SetCursorMotion( int deltaX, int deltaY );
    void SetWheelMotion( int delta );
    void SetButtonStatus( unsigned int i, bool pressed );
    void Update();
  private:
    struct Data
    {
      float axis[3];
      int button[3];

      Data() { axis[0] = axis[1] = axis[2] = 0; button[0] = button[1] = button[2] = 0; }
    };
  private:
    Data _read_data;
    Data _write_data;

  public: // singleton device dictionary
    static MouseInputDevice* GetDevice( const std::string& name ); // thread safe
    static void Init();
    static void Deinit();
    static bool IsReady() { return _lock != 0; }
    static MouseInputDevice* AddDevice( const std::string& ); // thread safe
    static void RemoveDevice( const std::string& );
  private:
    static boost::unordered_map< std::string, MouseInputDevice* > _devices;
    static void* _lock;
  };
}

#endif
