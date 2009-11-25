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
	
	if(TTF_Init() == -1) {
		fprintf(stderr, "SDL could not initialize TTF library.\n%s\n", TTF_GetError());
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
	if(src->w == 0 || src->h == 0 || dst->w == 0 || dst->h == 0) return;
	if(dstx >= dst->w || dsty >= dst->h) return;
	
	sdl_rect_adjust(&src_rect, src);
	
	if(src_rect.w > dst->w - dstx) src_rect.w = dst->w - dstx;
	if(src_rect.h > dst->h - dsty) src_rect.h = dst->h - dsty;
	
	if(src_rect.w <= 0 || src_rect.h <= 0) return;
	
	SDL_LockSurface(src);
	SDL_LockSurface(dst);
	
    int src_stride = src->w * 4;
    int dst_stride = dst->w * 4;
    const Uint8* src_pixels = ((Uint8*)src->pixels) + (src_rect.x + src_rect.y * src->w) * 4;
    Uint8* dst_pixels = ((Uint8*)dst->pixels) + (dstx + dsty * dst->w) * 4;

	if(alphablend) {
        if (opacity > 255) opacity = 255;
        if (opacity > 0) {
            for (int i = 0; i < src_rect.h; ++i) {
                for (int j = 0; j < src_rect.w; ++j) {
                    const Uint8* Src   = src_pixels + j * 4;
                    Uint8*       Dst   = dst_pixels + j * 4;

                    Uint8 SrcA = Src[3] * opacity / 255;
                    Dst[0] = (Dst[0] * (255 - SrcA) + Src[0] * SrcA) / 255;
                    Dst[1] = (Dst[1] * (255 - SrcA) + Src[1] * SrcA) / 255;
                    Dst[2] = (Dst[2] * (255 - SrcA) + Src[2] * SrcA) / 255;
                    Dst[3] = Dst[3] * (255 - SrcA) / 255 + SrcA;
                }
                src_pixels += src_stride;
                dst_pixels += dst_stride;
            }
        }
    }
    else {
		int pitch = src_rect.w * 4;
        for (int i = 0; i < src_rect.h; ++i) {
            memcpy(dst_pixels, src_pixels, pitch);
            src_pixels += src_stride;
            dst_pixels += dst_stride;
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

SDL_Surface* surface_resample(SDL_Surface* surface, int new_w, int new_h, SDL_Rect src_rect) {
	SDL_LockSurface(surface);
	
	SDL_Surface* nsurface = surface_creatergba(new_w, new_h);
	
	SDL_LockSurface(nsurface);
	
	Uint8* srcpixels = (Uint8*)surface->pixels;
	Uint8* dstpixels = (Uint8*)nsurface->pixels;

	sdl_rect_adjust(&src_rect, surface);
	if(src_rect.w <= 0 || src_rect.h <= 0) return nsurface;
	
    int row = surface->w * 4;
	
	double scaleWidth =  (double)new_w / (double)src_rect.w;
    double scaleHeight = (double)new_h / (double)src_rect.h;
	
	for(int yy = 0; yy < new_h; yy++) {
		int nearest_matchy = (src_rect.y + (int)(yy / scaleHeight)) * row;
		for(int xx = 0; xx < new_w; xx++) {
			int nearest_match = nearest_matchy + ((int)(xx / scaleWidth) + src_rect.x) * 4;
			dstpixels[0] = srcpixels[nearest_match];
			dstpixels[1] = srcpixels[nearest_match + 1];
			dstpixels[2] = srcpixels[nearest_match + 2];
			dstpixels[3] = srcpixels[nearest_match + 3];
			dstpixels += 4;
		}
	}
	
	SDL_UnlockSurface(surface);
	SDL_UnlockSurface(nsurface);
	
	return nsurface;
}

void sdl_rect_adjust(SDL_Rect* rect, SDL_Surface* surface) {
	if(rect->w == 0 || rect->h == 0) {
        rect->x = 0;
        rect->y = 0;
        rect->w = surface->w;
        rect->h = surface->h;
    }
    else {
        if(rect->x < 0) rect->x = 0;
        if(rect->y < 0) rect->y = 0;
        if(rect->w > surface->w - rect->x) rect->w = surface->w - rect->x;
        if(rect->h > surface->h - rect->y) rect->h = surface->h - rect->y;
    }
}