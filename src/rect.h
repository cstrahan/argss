#ifndef _ARGSS_RECTH_
#define _ARGSS_RECTH_

#include "SDL.h"

SDL_Rect argss_rect_getsdl(unsigned long rect);
unsigned long argss_rect_new(unsigned long x, unsigned long y, unsigned long w, unsigned long h);
unsigned long argss_rect_new2(int x, int y, int w, int h);

void Init_Rect();

#endif
