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


	iPoint Enemy1;
	iPoint Enemy2;
	List<SDL_Texture*>enemy;
	
	Collider* Enemy1col = nullptr;
	Collider* Enemy2col = nullptr;


	int BooLive = 1;
	int WaddleLive = 1;

private:
	SDL_Texture* WaddleDeeTex = nullptr;
	SDL_Texture* BooTex = nullptr;

	Animation* currentWaddleAnimation = nullptr;
	Animation WalkWaddleR,
		WalkWaddleL,
		AttackWaddleR,
		AttackWaddleL;

	Animation* currentBooAnimation = nullptr;
	Animation FlyingBooR,
		FlyingBooL;

};
#endif