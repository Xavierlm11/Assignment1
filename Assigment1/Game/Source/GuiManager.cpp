#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Scene.h"
#include "GuiButton.h"
#include "Audio.h"

GuiManager::GuiManager() :Module()
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{
	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text, SDL_Rect bounds, Module* observer, SDL_Rect sliderBounds)
{
	// L14: TODO1: Create a GUI control and add it to the list of controls

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text);
		break;
	
	// More Gui Controls can go here

	default:
		break;
	}

	//Set the observer

	control->SetObserver(observer);
	//control->SetTexture(texture);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.add(control);

	return control;
}

bool GuiManager::Update(float dt)
{	
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt,doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	
	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}

	}
	return true; 

}

bool GuiManager::Draw() {

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		switch (app->scene->currentScene)
		{
		case MENU:
			if(control->data->id <=5) control->data->Draw(app->render);

			break;

		case CONFIG:
			if (control->data->id >= 6&& control->data->id <= 14) control->data->Draw(app->render);
			break;

		case SCENE:
			if (app->scene->pause == true) {
				if (control->data->id >= 20 && control->data->id <= 30) control->data->Draw(app->render);
			}
			break;

		case SCENE2:

			break;

		}

		//control->data->Draw(app->render);
		control = control->next;
	}

	return true;

}

bool GuiManager::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;

	return false;
}



