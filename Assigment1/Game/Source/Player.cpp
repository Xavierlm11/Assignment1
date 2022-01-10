#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Player.h"
#include "Scene.h"
#include "Animation.h"
#include "Audio.h"
#include "ModuleCollisions.h"
#include "Scene.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

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
	GetItem = app->audio->LoadFx("Assets/audio/fx/GetItemFx.wav");
	GetCheckpoint = app->audio->LoadFx("Assets/audio/fx/GetCheckpointFx.wav");
	GetKey = app->audio->LoadFx("Assets/audio/fx/GetKeyFx.wav");
	GetCoin = app->audio->LoadFx("Assets/audio/fx/GetCoinFx.wav");
	JumpFx = app->audio->LoadFx("Assets/audio/fx/JumpFx.wav");
	playerAttack = app->audio->LoadFx("Assets/audio/fx/PlayerAttackFx.wav");

	currentAnimation = &idleAnimR; //player start with idle anim

	app->player->position.x = 30000;
	app->player->position.y = 30000;

	PlayerPosition = true;//if its true, player will be looking at the right, if not, player will be looking at the left

	//add colliders
	colliderPlayer = app->coll->AddCollider({ position.x,position.y, 12,5 }, Collider::Type::PLAYER, this);
	colliderPlayerR = app->coll->AddCollider({ position.x + 16,position.y - 16, 5,9 }, Collider::Type::PLAYERRIGHT, this);
	colliderPlayerL = app->coll->AddCollider({ position.x,position.y, 5,9 }, Collider::Type::PLAYERLEFT, this);
	colliderHead = app->coll->AddCollider({ position.x,position.y, 8,5 }, Collider::Type::PLAYERHEAD, this);

	//colliderplayerR y colliderplayerL solo colisionan para las paredes

	//misil = app->coll->AddCollider({ position.x,position.y, 30,30}, Collider::Type::PLAYERATTACK,this);
	
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
	
	MovementPlayer(dt);
		
	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;
	colliderPlayer->SetPos(position.x + 4, position.y + 13);
	colliderPlayerR->SetPos(position.x + 15, position.y + 4);
	colliderPlayerL->SetPos(position.x, position.y + 4);
	colliderHead->SetPos(position.x + 6, position.y + 5);
	
	Uint8 alpha = 80;
	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();	

	app->render->DrawTexture(texture, position.x, position.y, &rect);//draw player

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

// Load Game State PLAYER POSITION
bool Player::LoadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	PlayerLives = data.child("lives").attribute("count").as_int();

	Key = data.child("Key").attribute("keyused").as_bool();

	return true;
}


// Save Game State PLAYER POSITION
bool Player::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node pos = data.child("position");
	pugi::xml_node life = data.child("lives");
	pugi::xml_node key = data.child("Key");

	pos.attribute("x").set_value(position.x);
	pos.attribute("y").set_value(position.y);

	life.attribute("count").set_value(PlayerLives);

	key.attribute("keyused").set_value(Key);

	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2) {
	
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SUELO )
		{
			contact = true;
			jumps = 2;
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

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::CHECKPOINT1)
		{
			if (app->scene->Point1 == false) {
				app->audio->PlayFx(GetCheckpoint);
			}
			app->scene->Point1 = true;
			CheckActive1 = true;
			app->scene->ActiveTeleport1 = true;
			app->scene->tps1 == 1;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::CHECKPOINT2)
		{
			if (app->scene->Point2 == false) {
				app->audio->PlayFx(GetCheckpoint);
			}
			app->scene->Point2 = true;
			CheckActive2 = true;
			app->scene->ActiveTeleport2 = true;
			app->scene->tps2 == 1;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::CHECKPOINT3)
		{
			if (app->scene->Point3 == false) {
				app->audio->PlayFx(GetCheckpoint);
			}
			app->scene->Point3 = true;
			CheckActive3 = true;
			app->scene->ActiveTeleport3 = true;
			app->scene->tps3 == 1;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::CHECKPOINT4)
		{
			if (app->scene->Point4 == false) {
				app->audio->PlayFx(GetCheckpoint);
			}
			app->scene->Point4 = true;
			CheckActive4 = true;
			app->scene->ActiveTeleport4 = true;
			app->scene->tps4 == 1;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::CHECKPOINT5)
		{
			if (app->scene->Point5 == false) {
				app->audio->PlayFx(GetCheckpoint);
			}
			app->scene->Point5 = true;
			CheckActive5 = true;
			app->scene->ActiveTeleport5 = true;
			app->scene->tps5 == 1;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM1)
		{
			if (PlayerLives < 5) {
				item1Used = true;
				app->audio->PlayFx(GetItem);
			}
			if (item1Used == true && PlayerLives < 5) {
				PlayerLives += 1;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM2)
		{
			if (PlayerLives < 5) {
				item2Used = true;
				app->audio->PlayFx(GetItem);
			}
			if (item2Used == true && PlayerLives < 5) {
				PlayerLives += 1;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM3)
		{
			if (PlayerLives < 5) {
				item3Used = true;
				app->audio->PlayFx(GetItem);
			}
			if (item3Used == true && PlayerLives < 5) {
				PlayerLives += 1;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM4)
		{
			if (PlayerLives < 5) {
				item4Used = true;
				app->audio->PlayFx(GetItem);
			}
			if (item4Used == true && PlayerLives < 5) {
				PlayerLives += 1;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::KEY)
		{
			if (Key == false) {
				app->audio->PlayFx(GetKey);
			}
			Key = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::COIN1)
		{
			if (app->scene->CoinUsed1 == false) {

				app->coll->matrix[Collider::Type::COIN1][Collider::Type::PLAYER] = false;
				Money += 1;
				app->audio->PlayFx(GetCoin);
			}
			app->scene->CoinUsed1 = true;
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYERLEFT || c1->type == Collider::Type::PLAYERRIGHT || c1->type == Collider::Type::PLAYERHEAD) && c2->type == Collider::Type::COIN2)
		{
			if (app->scene->CoinUsed2 == false) {
				app->coll->matrix[Collider::Type::COIN2][Collider::Type::PLAYER] = false;
				Money += 1;
				app->audio->PlayFx(GetCoin);
			}
			app->scene->CoinUsed2 = true;
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYERLEFT ||  c1->type == Collider::Type::PLAYERRIGHT || c1->type == Collider::Type::PLAYERHEAD) && c2->type == Collider::Type::COIN3)
		{
			if (app->scene->CoinUsed3 == false) {
				app->coll->matrix[Collider::Type::COIN3][Collider::Type::PLAYER] = false;
				Money += 1;
				app->audio->PlayFx(GetCoin);
			}
			app->scene->CoinUsed3 = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::COIN4)
		{
			if (app->scene->CoinUsed4 == false) {
				app->coll->matrix[Collider::Type::COIN4][Collider::Type::PLAYER] = false;
				Money += 1;
				app->audio->PlayFx(GetCoin);
			}
			app->scene->CoinUsed4 = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::COIN5)
		{
			if (app->scene->CoinUsed5 == false) {
				app->coll->matrix[Collider::Type::COIN5][Collider::Type::PLAYER] = false;
				Money += 1;
				app->audio->PlayFx(GetCoin);
			}
			app->scene->CoinUsed5 = true;
		}
	
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WIN	)
		{
			app->scene->win = true;
			app->scene->WinAnim.Reset();
			app->scene->currentScene = WIN_GAME;
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYERHEAD || c1->type == Collider::Type::PLAYERLEFT || c1->type == Collider::Type::PLAYERRIGHT) && c2->type == Collider::Type::TELEPORT)
		{
			if (Key == true) {
				app->scene->AllowTeleport = true;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TIERRA)
		{
			LOG("TIERRAAAAAA A LA VISTA");
			app->scene->conT = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::VOLADOR)
		{
			LOG("AIUDAAAAAA");
			app->scene->conV = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::LAVA)
		{
			LOG("MORISTE");
			death = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMYBOO && hit==false)
		{
			PlayerLives -= 1;
			hit = true;
		}

		/*if (c1->type != Collider::Type::PLAYER && c2->type != Collider::Type::ENEMYBOO && hit == true) {
			hit = false;
		}*/

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMYWADDLE)
		{
			PlayerLives -= 1;
		}

		
}


void Player::MovementPlayer(float dt) {
	float speed = 2 * dt * 0.09;
	
	//particles
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		app->audio->PlayFx(playerAttack);
		if (PlayerPosition == true) {
			app->particles->PlayerAttack.speed.x = 3;
			app->particles->AddParticle(app->particles->PlayerAttack, position.x, position.y, 1, Collider::Type::PLAYERATTACK);
		}
		if (PlayerPosition == false) {
			app->particles->PlayerAttack.speed.x = -3;
			app->particles->AddParticle(app->particles->PlayerAttack, position.x, position.y, 1, Collider::Type::PLAYERATTACK);
		}
	}

	if ((app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN))
	{
		if (god) 
		{
			if (app->scene->currentScene==SCENE)
			{
		//		app->audio->PlayMusic("Assets/audio/music/BackgroundMusic.ogg");
			}
			if (app->scene->currentScene == SCENE2)
			{
			//	app->audio->PlayMusic("Assets/audio/music/BackgroundMusicLevel2.ogg");
			}
			god = false; 
		}
		else if (!god) 
		{
			god = true;
		//	app->audio->PlayMusic(("Assets/audio/music/GodMode.ogg"));
		}

	}
	if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && sidesR == false)
	{
		position.x += speed;
		if (currentAnimation != &walkAnimR)
		{
			walkAnimR.Reset();
			currentAnimation = &walkAnimR;
			PlayerPosition = true;
		}
		if (app->scene->currentScene == SCENE) {
			app->scene->scrollerX -= speed / 6;
			app->scene->scrollerX1 -= speed / 24;
		}
		if (app->scene->currentScene == SCENE2) {
			app->scene->scrollerX2 -= speed / 8;
			app->scene->scrollerX3 -= speed / 14;
		}

	}

	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && sidesL == false)
	{
		position.x -= speed * 0.68;
		if (currentAnimation != &walkAnimL)
		{
			walkAnimL.Reset();
			currentAnimation = &walkAnimL;
			PlayerPosition = false;
		}
		if (app->scene->currentScene == SCENE) {
			app->scene->scrollerX += speed / 6;
			app->scene->scrollerX1 += speed / 24;
		}
		if (app->scene->currentScene == SCENE2) {
			app->scene->scrollerX2 += speed / 8;
			app->scene->scrollerX3 += speed / 14;
		}
	}
	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (sidesL == false || sidesR == false) && god == true)
	{
		position.y -= speed * 2;
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
	int gravity = 3 * dt * 0.09;
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN )
	{
		if (jumps == 1)
		{
			app->audio->PlayFx(JumpFx);
			jumps--;
			jumping2 = true;
			jumped2 = 0;
		}
		if (contact||jumps==2)
		{
			app->audio->PlayFx(JumpFx);
			if (PlayerPosition == false) {
				jumpAnimL.Reset();
				currentAnimation = &jumpAnimL;
			}
			if (PlayerPosition == true)
			{
				jumpAnimR.Reset();
				currentAnimation = &jumpAnimR;
			}
			jumps--;
			jumped = 0;
			jumping = true;
		}
	}
	if (jumping == true)
	{
		position.y -= gravity;
		jumped += 10;

		if (jumped > 70)
			{
				jumping = false;
				jumped = 0;
			}
	}
	int gravity2 = 5 * dt * 0.09;
	if (jumping2 == true)
	{
		position.y -= gravity2;
		jumped2 += 10;

		if (jumped2 > 70)
		{
			jumping2 = false;
			jumped2 = 0;
		}
	}
	

	/*if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN && jumps<0)
	{
		jumped = 0;
		dbjump = false;
	}*/
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

	if (app->scene->currentScene == SCENE) {
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
	}

	currentAnimation->Update();

	if (death == true && god == false)
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
	if (contact == false && god == false && jumping == false) {
		position.y += 3;
	}

	//Lifes
	if (PlayerLives > 5) {
		PlayerLives = 5;
	}

	if (app->scene->currentScene == SCENE|| app->scene->currentScene == SCENE2) {
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{
			PlayerLives -= 1;
		}

		if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
		{
			PlayerLives += 1;
		}

		if (PlayerLives == 5) {
			app->render->DrawTexture(HealthBarTex, 5, 5, &(Bar5.GetCurrentFrame()), 0);
		}
		if (PlayerLives == 4) {
			app->render->DrawTexture(HealthBarTex, 5, 5, &(Bar4.GetCurrentFrame()), 0);
		}
		if (PlayerLives == 3) {
			app->render->DrawTexture(HealthBarTex, 5, 5, &(Bar3.GetCurrentFrame()), 0);
		}
		if (PlayerLives == 2) {
			app->render->DrawTexture(HealthBarTex, 5, 5, &(Bar2.GetCurrentFrame()), 0);
		}
		if (PlayerLives == 1) {
			app->render->DrawTexture(HealthBarTex, 5, 5, &(Bar1.GetCurrentFrame()), 0);
		}
		if (PlayerLives == 0) {
			LOG("MORISTE");
			death = true;
		}
	}
}