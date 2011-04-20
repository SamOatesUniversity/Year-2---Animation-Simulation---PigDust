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
#ifndef __TWM_CORE_SERVICE__
#define __TWM_CORE_SERVICE__

#include "entity.hpp"
#include "component.hpp"
#include "iterators.hpp"

namespace twm
{
  struct Message
  {
    unsigned int type;
    unsigned int id;
    EntityId entity1;
    EntityId entity2;
    ComponentId component1;
    ComponentId component2;
    float fval;
    int ival;
  };

  // TODO message iterator be concrete rather than an interface?
  class IMessageIterator
  {
  public:
    virtual const Message& Next() = 0;
    virtual bool HasNext() const = 0;
  protected:
    virtual ~IMessageIterator() {}
  };

  class IWorldUpdate
  {
  public: // modification api
    virtual void PostMessage( const Message& ) = 0;
    virtual Entity CreateEntity() = 0; // uses the root as the parent
    virtual Component CreateComponent( ComponentType ) = 0;
    virtual Entity GetEntity( EntityId ) const = 0;
    virtual Component GetComponent( ComponentId ) const = 0;
  public: // query api
    virtual EntityIterator QueryChildren( EntityId ) const = 0;
    virtual EntityIterator QueryEntitiesByType( ComponentType ) const = 0;
    virtual EntityIterator QueryEntitiesByComponent( ComponentId ) const = 0;
    virtual ComponentIterator QueryComponentsByType( ComponentType ) const = 0;
    virtual ComponentIterator QueryComponentsByEntity( EntityId ) const = 0;
  public:
    EntityIterator QueryChildren( const Entity& e ) const { return QueryChildren( e.GetId() ); }
    EntityIterator QueryEntitiesByComponent( const Component& c ) const { return QueryEntitiesByComponent( c.GetId() ); }
    ComponentIterator QueryComponentsByEntity( const Entity& e ) const { return QueryComponentsByEntity( e.GetId() ); }
  };

  class IService
  {
  public:
    virtual void DoStart( IWorldUpdate* ) {}
    virtual void DoStop( IWorldUpdate* ) {}
    virtual void DoFrame( IWorldUpdate*, IMessageIterator* ) {}
    virtual void DoAdvance() {}
  };
}

#endif
