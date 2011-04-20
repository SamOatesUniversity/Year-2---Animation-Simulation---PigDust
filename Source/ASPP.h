#pragma once

#include <vector>

#include "ASPX.h"

#include "twm/core/world.hpp"
#include "twm/core/service.hpp"

#include "twm/windows/window.hpp"
#include "twm/graphics/components.hpp"
#include "twm/graphics/basic_renderer.hpp"



#include "twm/util/math.hpp"
using namespace twm::operators;

namespace ASPX
{
	#define GRAVITY		-9.81

	namespace Particle
	{
		struct SParticle {
			twm::Vector position;
			twm::Vector velocity;
			twm::ColourAlpha colour;
			float size;
			float birthtime, lifeSpan;
		};

		//------------------------------------------------------------------------
		// Simple Particle Class
		// Dust effect, effected by gravity (-9.81) and wind (user defined)
		//------------------------------------------------------------------------
		class CParticle
		{
		//------------------------------------------------------------------------
		//Private class members
		//------------------------------------------------------------------------
		private:
			//The actual point sprites
			twm::PointSprites _point_sprites;

			//Position and Direction of the particle emitter can be found from this
			twm::Entity _entity;

			//Vector array of SParticles
			std::vector<SParticle> _particle;

			//maximum number of particles
			unsigned int _maximum_count;

			//the number of particles that have been birthed
			unsigned int _end_range;
			
			//next particle
			unsigned int _next_index;

			//number of active particles allowed
			unsigned int _active_particle_count;

			//has the particle system been initialised? and is it enabled?
			bool _initialised, _enabled;

			float _birthRate, _lastBirthed, _particleLifeSpan, _gravity;

			twm::Vector _wind;

		//------------------------------------------------------------------------
		//Private class methods
		//------------------------------------------------------------------------
		private:
			void BirthParticle( float time, unsigned int amount );
			void KillParticle( float time );

		//------------------------------------------------------------------------
		//Public class methods
		//------------------------------------------------------------------------
		public:
			CParticle( void );
			~CParticle( void );

			bool Initialise( twm::Entity base_entity, twm::Entity parent );

			void Update( float time, float deltatime );

			void SetEnabled( bool enabled ) { _enabled = enabled; }
			void SetSpawnRate( float rate ) { _birthRate = rate; }
			void SetLifeSpan( float time ) { _particleLifeSpan = time; }

			void CheckCollisions( float time, twm::Matrix pig_xform );

			unsigned int _particle_quantity;

		};
	}
}
