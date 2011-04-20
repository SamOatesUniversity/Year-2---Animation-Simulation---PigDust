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
#ifndef __TWM_CORE_ENTITY__
#define __TWM_CORE_ENTITY__

#include "types.hpp"
#include "component.hpp"

namespace twm
{
  class WorldDatabase;

  class Entity
  {
  public:
    Entity() : _db(0), _id(kNullEntity) {}
    Entity( WorldDatabase* db, EntityId id ) : _db(db), _id(id) {}
  public:
    bool Exists() const;
    bool HasType( ComponentType ) const;
    bool IsValid() const { return _db != 0 && _id != kNullEntity; }
    EntityId GetId() const { return _id; }
    CacheId GetCacheId() const;
    void Destroy();
    void SetParent( Entity );
    Entity CreateChild();
    void SetTransformation( const Matrix& );
    Matrix GetLocalTransformation() const;
    Matrix GetWorldTransformation() const;
    Component CreateComponent( ComponentType );
    void AttachComponent( Component );
    void DetachComponent( Component );
    Component GetComponent( ComponentType ) const;
  private:
    WorldDatabase* _db;
    EntityId _id;
  };
}

#endif
