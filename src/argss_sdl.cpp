#include "argss_sdl.h"
#include "sys.h"

void Init_SDL() {
    if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_JOYSTICK | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)) { 
        fprintf(stderr, "SDL could not initialize SDL.\n%s\n", SDL_GetError());
        exit(-1);
    }
	
	atexit(SDL_Quit);

    screen = SDL_SetVideoMode(Sys_Res[0], Sys_Res[1], Sys_Res[2], SDL_SWSURFACE);
    if (screen == NULL ) {
        fprintf(stderr, "SDL could not set %dx%dx%d video mode.\n%s\n", 
			Sys_Res[0], Sys_Res[1], Sys_Res[2], SDL_GetError());
        exit(-1);
    }
	
	SDL_WM_SetCaption(Sys_Title.c_str(), NULL);
}

Uint32 surface_getpixel(SDL_Surface *surface, int x, int y )
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[ ( y * surface->w ) + x ];
}

void surface_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[(y * surface->w) + x ] = pixel;
}

/*Uint32 surface_getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch (bpp) {
    case 1:
        return *p;
    case 2:
        return *(Uint16 *)p;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
        return *(Uint32 *)p;
    default:
        return 0;
    }
}

void surface_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch (bpp) {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
   default:
        break;
    }
}*/

void surface_getpixelcolor(SDL_Surface *surface, int x, int y, SDL_Color* color)
{
	SDL_GetRGBA(surface_getpixel(surface, x, y), surface->format, &color->r, &color->g, &color->b, &color->unused);
}

void surface_putpixelcolor(SDL_Surface *surface, int x, int y, SDL_Color* color)
{
	surface_putpixel(surface, x, y, SDL_MapRGBA(surface->format, color->r, color->g, color->b, color->unused));
}

void surface_enablealpha(SDL_Surface *surface) {
	SDL_SetAlpha(surface, SDL_SRCALPHA, surface->format->alpha);
}
void surface_disablealpha(SDL_Surface *surface) {
	SDL_SetAlpha(surface, 0, surface->format->alpha);
}
