#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
struct SDL_Texture;


enum State
{
	TITLE_SCREEN,
	SCENE,
	SCENE2,
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
	bool level1;
	bool level2;
	
	float scrollerX = 0;
	float scrollerX1 = 0;

	bool Point1 = false;
	bool CheckUsed1 = false;
	bool Point2 = false;
	bool CheckUsed2 = false;
	bool Point3 = false;
	bool CheckUsed3 = false;

	bool ActiveTeleport1 = false;
	int tps1 = 1;
	bool ActiveTeleport2 = false;
	int tps2 = 1;
	bool ActiveTeleport3 = false;
	int tps3 = 1;

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
	Collider* Check3 = nullptr;
	SDL_Texture* NameCheckTex1 = nullptr;
	SDL_Texture* NameCheckTex2 = nullptr;
	SDL_Texture* NameCheckTex3 = nullptr;
	//Teleports
	SDL_Texture* Teleport1Tex = nullptr;
	SDL_Texture* Teleport2Tex = nullptr;
	SDL_Texture* Teleport3Tex = nullptr;
	
	

	SDL_Texture* pathTex;
	SDL_Texture* originTex;

	// L12b: Debug pathfing
	iPoint origin1;
	bool originSelected = false;
};

#endif // __SCENE_H__