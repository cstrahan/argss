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

#ifndef _BITMAP_H_
#define _BITMAP_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <string>
#include "defines.h"
#include "argss_ruby.h"
#include "gl/gl.h"
#include "rect.h"
#include "color.h"
#include "tone.h"

////////////////////////////////////////////////////////////
/// Bitmap class
////////////////////////////////////////////////////////////
class Bitmap {
public:
	Bitmap();
	Bitmap(int iwidth, int iheight);
	Bitmap(unsigned long iid, std::string filename);
	Bitmap(unsigned long iid, int iwidth, int iheight);
	Bitmap(Bitmap* source, Rect src_rect);
	~Bitmap();
	
	static bool IsDisposed(unsigned long id);
	static void New(unsigned long id, std::string filename);
	static void New(unsigned long id, int width, int height);
	static Bitmap* Get(unsigned long id);
	static void Dispose(unsigned long id);
	static void RefreshBitmaps();
	static void DisposeBitmaps();

	int GetWidth();
	int GetHeight();
	void Copy(int x, int y, Bitmap* source, Rect src_rect);
	void Blit(int x, int y, Bitmap* source, Rect src_rect, int opacity);
	void StretchBlit(Rect dst_rect, Bitmap* src_bitmap, Rect src_rect, int opacity);
	void FillRect(Rect rect, Color color);
	void Clear();
	void Clear(Color color);
	Color GetPixel(int x, int y);
	void SetPixel(int x, int y, Color color);
	void HueChange(double hue);
	void SatChange(double saturation);
	void LumChange(double luminance);
	void HSLChange(double h, double s, double l);
	void HSLChange(double h, double s, double l, Rect rect);
	void TextDraw(Rect rect, std::string text, int align);
	Rect GetTextSize(std::string text);
	void GradientFillRect(Rect rect, Color color1, Color color2, bool vertical);
	void ClearRect(Rect rect);
	void Blur();
	void RadialBlur(int angle, int division);

	void ToneChange(Tone tone);
	void OpacityChange(int opacity, int bush_depth = 0);
	void Flip(bool flipx, bool flipy);
	void Zoom(double zoom_x, double zoom_y);
	Bitmap* Resample(int scalew, int scaleh, Rect src_rect);
	void Rotate(float angle);
	
	Rect GetRect();

	void Changed();
	void Refresh();
	void BindBitmap();
	Uint32* GetPixels();

protected:
	unsigned long id;

	GLuint gl_bitmap;
	long width;
	long height;

	std::vector<Uint32> pixels;

private:
	static std::map<unsigned long, Bitmap*> bitmaps;
};

#endif
