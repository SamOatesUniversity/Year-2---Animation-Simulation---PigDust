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
#ifndef __TWM_WINDOWS_KEYBOARD_INPUT_DEVICE__
#define __TWM_WINDOWS_KEYBOARD_INPUT_DEVICE__

#include "input_device.hpp"
#include <string>
#include <boost/unordered_map.hpp>

namespace twm
{
  class KeyboardInputDevice : public IInputDevice
  {
  public:
    enum {
      kAxisX = 0,
      kAxisY = 1,
      kBack = 0x08,
      kTab = 0x09,
      kClear = 0x0C,
      kReturn = 0x0D,
      kShift = 0x10,
      kCtrl = 0x11,
      kAlt = 0x12,
      kEsc = 0x1B,
      kSpace = 0x20,
      kPageUp = 0x21,
      kPageDown = 0x22,
      kEnd = 0x23,
      kHome = 0x24,
      kLeft = 0x25,
      kUp = 0x26,
      kRight = 0x27,
      kDown = 0x28,
      kInsert = 0x2D,
      kDelete = 0x2E,
      kF1 = 0x70,
      kF2,
      kF3,
      kF4,
      kF5,
      kF6,
      kF7,
      kF8,
      kF9,
      kF10,
      kF11,
      kF12,
    };
  public:
    bool GetButtonStatus( unsigned int i ) const;
    float GetAxisStatus( unsigned int i ) const;

  private:
    KeyboardInputDevice();
    ~KeyboardInputDevice();
  public:
    void SetKeyStatus( unsigned int i, bool pressed );
    void Update();
  private:
    struct Data
    {
      int key[255];

      Data() { for ( unsigned int i=0; i<255; ++i ) key[i] = 0; }
    };
  private:
    Data _read_data;
    Data _write_data;

  public: // singleton device dictionary
    static KeyboardInputDevice* GetDevice( const std::string& name );
    static void Init();
    static void Deinit();
    static bool IsReady() { return _lock != 0; }
    static KeyboardInputDevice* AddDevice( const std::string& );
    static void RemoveDevice( const std::string& );
  private:
    static boost::unordered_map< std::string, KeyboardInputDevice* > _devices;
    static void* _lock;
  };
}

#endif
