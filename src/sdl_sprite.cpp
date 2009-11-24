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

#include "sdl_sprite.h"
#include "argss_sdl.h"
#include "SDL_rotozoom.h"
//#include <string.h>
#include <math.h>

#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))

SDL_Sprite::SDL_Sprite()
{
	viewport = NULL;
	
	sprite = surface_creatergba(1, 1);
	if(sprite == NULL) {
		rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
	}
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = 0;
	src_rect.h = 0;
	visible = true;
	x = 0;
	y = 0;
	z = 0;
	ox = 0;
	oy = 0;
	zoom_x = 1.0;
	zoom_y = 1.0;
	angle = 0;
	flipx = false;
	flipy = false;
	bush_depth = 0;
	opacity = 255;
	blend_type = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.unused = 0;
	tone.r = 0;
	tone.g = 0;
	tone.b = 0;
	tone.gray = 0;
}

SDL_Sprite::SDL_Sprite(SDL_Viewport* viewport)
{
	viewport = viewport;
}

SDL_Sprite::~SDL_Sprite()
{
}

void SDL_Sprite::draw(SDL_Surface* surface) {
	if(needs_refresh) {
		refresh();
	}
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(sprite, NULL, surface, &offset);
}

void SDL_Sprite::refresh() {
	needs_refresh = false;
	
	SDL_FreeSurface(sprite);
	
	SDL_Rect rect;
	
	if(src_rect.w == 0 && src_rect.h == 0) {
		sprite = surface_creatergba(bitmap->w, bitmap->h);
		if(sprite == NULL) {
			rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
		}
		surface_disablealpha(bitmap);
		SDL_BlitSurface(bitmap, NULL, sprite, NULL);
	}
	else {
		sprite = surface_creatergba(src_rect.w, src_rect.h);
		if(sprite == NULL) {
			rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
		}
		surface_disablealpha(bitmap);
		SDL_BlitSurface(bitmap, &src_rect, sprite, NULL);
	}
	surface_enablealpha(bitmap);
		
	if(tone.r != 0 || tone.b != 0 || tone.g != 0 || tone.gray != 0) {
		apply_tone();
	}
	if(opacity < 255 || bush_depth > 0) {
		apply_opacity();
	}
	
	/*bool flip = flipx || flipy;
	bool zoom = zoom_x != 1.0 || zoom_y != 1.0;
	bool rotation = angle != 0;
	
	if(flip || zoom || rotation) {
		
		SDL_Surface* temp;
		
		if(rotation) {
			if(zoom || flip) {
				temp = rotozoomSurfaceXY(sprite, angle, zoom_x * (flipx ? -1 : 1), zoom_y * (flipy ? -1 : 1), 0);
			}
			else {
				temp = rotozoomSurface(sprite, angle, 1, 0);
			}
		}
		else if(zoom || flip) {
			temp = zoomSurface(sprite, zoom_x * (flipx ? -1 : 1), zoom_y * (flipy ? -1 : 1), 0);
		}
	
		SDL_FreeSurface(sprite);
		
		sprite = temp;
	}*/
	
	if(flipx || flipy) {
		apply_flip();
	}
	if(zoom_x != 1.0 || zoom_y != 1.0) {
		apply_zoom();
	}
	if(angle != 0) {
		apply_angle();
	}
}

void SDL_Sprite::apply_tone() {
	SDL_LockSurface(sprite);

	Uint8 *pixels = (Uint8 *)sprite->pixels;
	
	if(tone.gray == 0) {
		for (int yy = 0; yy < sprite->h; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				Uint8 *pixel = pixels;
				pixel[0] = max(min(pixel[0] + tone.r, 255), 0);
				pixel[1] = max(min(pixel[1] + tone.g, 255), 0);
				pixel[2] = max(min(pixel[2] + tone.b, 255), 0);
				pixels += 4;
			}
		}
	}
	else {
		double factor = (255 - tone.gray) / 255.0;
		double gray;
		for (int yy = 0; yy < sprite->h; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				Uint8 *pixel = pixels;
				
				gray = pixel[0] * 0.299 + pixel[1] * 0.587 + pixel[2] * 0.114;
				pixel[0] = (Uint8)max(min((pixel[0] - gray) * factor + gray + tone.r + 0.5, 255), 0);
				pixel[1] = (Uint8)max(min((pixel[1] - gray) * factor + gray + tone.g + 0.5, 255), 0);
				pixel[2] = (Uint8)max(min((pixel[2] - gray) * factor + gray + tone.b + 0.5, 255), 0);
				pixels += 4;
			}
		}
	}
	SDL_UnlockSurface(sprite);
}
void SDL_Sprite::apply_opacity() {
	SDL_LockSurface(sprite);
	
	Uint8 *pixels = (Uint8 *)sprite->pixels;
	
	int start_bush = max(sprite->h - bush_depth, 0);
	
	if (opacity < 255) {
		for (int yy = 0; yy < start_bush; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				Uint8 *pixel = pixels;
				pixel[3] = pixel[3] * opacity / 255;
				pixels += 4;
			}
		}
		for (int yy = start_bush; yy < sprite->h; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				Uint8 *pixel = pixels;
				pixel[3] = (pixel[3] / 2) * opacity / 255;
				pixels += 4;
			}
		}
	}
	else {
		pixels += start_bush * sprite->w * 4;
		for (int yy = start_bush; yy < sprite->h; yy++) {
			for (int xx = 0; xx < sprite->w; xx++) {
				Uint8 *pixel = pixels;
				pixel[3] = pixel[3] / 2;
				pixels += 4;
			}
		}
	}
	SDL_UnlockSurface(sprite);
}
void SDL_Sprite::apply_flip() {
	SDL_LockSurface(sprite);
	
	SDL_Surface* temp = surface_creatergba(sprite->w, sprite->h);
	
	SDL_LockSurface(temp);
	
	Uint32* srcpixels = (Uint32*)sprite->pixels;
	Uint32* dstpixels = (Uint32*)temp->pixels;
	
	if(flipx && flipy) {
		long srcpixel = 0;
		long dstpixel = sprite->w + (sprite->h - 1) * sprite->w - 1;
		for(int yy = 0; yy < sprite->h; yy++) {
			for(int xx = 0; xx < sprite->w; xx++) {
				dstpixels[dstpixel] = srcpixels[srcpixel];
				
				srcpixel += 1;
				dstpixel -= 1;
			}
		}
	}
	else if(flipx) {
		long srcpixel = 0;
		long dstpixel = sprite->w - 1;
		for(int yy = 0; yy < sprite->h; yy++) {
			for(int xx = 0; xx < sprite->w; xx++) {
				dstpixels[dstpixel] = srcpixels[srcpixel];
				
				srcpixel += 1;
				dstpixel -= 1;
			}
			dstpixel += sprite->w * 2;
		}
	}
	else if(flipy) {
		dstpixels += (sprite->h - 1) * sprite->w;
		for(int yy = 0; yy < sprite->h; yy++) {
			memcpy(dstpixels, srcpixels,  sprite->w * 4);
			srcpixels += sprite->w;
			dstpixels -= sprite->w;
		}
	}
	
	SDL_UnlockSurface(sprite);
	SDL_UnlockSurface(temp);
	
	SDL_BlitSurface(temp, NULL, sprite, NULL);
}
void SDL_Sprite::apply_zoom() {
	SDL_LockSurface(sprite);
	
	int scalew = (int)(sprite->w * zoom_x);
	int scaleh = (int)(sprite->h * zoom_y);
	
	SDL_Surface* nsprite = surface_creatergba(scalew, scaleh);
	
	SDL_LockSurface(nsprite);
	
	Uint8* srcpixels = (Uint8*)sprite->pixels;
	Uint8* dstpixels = (Uint8*)nsprite->pixels;

	int row = sprite->w * 4;

	for(int yy = 0; yy < nsprite->h; yy++) {
		int nearest_matchy = (int)(yy / zoom_y) * row;
		for(int xx = 0; xx < nsprite->w; xx++) {
			int nearest_match = nearest_matchy + (int)(xx / zoom_x) * 4;
			dstpixels[0] = srcpixels[nearest_match];
			dstpixels[1] = srcpixels[nearest_match + 1];
			dstpixels[2] = srcpixels[nearest_match + 2];
			dstpixels[3] = srcpixels[nearest_match + 3];
			dstpixels += 4;
		}
	}
	
	SDL_UnlockSurface(nsprite);
	SDL_FreeSurface(sprite);
	
	sprite = nsprite;
}
void SDL_Sprite::apply_angle() {
	/*SDL_LockSurface(sprite);
	
	float radians = (2 * 3.14159265 * angle) / 360; 

	float cosine = (float)cos(radians); 
	float sine = (float)sin(radians); 

	float p1x = -sprite->h * sine;
	float p1y = sprite->h * cosine;
	float p2x = sprite->w * cosine - sprite->h * sine;
	float p2y = sprite->h * cosine + sprite->w * sine;
	float p3x = sprite->w * cosine;
	float p3y = sprite->w * sine;

	float minx = min(0, min(p1x, min(p2x, p3x))); 
	float miny = min(0, min(p1y, min(p2y, p3y))); 
	float maxx = max(p1x, max(p2x, p3x)); 
	float maxy = max(p1y, max(p2y, p3y)); 

	int DestBitmapWidth=(int)ceil(fabs(maxx)-minx); 
	int DestBitmapHeight=(int)ceil(fabs(maxy)-miny);
	
	SDL_Surface* nsprite = surface_creatergba(scalew, scaleh);
	
	SDL_LockSurface(nsprite);
	
	Uint8* srcpixels = (Uint8*)sprite->pixels;
	Uint8* dstpixels = (Uint8*)nsprite->pixels;

	int row = sprite->w * 4;

	for(int yy = 0; yy < nsprite->h; yy++) {
		int nearest_matchy = (int)(yy / zoom_y) * row;
		for(int xx = 0; xx < nsprite->w; xx++) {
			int nearest_match = nearest_matchy + (int)(xx / zoom_x) * 4;
			dstpixels[0] = srcpixels[nearest_match];
			dstpixels[1] = srcpixels[nearest_match + 1];
			dstpixels[2] = srcpixels[nearest_match + 2];
			dstpixels[3] = srcpixels[nearest_match + 3];
			dstpixels += 4;
		}
	}
	
	SDL_UnlockSurface(nsprite);
	SDL_FreeSurface(sprite);
	
	sprite = nsprite;*/
}

int SDL_Sprite::get_width() {
	if(src_rect.w == 0) {
		return bitmap->w;
	}
	else {
		return src_rect.w;
	}
}
int SDL_Sprite::get_height() {
	if(src_rect.h == 0) {
		return bitmap->h;
	}
	else {
		return src_rect.h;
	}
}

void SDL_Sprite::update() {
	
}
void SDL_Sprite::flash(SDL_Color color, int duration){
	
}

unsigned long SDL_Sprite::get_id() {
	return id;
}
void SDL_Sprite::set_id(unsigned long nid) {
	id = nid;
}
SDL_Viewport* SDL_Sprite::get_viewport() {
	return viewport;
}
void SDL_Sprite::set_viewport(SDL_Viewport* nviewport) {
	viewport = nviewport;
}
SDL_Surface* SDL_Sprite::get_sprite() {
	return sprite;
}
SDL_Surface* SDL_Sprite::get_bitmap() {
	return bitmap;
}
void SDL_Sprite::set_bitmap(SDL_Surface* nbitmap) {
	bitmap = nbitmap;
	needs_refresh = true;
}
SDL_Rect SDL_Sprite::get_src_rect() {
	return src_rect;
}
void SDL_Sprite::set_src_rect(SDL_Rect nsrc_rect) {
	src_rect = nsrc_rect;
	needs_refresh = true;
}
bool SDL_Sprite::get_visible() {
	return visible;
}
void SDL_Sprite::set_visible(bool nvisible) {
	visible = nvisible;
}
int SDL_Sprite::get_x() {
	return x;
}
void SDL_Sprite::set_x(int nx) {
	x = nx;
}
int SDL_Sprite::get_y() {
	return y;
}
void SDL_Sprite::set_y(int ny) {
	y = ny;
}
int SDL_Sprite::get_z() {
	return z;
}
void SDL_Sprite::set_z(int nz) {
	z = nz;
}
int SDL_Sprite::get_ox() {
	return ox;
}
void SDL_Sprite::set_ox(int nox) {
	ox = nox;
	needs_refresh = true;
}
int SDL_Sprite::get_oy() {
	return oy;
}
void SDL_Sprite::set_oy(int noy) {
	oy = noy;
	needs_refresh = true;
}
float SDL_Sprite::get_zoom_x() {
	return zoom_x;
}
void SDL_Sprite::set_zoom_x(float nzoom_x) {
	zoom_x = nzoom_x;
	needs_refresh = true;
}
float SDL_Sprite::get_zoom_y() {
	return zoom_y;
}
void SDL_Sprite::set_zoom_y(float nzoom_y) {
	zoom_y = nzoom_y;
	needs_refresh = true;
}
float SDL_Sprite::get_angle() {
	return angle;
}
void SDL_Sprite::set_angle(float nangle) {
	angle = nangle;
	needs_refresh = true;
}
bool SDL_Sprite::get_flipx() {
	return flipx;
}
void SDL_Sprite::set_flipx(bool nflipx) {
	flipx = nflipx;
	needs_refresh = true;
}
bool SDL_Sprite::get_flipy() {
	return flipy;
}
void SDL_Sprite::set_flipy(bool nflipy) {
	flipy = nflipy;
	needs_refresh = true;
}
int SDL_Sprite::get_bush_depth() {
	return bush_depth;
}
void SDL_Sprite::set_bush_depth(int nbush_depth) {
	bush_depth = nbush_depth;
	needs_refresh = true;
}
int SDL_Sprite::get_opacity() {
	return opacity;
}
void SDL_Sprite::set_opacity(int nopacity) {
	opacity = nopacity;
}
int SDL_Sprite::get_blend_type() {
	return blend_type;
}
void SDL_Sprite::set_blend_type(int nblend_type) {
	blend_type = nblend_type;
}
SDL_Color SDL_Sprite::get_color() {
	return color;
}
void SDL_Sprite::set_color(SDL_Color ncolor) {
	color = ncolor;
}
SDL_Tone SDL_Sprite::get_tone() {
	return tone;
}
void SDL_Sprite::set_tone(SDL_Tone ntone) {
	tone = ntone;
	needs_refresh = true;
}
