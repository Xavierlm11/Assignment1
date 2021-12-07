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
	

	currentScene = TITLE_SCREEN; //Game starts with Title Screen

	//Checkpoints colliders
	Check1 = app->coll->AddCollider({ 70, 260, 20,20 }, Collider::Type::CHECKPOINT1, this);
	Check2 = app->coll->AddCollider({ 233, 26, 20,20 }, Collider::Type::CHECKPOINT2, this);
	Check3 = app->coll->AddCollider({ 590, 220, 20,20 }, Collider::Type::CHECKPOINT3, this);

	//Item Collider
	Item1 = app->coll->AddCollider({ 460, 214, 14,14 }, Collider::Type::ITEM1, this);
	Item2 = app->coll->AddCollider({ 200, 287, 14,14 }, Collider::Type::ITEM2, this);
	KeyColl= app->coll->AddCollider({ 206, 140, 14,14 }, Collider::Type::KEY, this);

	//Coin Collider
	CoinColl1 = app->coll->AddCollider({ 18,171, 12,12 }, Collider::Type::COIN1, this);
	CoinColl2 = app->coll->AddCollider({ 540, 135, 12,12 }, Collider::Type::COIN2, this);
	CoinColl3 = app->coll->AddCollider({ 289, 175, 12,12 }, Collider::Type::COIN3, this);

	startTitle = true;
	silence = true;
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
		app->map->Load("level1.tmx");
		Check1 = app->coll->AddCollider({ 70, 260, 20,20 }, Collider::Type::CHECKPOINT1, this);
		Check2 = app->coll->AddCollider({ 233, 26, 20,20 }, Collider::Type::CHECKPOINT2, this);
		Check3 = app->coll->AddCollider({ 590, 220, 20,20 }, Collider::Type::CHECKPOINT3, this);

		//Item Collider
		Item1 = app->coll->AddCollider({ 460, 214, 14,14 }, Collider::Type::ITEM1, this);
		Item2 = app->coll->AddCollider({ 200, 287, 14,14 }, Collider::Type::ITEM2, this);
		KeyColl = app->coll->AddCollider({ 206, 140, 14,14 }, Collider::Type::KEY, this);

		//Coin Collider
		CoinColl1 = app->coll->AddCollider({ 18,171, 12,12 }, Collider::Type::COIN1, this);
		CoinColl2 = app->coll->AddCollider({ 540, 135, 12,12 }, Collider::Type::COIN2, this);
		CoinColl3 = app->coll->AddCollider({ 289, 175, 12,12 }, Collider::Type::COIN3, this);
		app->map->CreateColliders();

		level1 = false;
		
	}
	if (level2) {
		app->map->Load("level2.tmx");
		app->map->CreateColliders();
		level2 = false;
		
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

			app->SaveGameRequest();
			
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

		{int speed = 8;

		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
			app->LoadGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
			app->SaveGameRequest();


		}
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
		Pathfinding();
		
		if (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
			app->map->CreateColliders();
		}

		if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN) {
			app->coll->clean();
			app->map->CleanUp();
			level2 = true;
			actualScene = 2;
			currentScene = SCENE2;	
		}		

		break;
		case SCENE2:
			if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
				app->coll->clean();
				app->map->CleanUp();
				level1 = true;
				startTitle = true;
				/*app->map->CreateColliders();*/
				actualScene = 1; 
				currentScene = SCENE;
			}	
			app->map->Draw();
			
			break;
	case GAME_OVER:

		SetGameOver();

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			if (actualScene == 1) 
			{
				startTitle = true;
				currentScene = SCENE;
				app->player->PlayerLives = 5;
				/*app->render->camera.y = 0;
				app->render->camera.x = 0;*/
				//app->player->position.y = 20;
				//app->player->position.x = 50;
				app->LoadGameRequest();
			}
			if (actualScene == 2)
			{
				startTitle = true;
				currentScene = SCENE2;
				app->player->PlayerLives = 5;
				/*app->render->camera.y = 0;
				app->render->camera.x = 0;*/
				//app->player->position.y = 20;
				//app->player->position.x = 50;
				app->LoadGameRequest();
			}
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

// Load / Save
bool Scene::LoadState(pugi::xml_node& data) {
	CheckUsed1 = data.child("teleport").attribute("check1").as_bool();
	CheckUsed2 = data.child("teleport").attribute("check2").as_bool();
	CheckUsed3 = data.child("teleport").attribute("check3").as_bool();

	return true;
}
bool Scene::SaveState(pugi::xml_node& data) const {
	pugi::xml_node teleports = data.child("teleport");

	teleports.attribute("check1").set_value(CheckUsed1);
	teleports.attribute("check2").set_value(CheckUsed2);
	teleports.attribute("check3").set_value(CheckUsed3);

	return true;
}


////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Function calls
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Scene::DrawScene()
{
	app->render->DrawTexture(bgpa, scrollerX, 0, NULL);
	app->render->DrawTexture(GalaxyTex, scrollerX1, 0, NULL);
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

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		app->player->position.y = 20;
		app->player->position.x = 50;
	}

}



void Scene::Checkpoints()
{
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
		app->render->DrawTexture(NameCheckTex1, app->player->position.x - 20, app->player->position.y + 100, NULL);
		app->player->CheckActive1 = false;
	}
	if (app->player->CheckActive2 == true) {
		app->render->DrawTexture(NameCheckTex2, app->player->position.x - 20, app->player->position.y + 100, NULL);
		app->player->CheckActive2 = false;
	}
	if (app->player->CheckActive3 == true) {
		app->render->DrawTexture(NameCheckTex3, app->player->position.x - 20, app->player->position.y + 100, NULL);
		app->player->CheckActive3 = false;
	}
	CheckPoint.Update();
	CheckpointUsed.Update();

}




void Scene::Teleports()
{
	if (ActiveTeleport1 == true) { //TP 1
		if (tps1 == 1) {
			app->render->DrawTexture(Teleport2Tex, app->player->position.x - 52, app->player->position.y + 90, NULL);
		}
		if (tps1 == 2) {
			app->render->DrawTexture(Teleport3Tex, app->player->position.x - 52, app->player->position.y + 90, NULL);
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
			app->render->DrawTexture(Teleport1Tex, app->player->position.x - 52, app->player->position.y + 90, NULL);
		}
		if (tps2 == 2) {
			app->render->DrawTexture(Teleport3Tex, app->player->position.x - 52, app->player->position.y + 90, NULL);
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
			app->render->DrawTexture(Teleport1Tex, app->player->position.x - 52, app->player->position.y + 90, NULL);
		}
		if (tps3 == 2) {
			app->render->DrawTexture(Teleport2Tex, app->player->position.x - 52, app->player->position.y + 90, NULL);
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




void Scene::Keys()
{
	if (app->player->Key == false) {
		app->render->DrawTexture(KeyTex, 206, 140, &(KeyAnim.GetCurrentFrame()));
	}
	if (app->player->Key == true) {
		app->render->DrawTexture(YellowKeyTex, app->player->position.x + 106, app->player->position.y - 54, NULL);
	}
	KeyAnim.Update();

}




void Scene::Coins()
{
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

	if (app->player->Money == 1) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 54, &(GetCoin1.GetCurrentFrame()));
	}
	if (app->player->Money == 2) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 54, &(GetCoin2.GetCurrentFrame()));
	}
	if (app->player->Money == 3) {
		app->render->DrawTexture(CoinTex, app->player->position.x + 70, app->player->position.y - 54, &(GetCoin3.GetCurrentFrame()));
	}

}




void Scene::Health()
{
	if (app->coll->matrix[Collider::Type::ITEM1][Collider::Type::PLAYER] == true) {
		app->render->DrawTexture(ItemHealth1Tex, 460, 214, NULL);
	}
	if (app->coll->matrix[Collider::Type::ITEM2][Collider::Type::PLAYER] == true) {
		app->render->DrawTexture(ItemHealth2Tex, 200, 285, NULL);
	}

}




void Scene::Pathfinding()
{
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

//void Scene::()
//{
//
//
//}