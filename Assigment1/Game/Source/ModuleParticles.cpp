#include "ModuleParticles.h"

#include "App.h"
#include "Particle.h"

#include "Animation.h"
#include "Render.h"
#include "ModuleCollisions.h"
#include "textures.h"
#include "Player.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles() : Module()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	ShootTex = app->tex->Load("Assets/textures/AmogusTex.png");
	
	//Particle
	PlayerAttack.anim.PushBack({ 0,0, 20, 35 });
	PlayerAttack.anim.loop = false;
	PlayerAttack.anim.speed = 0.2f;
	PlayerAttack.lifetime = 200;

	return true;
}

bool ModuleParticles::CleanUp()
{
	/*LOG("Unloading particles");*/

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		 /*Always destroy particles that collide*/
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			/*if (particles[i]->type == 1) {
				AddParticle(shuriken_explosion, particles[i]->position.x, particles[i]->position.y, particles[i]->type);
				particles[i]->type == 0;
			}

			if (particles[i]->type == 2) {
				AddParticle(knife_explosion, particles[i]->position.x, particles[i]->position.y, particles[i]->type);
				particles[i]->type == 0;
			}*/
			

			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

bool ModuleParticles::Update(float dt)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			/*AddParticle(PlayerAttack, particles[i]->position.x, particles[i]->position.y, 1);*/
			/*if (particles[i]->type == 1) {
				AddParticle(shuriken_explosion, particles[i]->position.x, particles[i]->position.y, 1);
			}

			if (particles[i]->type == 2) {
				AddParticle(knife_explosion, particles[i]->position.x, particles[i]->position.y, 2);
			}*/
			delete particle;
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			
			app->render->DrawTexture(ShootTex, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
			
		}
	}

	return true;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int type, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->type = type;
			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y-20;

			//Adding the particle's collider
			if (colliderType == Collider::Type::PLAYERATTACK && p->type == 1)
				p->collider = app->coll->AddCollider({app->player->position.x,app->player->position.y, 8,8 }, colliderType, this);
			
			else {
				p->collider = app->coll->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
			}

			particles[i] = p;
			break;
		}
	}
}