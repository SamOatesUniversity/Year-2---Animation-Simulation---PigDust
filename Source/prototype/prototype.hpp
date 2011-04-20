/**
  * Original Author: Tyrone Davison, Teesside University
  * Filename: prototype.hpp
  * Date: January 2011
  * Description: header for the given assignment framework
  */

#pragma once
#ifndef __WARTPIG_PROTOTYPE__
#define __WARTPIG_PROTOTYPE__

#include "twm/core/world.hpp"
#include "twm/core/service.hpp"
#include "twm/util/timer.hpp"

enum PrototypeComponents {
  kWartPig = 90001,
};

class WartPigComponent : public twm::ComponentBase< struct WartPigData, kWartPig >
{
public:
  WartPigComponent() {}
  WartPigComponent( const Component& c ) : ComponentBase(c) {}
public:
  void SetAcceleration( float acc );
  float GetAcceleration() const;
  void SetSpeed( float speed );
  float GetSpeed() const;
  void SetSteeringAngle( float radians );
  float GetSteeringAngle() const;
};

void RegisterPrototypeComponentTypes( twm::World* world );

class WartPig
{
public:
  WartPig();
  ~WartPig();
public:
  static void InitClass( twm::IWorldUpdate* world );
  void Init( twm::Entity entity, const twm::Vector initial_position, float initial_direction );
  void SetSteeringAngle( float radians );
  float GetSteeringAngle() const;
  void SetAcceleration( float acc );
  float GetAcceleration() const;
  void Update( float deltatime );
  twm::Entity GetEntity() const { return _chasis; }
private:
  static twm::Component _body_material;
  static twm::Component _wheel_material;
  static twm::Component _body_shape;
  static twm::Component _wheel_shape;
private:
  twm::Entity _chasis;
  twm::Entity _body;
  twm::Entity _wheel[4];
  float _wheel_rotation; // degrees
  float _chasis_direction; // radians
  twm::Vector _chasis_position;
  WartPigComponent _data;
};

class PrototypeService : public twm::IService
{
public:
  PrototypeService();
public:
  void DoStart( twm::IWorldUpdate* world );
  void DoStop( twm::IWorldUpdate* world );
  void DoFrame( twm::IWorldUpdate* world, twm::IMessageIterator* messages );
private:
  enum { kCameraFront, kCameraBack, kCameraDrop, kTogglePig };
  bool _key_pressed[4];
  int _active_pig;
  twm::Timer _frame_timer;
  WartPig _pigs[2];
  twm::Entity _camera;
  twm::Entity _pivot;
};

#endif
