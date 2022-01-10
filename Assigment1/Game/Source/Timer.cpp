// ----------------------------------------------------
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"

// L07: DONE 1: Fill Start(), Read(), ReadSec() methods
// they are simple, one line each!
	
Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	//...
	started_at = SDL_GetTicks();
	running = true;
}

void Timer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
}


uint32 Timer::Read() const
{
	//return SDL_GetTicks() - started_at;

	if (running == true)
	{
		return SDL_GetTicks() - started_at;
	}
	else
	{
		return stopped_at - started_at;
	}
}

float Timer::ReadSec() const
{
	return (float)(SDL_GetTicks() - started_at) / 1000.0f;
}