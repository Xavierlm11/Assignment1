#ifndef __MODULEENEMIES_H__
#define __MODULEENEMIES_H__

#include "Module.h"
#include "Animation.h"
#include "List.h"
#include "App.h"
#include "Point.h"

struct SDL_Texture;
struct SDL_Surface;
struct Collider;

class ModuleEnemies :public Module {
public:
	ModuleEnemies();
};
#endif