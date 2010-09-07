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

#ifndef _PLANE_H_
#define _PLANE_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include <string>
#include "graphics/bitmap.h"
#include "graphics/tone.h"
#include "graphics/drawable.h"

///////////////////////////////////////////////////////////
/// Plane class
///////////////////////////////////////////////////////////
class Plane : public Drawable {
public:
	Plane(unsigned long iid);
	~Plane();

	static bool IsDisposed(unsigned long id);
	static void New(unsigned long id);
	static Plane* Get(unsigned long id);
	static void Dispose(unsigned long id);

	void RefreshBitmaps();
	void Draw(long z);
	void Draw(long z, Bitmap* dst_bitmap);

	unsigned long GetViewport();
	void SetViewport(unsigned long nviewport);
	unsigned long GetBitmap();
	void SetBitmap(unsigned long nbitmap);
	bool GetVisible();
	void SetVisible(bool nvisible);
	int GetZ();
	void SetZ(int nz);
	int GetOx();
	void SetOx(int nox);
	int GetOy();
	void SetOy(int noy);
	float GetZoomX();
	void SetZoomX(float nzoom_x);
	float GetZoomY();
	void SetZoomY(float nzoom_y);
	int GetOpacity();
	void SetOpacity(int nopacity);
	int GetBlendType();
	void SetBlendType(int nblend_type);
	unsigned long GetColor();
	void SetColor(unsigned long ncolor);
	unsigned long GetTone();
	void SetTone(unsigned long ntone);

private:
	void Refresh();
	void ApplyTone();
	void ApplyZoom();
	bool needs_refresh;
	Tone tone_last;

	unsigned long id;
	unsigned long viewport;
	unsigned long bitmap;
	bool visible;
	int z;
	int ox;
	int oy;
	float zoom_x;
	float zoom_y;
	int opacity;
	int blend_type;
	unsigned long color;
	unsigned long tone;
};

#endif
