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

	//twm::Entity terrain = world->GetEntity( 7 );
	//twm::IndexedMeshShape terrain_component = terrain.GetComponent( twm::kIndexedMeshShape );	
	//terrain.SetTransformation( ASPX::Transformation::Position( 0.0f, time, 0.0f ) );

	twm::Matrix other_pig_xform;

	twm::EntityIterator pig_it = world->QueryEntitiesByType( kWartPig );
	int pig_id = 0;
	while ( pig_it.HasNext() )
	{
		_pig_entity = pig_it.Next();
		WartPigComponent pig_data = _pig_entity.GetComponent( kWartPig );
		const twm::Matrix pig_xform = _pig_entity.GetWorldTransformation();

		const float pig_speed = pig_data.GetSpeed();
		const float pig_acc = pig_data.GetAcceleration();

		if( _particle.size() < pig_it.Count() * 4 ) 
			CreateParticleSystems( world );

		for( int i = 0 + ( 4 * pig_id ); i < 4 + ( 4 * pig_id ); i++ )
		{
			_particle[i]->SetEnabled( false );

			//accelorating (forward/backwards)
			if( pig_acc != 0.0f && ( pig_speed < 10.0f && pig_speed > -10.0f ) )
			{
				_particle[i]->SetEnabled( true );
				_particle[i]->_particle_quantity = 16;
			}
			//decelorating
			else if( pig_acc == 0.0f && ( pig_speed >= 1.0f || pig_speed <= -1.0f ) )
			{
				_particle[i]->SetEnabled( true );
				_particle[i]->_particle_quantity = pig_speed < 0.0f ? (int)(-pig_speed * 0.33f) : (int)(pig_speed * 0.33f);
			}
			//at max speed
			else if( pig_acc != 0.0f && ( pig_speed > 10.0f || pig_speed < -10.0f ) )
			{
				_particle[i]->SetEnabled( true );
				float s = pig_data.GetSteeringAngle() < 0.0f ?  -pig_data.GetSteeringAngle() : pig_data.GetSteeringAngle();
				_particle[i]->_particle_quantity = 10 + s;
			}	

		}

		if( _pig_xform.size() < pig_it.Count() ) {
			_pig_xform.push_back( pig_xform );
		}

		pig_id++;
	}

	//Check collisions between particles and pig
	for( UINT p = 0; p < _pig_xform.size(); p++ )
	{
		for( unsigned int i = 0; i < _particle.size(); i++ )
			_particle[i]->CheckCollisions( time, _pig_xform[p] );
	}

	for( unsigned int i = 0; i < _particle.size(); i++ )
		_particle[i]->Update( time, deltatime );

	_pig_xform.clear();

}

void PigDustService::CreateParticleSystems( twm::IWorldUpdate* world )
{
	twm::Entity particle_parent_r = _pig_entity.CreateChild();
	particle_parent_r.SetTransformation( particle_parent_r.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( -1.1f, 0.2f, -2.2f ) );

	ASPX::Particle::CParticle *new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_r ) )
	{
		_particle.push_back( new_particle_system );
	}

	twm::Entity particle_parent_l = _pig_entity.CreateChild();
	particle_parent_l.SetTransformation( particle_parent_l.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( 1.1f, 0.2f, -2.2f ) );

	new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_l ) )
	{
		_particle.push_back( new_particle_system );
	}

	twm::Entity particle_parent_rr = _pig_entity.CreateChild();
	particle_parent_rr.SetTransformation( particle_parent_rr.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( -1.1f, 0.2f, 2.2f ) );

	new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_rr ) )
	{
		_particle.push_back( new_particle_system );
	}

	twm::Entity particle_parent_rl = _pig_entity.CreateChild();
	particle_parent_rl.SetTransformation( particle_parent_rl.GetLocalTransformation() 
		* ASPX::Transformation::Rotate( 0.0f, 180.0f, 0.0f )
		* ASPX::Transformation::Position( 1.1f, 0.2f, 2.2f ) );

	new_particle_system = new ASPX::Particle::CParticle();
	if( new_particle_system->Initialise( world->CreateEntity(), particle_parent_rl ) )
	{
		_particle.push_back( new_particle_system );
	}
}
