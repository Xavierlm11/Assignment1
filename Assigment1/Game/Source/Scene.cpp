#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "ModuleCollisions.h"
#include "PathFinding.h"
#include "ModuleEnemies.h"
#include "GuiManager.h"
#include "ModuleFonts.h"


#include "SDL_mixer/include/SDL_mixer.h"

Scene::Scene() : Module()
{
	name.Create("scene");
	//death scene animation
	Press.PushBack({ 0,0,115,55 });
	Press.PushBack({ 0,0,0,0 });
	Press.loop = true;
	Press.speed = 0.01f;

	//Press Enter Anim
	EnterStart.PushBack({ 0,0,0,0 });
	EnterStart.PushBack({ 0,0,85,26 });
	EnterStart.PushBack({ 0,0,0,0 });
	EnterStart.PushBack({ 0,0,85,26 });
	EnterStart.loop = true;
	EnterStart.speed = 0.01f;

	//intro animation
	intro.PushBack({ 0,0,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.loop = false;
	intro.speed = 0.01f;

	CheckPoint.PushBack({ 0,1,20,26 });
	CheckPoint.PushBack({ 22,1,20,26 });
	CheckPoint.PushBack({ 44,1,20,26 });
	CheckPoint.PushBack({ 66,1,20,26 });
	CheckPoint.PushBack({ 90,1,20,26 });
	CheckPoint.PushBack({ 112,1,20,26 });
	CheckPoint.loop = true;
	CheckPoint.speed = 0.15f;

	CheckpointUsed.PushBack({ 1,39,20,26 });
	CheckpointUsed.PushBack({ 24,39,20,26 });
	CheckpointUsed.PushBack({ 46,39,20,26 });
	CheckpointUsed.PushBack({ 68,39,20,26 });
	CheckpointUsed.PushBack({ 92,39,20,26 });
	CheckpointUsed.PushBack({ 114,39,20,26 });
	CheckpointUsed.loop = true;
	CheckpointUsed.speed = 0.15f;

	//Key
	KeyAnim.PushBack({ 1,1,10,19 });
	KeyAnim.PushBack({ 12,1,10,19 });
	KeyAnim.PushBack({ 23,1,10,19 });
	KeyAnim.PushBack({ 34,1,10,19 });
	KeyAnim.PushBack({ 45,1,10,19 });
	KeyAnim.PushBack({ 56,1,10,19 });
	KeyAnim.PushBack({ 66,1,10,19 });
	KeyAnim.PushBack({ 77,1,10,19 });
	KeyAnim.PushBack({ 88,1,10,19 });
	KeyAnim.PushBack({ 99,1,10,19 });
	KeyAnim.loop = true;
	KeyAnim.speed = 0.1f;

	//Coin
	CoinAnim.PushBack({ 1,2,13,12 });
	CoinAnim.PushBack({ 18,2,13,12 });
	CoinAnim.PushBack({ 34,1,13,12 });
	CoinAnim.PushBack({ 48,1,13,12 });
	CoinAnim.PushBack({ 65,1,13,12 });
	CoinAnim.PushBack({ 81,1,13,12 });
	CoinAnim.PushBack({ 96,1,13,12 });
	CoinAnim.PushBack({ 112,1,13,12 });
	CoinAnim.PushBack({ 128,1,13,12 });
	CoinAnim.loop = true;
	CoinAnim.speed = 0.15f;

	GetCoin1.PushBack({ 165,2,27,12 });
	GetCoin1.loop = false;

	GetCoin2.PushBack({ 197,2,29,12 });
	GetCoin2.loop = false;

	GetCoin3.PushBack({ 231,2,30,12 });
	GetCoin3.loop = false;

	GetCoin4.PushBack({ 266,2,30,12 });
	GetCoin4.loop = false;

	GetCoin5.PushBack({ 300,2,30,12 });
	GetCoin5.loop = false;

	TeleportAnim.PushBack({0,0,25,35});
	TeleportAnim.PushBack({ 51,0,25,35 });
	TeleportAnim.PushBack({ 102,0,25,35 });
	TeleportAnim.PushBack({ 153,0,25,35 });
	TeleportAnim.PushBack({ 205,0,25,35 });
	TeleportAnim.PushBack({ 256,0,25,35 });
	TeleportAnim.PushBack({ 307,0,25,35 });
	TeleportAnim.PushBack({ 358,0,25,35 });
	TeleportAnim.loop = true;
	TeleportAnim.speed = 0.15f;

	//Win Animation
	for (int i = 0; i < 39; i++) {
		WinAnim.PushBack({ i * 240,0,240,168 });
	}
	WinAnim.loop = false;
	WinAnim.speed = 0.15f;

	for (int i = 0; i < 40; i++) {
		TeleportFinalAnim.PushBack({ i * 25,0,25,25 });
	}
	TeleportFinalAnim.loop = true;
	TeleportFinalAnim.speed = 0.65f;

	Kirbo1Anim.PushBack({ 0,0,18,30 });

}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{

	//app->map->Load("level1.tmx");
	
	//app->map->CreateColliders();
	
	//Textures
	bgpa = app->tex->Load("Assets/textures/BackgroundParallax.png");
	bgpa1 = app->tex->Load("Assets/textures/BackgroundParallax.png");
	bgTexture = app->tex->Load("Assets/textures/IntroMenu.png");
	GameOver = app->tex->Load("Assets/textures/Wasted.png");//Game over
	EnterStartTex = app->tex->Load("Assets/textures/PressEnter.png");
	Enter = app->tex->Load("Assets/textures/LoseEnter.png");
	GalaxyTex= app->tex->Load("Assets/textures/GalaxyTex.png");
	Level2Paral1 = app->tex->Load("Assets/textures/Level2Parallax1.png");
	Level2Paral2 = app->tex->Load("Assets/textures/Level2Parallax2.png");
	TeleportToLevel2Tex = app->tex->Load("Assets/textures/TeleportTex.png");
	WinScreen = app->tex->Load("Assets/textures/WinScreenTex.png");
	TeleportFinalTex = app->tex->Load("Assets/textures/PadoruTex.png");
	MenuBackgroundTex = app->tex->Load("Assets/textures/MEnuBackground.png");
	MenuBoxTex= app->tex->Load("Assets/textures/MenuBoxesTex.png");
	MenuTitleTex= app->tex->Load("Assets/textures/MenuTitleTex.png");
	Kirbo1Tex= app->tex->Load("Assets/textures/Kirbo1Tex.png");
	Kirbo2Tex = app->tex->Load("Assets/textures/Kirbo2Tex.png");
	
	//CheckPoints
	CheckpointTex = app->tex->Load("Assets/textures/checkpointTex.png");
	NameCheckTex1 = app->tex->Load("Assets/textures/Checkpoint1Tex.png");
	NameCheckTex2 = app->tex->Load("Assets/textures/Checkpoint2Tex.png");
	NameCheckTex3 = app->tex->Load("Assets/textures/Checkpoint3Tex.png");
	Teleport1Tex= app->tex->Load("Assets/textures/TeleportTo1Tex.png");
	Teleport2Tex = app->tex->Load("Assets/textures/TeleportTo2Tex.png");
	Teleport3Tex = app->tex->Load("Assets/textures/TeleportTo3Tex.png");

	//Items
	ItemHealth1Tex = app->tex->Load("Assets/textures/CakeTex.png");
	ItemHealth2Tex = app->tex->Load("Assets/textures/PeachTex.png");
	KeyTex = app->tex->Load("Assets/textures/KeyTex.png");
	YellowKeyTex = app->tex->Load("Assets/textures/YellowKeyTex.png");

	//Coins
	CoinTex = app->tex->Load("Assets/textures/CoinTex.png");

	//Fx
	wasted=app->audio->LoadFx("Assets/audio/fx/Wasted.wav");
	teleportFx = app->audio->LoadFx("Assets/audio/fx/TeleportFx.wav");
	winFx = app->audio->LoadFx("Assets/audio/fx/WinFx.wav");
	
	currentScene = TITLE_SCREEN; //Game starts with Title Screen

	//lvl1mus = Mix_LoadMUS("Assets/audio/music/BackgroundMusic.ogg");

	// L14: TODO 2: Declare a GUI Button and create it using the GuiManager
	btnPlay = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Play", { (49), 91, 65, 31 }, this);
	btnContinue = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Continue", { (122), 91, 65, 31 }, this);
	btnSettings = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Settings", { (49), 127, 65, 20 }, this);
	btnCredits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits", { (122), 127, 65, 20 }, this);
	btnExit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Exit", { (2), 2, 5, 5 }, this);
	Backmen = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Back", { (188), 41, 5, 5 }, this);
	Config = app->tex->Load("Assets/textures/config.png");
	
	btnPlay->texture = CoinTex;

	//Fonts

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	Font = app->fonts->Load("Assets/Fonts/SelectedFont.png", lookupTable, 2);
	GrayFont = app->fonts->Load("Assets/Fonts/DeSelectedFont.png", lookupTable, 2);
	StartCollidersLevel1();
	
	if (app->map->Load("level1.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	//app->map->Load("level1.tmx");
	app->map->CreateColliders();
	pathTex = app->tex->Load("Assets/maps/cuad.png");
	originTex = app->tex->Load("Assets/maps/a.png");
	//app->map->CreateColliders();

	
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	/*int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);*/

	uint miliseconds = clock.Read() % 1000;
	uint seconds = (clock.Read() / 1000) % 60;
	uint minutes = (clock.Read() / 1000) / 60;

	iPoint tierra;
	iPoint volador;
	iPoint jug;

	
	if (currentScene == SCENE) {
		
		volador = app->map->WorldToMap(app->enemies->Enemy2.x, app->enemies->Enemy2.y);
		jug = app->map->WorldToMap(app->player->position.x, app->player->position.y);
		/*if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (originSelected == true)
			{
				app->pathfinding->CreatePath(origin1, p);
				originSelected = false;
			}
			else
			{
				origin1 = p;
				originSelected = true;
			}
		}*/
		if (!pause) {
			if (conV == true && app->enemies->BooLive == 1)
			{

				app->pathfinding->CreatePath(volador, jug);
			}
		}
	}

	if (currentScene == SCENE2)
	{
		tierra = app->map->WorldToMap(app->enemies->Enemy1.x, app->enemies->Enemy1.y);
		jug = app->map->WorldToMap(app->player->position.x, app->player->position.y);
		if (!pause) {
			if (conT == true && app->enemies->WaddleLive == 1)
			{

				app->pathfinding->CreatePath(tierra, jug);
			}
		}
	}
	if (level1) {
		app->map->Load("level1.tmx");
		StartCollidersLevel1();
		app->map->CreateColliders();
		level1 = false;	
	}
	if (level2) {
		app->map->Load("level2.tmx");
		StartCollidersLevel2();
		app->map->CreateColliders();
		level2 = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) {
		frcap = !frcap;

	}
	if (frcap) {
		app->maxFrameRate = 32;

	}
	else
	{
		app->maxFrameRate = 16;
	}
	
	
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	EnterStart.Update();
	switch (currentScene)
	{
	case TITLE_SCREEN:

		intro.Update();
		if (silence)
		{
			silence = false;
			app->audio->PlayMusic("Assets/audio/music/Silence.ogg");
		}
		if ((app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)||(app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)) {
						

			currentScene = MENU;
			silence = true;
			
		}
	
		app->render->DrawTexture(bgTexture, 0, 0, &(intro.GetCurrentFrame()));
		app->render->DrawTexture(EnterStartTex,80, 140, &(EnterStart.GetCurrentFrame()));
		
		break;

	case MENU:

		app->render->DrawTexture(MenuBackgroundTex, 0, 0, NULL);
		
		app->render->DrawTexture(Kirbo1Tex, movex, movey, &(Kirbo1Anim.GetCurrentFrame()),1.0f,rot);
		rot+= dt*0.09;
	
		movex += dt * 0.04;
		movey += dt * 0.03;
		
		if (movex > 230 && movey > 100) {
			movex = -10;
			movey = -10;
		}

		app->render->DrawTexture(Kirbo2Tex, movex1, movey1, &(Kirbo1Anim.GetCurrentFrame()), 1.0f, rot+80);
		if (config == false)
		{
			app->render->DrawTexture(MenuBoxTex, 40, 90, NULL);
			app->render->DrawTexture(MenuTitleTex, 0, 0, NULL);
		}
		if (config == true)
		{
			app->render->DrawTexture(Config, 0 ,0,NULL);
		}
		movex1 -= dt * 0.04;
		
		if (movex1 < -30) {
			movex1 = 260;
		}
		
		//Draw GUI
		app->guiManager->Draw();
		
		break;
	case CONFIG:
		app->render->DrawTexture(Config, 0, 0, NULL);

		app->guiManager->Draw();

		break;

	case PAUSEMEN:



		break;
	case SCENE:
		
		
		if (startTitle)
		{
			
			startTitle = false;
			
			app->audio->PlayMusic("Assets/audio/music/BackgroundMusic.ogg");
		}
		
	
		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
			app->LoadGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
			app->SaveGameRequest();

		// Draw map
		DrawScene();

		//Checkpoints
		Checkpoints();
		
		//Teleports
		Teleports();

		//Key
		Keys();

		//Coins
		Coins();

		//Draw Items
		Health();
		
		// L12b: Debug pathfinding
		if(!pause)Pathfinding(app->enemies->Enemy2);
		
		//if (conT)Pathfinding(app->enemies->Enemy1);

		
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
			ResetGame();
		}

		if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN || AllowTeleport==true) {
			Level1ToLevel2();
		}

		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
			win = true;
			WinAnim.Reset();
			currentScene = WIN_GAME;
		}
		
		break;
		case SCENE2:
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE && app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && UwU==0) {
				BugFixer = true;
			}
			if (BugFixer == true) {
				app->player->position.x = 40;
				app->player->position.y = 0;
				scrollerX2 = 0;
				scrollerX3 = 0;
				BugFixer = false;
				UwU = 1;
			}

			if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
				app->coll->clean();
				app->map->CleanUp();
				level1 = true;
				startTitle = true;
				app->player->position.x = 70;
				app->player->position.y = 0;
				actualScene = 1; 
				currentScene = SCENE;
			}

			if (silence) {
				app->audio->PlayMusic("Assets/audio/music/BackgroundMusicLevel2.ogg");
				silence = false;
			}
			
			app->map->Draw();
			// Draw map
			DrawScene();
			Checkpoints();
			Teleports();
			Health();
			Coins();
			if (!pause)Pathfinding(app->enemies->Enemy1);


			if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
				app->LoadGameRequest();

			if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
				app->SaveGameRequest();

			if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
				ResetGame();
			}

			if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
				win = true;
				WinAnim.Reset();
				currentScene = WIN_GAME;
			}
			
			break;
	case GAME_OVER:

		SetGameOver();
		clock.Stop();
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			if (actualScene == 1) 
			{
				startTitle = true;
				currentScene = SCENE;
				app->player->PlayerLives = 5;		
				app->LoadGameRequest();
			}
			if (actualScene == 2)
			{
				startTitle = true;
				currentScene = SCENE2;
				silence = true;
				app->player->PlayerLives = 5;
				app->LoadGameRequest();
			}
		}
		break;
	case WIN_GAME:
		SetWinGame();
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			
			ResetGame();
		/*	startTitle = true;
			currentScene = SCENE;
			app->player->PlayerLives = 5;		*/
			
		}
	}

	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || back==true)
		ret = false;

	//sprintf_s(scoreText, 10, "%4d", steps);
	switch (currentScene)
	{
	case MENU:
		if (config ==false)
		{
			app->fonts->BlitText(55, 100, Font, "play");
			app->fonts->BlitText(128, 100, GrayFont, "continue");

			app->fonts->BlitText(55, 135, Font, "config.");


		}
	

		break;

	//case :

	//	break;
	//case MENU:

	//	break;

	}
	
	return ret;
}

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	bool ret = true;

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{

		//Checks the GUI element ID
		
		if (currentScene==MENU ) {
			
				if (control->id == 1)
				{
					LOG("Click on button 1");
					currentScene = SCENE;
					clock.Stop();
					clock.Start();
					startTitle = true;

					app->render->camera.y = 0;
					app->render->camera.x = 0;

					app->player->position.x = 70;
					app->player->position.y = 15;
					app->SaveGameRequest();
				}

				if (control->id == 2)
				{
					LOG("Click on button 2");
				}

				if (control->id == 3)
				{
					LOG("Click on button 3");

					currentScene = CONFIG;
				}
				if (control->id == 4)
				{
					LOG("Click on button 4");
					a--;
					
					//Mix_Volume(1, a);
					Mix_VolumeMusic(a);
				}

				if (control->id == 5)
				{
					LOG("Click on button 5");
					back = true;
				}
			
			/*if (config == true)
			{
				
			}*/
		}
		if (currentScene == CONFIG)
		{
			if (control->id == 6)
			{
				LOG("Click on button 6");
				currentScene = MENU;
			}
		}
	}
	//Other cases here

	default: break;
	}

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

// Load / Save
bool Scene::LoadState(pugi::xml_node& data) {
	CheckUsed1 = data.child("teleport").attribute("check1").as_bool();
	CheckUsed2 = data.child("teleport").attribute("check2").as_bool();
	CheckUsed3 = data.child("teleport").attribute("check3").as_bool();
	CheckUsed4 = data.child("teleport").attribute("check4").as_bool();
	CheckUsed5 = data.child("teleport").attribute("check5").as_bool();

	app->player->Money = data.child("Money").attribute("coins").as_int();
	CoinUsed1 = data.child("Money").attribute("coinused1").as_bool();
	CoinUsed2 = data.child("Money").attribute("coinused2").as_bool();
	CoinUsed3 = data.child("Money").attribute("coinused3").as_bool();
	CoinUsed4 = data.child("Money").attribute("coinused4").as_bool();
	CoinUsed5 = data.child("Money").attribute("coinused5").as_bool();

	app->player->item1Used = data.child("Health").attribute("item1").as_bool();
	app->player->item2Used = data.child("Health").attribute("item2").as_bool();
	app->player->item3Used = data.child("Health").attribute("item3").as_bool();
	app->player->item4Used = data.child("Health").attribute("item4").as_bool();

	return true;
}
bool Scene::SaveState(pugi::xml_node& data) const {
	pugi::xml_node teleports = data.child("teleport");
	pugi::xml_node coins = data.child("Money");
	pugi::xml_node items = data.child("Health");

	teleports.attribute("check1").set_value(CheckUsed1);
	teleports.attribute("check2").set_value(CheckUsed2);
	teleports.attribute("check3").set_value(CheckUsed3);
	teleports.attribute("check4").set_value(CheckUsed4);
	teleports.attribute("check5").set_value(CheckUsed5);

	coins.attribute("coins").set_value(app->player->Money);
	coins.attribute("coinused1").set_value(CoinUsed1);
	coins.attribute("coinused2").set_value(CoinUsed2);
	coins.attribute("coinused3").set_value(CoinUsed3);
	coins.attribute("coinused4").set_value(CoinUsed4);
	coins.attribute("coinused5").set_value(CoinUsed5);

	items.attribute("item1").set_value(app->player->item1Used);
	items.attribute("item2").set_value(app->player->item2Used);
	items.attribute("item3").set_value(app->player->item3Used);
	items.attribute("item4").set_value(app->player->item4Used);

	return true;
}

////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            Function calls
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Scene::DrawScene()
{
	if (app->scene->currentScene == SCENE) {
		app->render->DrawTexture(bgpa, scrollerX, 0, NULL);
		app->render->DrawTexture(GalaxyTex, scrollerX1, 0, NULL);
	}
	if (app->scene->currentScene == SCENE2) {
		app->render->DrawTexture(Level2Paral2, scrollerX3 - 75, -40, NULL);
		app->render->DrawTexture(Level2Paral1, scrollerX2-75, -40, NULL);
		
	}

	app->map->Draw();

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		silence = true;
		currentScene = TITLE_SCREEN;

		app->player->position.x = 50000;
		app->player->position.y = 20000;
		app->render->camera.x = 0;
		app->render->camera.y = 0;
	}
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		app->audio->PlayFx(wasted);
		silence = true;
		currentScene = GAME_OVER;
	}

	

}



void Scene::Checkpoints()
{
	if (actualScene == 1) {
		if (Point1 == true && CheckUsed1 == false) {
			app->SaveGameRequest();
			Point1 = false;
			CheckUsed1 = true;
		}
		if (Point2 == true && CheckUsed2 == false) {
			app->SaveGameRequest();
			Point2 = false;
			CheckUsed2 = true;
		}
		if (Point3 == true && CheckUsed3 == false) {
			app->SaveGameRequest();
			Point3 = false;
			CheckUsed3 = true;
		}

		if (Point1 == false) {
			app->render->DrawTexture(CheckpointTex, 70, 255, &(CheckPoint.GetCurrentFrame()));
		}
		if (Point1 == true) {
			app->render->DrawTexture(CheckpointTex, 70, 255, &(CheckpointUsed.GetCurrentFrame()));
		}
		if (Point2 == false) {
			app->render->DrawTexture(CheckpointTex, 233, 23, &(CheckPoint.GetCurrentFrame()));
		}
		if (Point2 == true) {
			app->render->DrawTexture(CheckpointTex, 233, 23, &(CheckpointUsed.GetCurrentFrame()));
		}
		if (Point3 == false) {
			app->render->DrawTexture(CheckpointTex, 590, 216, &(CheckPoint.GetCurrentFrame()));
		}
		if (Point3 == true) {
			app->render->DrawTexture(CheckpointTex, 590, 216, &(CheckpointUsed.GetCurrentFrame()));
		}

		if (app->player->CheckActive1 == true) {
			app->render->DrawTexture(NameCheckTex1, app->player->position.x - 20, app->player->position.y + 90, NULL);
			app->player->CheckActive1 = false;
		}
		if (app->player->CheckActive2 == true) {
			app->render->DrawTexture(NameCheckTex2, app->player->position.x - 20, app->player->position.y + 90, NULL);
			app->player->CheckActive2 = false;
		}
		if (app->player->CheckActive3 == true) {
			app->render->DrawTexture(NameCheckTex3, app->player->position.x - 20, app->player->position.y + 90, NULL);
			app->player->CheckActive3 = false;
		}
		CheckPoint.Update();
		CheckpointUsed.Update();
	}
	if (actualScene == 2) {
		if (Point4 == true && CheckUsed4 == false) {
			app->SaveGameRequest();
			Point4 = false;
			CheckUsed4 = true;
		}
		if (Point5 == true && CheckUsed5 == false) {
			app->SaveGameRequest();
			Point5 = false;
			CheckUsed5 = true;
		}

		if (Point4 == false) {
			app->render->DrawTexture(CheckpointTex, 108, 136, &(CheckPoint.GetCurrentFrame()));
		}
		if (Point5 == false) {
			app->render->DrawTexture(CheckpointTex, 640, 110, &(CheckPoint.GetCurrentFrame()));
		}
		if (Point4 == true) {
			app->render->DrawTexture(CheckpointTex, 108, 137, &(CheckpointUsed.GetCurrentFrame()));
		}
		if (Point5 == true) {
			app->render->DrawTexture(CheckpointTex, 640, 111, &(CheckpointUsed.GetCurrentFrame()));
		}

		if (app->player->CheckActive4 == true) {
			app->render->DrawTexture(NameCheckTex1, app->player->position.x - 20, app->player->position.y + 90, NULL);
			app->player->CheckActive4 = false;
		}
		if (app->player->CheckActive5 == true) {
			app->render->DrawTexture(NameCheckTex2, app->player->position.x - 20, app->player->position.y + 90, NULL);
			app->player->CheckActive5 = false;
		}
		CheckPoint.Update();
		CheckpointUsed.Update();
	}
}


void Scene::Teleports()
{
	if (actualScene == 1) {
		
		app->render->DrawTexture(TeleportToLevel2Tex, 32, 23, &(TeleportAnim.GetCurrentFrame()));
		TeleportAnim.Update();

		if (ActiveTeleport1 == true) { //TP 1
			if (tps1 == 1) {
				app->render->DrawTexture(Teleport2Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (tps1 == 2) {
				app->render->DrawTexture(Teleport3Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				tps1 += 1;
			}
			if (tps1 == 3) {
				tps1 = 1;
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps1 == 1 && Point2 == true) {//Checkpoint 2 from 1
				app->player->position.x = 233;
				app->player->position.y = 5;
				ActiveTeleport1 = false;
				app->audio->PlayFx(teleportFx);
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps1 == 2 && Point3 == true) {//Checkpoint 3 from 1
				app->player->position.x = 590;
				app->player->position.y = 200;
				ActiveTeleport1 = false;
				app->audio->PlayFx(teleportFx);
			}
			ActiveTeleport1 = false;
		}

		if (ActiveTeleport2 == true) { //TP 2
			if (tps2 == 1) {
				app->render->DrawTexture(Teleport1Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (tps2 == 2) {
				app->render->DrawTexture(Teleport3Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				tps2 += 1;
			}
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
				tps2 -= 1;
			}
			if (tps2 == 3 || tps2 == 0) {
				tps2 = 1;
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps2 == 1 && Point1 == true) {//Checkpoint 1 from 2
				app->player->position.x = 70;
				app->player->position.y = 240;
				ActiveTeleport2 = false;
				app->audio->PlayFx(teleportFx);
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps2 == 2 && Point3 == true) {//Checkpoint 3 from 2
				app->player->position.x = 590;
				app->player->position.y = 200;
				ActiveTeleport2 = false;
				app->audio->PlayFx(teleportFx);
			}
			ActiveTeleport2 = false;
		}

		if (ActiveTeleport3 == true) { //TP 3
			if (tps3 == 1) {
				app->render->DrawTexture(Teleport1Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (tps3 == 2) {
				app->render->DrawTexture(Teleport2Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				tps3 += 1;
			}
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
				tps3 -= 1;
			}
			if (tps3 == 3 || tps3 == 0) {
				tps3 = 1;
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps3 == 1 && Point1 == true) {//Checkpoint 1 from 3
				app->player->position.x = 70;
				app->player->position.y = 240;
				ActiveTeleport3 = false;
				app->audio->PlayFx(teleportFx);
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps3 == 2 && Point2 == true) {//Checkpoint 2 from 3
				app->player->position.x = 233;
				app->player->position.y = 5;
				ActiveTeleport3 = false;
				app->audio->PlayFx(teleportFx);
			}
			ActiveTeleport3 = false;
		}
	}
	if (actualScene == 2) {
		if (ActiveTeleport4 == true) { //TP 4
			if (tps4 == 1) {
				app->render->DrawTexture(Teleport2Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps4 == 1 && Point5 == true) {
				app->player->position.x = 645;
				app->player->position.y = 95;
				ActiveTeleport4 = false;
				app->audio->PlayFx(teleportFx);
			}
			ActiveTeleport4 = false;
		}
		if (ActiveTeleport5 == true) { //TP 5
			if (tps5 == 1) {
				app->render->DrawTexture(Teleport1Tex, app->player->position.x - 52, app->player->position.y + 80, NULL);
			}
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && tps5 == 1 && Point4 == true) {
				app->player->position.x = 108;
				app->player->position.y = 125;
				ActiveTeleport5 = false;
				app->audio->PlayFx(teleportFx);
			}
			ActiveTeleport5 = false;
		}
		app->render->DrawTexture(TeleportFinalTex, 1390, 113, &(TeleportFinalAnim.GetCurrentFrame()));
		TeleportFinalAnim.Update();
	}

}



void Scene::Keys()
{
	if (app->player->Key == false) {
		app->render->DrawTexture(KeyTex, 206, 140, &(KeyAnim.GetCurrentFrame()));
	}
	if (app->player->Key == true) {
		app->render->DrawTexture(YellowKeyTex, app->player->position.x + 106, app->player->position.y - 67, NULL);
	}
	KeyAnim.Update();

}



void Scene::Coins()
{
	if (app->player->Money == 1) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 67, &(GetCoin1.GetCurrentFrame()));
	}
	if (app->player->Money == 2) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 67, &(GetCoin2.GetCurrentFrame()));
	}
	if (app->player->Money == 3) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 67, &(GetCoin3.GetCurrentFrame()));
	}
	if (app->player->Money ==4) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 67, &(GetCoin4.GetCurrentFrame()));
	}
	if (app->player->Money == 5) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 67, &(GetCoin5.GetCurrentFrame()));
	}
	
	if (actualScene == 1) {
		if (CoinUsed1 == false) {
			app->render->DrawTexture(CoinTex, 18, 172, &(CoinAnim.GetCurrentFrame()));
		}
		if (CoinUsed2 == false) {
			app->render->DrawTexture(CoinTex, 540, 135, &(CoinAnim.GetCurrentFrame()));
		}
		if (CoinUsed3 == false) {
			app->render->DrawTexture(CoinTex, 290, 174, &(CoinAnim.GetCurrentFrame()));
		}
		CoinAnim.Update();		
	}
	if (actualScene == 2) {
		
		if (CoinUsed4 == false) {
			app->render->DrawTexture(CoinTex, 650, 163, &(CoinAnim.GetCurrentFrame()));
		}
		if (CoinUsed5 == false) {
			app->render->DrawTexture(CoinTex, 470, 60, &(CoinAnim.GetCurrentFrame()));
		}
		CoinAnim.Update();
	}

}


void Scene::Health()
{
	if (actualScene == 1) {
		if (app->coll->matrix[Collider::Type::ITEM1][Collider::Type::PLAYER] == true) {
			app->render->DrawTexture(ItemHealth1Tex, 460, 214, NULL);
		}
		if (app->coll->matrix[Collider::Type::ITEM2][Collider::Type::PLAYER] == true) {
			app->render->DrawTexture(ItemHealth2Tex, 200, 285, NULL);
		}
		if (app->player->item1Used == true) {
			app->coll->matrix[Collider::Type::ITEM1][Collider::Type::PLAYER] = false;
		}
		if (app->player->item2Used == true) {
			app->coll->matrix[Collider::Type::ITEM2][Collider::Type::PLAYER] = false;
		}
	}
	if (actualScene == 2) {
		if (app->coll->matrix[Collider::Type::ITEM3][Collider::Type::PLAYER] == true) {
			app->render->DrawTexture(ItemHealth1Tex, 600, 90, NULL);
		}
		if (app->coll->matrix[Collider::Type::ITEM4][Collider::Type::PLAYER] == true) {
			app->render->DrawTexture(ItemHealth2Tex, 970, 105, NULL);
		}
		if (app->player->item3Used == true) {
			app->coll->matrix[Collider::Type::ITEM3][Collider::Type::PLAYER] = false;
		}
		if (app->player->item4Used == true) {
			app->coll->matrix[Collider::Type::ITEM4][Collider::Type::PLAYER] = false;
		}
	}

}



void Scene::Pathfinding(iPoint& enemy)
{
	{/*int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint mouseTile = app->map->WorldToMap(mouseX - app->render->camera.x, mouseY - app->render->camera.y);

	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	app->render->DrawTexture(pathTex, p.x, p.y);*/

	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();
	
	uint fpslim = 6;

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		if (i == 1 && app->frameCount % fpslim == 0) {
			
			
			if (conV)
			{
				enemy.x = pos.x;
				enemy.y = pos.y;
			}
			if (conT)
			{
				enemy.x = pos.x;
				//enemy.y = pos.y;
			}
			
		}
		
		if(app->coll->debug)app->render->DrawTexture(pathTex, pos.x, pos.y);
	}

	iPoint originScreen = app->map->MapToWorld(origin1.x, origin1.y);
	if (app->coll->debug)app->render->DrawTexture(originTex, originScreen.x, originScreen.y);
	}

}


void Scene::SetGameOver()
{
	app->player->death = false;
	app->player->position.y = 20000;
	app->player->position.x = 20000;
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (silence)
	{
		app->audio->PlayFx(wasted);
		silence = false;
		app->audio->PlayMusic("Assets/audio/music/Silence.ogg");
	}
	Press.Update();
	app->render->DrawTexture(GameOver, 0, 0);
	app->render->DrawTexture(Enter, 62, 100, &(Press.GetCurrentFrame()));

}

void Scene::SetWinGame() {
	app->player->position.y = 20000;
	app->player->position.x = 20000;
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	WinAnim.Update();
	if (win)
	{
		app->audio->PlayFx(winFx);
		win = false;
		app->audio->PlayMusic("Assets/audio/music/Silence.ogg");
	}
	
	app->render->DrawTexture(WinScreen, 0, 0, &(WinAnim.GetCurrentFrame()));
	
}


void Scene::StartCollidersLevel1()
{
	//Checkpoints colliders
	Check1 = app->coll->AddCollider({ 70, 260, 20,20 }, Collider::Type::CHECKPOINT1, this);
	Check2 = app->coll->AddCollider({ 233, 28, 20,20 }, Collider::Type::CHECKPOINT2, this);
	Check3 = app->coll->AddCollider({ 590, 220, 20,20 }, Collider::Type::CHECKPOINT3, this);

	//Item Collider
	Item1 = app->coll->AddCollider({ 460, 214, 14,14 }, Collider::Type::ITEM1, this);
	Item2 = app->coll->AddCollider({ 200, 287, 14,14 }, Collider::Type::ITEM2, this);
	KeyColl = app->coll->AddCollider({ 206, 140, 14,14 }, Collider::Type::KEY, this);

	//Coin Collider
	CoinColl1 = app->coll->AddCollider({ 18,171, 12,12 }, Collider::Type::COIN1, this);
	CoinColl2 = app->coll->AddCollider({ 540, 135, 12,12 }, Collider::Type::COIN2, this);
	CoinColl3 = app->coll->AddCollider({ 289, 175, 12,12 }, Collider::Type::COIN3, this);

	//Teleport
	Teleport= app->coll->AddCollider({ 40,44, 12,12 }, Collider::Type::TELEPORT, this);
}

void Scene::StartCollidersLevel2() 
{
	Check4 = app->coll->AddCollider({ 108, 140, 20,20 }, Collider::Type::CHECKPOINT4, this);
	Check5 = app->coll->AddCollider({ 640, 117, 20,20 }, Collider::Type::CHECKPOINT5, this);

	Item3= app->coll->AddCollider({ 600, 90, 12,12 }, Collider::Type::ITEM3, this);
	Item4 = app->coll->AddCollider({ 970, 105, 12,12 }, Collider::Type::ITEM4, this);

	CoinColl4 = app->coll->AddCollider({ 650, 163, 12,12 }, Collider::Type::COIN4, this);
	CoinColl5 = app->coll->AddCollider({ 470, 60, 12,12 }, Collider::Type::COIN5, this);

	WinCol = app->coll->AddCollider({ 1400, 113, 12,25 }, Collider::Type::WIN, this);
}

void Scene::Level1ToLevel2() {
	silence = true;
	app->coll->clean();
	app->map->CleanUp();
	level2 = true;
	actualScene = 2;
	app->player->position.x = 40;
	app->player->position.y = 0;
	app->SaveGameRequest();
	currentScene = SCENE2;
}

void Scene::ResetGame() {
	
		app->player->position.y = 20;
		app->player->position.x = 70;
		if (actualScene == 2)
		{
			app->coll->clean();
			app->map->CleanUp();
			level1 = true;
			startTitle = true;
		}
		app->scene->actualScene = 1;
		app->scene->ActiveTeleport1 = false;
		app->scene->ActiveTeleport2 = false;
		app->scene->ActiveTeleport3 = false;
		app->scene->ActiveTeleport4 = false;
		app->scene->AllowTeleport = false;
		app->scene->scrollerX = 0;
		app->scene->scrollerX1 = 0;
		app->scene->scrollerX2 = 0;
		app->scene->scrollerX3 = 0;
		app->scene->tps1 = 1;
		app->scene->tps2 = 1;
		app->scene->tps3 = 1;
		app->scene->tps4 = 1;
		app->scene->tps5 = 1;
		app->scene->Point1 = false;
		app->scene->Point2 = false;
		app->scene->Point3 = false;
		app->scene->Point4 = false;
		app->scene->Point5 = false;
		app->scene->CheckUsed1 = false;
		app->scene->CheckUsed2 = false;
		app->scene->CheckUsed3 = false;
		app->scene->CheckUsed4 = false;
		app->scene->CheckUsed5 = false;
		app->scene->CoinUsed1 = false;
		app->coll->matrix[Collider::Type::COIN1][Collider::Type::PLAYER] = true;
		app->scene->CoinUsed2 = false;
		app->coll->matrix[Collider::Type::COIN2][Collider::Type::PLAYER] = true;
		app->scene->CoinUsed3 = false;
		app->coll->matrix[Collider::Type::COIN3][Collider::Type::PLAYER] = true;
		app->scene->CoinUsed4 = false;
		app->coll->matrix[Collider::Type::COIN4][Collider::Type::PLAYER] = true;
		app->scene->CoinUsed5 = false;
		app->coll->matrix[Collider::Type::COIN5][Collider::Type::PLAYER] = true;
		app->scene->silence = true;

		app->player->god = false;
		app->player->ActivePlayer = false;
		app->player->CheckActive1 = false;
		app->player->CheckActive2 = false;
		app->player->CheckActive3 = false;
		app->player->CheckActive4 = false;
		app->player->CheckActive5 = false;
		app->player->item1Used = false;
		app->player->item2Used = false;
		app->player->item3Used = false;
		app->player->item4Used = false;
		app->player->Key = false;
		app->player->Money = 0;
		app->player->PlayerLives = 5;
		app->player->PlayerPosition = true;
		app->enemies->BooLive = 1;
		app->enemies->WaddleLive = 1;
		app->player->hit = false;
		app->enemies->Enemy1.x = 1100;
		app->enemies->Enemy1.y = 144;
		app->enemies->Enemy2.x = 550;
		app->enemies->Enemy2.y = 150;

		app->scene->currentScene = SCENE;

		app->SaveGameRequest();
	
}