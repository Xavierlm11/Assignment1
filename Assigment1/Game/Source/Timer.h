#ifndef __TIMER_H__
#define __TIMER_H__

#include "Defs.h"
#include "SDL\include\SDL.h"
class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Stop();
	uint32 Read() const;
	float ReadSec() const;
	bool	running;
private:
	uint32 startTime;
	
	uint32	started_at;
	uint32	stopped_at;
};

#endif //__TIMER_H__