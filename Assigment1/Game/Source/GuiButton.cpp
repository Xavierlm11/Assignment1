#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "GuiControl.h"
#include "GuiManager.h"
#include "ModuleFonts.h"
#include "Scene.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w )) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h )))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{
    ListItem<GuiControl*>* control = app->guiManager->controls.start;
	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED: 
	{
		render->DrawRectangle(bounds, 0, 0, 0, 0);
	} break;

	case GuiControlState::NORMAL:
	{
		//render->DrawRectangle(bounds, 255, 0, 0, 255);

	} break;

	//L14: TODO 4: Draw the button according the GuiControl State
	case GuiControlState::FOCUSED:
	{
		if (app->scene->hitbox)
		{
			render->DrawRectangle(bounds, 255, 255, 255, 160);
		}
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if (app->scene->currentScene == CONFIG) {
			if ((mouseX > 160) && (mouseX < (167)) &&
				(mouseY > 47) && (mouseY < (54)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 159, 46, NULL);
			}
			if ((mouseX > 132) && (mouseX < (139)) &&
				(mouseY > 47) && (mouseY < (54)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 131, 46, NULL);
			}
			if ((mouseX > 160) && (mouseX < (167)) &&
				(mouseY > 60) && (mouseY < (67)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 159, 59, NULL);
			}
			if ((mouseX > 132) && (mouseX < (139)) &&
				(mouseY > 60) && (mouseY < (67)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 131, 59, NULL);
			}
			if ((mouseX > 146) && (mouseX < (153)) &&
				(mouseY > 73) && (mouseY < (80)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 145, 72, NULL);
			}
			if ((mouseX > 146) && (mouseX < (153)) &&
				(mouseY > 91) && (mouseY < (98)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 145, 90, NULL);
			}
			if ((mouseX > 132) && (mouseX < (139)) &&
				(mouseY > 106) && (mouseY < (113)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 131, 106, NULL);
			}
			if ((mouseX > 160) && (mouseX < (167)) &&
				(mouseY > 106) && (mouseY < (113)))
			{
				app->render->DrawTexture(app->scene->BtnSelected, 159, 106, NULL);
			}
		}
		if (app->scene->currentScene == MENU) {
			if ((mouseX > 40) && (mouseX < (105)) &&
				(mouseY > 91) && (mouseY < (122)))
			{
				app->render->DrawTexture(app->scene->BtnBigRedTex, 40, 90, NULL);
			}
		
			if ((mouseX > 122) && (mouseX < (195)) &&
				(mouseY > 91) && (mouseY < (122)))
			{
				app->render->DrawTexture(app->scene->BtnBigRedTex, 121, 90, NULL);
			}
		
			if ((mouseX > 40) && (mouseX < (105)) &&
				(mouseY > 128) && (mouseY < (149)))
			{
				app->render->DrawTexture(app->scene->BtnSmallRedTex, 40, 128, NULL);
			}
	
			if ((mouseX > 122) && (mouseX < (180)) &&
				(mouseY > 128) && (mouseY < (149)))
			{
				app->render->DrawTexture(app->scene->BtnSmallRedTex, 122, 128, NULL);
			}
		}
		if (app->scene->pause == true) {
			if ((mouseX > 73) && (mouseX < (168)) &&
				(mouseY > 89) && (mouseY < (99)))
			{
				app->render->DrawTexture(app->scene->BtnPause1, 72, 88, NULL);
			}
			if ((mouseX > 73) && (mouseX < (168)) &&
				(mouseY > 68) && (mouseY < (78)))
			{
				app->render->DrawTexture(app->scene->BtnPause1, 72, 67, NULL);
			}
			if ((mouseX > 73) && (mouseX < (168)) &&
				(mouseY > 47) && (mouseY < (57)))
			{
				app->render->DrawTexture(app->scene->BtnPause1, 72, 46, NULL);
			}
			if ((mouseX > 89) && (mouseX < (151)) &&
				(mouseY > 107) && (mouseY < (117)))
			{
				app->render->DrawTexture(app->scene->BtnPause2, 88, 106, NULL);
			}
		}

		app->audio->PlayFx(app->scene->ClickFx);

	} break;
	case GuiControlState::PRESSED:
	{
		if (app->scene->hitbox)
		{
			render->DrawRectangle(bounds, 20, 20, 255, 255);
		}
		app->audio->PlayFx(app->scene->SelectedFx);
			
	} break;

	/******/

	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;

	default:
		break;
	}

	return false;
}

void GuiButton::setpos( int x, int y)
{
	if (this != nullptr) {
		bounds.x = x;
		bounds.y = y;
	}
}