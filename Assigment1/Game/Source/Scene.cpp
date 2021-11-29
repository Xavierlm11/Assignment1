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

Scene::Scene( ) : Module()
{
	name.Create("scene");
	//death scene animation
	Press.PushBack({ 0,0,115,55 });
	Press.PushBack({ 0,0,0,0 });
	Press.loop = true;
	Press.speed = 0.01f;

	//Press Enter Anim
	EnterStart.PushBack({ 0,0,0,0 });
	EnterStart.PushBack({0,0,85,26});
	EnterStart.PushBack({0,0,0,0});
	EnterStart.PushBack({ 0,0,85,26 });
	EnterStart.loop = true;
	EnterStart.speed = 0.01f;


	//intro animation
	intro.PushBack({ 0,0,240,168 });
	intro.PushBack({ 240,168,240,168 });
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

	app->map->Load("level1.tmx");
	
	app->map->CreateColliders();
	
	//Textures
	bgpa = app->tex->Load("Assets/textures/BackgroundParallax.png");
	bgpa1 = app->tex->Load("Assets/textures/BackgroundParallax.png");
	bgTexture = app->tex->Load("Assets/textures/IntroMenu.png");
	GameOver = app->tex->Load("Assets/textures/Wasted.png");//Game over
	EnterStartTex = app->tex->Load("Assets/textures/PressEnter.png");
	Enter = app->tex->Load("Assets/textures/LoseEnter.png");
	GalaxyTex= app->tex->Load("Assets/textures/GalaxyTex.png");

	//Fx
	wasted=app->audio->LoadFx("Assets/audio/fx/Wasted.wav");

	currentScene = TITLE_SCREEN; //Game starts with Title Screen

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
			app->player->position.y = 20;
			

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
		//SCROLLER
		/*scrollerX -= 0.2069;
		scrollerX1 -= 0.2069;

		if (scrollerX < -1550) {
			scrollerX = 1600;
		}
		if (scrollerX1 < -1550) {
			scrollerX1 = 1600;
		}*/
	
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
		break;

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
			app->render->camera.y = 0;
			app->render->camera.x = 0;
			app->player->position.y = 20;
			app->player->position.x = 50;
			
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
