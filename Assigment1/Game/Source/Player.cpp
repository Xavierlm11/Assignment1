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

	//Player Animations

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

	PlayerDeathR.PushBack({37,101,24,24});

	PlayerDeathL.PushBack({788,342,24,24});

	//HealthBar Animation
	Bar5.PushBack({ 10,16,59,8 });
	Bar4.PushBack({ 78,16,47,8 });
	Bar3.PushBack({ 130,16,35,8 });
	Bar2.PushBack({ 174,16,23,8 });
	Bar1.PushBack({ 202,16,11,8 });

	
}

// Destructor
Player::~Player()
{}

// Called before render is available
bool Player::Awake(pugi::xml_node& config)
{
	LOG("Init Image library");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool Player::Start()
{
	LOG("start Player");
	bool ret = true;

	texture = app->tex->Load("Assets/textures/PlayerKirby.png");
	HealthBarTex = app->tex->Load("Assets/textures/HealthBarTex.png");

	currentAnimation = &idleAnimR; //player start with idle anim

	app->player->position.x = 30000;
	app->player->position.y = 30000;

	PlayerPosition = true;//if its true, player will be looking at the right, if not, player will be looking at the left

	//add colliders
	colliderPlayer = app->coll->AddCollider({ position.x,position.y, 16,5 }, Collider::Type::PLAYER, this);
	colliderPlayerR = app->coll->AddCollider({ position.x + 16,position.y - 16, 5,9 }, Collider::Type::PLAYERRIGHT, this);
	colliderPlayerL = app->coll->AddCollider({ position.x,position.y, 5,9 }, Collider::Type::PLAYERLEFT, this);
	colliderHead = app->coll->AddCollider({ position.x,position.y, 16,5 }, Collider::Type::PLAYERHEAD, this);

	//colliderplayerR y colliderplayerL solo colisionan para las paredes

	contact = false;
	death = false;
	sidesR = false;
	sidesL = false;
	god = false;
	jumping = false;
	dbjump = false;
	jumped = 0;

	return ret;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt) {
	bool ret = true;
	float speed = 2;
	
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
		app->scene->scrollerX -= speed / 6;
		app->scene->scrollerX1 -= speed /24;
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
		app->scene->scrollerX += speed / 6;
		app->scene->scrollerX1 += speed / 24;
	}
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (sidesL == false || sidesR == false)  && god == true)
	{
		position.y -= speed*2;		
	}
	if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && contact == false && god == true)
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
	//if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && contact == true)
	//{

	//	startjump = true;
	//	if (startjump == true) {

	//		position.y -= 20;

	//	}

	//	if (PlayerPosition == false) {
	//		jumpAnimL.Reset();
	//		currentAnimation = &jumpAnimL;
	//	}
	//	if (PlayerPosition == true)
	//	{
	//		jumpAnimR.Reset();
	//		currentAnimation = &jumpAnimR;
	//	}

	//	if (startjump) //If is jumping
	//	{
	//		position.y += jumpVel;
	//		jumpVel -= gravity;
	//		maxjumpheight++;
	//	}

	//	if (maxjumpheight >= 40)
	//	{
	//		position.y += maxjumpheight;

	//		startjump = false;
	//		if (maxjumpheight == 40)
	//		{
	//			maxjumpheight == 0;
	//		}
	//	}
	//}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && contact == true)
	{
		jumping = true;
		dbjump = true;
	}
	if (jumping == true)
	{
		position.y -= 3;
		jumped += 10;
	}
	 if (jumped>=100)
	{
		jumping = false;
		jumped = 0;
	}
	 if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN  && dbjump==true)
	 { 
		 jumped = 0;
		 dbjump = false;
	 }
	//player animation if no movement detected
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

		//PLAYER LIMITS
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
			if (PlayerPosition == true) {
			PlayerDeathR.Reset();
			currentAnimation = &PlayerDeathR;
			}
			if (PlayerPosition == false) {
				PlayerDeathL.Reset();
				currentAnimation = &PlayerDeathL;
			}
			death = false;
			app->scene->silence = true;
			app->scene->currentScene = GAME_OVER;
		}
		
		//Gravity
		if (contact == false && god == false&&jumping==false) {
			position.y += 3;
		}

		//Lifes
		if (PlayerLives > 5) {
			PlayerLives = 5;
		}

		if (app->scene->currentScene == SCENE){
			if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
			{
				PlayerLives -= 1;
			}

			if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
			{
				PlayerLives += 1;
			}

			if (PlayerLives == 5) {
				app->render->DrawTexture(HealthBarTex, 5 ,10,&(Bar5.GetCurrentFrame()),0);
			}
			if (PlayerLives == 4) {
				app->render->DrawTexture(HealthBarTex, 5, 10, &(Bar4.GetCurrentFrame()), 0);
			}
			if (PlayerLives == 3) {
				app->render->DrawTexture(HealthBarTex, 5, 10, &(Bar3.GetCurrentFrame()), 0);
			}
			if (PlayerLives == 2) {
				app->render->DrawTexture(HealthBarTex, 5, 10, &(Bar2.GetCurrentFrame()), 0);
			}
			if (PlayerLives == 1) {
				app->render->DrawTexture(HealthBarTex, 5, 10, &(Bar1.GetCurrentFrame()), 0);
			}
		}

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;
	
	colliderPlayer->SetPos(position.x - 8, position.y + 33);
	colliderPlayerR->SetPos(position.x + 4, position.y + 26);
	colliderPlayerL->SetPos(position.x - 9, position.y + 26);
	colliderHead->SetPos(position.x -8, position.y + 21);
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


void Player::OnCollision(Collider* c1, Collider* c2) {
	
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SUELO )
		{
			contact = true;
		}
		if (c1->type == Collider::Type::PLAYERHEAD && c2->type == Collider::Type::PARED)
		{
			/*contact = true;*/
			position.y += 1;
		}

		if ((c1->type == Collider::Type::PLAYERRIGHT) && (c2->type == Collider::Type::PARED || c2->type == Collider::Type::SUELO))
		{
			sidesR = true;
		}

		if (c1->type == Collider::Type::PLAYERLEFT && (c2->type == Collider::Type::PARED || c2->type == Collider::Type::SUELO) )
		{
			sidesL = true;
		}
	
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LAVA )
		{
			LOG("MORISTE");
			death = true;
		}
	
	
}