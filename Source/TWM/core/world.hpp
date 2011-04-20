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
#ifndef __TWM_CORE_WORLD__
#define __TWM_CORE_WORLD__

#include "types.hpp"
#include <set>

namespace twm
{
  template< typename T > class Queue;
  struct Message;

  // TODO: move to own header
  struct ComponentTypeInfo
  {
    unsigned int size;
    void (*Constructor)( void* );
    void (*Destructor)( void* );
    void (*Copy)( const void*, void* );

    template< typename T >
    static ComponentTypeInfo Generate()
    {
      ComponentTypeInfo info;
      info.size = sizeof(T);
      info.Constructor = ComponentConstructor<T>;
      info.Destructor = ComponentDestructor<T>;
      info.Copy = ComponentCopy<T>;
      return info;
    }
  private:
    template< typename T >
    static void ComponentConstructor( void* ptr )
    {
      new(ptr) T();
    }
    template< typename T >
    static void ComponentDestructor( void* ptr )
    {
      ((T*)ptr)->T::~T();
    }
    template< typename T >
    static void ComponentCopy( const void* src, void* dst )
    {
      *((T*)dst) = *((const T*)src);
    }
  };

  class World // not thread safe
  {
  public:
    World();
    ~World();
  public:
    void Start(); // signal start to services
    void Stop(); // signal stop to services
    void AdvanceFrame();
    void AttachService( class IService* ); // only possible before start is called
    void RegisterComponentType( ComponentType, const ComponentTypeInfo& );
    void Serialise(); // TODO:
    void Deserialise(); // TODO:
  private:
    bool _active;
    std::set< IService* > _services;
    class WorldUpdate* _updater;
    class WorldDatabase* _database;
    Queue<Message>* _read_queue;
    Queue<Message>* _write_queue;
  };
}

#endif
