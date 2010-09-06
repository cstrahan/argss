/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

#ifndef _WINDOW_XP_H_
#define _WINDOW_XP_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include "graphics/bitmap.h"
#include "graphics/drawable.h"

////////////////////////////////////////////////////////////
/// Window class
////////////////////////////////////////////////////////////
class Window : public Drawable {
public:
	Window(unsigned long iid);
	~Window();

	static bool IsDisposed(unsigned long id);
	static void New(unsigned long id);
	static Window* Get(unsigned long id);
	static void Dispose(unsigned long id);

	void RefreshBitmaps();
	void Draw(long z);
	void Draw(long z, Bitmap* dst_bitmap);

	void Update();
	unsigned long GetViewport();
	void SetViewport(unsigned long nviewport);
	unsigned long GetWindowskin();
	void SetWindowskin(unsigned long nwindowskin);
	unsigned long GetContents();
	void SetContents(unsigned long ncontents);
	bool GetStretch();
	void SetStretch(bool nstretch);
	unsigned long GetCursorRect();
	void SetCursorRect(unsigned long ncursor_rect);
	bool GetActive();
	void SetActive(bool nactive);
	bool GetVisible();
	void SetVisible(bool nvisible);
	bool GetPause();
	void SetPause(bool npause);
	int GetX();
	void SetX(int nx);
	int GetY();
	void SetY(int ny);
	int GetWidth();
	void SetWidth(int nwidth);
	int GetHeight();
	void SetHeight(int nheight);
	int GetZ();
	void SetZ(int nz);
	int GetOx();
	void SetOx(int nox);
	int GetOy();
	void SetOy(int noy);
	int GetOpacity();
	void SetOpacity(int nopacity);
	int GetBackOpacity();
	void SetBackOpacity(int nback_opacity);
	int GetContentsOpacity();
	void SetContentsOpacity(int ncontents_opacity);

private:
	unsigned long id;
	unsigned long viewport;
	unsigned long windowskin;
	unsigned long contents;
	bool stretch;
	unsigned long cursor_rect;
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

	int cursor_frame;
	int pause_frame;
	int pause_id;
};

#endif
