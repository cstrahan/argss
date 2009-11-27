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

SDL_Window::SDL_Window() {
	viewport = NULL;
	
	background = NULL;
	frame = NULL;
	windowskin = NULL;
	cursor = NULL;
	arrows[0] = NULL;
	arrows[1] = NULL;
	arrows[2] = NULL;
	arrows[3] = NULL;
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
	pause_y = 0;
}

SDL_Window::~SDL_Window()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(cursor);
}

void SDL_Window::draw(SDL_Surface* surface) {
	if(windowskin != NULL) {
		if(background_needs_refresh) {
			refresh_background();
		}
		if(frame_needs_refresh) {
			refresh_frame();
		}
		
		SDL_Rect offset;

		offset.x = x;
		offset.y = y;
		SDL_BlitSurface(background, NULL, surface, &offset);
	
		SDL_BlitSurface(frame, NULL, surface, &offset);
	}
	
	if(contents != NULL) {
		SDL_Rect offset;

		offset.x = x + 16;
		offset.y = y + 16;
		
		SDL_BlitSurface(contents, NULL, surface, &offset);
	}
}

void SDL_Window::refresh_background() {
	if(background != NULL) SDL_FreeSurface(background);

	if(stretch) {
		SDL_Rect srcrect = {0, 0, 128, 128};
		background = surface_resample(windowskin, width, height, srcrect);
	}
	else {
		// TODO
	}
}

void SDL_Window::refresh_frame() {
}

void SDL_Window::update() {
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
