#ifndef _ARGSS_TONEH_
#define _ARGSS_TONEH_

#include "sdl_tone.h"

SDL_Tone argss_tone_getsdl(unsigned long self);
unsigned long argss_tone_new(unsigned long r, unsigned long gn, unsigned long b, unsigned long gy);
unsigned long argss_tone_new2(float r, float gn, float b, float gy);

void Init_Tone();

#endif
