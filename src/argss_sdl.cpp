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

#include "argss_sdl.h"
#include "sys.h"

void Init_SDL() {
    if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_JOYSTICK | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)) { 
        fprintf(stderr, "SDL could not initialize SDL.\n%s\n", SDL_GetError());
        exit(-1);
    }
	
	atexit(SDL_Quit);

    screen = SDL_SetVideoMode(Sys_Res[0], Sys_Res[1], Sys_Res[2], SDL_HWSURFACE);
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

SDL_Color surface_getpixelcolor(SDL_Surface *surface, int x, int y)
{
	SDL_Color color;
	SDL_GetRGBA(surface_getpixel(surface, x, y), surface->format, &color.r, &color.g, &color.b, &color.unused);
	return color;
}

void surface_putpixelcolor(SDL_Surface *surface, int x, int y, SDL_Color color)
{
	surface_putpixel(surface, x, y, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.unused));
}

void surface_enablealpha(SDL_Surface *surface) {
	SDL_SetAlpha(surface, SDL_SRCALPHA, surface->format->alpha);
}
void surface_disablealpha(SDL_Surface *surface) {
	SDL_SetAlpha(surface, 0, surface->format->alpha);
}
void surface_blit(SDL_Surface *src, SDL_Rect src_rect, SDL_Surface *dst, int dstx, int dsty, int opacity, bool alphablend) {
	if ((src->w == 0) || (src->h == 0) || (dst->w == 0) || (dst->h == 0))
        return;
	
	SDL_Rect rect = src_rect;
    if (rect.w == 0 || rect.h == 0)
    {
        rect.x = 0;
        rect.y = 0;
        rect.w = src->w;
        rect.h = src->h;
    }
    else
    {
        if (rect.x < 0) rect.x = 0;
        if (rect.y < 0) rect.y  = 0;
        if (rect.w > src->w) rect.w = src->w;
        if (rect.h > src->h) rect.h = src->h;
    }
		
	if(dstx + rect.w > dst->w) rect.w = dst->w - dstx;
    if(dsty + rect.h > dst->h) rect.h = dst->h - dsty;

    if(rect.w <= 0 || rect.h <= 0) return;
	
	SDL_LockSurface(src);
	SDL_LockSurface(dst);
	
    int          Pitch     = rect.w * 4;
    int          SrcStride = src->w * 4;
    int          DstStride = dst->w * 4;
    const Uint8* SrcPixels = ((Uint8*)src->pixels) + (rect.x + rect.y * src->w) * 4;
    Uint8*       DstPixels = ((Uint8*)dst->pixels) + (dstx + dsty * dst->w) * 4;

	if(alphablend) {
        if (opacity > 255) opacity = 255;
        if (opacity > 0) {
            for (int i = 0; i < rect.h; ++i) {
                for (int j = 0; j < rect.w; ++j) {
                    const Uint8* Src   = SrcPixels + j * 4;
                    Uint8*       Dst   = DstPixels + j * 4;

                    Uint8 SrcA = Src[3] * opacity / 255;
                    Dst[0] = (Dst[0] * (255 - SrcA) + Src[0] * SrcA) / 255;
                    Dst[1] = (Dst[1] * (255 - SrcA) + Src[1] * SrcA) / 255;
                    Dst[2] = (Dst[2] * (255 - SrcA) + Src[2] * SrcA) / 255;
                    Dst[3] = Dst[3] * (255 - SrcA) / 255 + SrcA;
                }
                SrcPixels += SrcStride;
                DstPixels += DstStride;
            }
        }
    }
    else {
        for (int i = 0; i < rect.h; ++i) {
            memcpy(DstPixels, SrcPixels, Pitch);
            SrcPixels += SrcStride;
            DstPixels += DstStride;
        }
    }
	
	SDL_UnlockSurface(src);
	SDL_UnlockSurface(dst);
}

SDL_Surface* surface_creatergb(int w, int h) {
	SDL_Surface* temp;
	SDL_Surface* formated;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, w, h, 32, rmask, gmask, bmask, amask);
	formated = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	return formated;
}

SDL_Surface* surface_creatergba(int w, int h) {
	SDL_Surface* temp;
	SDL_Surface* formated;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, w, h, 32, rmask, gmask, bmask, amask);
	formated = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);
	return formated;
}
