#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include"ModuleFadeToBlack.h"
#include "Defs.h"
#include "Log.h"

Scene::Scene(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");

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

	//Paral = app->tex->Load("Assets/textures/Fondo.png");
	bgpa = app->tex->Load("Assets/textures/backgroundParallax.png");
	bgpa1 = app->tex->Load("Assets/textures/backgroundParallax.png");
	// Load music
	if (app->player->ActivePlayer == true) {
		app->audio->PlayMusic("Assets/audio/music/BackgroundMusic.ogg");
	}
	

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

	int speed = 8;
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) && app->render->camera.y < 0)
		app->render->camera.y += speed;

	if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) && app->render->camera.y > -1160)
		app->render->camera.y -= speed;

	if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && app->render->camera.x < 0)
		app->render->camera.x += speed;

	if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && app->render->camera.x > -2200)
		app->render->camera.x -= speed;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	
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
