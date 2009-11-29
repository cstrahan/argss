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

#ifndef __sdl_window__
#define __sdl_window__

#include "SDL.h"
#include "sdl_viewport.h"

class SDL_Window {

public:
	SDL_Window();
	SDL_Window(SDL_Viewport* viewport);
	~SDL_Window();

	void draw(SDL_Surface *screen);

	void update();

	unsigned long get_id();
	void set_id(unsigned long nid);
	SDL_Viewport* get_viewport();
	SDL_Surface* get_windowskin();
	SDL_Surface* get_contents();
	bool get_stretch();
	SDL_Rect get_cursor_rect();
	bool get_active();
	bool get_visible();
	bool get_pause();
	int get_x();
	int get_y();
	int get_width();
	int get_height();
	int get_z();
	int get_ox();
	int get_oy();
	int get_opacity();
	int get_back_opacity();
	int get_contents_opacity();

	void set_viewport(SDL_Viewport* nviewport);
	void set_windowskin(SDL_Surface* nwindowskin);
	void set_contents(SDL_Surface* ncontents);
	void set_stretch(bool nstretch);
	void set_cursor_rect(SDL_Rect ncursor_rect);
	void set_active(bool nactive);
	void set_visible(bool nvisible);
	void set_pause(bool npause);
	void set_x(int nx);
	void set_y(int ny);
	void set_width(int nwidth);
	void set_height(int nheihgt);
	void set_z(int nz);
	void set_ox(int nox);
	void set_oy(int noy);
	void set_opacity(int nopacity);
	void set_back_opacity(int nback_opacity);
	void set_contents_opacity(int ncontents_opacity);

private:
	unsigned long id;
	SDL_Viewport* viewport;
	SDL_Surface* background;
	SDL_Surface* frame;
	SDL_Surface* cursor;
	SDL_Surface* windowskin;
	SDL_Surface* contents;
	bool stretch;
	SDL_Rect cursor_rect;
	bool active;
	bool visible;
	bool pause;
	int x;
	int y;
	int width;
	int height;
	int z;
	int ox;
	int oy;
	int opacity;
	int back_opacity;
	int contents_opacity;
	
	void refresh_background();
	void refresh_frame();
	void update_cursor();
	bool background_needs_refresh;
	bool frame_needs_refresh;
	int pause_frame;
	int pause_id;
};
#endif // __sdl_window__
