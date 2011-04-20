#include "ASPP.h"

namespace ASPX
{
	namespace Particle
	{
		CParticle::CParticle( void )
		{
			_next_index = 0;
			_maximum_count = 5000;
			_particle.resize( _maximum_count );
			_active_particle_count = _maximum_count;
			_initialised = false;
			_enabled = false;

			_lastBirthed = 0.0f;
			_birthRate = 0.017f;
			_particleLifeSpan = 8.0f;
			_particle_quantity = 16;

			_end_range = 0;
			_gravity = (float)(GRAVITY * 0.002f);
			_wind = twm::Vector( -0.08f, 0.0f, 0.08f );
		}

		CParticle::~CParticle( void )
		{

		}

		bool CParticle::Initialise( twm::Entity base_entity, twm::Entity parent )
		{
			if( _initialised ) return false;

			_entity	= parent;
			_point_sprites = base_entity.CreateComponent( twm::kPointSprites );

			_point_sprites.SetSizes( 0.01f );
#if _DEBUG
			_point_sprites.SetTexture( "swirl.dds" );
#else
			_point_sprites.SetTexture( "swirl_red.dds" );
#endif
			_point_sprites.SetColours( twm::ColourAlpha( 1, 1, 1, 1 ) );
			_point_sprites.SetBlendMode( twm::PointSprites::kBlendLerp );

			_initialised = true;

			return true;
		}

		void CParticle::Update( float time, float deltatime )
		{
			if( _initialised )
			{
				//if( _enabled ) 
				if( _enabled ) BirthParticle( time, _particle_quantity );

				// check to see if any particles are dead
				KillParticle( time );

				// update living particles
				for ( unsigned int i = 0; i < _end_range; i++ )
				{
					ASPX::Kinematics::Euler( _particle[i].position, _particle[i].velocity, deltatime );

					_particle[i].position.y += (_gravity * _particle[i].position.y);
					_particle[i].position += _wind;

					float scale = 1.0f - ( ( time - _particle[ i ].birthtime ) / _particle[ i ].lifeSpan );
					if( scale < 0.0f ) scale = 0.0f; if( scale > 1.0f ) scale = 1.0f;
					_particle[i].colour = twm::ColourAlpha( 1.0f, scale, scale, scale );

					_particle[i].size = ( scale * 0.1f );
				}

				// update TWM
				if( _particle.size() > 0 )
				{
					_point_sprites.SetPositions( &_particle[0].position, sizeof(SParticle), _end_range );
					_point_sprites.SetColours( &_particle[0].colour, sizeof(SParticle), _end_range );	
					_point_sprites.SetSizes( &_particle[0].size, sizeof(SParticle), _end_range );
				}
			}
		}

		void CParticle::BirthParticle( float time, unsigned int amount )
		{
			if( time - _lastBirthed > _birthRate )
			{
				_lastBirthed = time;
				const twm::Matrix emitter_world_xform = _entity.GetWorldTransformation();

				for( unsigned int i = 0; i < amount; i++ )
				{
					if( _end_range < _active_particle_count ) 
					{
						_particle[_end_range].position = ASPX::Transformation::getPosition( emitter_world_xform + 
							ASPX::Transformation::Position( ASPX::Conversion::LocalToWorld( twm::Vector( ASPX::random( -0.1f, 0.1f ), 0.0f, ASPX::random( -0.1f, 0.1f ) ), emitter_world_xform ) ) );
						_particle[_end_range].velocity = ASPX::Conversion::LocalToWorld( twm::Vector( ASPX::random( -6.0f, 6.0f ), ASPX::random( 0.0f, 4.0f ), ASPX::random( 2.5f, 4.0f ) ), emitter_world_xform );
						_particle[_end_range].birthtime = time;
						_particle[_end_range].lifeSpan = _particleLifeSpan;
						_particle[_end_range].size = 0.01f;
						_end_range++;
					}
				}
			}
		}

		void CParticle::KillParticle( float time )
		{
			for ( unsigned int i = 0; i < _end_range; i++ )
			{
				if( time - _particle[i].birthtime > _particle[i].lifeSpan )
				{
					if( _end_range > 0 )
					{
						_particle[i] = _particle[_end_range-1];
						_end_range--;
					}
				}
			}
		}

		void CParticle::CheckCollisions( float time, twm::Matrix pig_xform )
		{
			float pig_radius = 5.0f;
	
			for ( unsigned int i = 0; i < _end_range; i++ )
			{
				if( time - _particle[i].birthtime >= 0.25f )
				{
					twm::Vector relPos = ASPX::Transformation::getPosition( pig_xform ) - _particle[i].position;
					float dist = relPos.x * relPos.x + relPos.y * relPos.y + relPos.z * relPos.z;
					float minDist = pig_radius + _particle[i].size;
					if( dist <= (minDist * minDist) ) 
					{
						_particle[i].velocity += ASPX::Transformation::getDirection( pig_xform );
						_particle[i].velocity.y += 0.5f;
					}
				}
			}
		}

	}
}