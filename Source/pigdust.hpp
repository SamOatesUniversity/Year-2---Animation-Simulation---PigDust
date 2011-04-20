/**
* Original Author: Tyrone Davison, Teesside University
* Filename: pigdust.hpp
* Date: March 2011
* Description: class header for assignment task
*/

#include "twm/core/world.hpp"
#include "twm/core/service.hpp"
#include "twm/util/timer.hpp"
#include <vector>
#include <Windows.h>

#include "ASPX.h"

class PigDustService : public twm::IService
{
public:
	PigDustService();
	~PigDustService();
public:
	void DoStart( twm::IWorldUpdate* world );
	void DoStop( twm::IWorldUpdate* world );
	void DoFrame( twm::IWorldUpdate* world, twm::IMessageIterator* messages );
private:
	twm::Timer _timer;
	twm::Timer _frame_timer;
	twm::Entity _pig_entity;
	
	std::vector<ASPX::Particle::CParticle*> _particle;

	std::vector<twm::Matrix> _pig_xform;

	void CreateParticleSystems( twm::IWorldUpdate* world );
};
