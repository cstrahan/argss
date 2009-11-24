#ifndef _HSLRGB_H_
#define _HSLRGB_H_

#include "SDL.h"

SDL_Color RGBAdjustHSL(SDL_Color col, int h, float s, float l);

#endif
