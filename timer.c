#include "timer.h"

void initialize_timer(struct Timer *timer)
{
	timer->start_tick = 0;
	timer->current_tick = 0;
}

void start_timer(struct Timer *timer)
{
	timer->start_tick = SDL_GetTicks();
}

void set_start_tick(struct Timer *timer, Uint32 tick_value)
{
	timer->start_tick = tick_value;
}

void set_current_tick(struct Timer *timer, Uint32 tick_value)
{
	timer->current_tick = tick_value;
}

Uint32 get_start_tick(const struct Timer *timer)
{
	return timer->start_tick;
}

Uint32 get_current_tick(const struct Timer *timer)
{
	Uint32 time = 0;
	time = SDL_GetTicks() - timer->start_tick;

	return time;
}

