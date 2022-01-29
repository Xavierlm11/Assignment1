#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "GuiButton.h"
#include "Audio.h"
#include "SDL_mixer/include/SDL_mixer.h"
struct SDL_Texture;


enum State
{
	TITLE_SCREEN,
	MENU,
	SCENE,
	CONFIG,
	PAUSEMEN,
	SCENE2,
	GAME_OVER,
	WIN_GAME
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

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	State currentScene;

	bool startTitle=true;
	bool silence=true;
	bool win;
	bool level1=false;
	bool level2=false;
	
	float scrollerX = 0;
	float scrollerX1 = 0;

	float scrollerX2 = 0;
	float scrollerX3 = 0;

	bool Point1 = false;
	bool CheckUsed1 = false;
	bool Point2 = false;
	bool CheckUsed2 = false;
	bool Point3 = false;
	bool CheckUsed3 = false;
	bool Point4 = false;
	bool CheckUsed4 = false;
	bool Point5= false;
	bool CheckUsed5 = false;

	bool ActiveTeleport1 = false;
	int tps1 = 1;
	bool ActiveTeleport2 = false;
	int tps2 = 1;
	bool ActiveTeleport3 = false;
	int tps3 = 1;
	bool ActiveTeleport4 = false;
	int tps4 = 1;
	bool ActiveTeleport5 = false;
	int tps5 = 1;

	SDL_Texture* ItemHealth1Tex = nullptr;
	SDL_Texture* ItemHealth2Tex = nullptr;
	SDL_Texture* YellowKeyTex = nullptr;

	bool CoinUsed1 = false;
	bool CoinUsed2 = false;
	bool CoinUsed3 = false;
	bool CoinUsed4 = false;
	bool CoinUsed5 = false;

	bool AllowTeleport = false;

	bool BugFixer = false;
	int UwU = 0;

	Animation WinAnim;

public:
	void DrawScene();
	void Checkpoints();
	void Teleports();
	void Keys();
	void Coins();
	void Health();
	void Pathfinding(iPoint& enemy);
	void SetGameOver();
	void SetWinGame();
	void StartCollidersLevel1();
	void StartCollidersLevel2();
	void Level1ToLevel2();
	void ResetGame();
	void ConfigMenu();
	int actualScene = 1;
	bool conT = false;
	bool conV = false;
	bool frcap = false;
	Timer clock;

	uint score = 000;
	int Font = -1;
	int GrayFont = -1;
	char scoreText[150] = { "\0" };
	//void;

	float a = 128;
	float b = 128;
	float secs = 0;
	bool pause = false;

	//Textures and fx Config
	SDL_Texture* BtnSelected;
	SDL_Texture* BtnExitTex;
	uint ClickFx = 0;
	uint SelectedFx = 0;
	SDL_Texture* BtnBigRedTex;
	SDL_Texture* BtnSmallRedTex;
private:
	//scenes
	SDL_Texture* bgTexture;
	SDL_Texture* GameOver;
	SDL_Texture* Enter;
	SDL_Texture* WinScreen;
	SDL_Texture* TeleportFinalTex;
	SDL_Texture* MenuBackgroundTex;
	SDL_Texture* MenuBoxTex;
	SDL_Texture* MenuTitleTex;
	SDL_Texture* Kirbo1Tex;
	SDL_Texture* Kirbo2Tex;

	//parallax
	SDL_Texture* img;
	SDL_Texture* Paral;
	SDL_Texture* bgpa;
	SDL_Texture* bgpa1;
	SDL_Texture* PressEnterTex;
	SDL_Texture* EnterStartTex;
	SDL_Texture* GalaxyTex;
	SDL_Texture* Level2Paral1;
	SDL_Texture* Level2Paral2;

	//mGUIII conf
	SDL_Texture* Config;
	SDL_Texture* PauseTex;
	GuiButton* Backmen;
	GuiButton* btnPlay;
	GuiButton* btnContinue;
	GuiButton* btnSettings;
	GuiButton* btnCredits;
	GuiButton* btnExit;
	GuiButton* btnMusicUp;
	GuiButton* btnMusicDown;
	GuiButton* btnFxUp;
	GuiButton* btnFxDown;
	GuiButton* btnFullScreen;
	GuiButton* btnVsync;
	GuiButton* btn30fps;
	GuiButton* btn60fps;
	bool config = false;
	bool back = false;

	

	//scenes animations
	Animation Press;
	Animation intro;
	Animation EnterStart;
	Animation TeleportFinalAnim;
	Animation Kirbo1Anim;

	
	//Fx
	uint wasted=0;
	uint winFx = 0;
	uint teleportFx = 0;
	
	
	//CheckPoint
	SDL_Texture* CheckpointTex = nullptr;
	Animation CheckPoint, CheckpointUsed;
	Collider* Check1 = nullptr;
	Collider* Check2 = nullptr;
	Collider* Check3 = nullptr;
	Collider* Check4 = nullptr;
	Collider* Check5 = nullptr;
	SDL_Texture* NameCheckTex1 = nullptr;
	SDL_Texture* NameCheckTex2 = nullptr;
	SDL_Texture* NameCheckTex3 = nullptr;

	//Teleports
	SDL_Texture* TeleportToLevel2Tex = nullptr;
	Animation TeleportAnim;
	SDL_Texture* Teleport1Tex = nullptr;
	SDL_Texture* Teleport2Tex = nullptr;
	SDL_Texture* Teleport3Tex = nullptr;
	Collider* Item1 = nullptr;
	Collider* Item2 = nullptr;
	Collider* Item3 = nullptr;
	Collider* Item4 = nullptr;
	Collider* Teleport = nullptr;

	//Key
	SDL_Texture* KeyTex = nullptr;
	Animation KeyAnim;
	Collider* KeyColl = nullptr;

	//Coins
	SDL_Texture* CoinTex = nullptr;
	Animation CoinAnim, GetCoin1, GetCoin2, GetCoin3, GetCoin4, GetCoin5;
	Collider* CoinColl1 = nullptr;
	Collider* CoinColl2 = nullptr;
	Collider* CoinColl3 = nullptr;
	Collider* CoinColl4 = nullptr;
	Collider* CoinColl5 = nullptr;

	Collider* WinCol = nullptr;
	
	SDL_Texture* pathTex;
	SDL_Texture* originTex;

	// L12b: Debug pathfing
	iPoint origin1;
	bool originSelected = false;


	int rot = 0;
	float movex = -10;
	float movey = -10;
	float movex1 = 260;
	float movey1 = 30;

	//_Mix_Music* lvl1mus;
	/*_Mix_Music* lvl2mus = 0;
	_Mix_Music* Godmus=0;*/

	//uint* lvl1mus;
	/*uint* lvl2mus ;
	uint* Godmus ;*/
};

#endif // __SCENE_H__