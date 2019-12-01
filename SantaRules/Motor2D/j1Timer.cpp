// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "j1Timer.h"
#include "SDL\include\SDL_timer.h"

// ---------------------------------------------
j1Timer::j1Timer()
{
	Start();
}

// ---------------------------------------------
void j1Timer::Start()									//Velocity rather than precision, SDL_GetTicks() instead of SDL_GetPerformanceCounter. 
{
	started_at = SDL_GetTicks();						//Amount of ticks (in milliseconds) whenever the function is called. Used to set the start of the timer.
}

// ---------------------------------------------
uint32 j1Timer::Read() const
{
	return SDL_GetTicks() - started_at;					//Time (in milliseconds) since Start() function call.
}

// ---------------------------------------------
float j1Timer::ReadSec() const
{
	return (SDL_GetTicks() - started_at) / 1000.0f;		//Time passed from Start method call until this method's call. ms converted to seconds.
}