#ifndef _ARGSS_COLORH_
#define _ARGSS_COLORH_

#include "SDL.h"

Uint32 argss_color_getuint32(unsigned long self, SDL_PixelFormat* format);
SDL_Color argss_color_getsdl(unsigned long self);
unsigned long argss_color_new(unsigned long r, unsigned long g, unsigned long b, unsigned long a);
unsigned long argss_color_new2(float r, float g, float b, float a);
unsigned long argss_color_new3(Uint32 color, SDL_PixelFormat* format);
unsigned long argss_color_new4(SDL_Color color);

void Init_Color();

#endif
