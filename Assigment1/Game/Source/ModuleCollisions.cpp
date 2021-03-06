#include "ModuleCollisions.h"

#include "App.h"
#include "scene.h"

#include "Defs.h"
#include "Log.h"


#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions( ) : Module()
{

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	//PLAYER
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::LAVA] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SUELO] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PARED] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CHECKPOINT1] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CHECKPOINT2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CHECKPOINT3] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMYBOO] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMYWADDLE] = true;

	//PLAYER RIGHT
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::LAVA] = false;
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::PARED] = true;
	matrix[Collider::Type::PLAYERRIGHT][Collider::Type::SUELO] = false;

	//PLAYER LEFT
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::LAVA] = false;
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::PARED] = true;
	matrix[Collider::Type::PLAYERLEFT][Collider::Type::SUELO] = false;

	//PLAYERATTACK
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::PLAYERATTACK] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::PARED] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::SUELO] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::LAVA] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::ENEMYWADDLE] = false;
	matrix[Collider::Type::PLAYERATTACK][Collider::Type::ENEMYBOO] = true;
	
	//SUELO
	matrix[Collider::Type::SUELO][Collider::Type::SUELO] = false;
	matrix[Collider::Type::SUELO][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SUELO][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::SUELO][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::SUELO][Collider::Type::PLAYERHEAD] = false;
	//matrix[Collider::Type::SUELO][Collider::Type::PLAYERATTACK] = true;
	matrix[Collider::Type::SUELO][Collider::Type::LAVA] = false;
	matrix[Collider::Type::SUELO][Collider::Type::PARED] = false;
	
	//PARED
	matrix[Collider::Type::PARED][Collider::Type::SUELO] = false;
	matrix[Collider::Type::PARED][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PARED][Collider::Type::PLAYERRIGHT] = true;
	matrix[Collider::Type::PARED][Collider::Type::PLAYERLEFT] = true;
	matrix[Collider::Type::PARED][Collider::Type::PLAYERHEAD] = true;
	/*matrix[Collider::Type::PARED][Collider::Type::PLAYERATTACK] = true;*/
	matrix[Collider::Type::PARED][Collider::Type::LAVA] = false;
	matrix[Collider::Type::PARED][Collider::Type::PARED] = false;

	//LAVA
	matrix[Collider::Type::LAVA][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::LAVA][Collider::Type::LAVA] = false;
	matrix[Collider::Type::LAVA][Collider::Type::PARED] = false;
	matrix[Collider::Type::LAVA][Collider::Type::SUELO] = false;
	matrix[Collider::Type::LAVA][Collider::Type::TELEPORT] = false;

	//PLAYER HEAD
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::LAVA] = false;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::PARED] = true;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::SUELO] = false;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::ENEMYWADDLE] = true;
	matrix[Collider::Type::PLAYERHEAD][Collider::Type::ENEMYBOO] = true;

	//CHECKPOINT 1
	matrix[Collider::Type::CHECKPOINT1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT1][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::CHECKPOINT1][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::CHECKPOINT1][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::CHECKPOINT1][Collider::Type::CHECKPOINT1] = false;

	//CHECKPOINT 2
	matrix[Collider::Type::CHECKPOINT2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT2][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::CHECKPOINT2][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::CHECKPOINT2][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::CHECKPOINT2][Collider::Type::CHECKPOINT2] = false;

	//CHECKPOINT 3
	matrix[Collider::Type::CHECKPOINT3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT3][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::CHECKPOINT3][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::CHECKPOINT3][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::CHECKPOINT3][Collider::Type::CHECKPOINT3] = false;

	//CHECKPOINT 4
	matrix[Collider::Type::CHECKPOINT4][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT4][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::CHECKPOINT4][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::CHECKPOINT4][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::CHECKPOINT4][Collider::Type::CHECKPOINT4] = false;

	//CHECKPOINT 5
	matrix[Collider::Type::CHECKPOINT5][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT5][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::CHECKPOINT5][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::CHECKPOINT5][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::CHECKPOINT5][Collider::Type::CHECKPOINT5] = false;

	//AIR
	matrix[Collider::Type::AIR][Collider::Type::SUELO] = false;
	matrix[Collider::Type::AIR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::AIR][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::AIR][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::AIR][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::AIR][Collider::Type::LAVA] = false;
	matrix[Collider::Type::AIR][Collider::Type::PARED] = false;

	//ITEM1
	matrix[Collider::Type::ITEM1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM1][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::ITEM1][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::ITEM1][Collider::Type::PLAYERHEAD] = false;

	//ITEM2
	matrix[Collider::Type::ITEM2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM2][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::ITEM2][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::ITEM2][Collider::Type::PLAYERHEAD] = false;

	//ITEM3
	matrix[Collider::Type::ITEM3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM3][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::ITEM3][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::ITEM3][Collider::Type::PLAYERHEAD] = false;

	//ITEM4
	matrix[Collider::Type::ITEM4][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM4][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::ITEM4][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::ITEM4][Collider::Type::PLAYERHEAD] = false;

	//KEY
	matrix[Collider::Type::KEY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::KEY][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::KEY][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::KEY][Collider::Type::PLAYERHEAD] = false;

	//COIN1
	matrix[Collider::Type::COIN1][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN1][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::COIN1][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::COIN1][Collider::Type::PLAYERHEAD] = false;

	//COIN2
	matrix[Collider::Type::COIN2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN2][Collider::Type::PLAYERRIGHT] = true;
	matrix[Collider::Type::COIN2][Collider::Type::PLAYERLEFT] = true;
	matrix[Collider::Type::COIN2][Collider::Type::PLAYERHEAD] = true;

	//COIN3
	matrix[Collider::Type::COIN3][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN3][Collider::Type::PLAYERRIGHT] = true;
	matrix[Collider::Type::COIN3][Collider::Type::PLAYERLEFT] = true;
	matrix[Collider::Type::COIN3][Collider::Type::PLAYERHEAD] = true;

	//COIN4
	matrix[Collider::Type::COIN4][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN4][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::COIN4][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::COIN4][Collider::Type::PLAYERHEAD] = false;

	//COIN5
	matrix[Collider::Type::COIN5][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN5][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::COIN5][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::COIN5][Collider::Type::PLAYERHEAD] = false;

	//voolador
	matrix[Collider::Type::VOLADOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::VOLADOR][Collider::Type::PLAYERRIGHT] = true;
	matrix[Collider::Type::VOLADOR][Collider::Type::PLAYERLEFT] = true;
	matrix[Collider::Type::VOLADOR][Collider::Type::PLAYERHEAD] = true;

	//TIERRA
	matrix[Collider::Type::TIERRA][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TIERRA][Collider::Type::PLAYERRIGHT] = true;
	matrix[Collider::Type::TIERRA][Collider::Type::PLAYERLEFT] = true;
	matrix[Collider::Type::TIERRA][Collider::Type::PLAYERHEAD] = true;

	//TELEPORT
	matrix[Collider::Type::TELEPORT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TELEPORT][Collider::Type::PLAYERRIGHT] = true;
	matrix[Collider::Type::TELEPORT][Collider::Type::PLAYERLEFT] = true;
	matrix[Collider::Type::TELEPORT][Collider::Type::PLAYERHEAD] = true;

	//WIN
	matrix[Collider::Type::WIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WIN][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::WIN][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::WIN][Collider::Type::PLAYERHEAD] = false;

	//BOO 
	matrix[Collider::Type::ENEMYBOO][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMYBOO][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::ENEMYBOO][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::ENEMYBOO][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::ENEMYBOO][Collider::Type::PLAYERATTACK] = true;

	//WADDLE
	matrix[Collider::Type::ENEMYWADDLE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMYWADDLE][Collider::Type::PLAYERRIGHT] = false;
	matrix[Collider::Type::ENEMYWADDLE][Collider::Type::PLAYERLEFT] = false;
	matrix[Collider::Type::ENEMYWADDLE][Collider::Type::PLAYERHEAD] = false;
	matrix[Collider::Type::ENEMYWADDLE][Collider::Type::PLAYERATTACK] = true;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::PreUpdate() {
	for (uint i = 0; i < MAX_COLLIDERS; i++) {
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true) {
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; i++) {
		if (colliders[i] == nullptr) {
			continue;
		}
		c1 = colliders[i];
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k) {
			if (colliders[k] == nullptr) {
				continue;
			}
			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
				{
					if (c1->listeners[i] != nullptr)
					{
						c1->listeners[i]->OnCollision(c1, c2);
					}
				}
				for (uint i = 0; i < MAX_LISTENERS; ++i)
				{
					if (c2->listeners[i] != nullptr) {
						c2->listeners[i]->OnCollision(c2, c1);
					}
				}
			}
		}
	}
	return true;
}

bool ModuleCollisions::Update(float dt)
{

	if ((app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) ) {
		debug = !debug;
	}

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug && (app->scene->currentScene == SCENE|| app->scene->currentScene == SCENE2)) {
		DebugDraw();
	}

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
			case Collider::Type::PLAYERRIGHT: //
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYERLEFT: //
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYERHEAD: //
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case Collider::Type::SUELO: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PARED: //yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::LAVA: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::CHECKPOINT1: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::CHECKPOINT2: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::CHECKPOINT3: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::CHECKPOINT4: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::CHECKPOINT5: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::AIR: // red
			app->render->DrawRectangle(colliders[i]->rect, 0, 200,20, alpha);
			break;
			case Collider::Type::ITEM1: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 150, 20, alpha);
			break;
			case Collider::Type::ITEM2: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 150, 20, alpha);
			break; case Collider::Type::ITEM3: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 150, 20, alpha);
			break;
			break; case Collider::Type::ITEM4: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 150, 20, alpha);
			break;
			case Collider::Type::KEY: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 200, alpha);
			break;
			case Collider::Type::COIN1: // red
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::COIN2: // red
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::COIN3: // red
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::COIN4: // red
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::COIN5: // red
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::VOLADOR: // red
			app->render->DrawRectangle(colliders[i]->rect, 150, 150, 250, alpha);
			break;
			case Collider::Type::TIERRA: // red
			app->render->DrawRectangle(colliders[i]->rect, 150, 150, 250, alpha);
			break;
			case Collider::Type::TELEPORT:
			app->render->DrawRectangle(colliders[i]->rect, 170, 150, 50, alpha);
			break;
			case Collider::Type::WIN:
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case Collider::Type::PLAYERATTACK:
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case Collider::Type::ENEMYBOO:
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::ENEMYWADDLE:
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
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

void ModuleCollisions::clean()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && (colliders[i]->type!= Collider::Type::PLAYER && colliders[i]->type != Collider::Type::PLAYERHEAD && colliders[i]->type != Collider::Type::PLAYERLEFT && colliders[i]->type != Collider::Type::PLAYERRIGHT && colliders[i]->type != Collider::Type::ENEMYBOO && colliders[i]->type != Collider::Type::ENEMYWADDLE))
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

}