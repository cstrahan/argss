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

#include "sdl_window.h"
#include "argss_sdl.h"
#include "aerror.h"
#include "sys.h"

#define max(a, b)  (((a) > (b)) ? (a) : (b))
#define min(a, b)  (((a) < (b)) ? (a) : (b))

SDL_Window::SDL_Window() {
	viewport = NULL;
	
	background = NULL;
	frame = NULL;
	windowskin = NULL;
	cursor = NULL;
	contents = NULL;
	stretch = true;
	cursor_rect.x = 0;
	cursor_rect.y = 0;
	cursor_rect.w = 0;
	cursor_rect.h = 0;
	active = true;
	visible = true;
	pause = false;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	z = 0;
	ox = 0;
	oy = 0;
	opacity = 255;
	back_opacity = 255;
	contents_opacity = 255;
	pause_frame = 0;
	pause_id = 0;
}

SDL_Window::~SDL_Window()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(cursor);
}

void SDL_Window::draw(SDL_Surface* surface) {
	if(!visible) return;
	if(x < -width || x > Sys_Res[0] || y < -height || y > Sys_Res[1]) return;
	if(width <= 0 || height <= 0) return;
	
	if(windowskin != NULL) {
		if(width > 4 && height > 4 && (back_opacity * opacity / 255 > 0)) {
			if(background_needs_refresh) {
				refresh_background();
			}
			SDL_Rect src_rect = {0, 0, background->w, background->h};
			
			if(back_opacity * opacity / 255 >= 255) {
				SDL_Rect offset = {x + 2, y + 2, 0, 0};
				
				SDL_BlitSurface(background, &src_rect, surface, &offset);
			}
			else {
				surface_blit(background, src_rect, surface, x + 2, y + 2, back_opacity * opacity / 255, true);
			}
		}
		
		if(width > 0 && height > 0 && opacity > 0) {
			if(frame_needs_refresh) {
				refresh_frame();
			}
			SDL_Rect src_rect = {0, 0, frame->w, frame->h};
			
			if(opacity >= 255) {
				SDL_Rect offset = {x, y, 0, 0};
				
				SDL_BlitSurface(frame, &src_rect, surface, &offset);
			}
			else {
				surface_blit(frame, src_rect, surface, x, y, opacity, true);
			}
		}
	}
	
	if(contents != NULL) {
		if(width > 32 && height > 32 && -ox < width - 32 && -oy < height - 32 && contents_opacity > 0) {
			SDL_Rect offset = {max(x + 16, x + 16 - ox), max(y + 16, y + 16 - oy), 0, 0};
			
			SDL_Rect src_rect = {-min(-ox, 0), -min(-oy, 0), min(width - 32, width - 32 + ox), min(height - 32, height - 32 + oy)};
			
			if(contents_opacity >= 255) {
				SDL_BlitSurface(contents, &src_rect, surface, &offset);
			}
			else {
				surface_blit(contents, src_rect, surface, offset.x, offset.y, contents_opacity, true);
			}
		}
		if(ox > 0) {
			SDL_Rect offset = {x + 4, y + height / 2 - 8, 0, 0};
			
			SDL_Rect src_rect = {128 + 16, 24, 8, 16};
			
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
		if(oy > 0) {
			SDL_Rect offset = {x + width / 2 - 8, y + 4, 0, 0};
			
			SDL_Rect src_rect = {128 + 24, 16, 16, 8};
			
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
		if(contents->w - ox > width - 32) {
			SDL_Rect offset = {x + width - 12, y + height / 2 - 8, 0, 0};
			SDL_Rect src_rect = {128 + 40, 24, 8, 16};
			
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
		if(contents->h - oy > height - 32) {
			SDL_Rect offset = {x + width / 2 - 8, y + height - 12, 0, 0};
			
			SDL_Rect src_rect = {128 + 24, 40, 16, 8};
			
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
	}
	
	if(pause) {
		int dstx = max(x + width / 2 - 8, x);
		int dsty = max(y + height - 16, y);
		int w = min(16, width);
		int h = min(16, height);
		if(pause_id == 0) {
			SDL_Rect src_rect = {160, 64, w, h};
			surface_blit(windowskin, src_rect, surface, dstx, dsty, 255 / 8 * pause_frame, true);
		}
		else if(pause_id == 1) {
			SDL_Rect src_rect = {176, 64, w, h};
			SDL_Rect offset = {dstx, dsty, 0, 0};
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
		else if(pause_id == 2) {
			SDL_Rect src_rect = {160, 80, w, h};
			SDL_Rect offset = {dstx, dsty, 0, 0};
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
		else if(pause_id == 3) {
			SDL_Rect src_rect = {176, 80, w, h};
			SDL_Rect offset = {dstx, dsty, 0, 0};
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
		else if(pause_id == 4) {
			SDL_Rect src_rect = {160, 64, w, h};
			SDL_Rect offset = {dstx, dsty, 0, 0};
			SDL_BlitSurface(windowskin, &src_rect, surface, &offset);
		}
	}
}

void SDL_Window::refresh_background() {
	if(background != NULL) SDL_FreeSurface(background);

	if(stretch) {
		SDL_Rect srcrect = {0, 0, 128, 128};
		background = surface_resample(windowskin, width - 4, height - 4, srcrect);
	}
	else {
		// TODO
	}
	
	background_needs_refresh = false;
}

void SDL_Window::refresh_frame() {
	if(frame != NULL) SDL_FreeSurface(frame);

	/*frame = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, rmask, gmask, bmask, amask);
	if(frame == NULL) {
		rb_raise(ARGSS_Error, "SDL could not create sprite surface.\n%s\n", SDL_GetError());
	}*/
	frame = surface_creatergba(width, height);

	surface_disablealpha(windowskin);
	
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	
	// Corners
	srcrect.x = 128;
	srcrect.y = 0;
	srcrect.w = 16;
	srcrect.h = 16;
	dstrect.x = 0;
	dstrect.y = 0;
	SDL_BlitSurface(windowskin, &srcrect, frame, &dstrect);
	
	srcrect.x = 192 - 16;
	dstrect.x = width - 16;
	SDL_BlitSurface(windowskin, &srcrect, frame, &dstrect);
	
	srcrect.y = 64 - 16;
	dstrect.y = height - 16;
	SDL_BlitSurface(windowskin, &srcrect, frame, &dstrect);
	
	srcrect.x = 128;
	dstrect.x = 0;
	SDL_BlitSurface(windowskin, &srcrect, frame, &dstrect);

	// Border Up
	srcrect.x = 128 + 16;
	srcrect.y = 0;
	srcrect.w = 32;
	srcrect.h = 16;
	SDL_Surface* border = surface_resample(windowskin, max(width - 32, 1), 16, srcrect);
	dstrect.x = 16;
	dstrect.y = 0;
	surface_disablealpha(border);
	SDL_BlitSurface(border, NULL, frame, &dstrect);
	SDL_FreeSurface(border);
	
	// Border Down
	srcrect.y = 64 - 16;
	border = surface_resample(windowskin, max(width - 32, 1), 16, srcrect);
	dstrect.y = height - 16;
	surface_disablealpha(border);
	SDL_BlitSurface(border, NULL, frame, &dstrect);
	SDL_FreeSurface(border);
	
	// Border Left
	srcrect.x = 128;
	srcrect.y = 16;
	srcrect.w = 16;
	srcrect.h = 32;
	border = surface_resample(windowskin, 16, max(height - 32, 1), srcrect);
	dstrect.x = 0;
	dstrect.y = 16;
	surface_disablealpha(border);
	SDL_BlitSurface(border, NULL, frame, &dstrect);
	SDL_FreeSurface(border);
	
	// Border Right
	srcrect.x = 192 - 16;
	border = surface_resample(windowskin, 16, max(height - 32, 1), srcrect);
	dstrect.x = width - 16;
	surface_disablealpha(border);
	SDL_BlitSurface(border, NULL, frame, &dstrect);
	SDL_FreeSurface(border);
	
	surface_enablealpha(windowskin);
	
	frame_needs_refresh = false;
}

void SDL_Window::update() {
	if(pause) {
		pause_frame += 1;
		if(pause_frame == 8) {
			pause_frame = 0;
			pause_id += 1;
			if(pause_id == 5) {
				pause_id = 1;
			}
		}
	}
}

unsigned long SDL_Window::get_id() {
	return id;
}
SDL_Viewport* SDL_Window::get_viewport() {
	return viewport;
}
SDL_Surface* SDL_Window::get_windowskin() {
	return windowskin;
}
SDL_Surface* SDL_Window::get_contents() {
	return contents;
}
bool SDL_Window::get_stretch() {
	return stretch;
}
SDL_Rect SDL_Window::get_cursor_rect() {
	return cursor_rect;
}
bool SDL_Window::get_active() {
	return active;
}
bool SDL_Window::get_visible() {
	return visible;
}
bool SDL_Window::get_pause() {
	return pause;
}
int SDL_Window::get_x() {
	return x;
}
int SDL_Window::get_y() {
	return y;
}
int SDL_Window::get_width() {
	return width;
}
int SDL_Window::get_height() {
	return height;
}
int SDL_Window::get_z() {
	return z;
}
int SDL_Window::get_ox() {
	return ox;
}
int SDL_Window::get_oy() {
	return oy;
}
int SDL_Window::get_opacity() {
	return opacity;
}
int SDL_Window::get_back_opacity() {
	return back_opacity;
}
int SDL_Window::get_contents_opacity() {
	return contents_opacity;
}

void SDL_Window::set_id(unsigned long nid) {
	id = nid;
}
void SDL_Window::set_viewport(SDL_Viewport* nviewport) {
	viewport = nviewport;
}
void SDL_Window::set_windowskin(SDL_Surface* nwindowskin) {
	windowskin = nwindowskin;
	background_needs_refresh = true;
	frame_needs_refresh = true;
}
void SDL_Window::set_contents(SDL_Surface* ncontents) {
	contents = ncontents;
}
void SDL_Window::set_stretch(bool nstretch) {
	stretch = nstretch;
	background_needs_refresh = true;
}
void SDL_Window::set_cursor_rect(SDL_Rect ncursor_rect) {
	cursor_rect = ncursor_rect;
}
void SDL_Window::set_active(bool nactive) {
	active = nactive;
}
void SDL_Window::set_visible(bool nvisible) {
	visible = nvisible;
}
void SDL_Window::set_pause(bool npause) {
	if(npause != pause) {
		pause_frame = 0;
		pause_id = 0;
	}
	pause = npause;
}
void SDL_Window::set_x(int nx) {
	x = nx;
}
void SDL_Window::set_y(int ny) {
	y = ny;
}
void SDL_Window::set_width(int nwidth) {
	width = nwidth;
	background_needs_refresh = true;
	frame_needs_refresh = true;
}
void SDL_Window::set_height(int nheight) {
	height = nheight;
	background_needs_refresh = true;
	frame_needs_refresh = true;
}
void SDL_Window::set_z(int nz) {
	z = nz;
}
void SDL_Window::set_ox(int nox) {
	ox = nox;
}
void SDL_Window::set_oy(int noy) {
	oy = noy;
}
void SDL_Window::set_opacity(int nopacity) {
	opacity = nopacity;
}
void SDL_Window::set_back_opacity(int nback_opacity) {
	back_opacity = nback_opacity;
}
void SDL_Window::set_contents_opacity(int ncontents_opacity) {
	contents_opacity = ncontents_opacity;
}
