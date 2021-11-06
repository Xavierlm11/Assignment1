#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Player.h"
#include "Animation.h"
#include "Audio.h"
#include "ModuleCollisions.h"
#include "Scene.h"
#include <stdio.h>
#include <stdlib.h>

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL_scancode.h"

#include "SDL_image/include/SDL_image.h"
//#pragma comment(lib, "../Game/Source/External/SDL_image/libx86/SDL2_image.lib")

Player::Player( ) : Module()
{
	name.Create("player");

	idleAnimR.PushBack({8,11,21,19});
	idleAnimR.PushBack({ 8,11,21,19 });
	idleAnimR.PushBack({ 8,11,21,19 });
	idleAnimR.PushBack({ 8,11,21,19 });
	idleAnimR.PushBack({405,72,20,18});
	idleAnimR.PushBack({ 405,72,20,18 });
	idleAnimR.loop = true;
	idleAnimR.speed = 0.069f;

	idleAnimL.PushBack({ 944,338,20,18 });
	idleAnimL.PushBack({ 944,338,20,18 });
	idleAnimL.PushBack({ 944,338,20,18 });
	idleAnimL.PushBack({ 944,338,20,18 });
	idleAnimL.PushBack({ 971,338,20,18 });
	idleAnimL.PushBack({ 971,338,20,18 });
	idleAnimL.loop = true;
	idleAnimL.speed = 0.069f;

	walkAnimR.PushBack({ 254,11,20,18 });
	walkAnimR.PushBack({ 276,10,22,19 });
	walkAnimR.PushBack({ 299,11,20,18 });
	walkAnimR.PushBack({ 321,11,20,18 });
	walkAnimR.PushBack({ 342,11,18,18 });
	walkAnimR.PushBack({ 361,11,20,18 });
	walkAnimR.loop = true;
	walkAnimR.speed = 0.1f;

	walkAnimL.PushBack({ 971,313,20,18 });
	walkAnimL.PushBack({ 948,312,21,19 });
	walkAnimL.PushBack({ 926,313,20,18 });
	walkAnimL.PushBack({ 905,315,19,18 });
	walkAnimL.PushBack({ 886,314,19,18 });
	walkAnimL.PushBack({ 867,313,19,18 });
	walkAnimL.loop = true;
	walkAnimL.speed = 0.1f;

	jumpAnimR.PushBack({ 107,7,20,22 });
	jumpAnimR.PushBack({ 130,14,24,15 });
	jumpAnimR.PushBack({ 156,8,20,21 });
	jumpAnimR.PushBack({ 8,11,21,19 });
	jumpAnimR.loop = false;
	jumpAnimR.speed = 0.080f;

	jumpAnimL.PushBack({ 839,311,20,22 });
	jumpAnimL.PushBack({ 812,318,24,15 });
	jumpAnimL.PushBack({ 790,312,20,21 });
	jumpAnimL.PushBack({ 944,338,20,18 });
	jumpAnimL.loop = false;
	jumpAnimL.speed = 0.080f;
}

// Destructor
Player::~Player()
{}

// Called before render is available
bool Player::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;
	
	// Load support for the PNG image format
	

	return ret;
}

// Called before the first frame
bool Player::Start()
{
	texture = app->tex->Load("Assets/textures/PlayerKirby.png");
	LOG("start Player");
	bool ret = true;
	
	/*if (app->scene->currentScene == State::SCENE)
	{*/
		currentAnimation = &idleAnimR;

		app->player->position.x = 30000;
		app->player->position.y = 30000;
		PlayerPosition = true;

		colliderPlayer = app->coll->AddCollider({ position.x,position.y, 16,5 }, Collider::Type::PLAYER, this);
		colliderPlayerR = app->coll->AddCollider({ position.x + 16,position.y - 16, 5,12 }, Collider::Type::PLAYERRIGHT, this);
		colliderPlayerL = app->coll->AddCollider({ position.x,position.y, 5,12 }, Collider::Type::PLAYERLEFT, this);

		contact = false;
		death = false;
		sidesR = false;
		sidesL = false;
		god = false;
	return ret;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt) {
	bool ret = true;
	int speed = 2;

	
	/*if (app->scene->currentScene == State::SCENE)
	{*/
		if ((app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) )
		{
			if (god) { god = false; }
			else if (!god) { god = true; }
		
		}
		if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && sidesR==false)
		{
			position.x += speed;
			if (currentAnimation != &walkAnimR)
			{
				walkAnimR.Reset();
				currentAnimation = &walkAnimR;
				PlayerPosition = true;
			}
		}

		if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && sidesL == false)
		{
			position.x -= speed;
			if (currentAnimation != &walkAnimL)
			{
				walkAnimL.Reset();
				currentAnimation = &walkAnimL;
				PlayerPosition = false;
			}
		}
		if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (sidesL == false || sidesR == false)  && god == true)
		{
			position.y -= speed*2;
			
		}
		if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && /*(sidesL == false || sidesR == false) &&*/ contact == false && god == true)
		{
			position.y += speed;

		}
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			if (PlayerPosition == false) {
				jumpAnimL.Reset();
				currentAnimation = &jumpAnimL;
			}
			if (PlayerPosition == true)
			{
				jumpAnimR.Reset();
				currentAnimation = &jumpAnimR;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			if (PlayerPosition == false) {
				jumpAnimL.Reset();
				currentAnimation = &jumpAnimL;
			}
			if (PlayerPosition == true)
			{
				jumpAnimR.Reset();
				currentAnimation = &jumpAnimR;
			}
		}

		//Salto
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && contact == true)
		{

			startjump = true;
			if (startjump == true) {

				position.y -= 20;

			}

			if (PlayerPosition == false) {
				jumpAnimL.Reset();
				currentAnimation = &jumpAnimL;
			}
			if (PlayerPosition == true)
			{
				jumpAnimR.Reset();
				currentAnimation = &jumpAnimR;
			}


			if (startjump) //If is jumping
			{
				position.y += jumpVel;
				jumpVel -= gravity;
				maxjumpheight++;
			}

			if (maxjumpheight >= 40)
			{
				position.y += maxjumpheight;

				startjump = false;
				if (maxjumpheight == 40)
				{
					maxjumpheight == 0;
				}
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE) {
			if (currentAnimation != &idleAnimR && currentAnimation != &idleAnimL && currentAnimation != &jumpAnimR && currentAnimation != &jumpAnimL) {
				if (PlayerPosition == true) {
					idleAnimR.Reset();
					currentAnimation = &idleAnimR;
				}
				if (PlayerPosition == false) {
					idleAnimL.Reset();
					currentAnimation = &idleAnimL;
				}
			}
		}
		//PPLAYER LIMITS
		if (position.x > 660)
		{
			position.x = 660;
		}
		if (position.y < 0) {
			position.y = 0;
		}
		if (position.x < 20) {
			position.x = 20;
		}

		currentAnimation->Update();

		if (death == true && god==false )
		{
			death = false;
			app->scene->silence = true;
			app->scene->currentScene = GAME_OVER;
		}
		
		if (contact == false && god == false) {
			position.y += 3;
		}

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;
	
	colliderPlayer->SetPos(position.x - 8, position.y + 33);
	colliderPlayerR->SetPos(position.x + 4, position.y + 21);
	colliderPlayerL->SetPos(position.x - 9, position.y + 21);
	Uint8 alpha = 80;
	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();	

	app->render->DrawTexture(texture, position.x - 10, position.y + 20, &rect);//draw player

	
	contact = false;
	sidesR = false;
	sidesL = false;
	
	return ret;
}

// Called before quitting
bool Player::CleanUp()
{
	LOG("Freeing textures and Image library");
	ListItem<SDL_Texture*>* item;

	for (item = player.start; item != NULL; item = item->next)
	{
		SDL_DestroyTexture(item->data);
	}

	player.clear();
	IMG_Quit();
	return true;
}

//bool Player::LoadState(pugi::xml_node& data)
//{
//	position.x = data.child("position").attribute("x").as_int();
//	position.y = data.child("position").attribute("y").as_int();
//
//	return true;
//}
//
//// L02: DONE 8: Create a method to save the state of the renderer
//// Save Game State
//bool Player::SaveState(pugi::xml_node& data) const
//{
//	pugi::xml_node pla = data.child("position");
//
//	pla.attribute("x").set_value(position.x);
//	pla.attribute("y").set_value(position.y);
//
//	return true;
//}

void Player::OnCollision(Collider* c1, Collider* c2) {
	
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SUELO )
		{
			contact = true;
			LOG("AAAA ");
		}

		if ((c1->type == Collider::Type::PLAYERRIGHT) && (c2->type == Collider::Type::PARED || c2->type == Collider::Type::SUELO))
		{
			LOG("CCCCCCCC ");
			sidesR = true;
		}

		if (c1->type == Collider::Type::PLAYERLEFT && (c2->type == Collider::Type::PARED || c2->type == Collider::Type::SUELO) )
		{
			LOG("CCCCCCCC ");
			sidesL = true;
		}
	
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LAVA )
		{
			LOG("MORISTE PUTOOOOOOOOOOOOO");
			death = true;
		}
	
	
}