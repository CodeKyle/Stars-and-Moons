#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

struct Timer
{
	Uint32 start_tick;
	Uint32 current_tick;
};

void initialize_timer(struct Timer *timer);
void start_timer(struct Timer *timer);

void update_current_tick(struct Timer *timer);

void set_start_tick(struct Timer *timer, Uint32 tick_value);
void set_current_tick(struct Timer *timer, Uint32 tick_value);

Uint32 get_start_tick(const struct Timer *timer);
Uint32 get_current_tick(const struct Timer *timer);


#endif