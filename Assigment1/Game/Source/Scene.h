#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
struct SDL_Texture;


enum State
{
	TITLE_SCREEN,
	SCENE,
	GAME_OVER
};


class Scene : public Module
{
public:

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

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

	State currentScene;

	bool startTitle;
	bool LoseScreen;
	bool silence;
	

private:
	SDL_Texture* bgTexture;
	SDL_Texture* GameOver;
	SDL_Texture* Enter;

	SDL_Texture* img;
	SDL_Texture* Paral;
	SDL_Texture* bgpa;
	SDL_Texture* bgpa1;

	float scrollerX = 0;
	float scrollerX1 = 1600;

	Animation Press;
	
};

#endif // __SCENE_H__