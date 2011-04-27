/**
* Original Author: Tyrone Davison, Teesside University
* Filename: pigdust.cpp
* Date: March 2011
* Description: class source for assignment task 3
* Notes: most of your work will be in here
*/

#include "prototype.hpp"
#include "pigdust.hpp"

#include "twm/graphics/components.hpp"
#include "twm/util/math.hpp"

#include <iostream>

using namespace twm::operators;

PigDustService::PigDustService()
{
}

PigDustService::~PigDustService()
{
	for( unsigned int i = 0; i < _particle.size(); i++ )
		delete _particle[i];
}

void PigDustService::DoStart( twm::IWorldUpdate* world )
{
	// reset (zero) the timer
	_timer.Reset();
	_frame_timer.Reset(); 

	ShowWindow( GetActiveWindow(), SW_MAXIMIZE );
}

void PigDustService::DoStop( twm::IWorldUpdate* world )
{
}

void PigDustService::DoFrame( twm::IWorldUpdate* world, twm::IMessageIterator* messages )
{
	// compute the elapsed time in seconds since the service started
	const float time = 0.001f * _timer.GetTime();
	const float deltatime = 0.001f * _frame_timer.GetTime();
	_frame_timer.Reset();

	//pig_id is a counter used to work out which set of 4 wheels to use and
	//which pig entity to store in the pig_entity vector.
	int pig_id = 0;

	twm::EntityIterator pig_it = world->QueryEntitiesByType( kWartPig );
	
	//resize the pig_entity vector where needed.
	if( _pig_entity.capacity() != pig_it.Count() ) 
		_pig_entity.resize( pig_it.Count() );

	while ( pig_it.HasNext() )
	{
		twm::Entity pig_entity = pig_it.Next();
		WartPigComponent pig_data = pig_entity.GetComponent( kWartPig );
		const twm::Matrix pig_xform = pig_entity.GetWorldTransformation();

		const float pig_speed = pig_data.GetSpeed();
		const float pig_acc = pig_data.GetAcceleration();

		//if the number of particle systems is less then the number of pigs 
		//times number of wheels (4) make particle systems.
		if( _particle.size() < pig_it.Count() * 4 ) 
			CreateParticleSystems( world, pig_entity );

		//foreach particle system, update.
		for( int i = 0 + ( 4 * pig_id ); i < 4 + ( 4 * pig_id ); i++ )
		{
			_particle[i]->SetEnabled( false );

			//accelorating (forward/backwards)
			if( pig_acc != 0.0f && ( pig_speed < 10.0f && pig_speed > -10.0f ) )
			{
				_particle[i]->SetEnabled( true );
				_particle[i]->_particle_quantity = 8;
			}
			//decelorating
			else if( pig_acc == 0.0f && ( pig_speed >= 1.0f || pig_speed <= -1.0f ) )
			{
				_particle[i]->SetEnabled( true );
				_particle[i]->_particle_quantity = pig_speed < 0.0f ? (int)(-pig_speed * 0.1f) : (int)(pig_speed * 0.1f);
			}
			//at max speed
			else if( pig_acc != 0.0f && ( pig_speed > 10.0f || pig_speed < -10.0f ) )
			{
				_particle[i]->SetEnabled( true );
				float s = pig_data.GetSteeringAngle() < 0.0f ?  -pig_data.GetSteeringAngle() * 10.0f : pig_data.GetSteeringAngle() * 10.0f;
				_particle[i]->_particle_quantity = (unsigned int)(4 + s);
			}	

		}

		//add the pig_entity to the storage vector.
		if( pig_id < pig_it.Count() ) {
			_pig_entity[pig_id] = pig_entity;
		}

		pig_id++;
	}

	//Check collisions between particles and pig
	for( UINT p = 0; p < _pig_entity.size(); p++ )
	{
		for( unsigned int i = 0; i < _particle.size(); i++ )
		{
			_particle[i]->CheckCollisions( time, &_pig_entity[p] );
		}
	}

	//update particle systems with new values
	for( unsigned int i = 0; i < _particle.size(); i++ )
		_particle[i]->Update( time, deltatime );
}

void PigDustService::CreateParticleSystems( twm::IWorldUpdate* world, twm::Entity pig_entity )
{
	//create four particle systems. one at each wheel.

	twm::Entity particle_parent_r = pig_entity.CreateChild();
	particle_parent_r.SetTransformation( particle_parent_r.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( -1.1f, 0.2f, -2.2f ) );

	ASPX::Particle::CParticle *new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_r ) )
	{
		_particle.push_back( new_particle_system );
	}

	twm::Entity particle_parent_l = pig_entity.CreateChild();
	particle_parent_l.SetTransformation( particle_parent_l.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( 1.1f, 0.2f, -2.2f ) );

	new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_l ) )
	{
		_particle.push_back( new_particle_system );
	}

	twm::Entity particle_parent_rr = pig_entity.CreateChild();
	particle_parent_rr.SetTransformation( particle_parent_rr.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( -1.1f, 0.2f, 2.2f ) );

	new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_rr ) )
	{
		_particle.push_back( new_particle_system );
	}

	twm::Entity particle_parent_rl = pig_entity.CreateChild();
	particle_parent_rl.SetTransformation( particle_parent_rl.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( 1.1f, 0.2f, 2.2f ) );

	new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_rl ) )
	{
		_particle.push_back( new_particle_system );
	}
}
