#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "List.h"
#include "App.h"


struct SDL_Texture;
struct SDL_Surface;

class Player :public Module {
public:
	Player(bool startEnabled);

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

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	// Load Texture
	SDL_Texture* const Load(const char* path);
	SDL_Texture* const LoadSurface(SDL_Surface* surface);
	bool UnLoad(SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

	iPoint position;

	bool ActivePlayer = false;

public:
	List<SDL_Texture*> player;

private:
	bool PlayerPosition = true;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	Animation idleAnimR,
		idleAnimL,
		jumpAnimR,
		jumpAnimL,
		walkAnimR,
		walkAnimL,
		PlayerDeathR,
		PlayerDeathL;

	bool god = false;

};


#endif