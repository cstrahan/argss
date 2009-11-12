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
void surface_getpixelcolor(SDL_Surface *surface, int x, int y, SDL_Color* color);
void surface_putpixelcolor(SDL_Surface *surface, int x, int y, SDL_Color* color);
void surface_enablealpha(SDL_Surface *surface);
void surface_disablealpha(SDL_Surface *surface);

#endif
