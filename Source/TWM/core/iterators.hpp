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
#ifndef __TWM_CORE_ITERATORS__
#define __TWM_CORE_ITERATORS__

#include "types.hpp"
#include "entity.hpp"
#include "component.hpp"
#include <boost/unordered_map.hpp>

namespace twm
{
  class EntityIdIterator
  {
  public:
    typedef boost::unordered_multimap< unsigned int, unsigned int >::const_iterator Iter;
  public:
    EntityIdIterator( Iter begin, Iter end ) : _iter(begin), _end(end), _count(0)
    {
      Iter it = begin;
      while ( it != end )
      {
        ++_count;
        it++;
      }
    }
  public:
    bool HasNext() const { return _iter != _end; }
    EntityId Next() { return (_iter++)->second; }
    unsigned int Count() const { return _count; }
  private:
    Iter _iter;
    Iter _end;
    unsigned int _count;
  };

  class ComponentIdIterator
  {
  public:
    typedef boost::unordered_multimap< unsigned int, unsigned int >::const_iterator Iter;
  public:
    ComponentIdIterator( Iter begin, Iter end ) : _iter(begin), _end(end), _count(0)
    {
      Iter it = begin;
      while ( it != end )
      {
        ++_count;
        it++;
      }
    }
  public:
    bool HasNext() const { return _iter != _end; }
    ComponentId Next() { return (_iter++)->second; }
    unsigned int Count() const { return _count; }
  private:
    Iter _iter;
    Iter _end;
    unsigned int _count;
  };
  
  class EntityIterator
  {
  public:
    EntityIterator( class WorldDatabase* db, const EntityIdIterator& iter ) : _iter(iter), _db(db) {}
  public:
    bool HasNext() const { return _iter.HasNext(); }
    Entity Next() { return Entity( _db, _iter.Next() ); }
    unsigned int Count() const { return _iter.Count(); }
  private:
    EntityIdIterator _iter;
    WorldDatabase* _db;
  };

  class ComponentIterator
  {
  public:
    ComponentIterator( class WorldDatabase* db, const ComponentIdIterator& iter ) : _iter(iter), _db(db) {}
  public:
    bool HasNext() const { return _iter.HasNext(); }
    Component Next() { return Component( _db, _iter.Next() ); }
    unsigned int Count() const { return _iter.Count(); }
  private:
    ComponentIdIterator _iter;
    WorldDatabase* _db;
  };
}

#endif
