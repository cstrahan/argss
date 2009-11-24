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

#ifndef __sdl_sprite__
#define __sdl_sprite__

#include "SDL.h"
#include "sdl_viewport.h"
#include "sdl_tone.h"

class SDL_Sprite {

public:
	SDL_Sprite();
	SDL_Sprite(SDL_Viewport* viewport);
	~SDL_Sprite();
	
	void draw(SDL_Surface* surface);
	int get_width();
	int get_height();
	
	void update();
	void flash(SDL_Color color, int duration);
	
	unsigned long get_id();
	void set_id(unsigned long nid);
	SDL_Viewport* get_viewport();
	void set_viewport(SDL_Viewport* nviewport);
	SDL_Surface* get_sprite();
	SDL_Surface* get_bitmap();
	void set_bitmap(SDL_Surface* nbitmap);
	SDL_Rect get_src_rect();
	void set_src_rect(SDL_Rect nsrc_rect);
	bool get_visible();
	void set_visible(bool nvisible);
	int get_x();
	void set_x(int nx);
	int get_y();
	void set_y(int ny);
	int get_z();
	void set_z(int nz);
	int get_ox();
	void set_ox(int nox);
	int get_oy();
	void set_oy(int noy);
	float get_zoom_x();
	void set_zoom_x(float nzoom_x);
	float get_zoom_y();
	void set_zoom_y(float nzoom_y);
	float get_angle();
	void set_angle(float nangle);
	bool get_flipx();
	void set_flipx(bool nflipx);
	bool get_flipy();
	void set_flipy(bool nflipy);
	int get_bush_depth();
	void set_bush_depth(int nbush_depth);
	int get_opacity();
	void set_opacity(int nopacity);
	int get_blend_type();
	void set_blend_type(int nblend_type);
	SDL_Color get_color();
	void set_color(SDL_Color ncolor);
	SDL_Tone get_tone();
	void set_tone(SDL_Tone ntone);
	
private:
	unsigned long id;
	SDL_Viewport* viewport;
	SDL_Surface* sprite;
	SDL_Surface* bitmap;
	SDL_Rect src_rect;
	bool visible;
	int x;
	int y;
	int z;
	int ox;
	int oy;
	double zoom_x;
	double zoom_y;
	double angle;
	bool flipx;
	bool flipy;
	int bush_depth;
	int opacity;
	int blend_type;
	SDL_Color color;
	SDL_Tone tone;
	
	SDL_Color flash_color;
	int flash_duration;
	int flash_frame;
	
	void refresh();
	void apply_tone();
	void apply_opacity();
	void apply_flip();
	void apply_zoom();
	void apply_angle();
	bool needs_refresh;
};
#endif // __sdl_sprite__
