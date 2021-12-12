#include "ModuleEnemies.h"
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

ModuleEnemies::ModuleEnemies() :Module() 
{
	name.Create("enemy");

	WalkWaddleR.PushBack({14,26,19,16});
	WalkWaddleR.PushBack({35,26,19,16});
	WalkWaddleR.PushBack({ 57,26,19,16 });
	WalkWaddleR.PushBack({ 78,26,19,16 });
	WalkWaddleR.loop = true;
	WalkWaddleR.speed = 0.1f;

	WalkWaddleL.PushBack({270,24,19,16});
	WalkWaddleL.PushBack({291,25,19,16 });
	WalkWaddleL.PushBack({ 313,25,19,16 });
	WalkWaddleL.PushBack({ 334,25,19,16 });
	WalkWaddleL.loop = true;
	WalkWaddleL.speed = 0.1f;

	FlyingBooL.PushBack({ 1,4,24,20 });
	FlyingBooL.PushBack({ 1,36,24,20 });
	FlyingBooL.PushBack({ 1,68,24,20 });
	FlyingBooL.loop = true;
	FlyingBooL.speed = 0.1f;

	FlyingBooR.PushBack({ 34,2,24,20 });
	FlyingBooR.PushBack({ 34,34,24,20 });
	FlyingBooR.PushBack({ 34,66,24,20 });
	FlyingBooR.loop = true;
	FlyingBooR.speed = 0.1f;

}

ModuleEnemies::~ModuleEnemies()
{}

// Called before render is available
bool ModuleEnemies::Awake(pugi::xml_node&) {

	LOG("Init Image library");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ModuleEnemies::Start() {
	Enemy1.x = 1100;
	Enemy1.y = 144;
	Enemy2.x = 550;
	Enemy2.y = 150;
	WaddleDeeTex = app->tex->Load("Assets/textures/WaddleDeeEnemies.png");
	BooTex = app->tex->Load("Assets/textures/BooSheet.png");

	currentWaddleAnimation = &WalkWaddleL;
	currentBooAnimation = &FlyingBooL;

	Enemy1col = app->coll->AddCollider({ Enemy1.x,Enemy1.y,20,20 }, Collider::Type::ENEMYWADDLE, this);
	Enemy2col = app->coll->AddCollider({ Enemy2.x,Enemy2.y,20,20 }, Collider::Type::ENEMYBOO, this);

	return true;
}

// Called each loop iteration
bool ModuleEnemies::PreUpdate(){
	return true;
}

bool ModuleEnemies::Update(float dt){
	//COLLISIONS
	Enemy1col->SetPos(Enemy1.x, Enemy1.y);
	Enemy2col->SetPos(Enemy2.x, Enemy2.y);


	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
		Enemy1.x += 2;
		Enemy2.x += 2;
		WalkWaddleR.Reset();
		currentWaddleAnimation = &WalkWaddleR;

		FlyingBooR.Reset();
		currentBooAnimation = &FlyingBooR;
	}
	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
		Enemy1.x -= 2;
		Enemy2.x -= 2;
		WalkWaddleL.Reset();
		currentWaddleAnimation = &WalkWaddleL;

		FlyingBooL.Reset();
		currentBooAnimation = &FlyingBooL;
	}
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) {
		Enemy1.y += 2;
		Enemy2.y += 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) {
		Enemy1.y -= 2;
		Enemy2.y -= 2;
	}

	currentWaddleAnimation->Update();
	currentBooAnimation->Update();

	return true;
}

bool ModuleEnemies::PostUpdate(){
	if (app->scene->currentScene == SCENE) {
		//Draw Waddle Dee
		SDL_Rect rect = currentWaddleAnimation->GetCurrentFrame();
		app->render->DrawTexture(WaddleDeeTex, Enemy1.x, Enemy1.y, &rect);
		
		//Draw Boo
		SDL_Rect Boo = currentBooAnimation->GetCurrentFrame();
		app->render->DrawTexture(BooTex, Enemy2.x, Enemy2.y, &Boo);
		
	}
	if (app->scene->currentScene == SCENE2) {
		//Draw Waddle Dee
		SDL_Rect rect = currentWaddleAnimation->GetCurrentFrame();
		app->render->DrawTexture(WaddleDeeTex, Enemy1.x, Enemy1.y, &rect);

		

	}

	return true;
}

// Called before quitting
bool ModuleEnemies::CleanUp(){
	LOG("Freeing textures and Image library");
	ListItem<SDL_Texture*>* item;

	for (item = enemy.start; item != NULL; item = item->next)
	{
		SDL_DestroyTexture(item->data);
	}

	enemy.clear();
	IMG_Quit();
	return true;
}

// Load / Save
bool ModuleEnemies::LoadState(pugi::xml_node& data) {
	Enemy1.x = data.child("enemy1").attribute("x").as_int();
	Enemy1.y = data.child("enemy1").attribute("y").as_int();

	Enemy2.x = data.child("enemy2").attribute("x").as_int();
	Enemy2.y = data.child("enemy2").attribute("y").as_int();

	return true;
}
bool ModuleEnemies::SaveState(pugi::xml_node& data) const {
	pugi::xml_node posenemy1 = data.child("enemy1");
	pugi::xml_node posenemy2 = data.child("enemy2");

	posenemy1.attribute("x").set_value(Enemy1.x);
	posenemy1.attribute("y").set_value(Enemy1.y);

	posenemy2.attribute("x").set_value(Enemy2.x);
	posenemy2.attribute("y").set_value(Enemy2.y);

	return true;
}
