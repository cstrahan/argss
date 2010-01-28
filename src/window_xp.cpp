//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
///         All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///     * Redistributions of source code must retain the above copyright
///       notice, this list of conditions and the following disclaimer.
///     * Redistributions in binary form must reproduce the above copyright
///       notice, this list of conditions and the following disclaimer in the
///       documentation and/or other materials provided with the distribution.
///
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
/// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
/// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
/// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
/// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
/// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <math.h>
#include "window_xp.h"
#include "argss_ruby.h"
#include "argss_window.h"
#include "graphics.h"
#include "system.h"
#include "rect.h"

////////////////////////////////////////////////////////////
/// Static Variables
////////////////////////////////////////////////////////////
std::map<unsigned long, Window*> Window::windows;

////////////////////////////////////////////////////////////
/// Defines
////////////////////////////////////////////////////////////
#define max(a, b)	(((a) > (b)) ? (a) : (b))
#define min(a, b)	(((a) < (b)) ? (a) : (b))

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Window::Window(VALUE iid) {
	id = iid;
	viewport = rb_iv_get(id, "@viewport");
	windowskin = Qnil;
	contents = Qnil;
	stretch = true;
	cursor_rect = rb_iv_get(id, "@cursor_rect");
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
	background = NULL;
	frame = NULL;
	cursor = NULL;
	last_cursor_rect = Rect(cursor_rect);
	cursor_frame = 0;
	pause_frame = 0;
	pause_id = 0;

	Graphics::RegisterZObj(0, ARGSS::AWindow::id, id);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Window::~Window() {
	delete background;
	delete frame;
	delete cursor;
}

////////////////////////////////////////////////////////////
/// Class Is Window Disposed?
////////////////////////////////////////////////////////////
bool Window::IsDisposed(VALUE id) {
	return windows.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Window
////////////////////////////////////////////////////////////
void Window::New(VALUE id) {
	windows[id] = new Window(id);
}

////////////////////////////////////////////////////////////
/// Class Get Window
////////////////////////////////////////////////////////////
Window* Window::Get(VALUE id) {
	return windows[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Window
////////////////////////////////////////////////////////////
void Window::Dispose(unsigned long id) {
	delete windows[id];
	std::map<unsigned long, Window*>::iterator it = windows.find(id);
	windows.erase(it);
	Graphics::RemoveZObj(id);
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Window::Draw() {
	if (!visible) return;
	if (width <= 0 || height <= 0) return;
	if (x < -width || x > System::Width || y < -height || y > System::Height) return;
	
	if (windowskin != Qnil) {
		if (width > 4 && height > 4 && (back_opacity * opacity / 255 > 0)) {
			if (background_needs_refresh) RefreshBackground();

			background->BlitScreen(x + 2, y + 2, back_opacity * opacity / 255);
		}
		if (width > 0 && height > 0 && opacity > 0) {
			if (frame_needs_refresh) RefreshFrame();

			frame->BlitScreen(x, y, opacity);
		}

		if (width > 32 && height > 32) {
			RefreshCursor();

			if (last_cursor_rect.width > 0 && last_cursor_rect.height > 0) {
				int cursor_opacity = 255;
				if (cursor_frame <= 16) {
					cursor_opacity -= (int)((128.0f / 16.0f) * cursor_frame);
				}
				else {
					cursor_opacity -= (int)((128.0f / 16.0f) * (32 - cursor_frame));
				}
				Rect rect(cursor_rect);
				Rect src_rect(-min(rect.x + 16, 0), -min(rect.y + 16, 0), min(rect.width, width - 16 - rect.x), min(rect.height, height - 16 - rect.y));
				cursor->BlitScreen(x + 16 + rect.x, y + 16 + rect.y, src_rect, cursor_opacity);
			}
		}
	}

	if (contents != Qnil) {
		if (width > 32 && height > 32 && -ox < width - 32 && -oy < height - 32 && contents_opacity > 0) {
			Rect src_rect(-min(-ox, 0), -min(-oy, 0), min(width - 32, width - 32 + ox), min(height - 32, height - 32 + oy));
			Bitmap::Get(contents)->BlitScreen(max(x + 16, x + 16 - ox), max(y + 16, y + 16 - oy), src_rect, contents_opacity);
		}
		if (ox > 0) {
			Rect src_rect(128 + 16, 24, 8, 16);
			Bitmap::Get(windowskin)->BlitScreen(x + 4, y + height / 2 - 8, src_rect);
		}
		if (oy > 0) {
			Rect src_rect(128 + 24, 16, 16, 8);
			Bitmap::Get(windowskin)->BlitScreen(x + width / 2 - 8, y + 4, src_rect);
		}
		if (Bitmap::Get(contents)->GetWidth() - ox > width - 32) {
			Rect src_rect(128 + 40, 24, 8, 16);
			Bitmap::Get(windowskin)->BlitScreen(x + width - 12, y + height / 2 - 8, src_rect);
		}
		if (Bitmap::Get(contents)->GetHeight() - oy > height - 32) {
			Rect src_rect(128 + 24, 40, 16, 8);
			Bitmap::Get(windowskin)->BlitScreen(x + width / 2 - 8, y + height - 12, src_rect);
		}
	}
	
	if (pause) {
		int dstx = max(x + width / 2 - 8, x);
		int dsty = max(y + height - 16, y);
		int w = min(16, width);
		int h = min(16, height);
		if (pause_id == 0) {
			Rect src_rect(160, 64, w, h);
			Bitmap::Get(windowskin)->BlitScreen(dstx, dsty, src_rect, 255 / 8 * pause_frame);
		}
		else {
			Rect src_rect;
			if (pause_id == 1) src_rect.Set(176, 64, w, h);
			else if (pause_id == 2) src_rect.Set(160, 80, w, h);
			else if (pause_id == 3) src_rect.Set(176, 80, w, h);
			else if (pause_id == 4) src_rect.Set(160, 64, w, h);
			Bitmap::Get(windowskin)->BlitScreen(dstx, dsty, src_rect);
		}
	}
}

////////////////////////////////////////////////////////////
/// Refresh Background
////////////////////////////////////////////////////////////
void Window::RefreshBackground() {
	background_needs_refresh = false;

	delete background;

	if (stretch) {
		Rect src_rect(0, 0, 128, 128);
		Rect dst_rect(0, 0, width - 4, height - 4);
		background = new Bitmap(width - 4, height - 4);
		background->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
	}
	else {
		background = new Bitmap(width - 4, height - 4);
		int tilesx = (int)(ceil(background->GetWidth() / 128.0));
		int tilesy = (int)(ceil(background->GetHeight() / 128.0));
		Rect src_rect(0, 0, 128, 128);
		for (int i = 0; i < tilesx; i++) {
			for (int j = 0; j < tilesy; j++) {
				background->Blit(i * 128, j * 128, Bitmap::Get(windowskin), src_rect, 255);
			}
		}
	}
}

////////////////////////////////////////////////////////////
/// Refresh Frame
////////////////////////////////////////////////////////////
void Window::RefreshFrame() {
	frame_needs_refresh = false;

	delete frame;

	frame = new Bitmap(width, height);

	Rect src_rect;
	
	// Draw Corners
	src_rect.x = 128;
	src_rect.y = 0;
	src_rect.width = 16;
	src_rect.height = 16;
	frame->Blit(0, 0, Bitmap::Get(windowskin), src_rect, 255);
	
	src_rect.x = 192 - 16;
	frame->Blit(width - 16, 0, Bitmap::Get(windowskin), src_rect, 255);
	
	src_rect.y = 64 - 16;
	frame->Blit(width - 16, height - 16, Bitmap::Get(windowskin), src_rect, 255);
	
	src_rect.x = 128;
	frame->Blit(0, height - 16, Bitmap::Get(windowskin), src_rect, 255);


	Rect dst_rect;

	// Border Up
	src_rect.x = 128 + 16;
	src_rect.y = 0;
	src_rect.width = 32;
	src_rect.height = 16;
	dst_rect.x = 16;
	dst_rect.y = 0;
	dst_rect.width = max(width - 32, 1);
	dst_rect.height = 16;
	frame->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
	
	// Border Down
	src_rect.y = 64 - 16;
	dst_rect.y = height - 16;
	frame->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
	
	// Border Left
	src_rect.x = 128;
	src_rect.y = 16;
	src_rect.width = 16;
	src_rect.height = 32;
	dst_rect.x = 0;
	dst_rect.y = 16;
	dst_rect.width = 16;
	dst_rect.height = max(height - 32, 1);
	frame->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
	
	// Border Right
	src_rect.x = 192 - 16;
	dst_rect.x = width - 16;
	frame->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
}

////////////////////////////////////////////////////////////
/// Refresh Cursor
////////////////////////////////////////////////////////////
void Window::RefreshCursor() {
	Rect rect(cursor_rect);

	if (rect.width != last_cursor_rect.width || rect.height != last_cursor_rect.height) {
		last_cursor_rect = rect;
		cursor_needs_refresh = true;
	}

	if (cursor_needs_refresh) {
		cursor_needs_refresh = false;
	}
	else {
		return;
	}

	if (rect.width > 0 && rect.height > 0) {
		delete cursor;

		cursor = new Bitmap(rect.width, rect.height);

		Rect src_rect(130, 66, 28, 28);
		Rect dst_rect(2, 2, rect.width - 4, rect.height - 4);
		cursor->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);

		src_rect.x = 128;
		src_rect.y = 64;
		src_rect.width = 2;
		src_rect.height = 2;
		cursor->Blit(0, 0, Bitmap::Get(windowskin), src_rect, 255);

		src_rect.x = 158;
		cursor->Blit(rect.width - 2, 0, Bitmap::Get(windowskin), src_rect, 255);

		src_rect.y = 94;
		cursor->Blit(rect.width - 2, rect.height - 2, Bitmap::Get(windowskin), src_rect, 255);

		src_rect.x = 128;
		cursor->Blit(0, rect.height - 2, Bitmap::Get(windowskin), src_rect, 255);

		// Border Up
		src_rect.x = 130;
		src_rect.y = 64;
		src_rect.width = 28;
		src_rect.height = 2;
		dst_rect.x = 2;
		dst_rect.y = 0;
		dst_rect.width = max(rect.width - 4, 1);
		dst_rect.height = 2;
		cursor->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);

		// Border Down
		src_rect.y = 94;
		dst_rect.y = rect.height - 2;
		cursor->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);

		// Border Left
		src_rect.x = 128;
		src_rect.y = 66;
		src_rect.width = 2;
		src_rect.height = 28;
		dst_rect.x = 0;
		dst_rect.y = 2;
		dst_rect.width = 2;
		dst_rect.height = max(rect.height - 4, 1);
		cursor->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
		
		// Border Right
		src_rect.x = 158;
		dst_rect.x = rect.width - 2;
		cursor->StretchBlit(dst_rect, Bitmap::Get(windowskin), src_rect, 255);
	}
}

////////////////////////////////////////////////////////////
/// Update
////////////////////////////////////////////////////////////
void Window::Update() {
	if (active) {
		cursor_frame += 1;
		if (cursor_frame == 32) {
			cursor_frame = 0;
		}
		if (pause) {
			pause_frame += 1;
			if (pause_frame == 8) {
				pause_frame = 0;
				pause_id += 1;
				if (pause_id == 5) {
					pause_id = 1;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Window::GetViewport() {
	return viewport;
}
void Window::SetViewport(VALUE nviewport) {
	viewport = nviewport;
}
VALUE Window::GetWindowskin() {
	return windowskin;
}
void Window::SetWindowskin(VALUE nwindowskin) {
	if (windowskin != nwindowskin) {
		background_needs_refresh = true;
		frame_needs_refresh = true;
		cursor_needs_refresh = true;
	}
	windowskin = nwindowskin;
}
VALUE Window::GetContents() {
	return contents;
}
void Window::SetContents(VALUE ncontents) {
	contents = ncontents;
}
bool Window::GetStretch() {
	return stretch;
}
void Window::SetStretch(bool nstretch) {
	if (stretch != nstretch) background_needs_refresh = true;
	stretch = nstretch;
}
VALUE Window::GetCursorRect() {
	return cursor_rect;
}
void Window::SetCursorRect(VALUE ncursor_rect) {
	cursor_rect = ncursor_rect;
}
bool Window::GetActive() {
	return active;
}
void Window::SetActive(bool nactive) {
	active = nactive;
}
bool Window::GetVisible() {
	return visible;
}
void Window::SetVisible(bool nvisible) {
	visible = nvisible;
}
bool Window::GetPause() {
	return pause;
}
void Window::SetPause(bool npause) {
	pause = npause;
}
int Window::GetX() {
	return x;
}
void Window::SetX(int nx) {
	x = nx;
}
int Window::GetY() {
	return y;
}
void Window::SetY(int ny) {
	y = ny;
}
int Window::GetWidth() {
	return width;
}
void Window::SetWidth(int nwidth) {
	if (width != nwidth) {
		background_needs_refresh = true;
		frame_needs_refresh = true;
	}
	width = nwidth;
}
int Window::GetHeight() {
	return height;
}
void Window::SetHeight(int nheight) {
	if (height != nheight) {
		background_needs_refresh = true;
		frame_needs_refresh = true;
	}
	height = nheight;
}
int Window::GetZ() {
	return z;
}
void Window::SetZ(int nz) {
	if (z != nz) Graphics::UpdateZObj(id, nz);
	z = nz;
}
int Window::GetOx() {
	return ox;
}
void Window::SetOx(int nox) {
	ox = nox;
}
int Window::GetOy() {
	return oy;
}
void Window::SetOy(int noy) {
	oy = noy;
}
int Window::GetOpacity() {
	return opacity;
}
void Window::SetOpacity(int nopacity) {
	opacity = nopacity;
}
int Window::GetBackOpacity() {
	return back_opacity;
}
void Window::SetBackOpacity(int nback_opacity) {
	back_opacity = nback_opacity;
}
int Window::GetContentsOpacity() {
	return contents_opacity;
}
void Window::SetContentsOpacity(int ncontents_opacity) {
	contents_opacity = ncontents_opacity;
}
