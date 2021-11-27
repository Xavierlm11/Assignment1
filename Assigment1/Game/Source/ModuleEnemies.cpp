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

	WalkWaddleL.PushBack({334,25,19,16});
	WalkWaddleL.PushBack({ 355,25,19,16 });
	WalkWaddleL.PushBack({ 377,25,19,16 });
	WalkWaddleL.PushBack({ 398,25,19,16 });
	WalkWaddleL.loop = true;
	WalkWaddleL.speed = 0.1f;

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
	positionEnemy.x = 10;
	positionEnemy.y = 10;
	WaddleDeeTex = app->tex->Load("Assets/textures/WaddleDeeEnemies.png");

	currentEnemyAnimation = &WalkWaddleL;
	return true;
}

// Called each loop iteration
bool ModuleEnemies::PreUpdate(){
	return true;
}

bool ModuleEnemies::Update(float dt){
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
		positionEnemy.x += 2;
		
		WalkWaddleR.Reset();
		currentEnemyAnimation = &WalkWaddleR;		
	}
	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
		positionEnemy.x -= 2;
		WalkWaddleL.Reset();
		currentEnemyAnimation = &WalkWaddleL;
	}
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) {
		positionEnemy.y += 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) {
		positionEnemy.y -= 2;
	}

	currentEnemyAnimation->Update();

	return true;
}

bool ModuleEnemies::PostUpdate(){
	Uint8 alpha = 80;
	app->render->DrawRectangle({ positionEnemy.x,positionEnemy.y,20,20}, 250, 0, 250, alpha);
	//Draw Waddle Dee
	SDL_Rect rect = currentEnemyAnimation->GetCurrentFrame();
	app->render->DrawTexture(WaddleDeeTex, positionEnemy.x - 10, positionEnemy.y + 20, &rect);

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
bool ModuleEnemies::LoadState(pugi::xml_node& data){
	positionEnemy.x = data.child("enemypos").attribute("x").as_int();
	positionEnemy.y = data.child("enemypos").attribute("y").as_int();

	return true;
}
bool ModuleEnemies::SaveState(pugi::xml_node& data) const{
	pugi::xml_node posenemy = data.child("enemypos");

	posenemy.attribute("x").set_value(posenemy);
	posenemy.attribute("y").set_value(posenemy);

	return true;
}