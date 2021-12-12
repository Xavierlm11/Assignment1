#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;
#define MAX_LISTENERS 1000
struct Collider
{
	enum Type
	{
		NONE = -1,
		PLAYER,
		PLAYERRIGHT,
		PLAYERLEFT,
		PLAYERHEAD,
		SUELO,
		PARED,
		LAVA,
		AIR,
		CHECKPOINT1,
		CHECKPOINT2,
		CHECKPOINT3,
		CHECKPOINT4,
		CHECKPOINT5,
		TELEPORT,
		ITEM1,
		ITEM2,
		ITEM3,
		ITEM4,
		KEY,
		COIN1,
		COIN2,
		COIN3,
		COIN4,
		COIN5,
		VOLADOR,
		TIERRA,
		WIN,
		PLAYERATTACK,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

