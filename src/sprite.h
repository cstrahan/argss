//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
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

#ifndef _SPRITE_H_
#define _SPRITE_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <map>

#include "bitmap.h"
#include "color.h"
#include "tone.h"
#include "rect.h"

////////////////////////////////////////////////////////////
/// Sprite class
////////////////////////////////////////////////////////////
class Sprite {
public:
	Sprite(unsigned long iid);
	~Sprite();
	
	static bool IsDisposed(unsigned long id);
	static void New(unsigned long id);
	static Sprite* Get(unsigned long id);

	void Draw();

	void Dispose();
	void Flash(int duration);
	void Flash(Color color, int duration);
    void Update();
	unsigned long GetViewport();
	void SetViewport(unsigned long nviewport);
	unsigned long GetBitmap();
	void SetBitmap(unsigned long nbitmap);
	unsigned long GetSrcRect();
	void SetSrcRect(unsigned long nsrc_rect);
	bool GetVisible();
	void SetVisible(bool nvisible);
	int GetX();
	void SetX(int nx);
    int GetY();
	void SetY(int ny);
	int GetZ();
	void SetZ(int nz);
	int GetOx();
	void SetOx(int nox);
	int GetOy();
	void SetOy(int noy);
	double GetZoomX();
	void SetZoomX(double nzoom_x);
	double GetZoomY();
	void SetZoomY(double nzoom_y);
	double GetAngle();
	void SetAngle(double nangle);
    bool GetFlipX();
	void SetFlipX(bool nflipx);
    bool GetFlipY();
	void SetFlipY(bool nflipy);
    int GetBushDepth();
	void SetBushDepth(int nbush_depth);
	int GetOpacity();
	void SetOpacity(int nopacity);
	int GetBlendType();
	void SetBlendType(int nblend_type);
	unsigned long GetColor();
	void SetColor(unsigned long ncolor);
	unsigned long GetTone();
	void SetTone(unsigned long ntone);

private:
	static std::map<unsigned long, Sprite*> sprites;

	unsigned long id;
	unsigned long viewport;
	unsigned long bitmap;
	unsigned long src_rect;
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
	unsigned long color;
	unsigned long tone;
	
	Color flash_color;
	int flash_duration;
	int flash_frame;
	Bitmap* sprite;
	Rect src_rect_sprite;
	Rect src_rect_last;
	Color color_sprite;
	Tone tone_sprite;
	bool needs_refresh;

	void Refresh();
	int GetWidth();
	int GetHeight();
};

#endif
