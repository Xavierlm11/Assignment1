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
	
	/*app->map->CreateColliders();*/
	
	//Textures
	bgpa = app->tex->Load("Assets/textures/BackgroundParallax.png");
	bgpa1 = app->tex->Load("Assets/textures/BackgroundParallax.png");
	bgTexture = app->tex->Load("Assets/textures/IntroMenu.png");
	GameOver = app->tex->Load("Assets/textures/Wasted.png");//Game over
	EnterStartTex = app->tex->Load("Assets/textures/PressEnter.png");
	Enter = app->tex->Load("Assets/textures/LoseEnter.png");
	GalaxyTex= app->tex->Load("Assets/textures/GalaxyTex.png");
	CheckpointTex = app->tex->Load("Assets/textures/checkpointTex.png");
	NameCheckTex1 = app->tex->Load("Assets/textures/Checkpoint1Tex.png");
	NameCheckTex2 = app->tex->Load("Assets/textures/Checkpoint2Tex.png");
	NameCheckTex3 = app->tex->Load("Assets/textures/Checkpoint3Tex.png");

	//Fx
	wasted=app->audio->LoadFx("Assets/audio/fx/Wasted.wav");

	currentScene = TITLE_SCREEN; //Game starts with Title Screen

	//collider
	Check1 = app->coll->AddCollider({ 70, 260, 20,20 }, Collider::Type::CHECKPOINT1, this);
	Check2 = app->coll->AddCollider({ 233, 26, 20,20 }, Collider::Type::CHECKPOINT2, this);
	Check3 = app->coll->AddCollider({ 590, 218, 20,20 }, Collider::Type::CHECKPOINT3, this);

	startTitle = true;
	silence = true;
	level1 = true;
	level2 = false;
	app->render->camera.x = 0;
	app->render->camera.y = 0;


	if (app->map->Load("level1.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	pathTex = app->tex->Load("Assets/maps/path2.png");
	originTex = app->tex->Load("Assets/maps/x.png");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
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
	}

	if (level1) {
		level1 = false;
		app->map->Load("level1.tmx");
	}
	if (level2) {
		level2 = false;
		app->map->Load("level2.tmx");
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
			startTitle = true;

			app->render->camera.y = 0;
			app->render->camera.x = 0;

			app->player->position.x = 50;
			app->player->position.y = 15;
			

			currentScene = SCENE;
			
		}

		app->render->DrawTexture(bgTexture, 0, 0, &(intro.GetCurrentFrame()));
		app->render->DrawTexture(EnterStartTex,80, 140, &(EnterStart.GetCurrentFrame()));
		
		break;
	case SCENE:
	
		if (startTitle)
		{
			startTitle = false;
			app->audio->PlayMusic("Assets/audio/music/BackgroundMusic.ogg");
		}

		if (app->scene->currentScene == SCENE)
		{
			app->map->CreateColliders();
		}

	
		app->render->DrawTexture(bgpa, scrollerX, 0, NULL);
		app->render->DrawTexture(GalaxyTex, scrollerX1, 0, NULL);

		//app->render->DrawTexture(bgpa1, scrollerX1, 0, NULL);

		{int speed = 8; 
		
		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
			app->LoadGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
			app->SaveGameRequest();


		
		//CAMERA MOVEMENT
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && app->render->camera.y < 0)
			app->render->camera.y += speed;

		if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) && app->render->camera.y > -1160)
			app->render->camera.y -= speed;

		if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && app->render->camera.x < 0)
			app->render->camera.x += speed;

		if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && app->render->camera.x > -2200)
			app->render->camera.x -= speed;
         }
		
		// Draw map
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
			currentScene =GAME_OVER;
		}
			
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
			app->player->position.y = 20;
			app->player->position.x = 50;
		}

		//Checkpoints
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
			app->render->DrawTexture(CheckpointTex, 590, 214, &(CheckPoint.GetCurrentFrame()));
		}
		if (Point3 == true) {
			app->render->DrawTexture(CheckpointTex, 590, 214, &(CheckpointUsed.GetCurrentFrame()));
		}

		if (app->player->CheckActive1 == true) {
			app->render->DrawTexture(NameCheckTex1, app->player->position.x - 20, app->player->position.y + 95, NULL);
			app->player->CheckActive1 = false;
		}
		if (app->player->CheckActive2 == true) {
			app->render->DrawTexture(NameCheckTex2, app->player->position.x - 20, app->player->position.y + 95, NULL);
			app->player->CheckActive2 = false;
		}
		if (app->player->CheckActive3 == true) {
			app->render->DrawTexture(NameCheckTex3, app->player->position.x - 20, app->player->position.y + 95, NULL);
			app->player->CheckActive3 = false;
		}
		CheckPoint.Update();
		CheckpointUsed.Update();


		// L12b: Debug pathfinding
		{int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);
		iPoint mouseTile = app->map->WorldToMap(mouseX - app->render->camera.x, mouseY - app->render->camera.y);

		app->input->GetMousePosition(mouseX, mouseY);
		iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
		p = app->map->WorldToMap(p.x, p.y);
		p = app->map->MapToWorld(p.x, p.y);

		app->render->DrawTexture(pathTex, p.x, p.y);

		const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			app->render->DrawTexture(pathTex, pos.x, pos.y);
		}

		iPoint originScreen = app->map->MapToWorld(origin1.x, origin1.y);
		app->render->DrawTexture(originTex, originScreen.x, originScreen.y);
		}

		//if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN) {
		//	app->coll->CleanUp();
		//	app->map->CleanUp();
		//	currentScene = SCENE2;
		//	level2 = true;
		//}		

		break;
		//case SCENE2:
		//	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		//		app->coll->CleanUp();
		//		app->map->CleanUp();
		//		currentScene = SCENE;
		//		level1 = true;	

		//	}	
		//	app->map->Draw();
		//	app->map->CreateColliders();
		//	break;
	case GAME_OVER:

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

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			startTitle = true;
			currentScene = SCENE;
			/*app->render->camera.y = 0;
			app->render->camera.x = 0;*/
			//app->player->position.y = 20;
			//app->player->position.x = 50;
			app->LoadGameRequest();
		}

		break;
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
