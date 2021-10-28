#include "ModuleFadeToBlack.h"

#include "Render.h"
#include "App.h"
#include "window.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL_render.h"

ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
	{
	//int s = app->win->GetScale();
		screenRect = {0,0,1200  ,840};
	}
ModuleFadeToBlack::~ModuleFadeToBlack()
{

}
bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool ModuleFadeToBlack::Update(float dt)
{
	bool ret = true;
	if (currentStep == Fade_Step::NONE) 
	{ 
		return ret;
	}

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			moduleToDisable->Disable();
			moduleToEnable->Enable();

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		--frameCount;
		if(frameCount<=0)
		{
			currentStep = Fade_Step::NONE;
		}
	}
	return ret;
}

bool ModuleFadeToBlack::PostUpdate()
{
	bool ret = true;
	if(currentStep == Fade_Step::NONE)
	{
		return ret;
	}
	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screenRect);

	return ret;
}

bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;
		ret = true;
	}
	return ret;
}