#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "List.h"
#include "App.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;


class Player :public Module {
public:
	Player();

	// Destructor
	virtual ~Player();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override ;
	
	// Load Texture
	SDL_Texture* const Load(const char* path);
	SDL_Texture* const LoadSurface(SDL_Surface* surface);

	iPoint position;

	bool ActivePlayer = false;

	bool contact;
	

	bool god = false;
	bool death;
	bool sidesR;
	bool sidesL;
	bool jumping;
	int jumped;
	bool dbjump;
public:
	List<SDL_Texture*> player;

private:
	bool PlayerPosition = true;

	//cargar textura del jugador
	SDL_Texture* texture = nullptr;

	//player animations
	Animation* currentAnimation = nullptr;
	Animation idleAnimR,
		idleAnimL,
		jumpAnimR,
		jumpAnimL,
		walkAnimR,
		walkAnimL,
		PlayerDeathR,
		PlayerDeathL;

	//Declarar colisiones del jugador
	Collider* colliderPlayer = nullptr;
	Collider* colliderPlayerR = nullptr;
	Collider* colliderPlayerL = nullptr;
	Collider* colliderHead = nullptr;

	//gravity
	int gravity = 1;
	
	//salto
	bool startjump = false;
	int jumpVel = 0;
	int maxjumpheight = 0;
};


#endif