#ifndef __MODULE_H__
#define __MODULE_H__

#include "SString.h"

#include "PugiXml/src/pugixml.hpp"

class App;

class Module
{
public:

	Module(bool startEnabled) : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	// L01: DONE 5: Sending config file to all modules
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

    // L02: DONE 2: Create new virtual methods to Load / Save state
	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&) const
	{
		return true;
	}

	//void Module::OnCollision(Collider* c1, Collider* c2) {

	//}
	// to enable and disable modules
	void Module::Enable()
	{
		if (!isEnabled)
		{
			isEnabled = true;
			Start();
		}
	}

	void Module::Disable()
	{
		if (isEnabled)
		{
			isEnabled = false;
			CleanUp();
		}
	}

	virtual void OnCollision(Collider* c1, Collider* c2)
	{}

	inline bool IsEnabled() const { return  isEnabled; }

public:

	SString name;
	bool active;

private:
	bool isEnabled = true;
};

#endif // __MODULE_H__