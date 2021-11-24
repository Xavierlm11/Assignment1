#ifndef __MODULEENEMIES_H__
#define __MODULEENEMIES_H__

#include "Module.h"
#include "Animation.h"
#include "List.h"
#include "App.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class ModuleEnemies :public Module {
public:
	ModuleEnemies();

	virtual ~ModuleEnemies();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	iPoint positionEnemy;

	List<SDL_Texture*>enemy;

private:
	SDL_Texture* WaddleDeeTex = nullptr;

	Animation* currentEnemyAnimation = nullptr;
	Animation WalkWaddleR,
		WalkWaddleL,
		AttackWaddleR,
		AttackWaddleL;
};
#endif