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
#ifndef __TWM_CORE_COMPONENT__
#define __TWM_CORE_COMPONENT__

#include "types.hpp"
#include <cassert>

namespace twm
{
  class WorldDatabase;

  class Component
  {
  public:
    Component() : _db(0), _id(kNullComponent) {}
    Component( WorldDatabase* db, ComponentId id ) : _db(db), _id(id) {}
  public:
    ComponentId GetId() const { return _id; }
    bool IsValid() const { return _id != kNullComponent; }
    void Destroy();
    bool Exists() const;
    ComponentType GetType() const;
    CacheId GetCacheId() const;
  protected:
    void* _BeginWrite();
    void EndWrite();
    const void* _BeginRead() const;
    void EndRead() const;
  private:
    WorldDatabase* _db;
    ComponentId _id;
  };

  // TODO: is TYPE required?
  template< class T, ComponentType TYPE >
  class ComponentBase : public Component
  {
  public:
    ComponentBase() {}
    ComponentBase( const Component& c ) : Component( c ) {} // TODO: add type validation
  public:
    const T* BeginRead() const { return (const T*)_BeginRead(); }
    void EndRead() const { Component::EndRead(); }
    T* BeginWrite() { return (T*)_BeginWrite(); }
    void EndWrite() { Component::EndWrite(); }
  protected:
    class WritePtr
    {
    public:
      WritePtr( ComponentBase* base ) : _base(base) { _ptr = _base->BeginWrite(); assert( _ptr != 0 ); }
      ~WritePtr() { _base->EndWrite(); }
      T* operator->() { return _ptr; }
      T& operator*() { return *_ptr; }
    private:
      ComponentBase* _base;
      T* _ptr;
    };
  protected:
    class ReadPtr
    {
    public:
      ReadPtr( const ComponentBase* base ) : _base(base) { _ptr = _base->BeginRead(); assert( _ptr != 0 ); }
      ~ReadPtr() { _base->EndRead(); }
      const T* operator->() { return _ptr; }
      const T& operator*() { return *_ptr; }
    private:
      const ComponentBase* _base;
      const T* _ptr;
    };
  };
}

#endif
