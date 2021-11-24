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

ModuleEnemies::ModuleEnemies() :Module() {
	name.Create("enemy");
}

// Called before render is available
bool ModuleEnemies::Awake(pugi::xml_node&) {

	return true;
}

// Called before the first frame
bool ModuleEnemies::Start() {
	positionEnemy.x = 10;
	positionEnemy.y = 10;

	return true;
}

// Called each loop iteration
bool ModuleEnemies::PreUpdate(){
	return true;
}
bool ModuleEnemies::Update(float dt){
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
		positionEnemy.x += 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
		positionEnemy.x -= 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) {
		positionEnemy.y += 2;
	}
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) {
		positionEnemy.y -= 2;
	}
	return true;
}
bool ModuleEnemies::PostUpdate(){
	Uint8 alpha = 80;
	app->render->DrawRectangle({ positionEnemy.x,positionEnemy.y,20,20}, 250, 0, 250, alpha);

	return true;
}

// Called before quitting
bool ModuleEnemies::CleanUp(){
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