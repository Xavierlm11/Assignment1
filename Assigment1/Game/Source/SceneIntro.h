#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
class SceneIntro : public Module {
	public:
		SceneIntro(bool startEnabled);

		~SceneIntro();

		bool Start() override;

		//updates the scene's background animations
		bool Update(float dt) override;

		//forms the render call of all the parts of the scene's backgroud
		bool PostUpdate() override;

		bool CleanUp();

public:

	//sprite loaded into an SDL_Texture
	SDL_Texture* bgTexture;
	SDL_Texture* PressEnterTex;
	//The intro animation 
	Animation intro;
};

#endif