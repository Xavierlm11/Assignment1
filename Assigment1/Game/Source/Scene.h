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

	Scene( );

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
	
	float scrollerX = 0;
	float scrollerX1 = 0;

	bool Point1 = false;
	bool CheckUsed1 = false;
	bool Point2 = false;
	bool CheckUsed2 = false;

private:
	//scenes
	SDL_Texture* bgTexture;
	SDL_Texture* GameOver;
	SDL_Texture* Enter;

	//parallax
	SDL_Texture* img;
	SDL_Texture* Paral;
	SDL_Texture* bgpa;
	SDL_Texture* bgpa1;
	SDL_Texture* PressEnterTex;
	SDL_Texture* EnterStartTex;
	SDL_Texture* GalaxyTex;
	//scenes animations
	Animation Press;
	Animation intro;
	Animation EnterStart;
	
	//Fx
	uint wasted=0;

	//CheckPoint
	SDL_Texture* CheckpointTex = nullptr;
	Animation CheckPoint, CheckpointUsed;
	Collider* Check1 = nullptr;
	Collider* Check2 = nullptr;
	
};

#endif // __SCENE_H__