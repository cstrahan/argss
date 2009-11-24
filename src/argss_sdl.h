// Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _SDL_H_
#define _SDL_H_

#include <map>
#include "argss.h"
#include "SDL.h"
#include "sdl_sprite.h"
#include "sdl_viewport.h"
#include "sdl_plane.h"
#include "sdl_window.h"
#include "sdl_tilemap.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	#define rmask 0xff000000
	#define gmask 0x00ff0000
	#define bmask 0x0000ff00
	#define amask 0x000000ff
#else
	#define rmask 0x000000ff
	#define gmask 0x0000ff00
	#define bmask 0x00ff0000
	#define amask 0xff000000
#endif

extern SDL_Surface* screen;

extern std::map<VALUE, SDL_Surface*> ARGSS_mapBitmaps;
extern std::map<VALUE, SDL_Sprite> ARGSS_mapSprites;
extern std::map<VALUE, SDL_Viewport> ARGSS_mapViewports;
extern std::map<VALUE, SDL_Plane> ARGSS_mapPlanes;
extern std::map<VALUE, SDL_Window> ARGSS_mapWindows;
extern std::map<VALUE, SDL_Tilemap> ARGSS_mapTilemaps;
extern Uint32 ARGSS_Graphics_BackColor;

void Init_SDL();

Uint32 surface_getpixel(SDL_Surface *surface, int x, int y);
void surface_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Color surface_getpixelcolor(SDL_Surface *surface, int x, int y);
void surface_putpixelcolor(SDL_Surface *surface, int x, int y, SDL_Color color);
void surface_enablealpha(SDL_Surface *surface);
void surface_disablealpha(SDL_Surface *surface);

void surface_blit(SDL_Surface *src, SDL_Rect src_rect, SDL_Surface *dst, int dstx, int dsty, int opacity, bool alphablend);

SDL_Surface* surface_creatergb(int w, int h);
SDL_Surface* surface_creatergba(int w, int h);

#endif
