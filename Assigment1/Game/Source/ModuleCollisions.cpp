#include "ModuleCollisions.h"

#include "App.h"

#include "Defs.h"
#include "Log.h"


#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PURPLE_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ORANGE_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WHITE_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::PLAYER_ATTACK][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::PURPLE_ATTACK][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::ORANGE_ATTACK][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::WHITE_ATTACK][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::ENEMY_SHOT] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_ATTACK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PURPLE_ATTACK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ORANGE_ATTACK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WHITE_ATTACK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update(float dt)
{
	// Get gamepad info
	/*GamePad& pad = app->input->pads[0];*/
	if (app->input->GetKey(SDL_SCANCODE_F1 == KEY_DOWN)/*||pad.r1*/) {
		if (debug == true) {
			debug = false;
		}
		else {
			debug = true;
		}
	}

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug==true)
		DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_ATTACK: // yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::PURPLE_ATTACK: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::ORANGE_ATTACK: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::WHITE_ATTACK: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::BOSS_ATTACK: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::ENEMY_SHOT: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}
