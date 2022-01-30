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

	//All player movement
	void MovementPlayer(float dt);

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	
	//// Load Texture
	//SDL_Texture* const Load(const char* path);
	//SDL_Texture* const LoadSurface(SDL_Surface* surface);

	iPoint position;

	bool ActivePlayer = false;

	bool contact;
	
	bool god = false;
	bool death;
	bool sidesR;
	bool sidesL;
	bool jumping;
	bool jumping2;
	int jumps;
	int jumped;
	int jumped2;
	bool dbjump;

	bool hit = false;

	Collider* misil = nullptr;

public:
	List<SDL_Texture*> player;

	bool CheckActive1 = false;
	bool CheckActive2 = false;
	bool CheckActive3 = false;
	bool CheckActive4 = false;
	bool CheckActive5 = false;

	bool item1Used = false;
	bool item2Used = false;
	bool item3Used = false;
	bool item4Used = false;

	bool Key = false;

	int Money = 0;
	uint GetCoin = 0;

	//Player Lives
	int PlayerLives = 5;
	bool PlayerPosition = true;

	uint JumpFx = 0;

	uint playerAttack = 0;

	int score = 0;
	int timer = 500;
	int secs;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int limitFont = -1;
	char limitText[10] = { "\0" };
private:
	

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

	//Lifes
	SDL_Texture* HealthBarTex = nullptr;
	Animation Bar5, Bar4, Bar3, Bar2, Bar1;

	uint GetItem = 0;
	uint GetCheckpoint = 0;
	uint GetKey = 0;

	//Declarar colisiones del jugador
	Collider* colliderPlayer = nullptr;
	Collider* colliderPlayerR = nullptr;
	Collider* colliderPlayerL = nullptr;
	Collider* colliderHead = nullptr;

	//gravity
	int gravity = 1;
	

};


#endif