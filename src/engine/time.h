#ifndef _TIME_H_
#define _TIME_H_

#include "types.h"

extern u16_t Current_Tsecond;
extern u16_t Current_Second;

extern void Time_Tick();
extern void Time_FrameDelay(unsigned short mseconds, u16_t id);
extern bool Time_FrameReady(u16_t id);

#endif