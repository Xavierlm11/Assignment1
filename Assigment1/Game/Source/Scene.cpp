#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "SceneIntro.h"
#include "Map.h"
#include "Player.h"
#include"ModuleFadeToBlack.h"
#include "Defs.h"
#include "Log.h"
#include "ModuleCollisions.h"

Scene::Scene( ) : Module()
{
	name.Create("scene");
	//death scene animation
	Press.PushBack({ 0,0,115,55 });
	Press.PushBack({ 0,0,1,1 });
	Press.loop = true;
	Press.speed = 0.01f;

	//intro animation
	intro.PushBack({ 0,0,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.PushBack({ 240,168,240,168 });
	intro.PushBack({ 0,168,240,168 });
	intro.loop = false;
	intro.speed = 0.01f;

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

	// L03: DONE: Load map
	//app->map->Load("hello.tmx");
	app->map->Load("level1.tmx");
	if(currentScene==SCENE)
		app->map->CreateColliders();
	

	//Paral = app->tex->Load("Assets/textures/Fondo.png");
	bgpa = app->tex->Load("Assets/textures/backgroundParallax.png");
	bgpa1 = app->tex->Load("Assets/textures/backgroundParallax.png");
	// Load music
	/*if (app->player->ActivePlayer == true) {
		app->audio->PlayMusic("Assets/audio/music/BackgroundMusic.ogg");
	}*/
	bgTexture = app->tex->Load("Assets/textures/IntroMenu.png");
	GameOver = app->tex->Load("Assets/textures/Wasted.png");
	Enter = app->tex->Load("Assets/textures/LoseEnter.png");

	currentScene = SCENE;
	startTitle = true;
	silence = true;
	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	switch (currentScene)
	{
	case TITLE_SCREEN:

		intro.Update();
		if (silence)
		{
			silence = false;
			app->audio->PlayMusic("Assets/audio/music/silence.ogg");
		}
		//if (startTitle)
		//{
		//	startTitle = false;
		//	/*app->audio->PlayMusic("pinball/audio/music/TitleScreen.ogg", 0.0f);*/
		//}

		if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
			startTitle = true;

			app->render->camera.y = 0;
			app->render->camera.x = 0;

			app->player->position.y = 0;
			app->player->position.x = 0;

			currentScene = SCENE;
			/*app->audio->PlayMusic("pinball/audio/music/silence.ogg");*/
			//app->fade->FadeToBlack((Module*)app->intro, (Module*)app->scene, 90);
		}

		app->render->DrawTexture(bgTexture, 0, 0, &(intro.GetCurrentFrame()));

		break;
	case SCENE:
		if (startTitle)
		{
			startTitle = false;
			app->audio->PlayMusic("Assets/audio/music/BackgroundMusic.ogg");
		}


		/*if (app->input->GetKey(SDL_SCANCODE_O) == KEY_REPEAT) {
			app->coll->DebugDraw();
		}*/

		scrollerX -= 0.2069;
		scrollerX1 -= 0.2069;
		if (scrollerX < -1550) {
			scrollerX = 1600;
		}
		if (scrollerX1 < -1550) {
			scrollerX1 = 1600;
		}
		//app->render->DrawTexture(Paral, 0, 0);
		app->render->DrawTexture(bgpa, scrollerX, 0, NULL);

		app->render->DrawTexture(bgpa1, scrollerX1, 0, NULL);

		{int speed = 8; 
		// L02: DONE 3: Request Load / Save when pressing L/S
		if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
			app->LoadGameRequest();

		if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
			app->SaveGameRequest();

		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && app->render->camera.y < 0)
			app->render->camera.y += speed;

		if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) && app->render->camera.y > -1160)
			app->render->camera.y -= speed;

		if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && app->render->camera.x < 0)
			app->render->camera.x += speed;

		if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && app->render->camera.x > -2200)
			app->render->camera.x -= speed;
         }
		//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

		// Draw map
		app->map->Draw();

		if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
			silence = true;
			currentScene = TITLE_SCREEN;

			app->render->camera.x = 0;
			app->render->camera.y = 0;
		
			/*app->audio->PlayMusic("pinball/audio/music/silence.ogg");*/
		/*	app->fade->FadeToBlack((Module*)app->scene, (Module*)app->intro, 90);*/
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
			currentScene =GAME_OVER;

			/*app->audio->PlayMusic("pinball/audio/music/silence.ogg");*/
		/*	app->fade->FadeToBlack((Module*)app->scene, (Module*)app->intro, 90);*/
		}
		break;

	case GAME_OVER:
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->audio->PlayMusic("Assets/audio/music/silence.ogg");
		Press.Update();
		app->render->DrawTexture(GameOver, 0, 0);
		app->render->DrawTexture(Enter, 62, 100, &(Press.GetCurrentFrame()));

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			currentScene = SCENE;
			app->render->camera.y = 0;
			app->render->camera.x = 0;

			app->player->position.y = 0;
			app->player->position.x = 0;
			
		}

		break;
		

	}
	// L03: DONE 7: Set the window title with map/tileset info
		/*SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
			app->map->mapData.width, app->map->mapData.height,
			app->map->mapData.tileWidth, app->map->mapData.tileHeight,
			app->map->mapData.tilesets.count());

		app->win->SetTitle(title.GetString());*/

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
