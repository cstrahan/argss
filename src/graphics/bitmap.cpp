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

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include <algorithm>
#include "SOIL.h"
#include "graphics/text.h"
#include "graphics/bitmap.h"
#include "defines.h"
#include "hslrgb.h"
#include "graphics/graphics.h"
#include "system.h"
#include "argss/classes/aerror.h"
#include "tools/filefinder.h"

///////////////////////////////////////////////////////////
/// Static Variables
///////////////////////////////////////////////////////////
std::map<unsigned long, Bitmap*> Bitmap::bitmaps;

///////////////////////////////////////////////////////////
/// Defines
///////////////////////////////////////////////////////////
#define min(a, b)	(((a) < (b)) ? (a) : (b))
#define max(a, b)	(((a) > (b)) ? (a) : (b))

///////////////////////////////////////////////////////////
/// Constructors
///////////////////////////////////////////////////////////
Bitmap::Bitmap(int iwidth, int iheight) {
	id = 0;
	pixels.resize(iwidth * iheight, 0);
	width = (long)iwidth;
	height = (long)iheight;
	gl_bitmap = 0;
}
Bitmap::Bitmap(unsigned long iid, std::string filename) {
	std::string path = FileFinder::FindImage(filename);
	if (path == "") {
		VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
		rb_raise(enoent, "No such file or directory - %s", filename.c_str());
	}

	int rwidth, rheight, channels;
	unsigned char* load_pixels = SOIL_load_image(path.c_str(), &rwidth, &rheight, &channels, SOIL_LOAD_RGBA);

	if (!load_pixels) {
		rb_raise(ARGSS::AError::id, "couldn't load %s image.\n%s\n", filename.c_str(), SOIL_last_result());
	}

	pixels.resize(rwidth * rheight);
	memcpy(&pixels[0], load_pixels, rwidth * rheight * 4);

	SOIL_free_image_data(load_pixels);

	id = iid;
	width = (long)rwidth;
	height = (long)rheight;
	gl_bitmap = 0;
}
Bitmap::Bitmap(unsigned long iid, int iwidth, int iheight) {
	if (iwidth <= 0 && iheight <= 0) {
		rb_raise(ARGSS::AError::id, "cant't create %dx%d image.\nWidth and height must be bigger than 0.\n", iwidth, iheight);
	}
	id = iid;
	pixels.resize(iwidth * iheight, 0);
	width = (long)iwidth;
	height = (long)iheight;
	gl_bitmap = 0;
}
Bitmap::Bitmap(Bitmap* source, Rect src_rect) {
	if (src_rect.width <= 0 && src_rect.height <= 0) {
		rb_raise(ARGSS::AError::id, "cant't create %dx%d image.\nWidth and height must be bigger than 0.\n", src_rect.width, src_rect.height);
	}
	id = 0;
	width = (long)src_rect.width;
	height = (long)src_rect.height;
	pixels.resize(width * height, 0);
	gl_bitmap = 0;
	Copy(0, 0, source, src_rect);
}

///////////////////////////////////////////////////////////
/// Destructor
///////////////////////////////////////////////////////////
Bitmap::~Bitmap() {
	if (gl_bitmap > 0) {
		glDeleteTextures(1, &gl_bitmap);
	}
}

///////////////////////////////////////////////////////////
/// Class Is Bitmap Disposed?
///////////////////////////////////////////////////////////
bool Bitmap::IsDisposed(unsigned long id) {
	return bitmaps.count(id) == 0;
}

///////////////////////////////////////////////////////////
/// Class New Bitmap
///////////////////////////////////////////////////////////
void Bitmap::New(unsigned long id, std::string filename) {
	bitmaps[id] = new Bitmap(id, filename);
}
void Bitmap::New(unsigned long id, int width, int height) {
	bitmaps[id] = new Bitmap(id, width, height);
}

///////////////////////////////////////////////////////////
/// Class Get Bitmap
///////////////////////////////////////////////////////////
Bitmap* Bitmap::Get(unsigned long id) {
	return bitmaps[id];
}

///////////////////////////////////////////////////////////
/// Class Dispose Bitmap
///////////////////////////////////////////////////////////
void Bitmap::Dispose(unsigned long id) {
	delete bitmaps[id];
	std::map<unsigned long, Bitmap*>::iterator it = bitmaps.find(id);
	bitmaps.erase(it);
}

///////////////////////////////////////////////////////////
/// Class Refresh Bitmaps
///////////////////////////////////////////////////////////
void Bitmap::RefreshBitmaps() {
	std::map<unsigned long, Bitmap*>::iterator it_bitmaps;
	for (it_bitmaps = bitmaps.begin(); it_bitmaps != bitmaps.end(); it_bitmaps++) {
		it_bitmaps->second->Changed();
	}
}

///////////////////////////////////////////////////////////
/// Class Dispose Bitmaps
///////////////////////////////////////////////////////////
void Bitmap::DisposeBitmaps() {
	std::map<unsigned long, Bitmap*>::iterator it_bitmaps;
	for (it_bitmaps = bitmaps.begin(); it_bitmaps != bitmaps.end(); it_bitmaps++) {
		delete it_bitmaps->second;
	}
	bitmaps.clear();
}

///////////////////////////////////////////////////////////
/// Changed
///////////////////////////////////////////////////////////
void Bitmap::Changed() {
	if (gl_bitmap > 0) {
		glEnable(GL_TEXTURE_2D);

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		glBindTexture(GL_TEXTURE_2D, gl_bitmap);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
		//glDeleteTextures(1, &gl_bitmap);
		//gl_bitmap = 0;
	}
}

///////////////////////////////////////////////////////////
/// Refresh
///////////////////////////////////////////////////////////
void Bitmap::Refresh() {
	if (gl_bitmap > 0) return;

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glGenTextures(1, &gl_bitmap);
	glBindTexture(GL_TEXTURE_2D, gl_bitmap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
}

///////////////////////////////////////////////////////////
/// Bind Bitmap texture
///////////////////////////////////////////////////////////
void Bitmap::BindBitmap() {
	glBindTexture(GL_TEXTURE_2D, gl_bitmap);
}

///////////////////////////////////////////////////////////
/// Get Pixels
///////////////////////////////////////////////////////////
Uint32* Bitmap::GetPixels() {
	return &pixels[0];
}

///////////////////////////////////////////////////////////
/// Get width
///////////////////////////////////////////////////////////
int Bitmap::GetWidth() {
	return width;
}

///////////////////////////////////////////////////////////
/// Get height
///////////////////////////////////////////////////////////
int Bitmap::GetHeight() {
	return height;
}

///////////////////////////////////////////////////////////
/// Copy
///////////////////////////////////////////////////////////
void Bitmap::Copy(int x, int y, Bitmap* src_bitmap, Rect src_rect) {
	if (src_bitmap->GetWidth() == 0 || src_bitmap->GetHeight() == 0 || width == 0 || height == 0) return;
	if (x >= width || y >= height) return;

	if (x < 0) {
		src_rect.x -= x;
		x = 0;
	}
	if (y < 0) {
		src_rect.y -= y;
		y = 0;
	}

	src_rect.Adjust(src_bitmap->GetWidth(), src_bitmap->GetHeight());
	if (src_rect.IsOutOfBounds(src_bitmap->GetWidth(), src_bitmap->GetHeight())) return;

	int src_width = src_rect.width;
	int src_height = src_rect.height;
	if (x + src_width > width) src_width = width - x;
	if (y + src_height > height) src_height = height - y;
	if (src_width <= 0 || src_height <= 0) return;

	int src_pitch = src_width * 4;
	int src_row = src_bitmap->GetWidth();
	const Uint32* src_pixels = ((Uint32*)(&src_bitmap->pixels[0])) + src_rect.x + src_rect.y * src_bitmap->GetWidth();
	Uint32* dst_pixels = ((Uint32*)(&pixels[0])) + x + y * width;

	for (int i = 0; i < src_height; ++i) {
		memcpy(dst_pixels, src_pixels, src_pitch);
		src_pixels += src_row;
		dst_pixels += width;
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Blit
///////////////////////////////////////////////////////////
void Bitmap::Blit(int x, int y, Bitmap* src_bitmap, Rect src_rect, int opacity) {
	if (src_bitmap->GetWidth() == 0 || src_bitmap->GetHeight() == 0 || width == 0 || height == 0) return;
	if (x >= width || y >= height) return;

	if (x < 0) {
		src_rect.x -= x;
		x = 0;
	}
	if (y < 0) {
		src_rect.y -= y;
		y = 0;
	}

	src_rect.Adjust(src_bitmap->GetWidth(), src_bitmap->GetHeight());
	if (src_rect.IsOutOfBounds(src_bitmap->GetWidth(), src_bitmap->GetHeight())) return;

	int src_width = src_rect.width;
	int src_height = src_rect.height;
	if (x + src_width > width) src_width = width - x;
	if (y + src_height > height) src_height = height - y;
	if (src_width <= 0 || src_height <= 0) return;

	int src_row = src_bitmap->GetWidth() * 4;
	int dst_row = width * 4;
	const Uint8* src_pixels = ((Uint8*)(&src_bitmap->pixels[0])) + (src_rect.x + src_rect.y * src_bitmap->GetWidth()) * 4;
	Uint8* dst_pixels = ((Uint8*)(&pixels[0])) + (x + y * width) * 4;

	if (opacity > 255) opacity = 255;
	if (opacity > 0) {
		for (int i = 0; i < src_height; ++i) {
			for (int j = 0; j < src_width; ++j) {
				const Uint8* src = src_pixels + j * 4;
				Uint8* dst = dst_pixels + j * 4;

				Uint8 srca = (Uint8)(src[3] * opacity / 255);
				dst[0] = (dst[0] * (255 - srca) + src[0] * srca) / 255;
				dst[1] = (dst[1] * (255 - srca) + src[1] * srca) / 255;
				dst[2] = (dst[2] * (255 - srca) + src[2] * srca) / 255;
				dst[3] = dst[3] * (255 - srca) / 255 + srca;
			}
			src_pixels += src_row;
			dst_pixels += dst_row;
		}
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Stretch blit
///////////////////////////////////////////////////////////
void Bitmap::StretchBlit(Rect dst_rect, Bitmap* src_bitmap, Rect src_rect, int opacity) {
	if (src_rect.width == dst_rect.width && src_rect.height == dst_rect.height) {
		Blit(dst_rect.x, dst_rect.y, src_bitmap, src_rect, opacity);
	} else {
		src_rect.Adjust(src_bitmap->GetWidth(), src_bitmap->GetHeight());
		if (src_rect.IsOutOfBounds(src_bitmap->GetWidth(), src_bitmap->GetHeight())) return;

		Bitmap* resampled = src_bitmap->Resample(dst_rect.width, dst_rect.height, src_rect);
		Rect rect(0, 0, dst_rect.width, dst_rect.height);
		Blit(dst_rect.x, dst_rect.y, resampled, rect, opacity);
		delete resampled;
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Fill rect
///////////////////////////////////////////////////////////
void Bitmap::FillRect(Rect rect, Color color) {
	rect.Adjust(GetWidth(), GetHeight());
	if (rect.IsOutOfBounds(GetWidth(), GetHeight())) return;

	long dst = rect.x + rect.y * width;
	Uint32 col = color.GetUint32();
	for (int i = 0; i < rect.height; i++) {
		fill_n(pixels.begin() + dst, rect.width, col);
		dst += width;
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Clear
///////////////////////////////////////////////////////////
void Bitmap::Clear() {
	memset(&pixels[0], 0, width * height * 4);

	Changed();
}
void Bitmap::Clear(Color color) {
	fill_n(pixels.begin(), width * height, color.GetUint32());

	Changed();
}

///////////////////////////////////////////////////////////
/// Get pixel
///////////////////////////////////////////////////////////
Color Bitmap::GetPixel(int x, int y) {
	if (x < 0 || y < 0) return Color(0, 0, 0, 0);
	if (x >= GetWidth() || y > GetHeight()) return Color(0, 0, 0, 0);
	return Color::NewUint32(pixels[(y * width) + x]);
}

///////////////////////////////////////////////////////////
/// Set pixel
///////////////////////////////////////////////////////////
void Bitmap::SetPixel(int x, int y, Color color) {
	if (x < 0 || y < 0) return;
	if (x >= width || y > height) return;
	pixels[(y * width) + x] = color.GetUint32();

	Changed();
}

///////////////////////////////////////////////////////////
/// Hue change
///////////////////////////////////////////////////////////
void Bitmap::HueChange(double hue) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Color color = Color::NewUint32(pixels[(i * width) + j]);
			pixels[(i * width) + j] = RGBAdjustHSL(color, hue, 0, 1).GetUint32();
		}
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Saturation change
///////////////////////////////////////////////////////////
void Bitmap::SatChange(double saturation) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Color color = Color::NewUint32(pixels[(i * width) + j]);
			pixels[(i * width) + j] = RGBAdjustHSL(color, 0, saturation, 1).GetUint32();
		}
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Luminance change
///////////////////////////////////////////////////////////
void Bitmap::LumChange(double luminance) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Color color = Color::NewUint32(pixels[(i * width) + j]);
			pixels[(i * width) + j] = RGBAdjustHSL(color, 0, 0, luminance).GetUint32();
		}
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// HSL change
///////////////////////////////////////////////////////////
void Bitmap::HSLChange(double h, double s, double l) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Color color = Color::NewUint32(pixels[(i * width) + j]);
			pixels[(i * width) + j] = RGBAdjustHSL(color, h, s, l).GetUint32();
		}
	}

	Changed();
}
void Bitmap::HSLChange(double h, double s, double l, Rect rect) {
	rect.Adjust(GetWidth(), GetHeight());
	if (rect.IsOutOfBounds(GetWidth(), GetHeight())) return;

	for (int i = rect.y; i < rect.y + rect.height; i++) {
		for (int j = rect.x; j < rect.x + rect.width; j++) {
			Color color = Color::NewUint32(pixels[(i * width) + j]);
			pixels[(i * width) + j] = RGBAdjustHSL(color, h, s, l).GetUint32();
		}
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Draw text
///////////////////////////////////////////////////////////
void Bitmap::TextDraw(Rect rect, std::string text, int align) {
	if (text.length() == 0) return;
	if (rect.IsOutOfBounds(GetWidth(), GetHeight())) return;

	VALUE font_id = rb_iv_get(id, "@font");
	VALUE name_id = rb_iv_get(font_id, "@name");
	Color color = Color(rb_iv_get(font_id, "@color"));
	int size = NUM2INT(rb_iv_get(font_id, "@size"));
	bool bold = NUM2BOOL(rb_iv_get(font_id, "@bold"));
	bool italic = NUM2BOOL(rb_iv_get(font_id, "@italic"));

	Bitmap* text_bmp = Text::Draw(text, StringValuePtr(name_id), color, size, bold, italic, false);

	if (text_bmp->GetWidth() > rect.width) {
		int stretch = (int)(text_bmp->GetWidth() * 0.4);
		if (rect.width > stretch) stretch = rect.width;
		Rect resample_rect(0, 0, text_bmp->GetWidth(), text_bmp->GetHeight());
		Bitmap* resampled = text_bmp->Resample(stretch, text_bmp->GetHeight(), resample_rect);
		delete text_bmp;
		text_bmp = resampled;
	}
	Rect src_rect(0, 0, rect.width, rect.height);
	int y = rect.y;
	if (rect.height > text_bmp->GetHeight()) y += ((rect.height - text_bmp->GetHeight()) / 2);
	int x = rect.x;
	if (rect.width > text_bmp->GetWidth()) {
		if (align == 1) {
			x += (rect.width - text_bmp->GetWidth()) / 2;
		} else if (align == 2) {
			x += rect.width - text_bmp->GetWidth();
		}
	}
	Blit(x, y, text_bmp, src_rect, (int)color.alpha);
	delete text_bmp;

	Changed();
}

///////////////////////////////////////////////////////////
/// Get text size
///////////////////////////////////////////////////////////
Rect Bitmap::GetTextSize(std::string text) {
	VALUE font_id = rb_iv_get(id, "@font");
	VALUE name_id = rb_iv_get(font_id, "@name");
	int size = NUM2INT(rb_iv_get(font_id, "@size"));
	return Text::RectSize(text, StringValuePtr(name_id), size);
}

///////////////////////////////////////////////////////////
/// Gradient fill rect
///////////////////////////////////////////////////////////
void Bitmap::GradientFillRect(Rect rect, Color color1, Color color2, bool vertical) {
	// TODO
}

///////////////////////////////////////////////////////////
/// Clear Rect
///////////////////////////////////////////////////////////
void Bitmap::ClearRect(Rect rect) {
	// TODO
}

///////////////////////////////////////////////////////////
/// Blur
///////////////////////////////////////////////////////////
void Bitmap::Blur() {
	// TODO
}

///////////////////////////////////////////////////////////
/// Radial Blur
///////////////////////////////////////////////////////////
void Bitmap::RadialBlur(int angle, int division) {
	// TODO
}

///////////////////////////////////////////////////////////
/// Tone change
///////////////////////////////////////////////////////////
void Bitmap::ToneChange(Tone tone) {
	if (tone.red == 0 && tone.green == 0 && tone.blue == 0 && tone.gray == 0) return;

	Uint8* dst_pixels = (Uint8*)&pixels[0];

	if (tone.gray == 0) {
		for (int i = 0; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8* pixel = dst_pixels;
				pixel[0] = (Uint8)max(min(pixel[0] + tone.red, 255), 0);
				pixel[1] = (Uint8)max(min(pixel[1] + tone.green, 255), 0);
				pixel[2] = (Uint8)max(min(pixel[2] + tone.blue, 255), 0);
				dst_pixels += 4;
			}
		}
	} else {
		double factor = (255 - tone.gray) / 255.0;
		double gray;
		for (int i = 0; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8* pixel = dst_pixels;

				gray = pixel[0] * 0.299 + pixel[1] * 0.587 + pixel[2] * 0.114;
				pixel[0] = (Uint8)max(min((pixel[0] - gray) * factor + gray + tone.red + 0.5, 255), 0);
				pixel[1] = (Uint8)max(min((pixel[1] - gray) * factor + gray + tone.green + 0.5, 255), 0);
				pixel[2] = (Uint8)max(min((pixel[2] - gray) * factor + gray + tone.blue + 0.5, 255), 0);
				dst_pixels += 4;
			}
		}
	}

	Changed();
}

///////////////////////////////////////////////////////////
/// Opacity change
///////////////////////////////////////////////////////////
void Bitmap::OpacityChange(int opacity, int bush_depth) {
	/*if (opacity >= 255 && bush_depth <= 0) return;

	SDL_LockSurface(bitmap);

	Uint8* pixels = (Uint8 *)bitmap->pixels;

	int start_bush = max(GetHeight() - bush_depth, 0);

	const int abyte = MaskGetByte(bitmap->format->Amask);

	if (opacity < 255) {
		for (int i = 0; i < start_bush; i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8* pixel = pixels;
				pixel[abyte] = pixel[abyte] * opacity / 255;
				pixels += 4;
			}
		}
		for (int i = start_bush; i< GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8* pixel = pixels;
				pixel[abyte] = (pixel[abyte] / 2) * opacity / 255;
				pixels += 4;
			}
		}
	} else {
		pixels += start_bush * GetWidth() * 4;
		for (int i = start_bush; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8* pixel = pixels;
				pixel[abyte] = pixel[abyte] / 2;
				pixels += 4;
			}
		}
	}
	SDL_UnlockSurface(bitmap);

	Changed();*/
}

///////////////////////////////////////////////////////////
/// Flip
///////////////////////////////////////////////////////////
void Bitmap::Flip(bool flipx, bool flipy) {
	/*if (!(flipx || flipy)) return;

	SDL_LockSurface(bitmap);

	Bitmap* temp_bmp = new Bitmap(GetWidth(), GetHeight());
	SDL_Surface* temp = temp_bmp->bitmap;

	SDL_LockSurface(temp);

	Uint32* srcpixels = (Uint32*)bitmap->pixels;
	Uint32* dstpixels = (Uint32*)temp->pixels;

	if (flipx && flipy) {
		long srcpixel = 0;
		long dstpixel = GetWidth() + (GetHeight() - 1) * GetWidth() - 1;
		for (int i = 0; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				dstpixels[dstpixel] = srcpixels[srcpixel];

				srcpixel += 1;
				dstpixel -= 1;
			}
		}
	} else if (flipx) {
		long srcpixel = 0;
		long dstpixel = GetWidth() - 1;
		for (int i = 0; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				dstpixels[dstpixel] = srcpixels[srcpixel];

				srcpixel += 1;
				dstpixel -= 1;
			}
			dstpixel += GetWidth() * 2;
		}
	} else if (flipy) {
		dstpixels += (GetHeight() - 1) * GetWidth();
		for (int i = 0; i < GetHeight(); i++) {
			memcpy(dstpixels, srcpixels, GetWidth() * 4);
			srcpixels += GetWidth();
			dstpixels -= GetWidth();
		}
	}

	SDL_UnlockSurface(bitmap);
	SDL_UnlockSurface(temp);

	SDL_FreeSurface(bitmap);

	bitmap = temp;

	temp_bmp->bitmap = NULL;
	delete temp_bmp;

	Changed();*/
}

///////////////////////////////////////////////////////////
/// Zoom
///////////////////////////////////////////////////////////
void Bitmap::Zoom(double zoom_x, double zoom_y) {
	/*if (zoom_x == 1.0 && zoom_y == 1.0) return;

	SDL_LockSurface(bitmap);

	int scalew = (int)(GetWidth() * zoom_x);
	int scaleh = (int)(GetHeight() * zoom_y);

	Bitmap* nbitmap = new Bitmap(scalew, scaleh);
	SDL_Surface* surface = nbitmap->bitmap;

	SDL_LockSurface(surface);

	Uint8* srcpixels = (Uint8*)bitmap->pixels;
	Uint8* dstpixels = (Uint8*)surface->pixels;

	int row = GetWidth() * 4;

	for (int yy = 0; yy < surface->h; yy++) {
		int nearest_matchy = (int)(yy / zoom_y) * row;
		for (int xx = 0; xx < surface->w; xx++) {
			int nearest_match = nearest_matchy + (int)(xx / zoom_x) * 4;
			dstpixels[0] = srcpixels[nearest_match];
			dstpixels[1] = srcpixels[nearest_match + 1];
			dstpixels[2] = srcpixels[nearest_match + 2];
			dstpixels[3] = srcpixels[nearest_match + 3];
			dstpixels += 4;
		}
	}

	SDL_UnlockSurface(surface);
	SDL_FreeSurface(bitmap);

	bitmap = surface;

	nbitmap->bitmap = NULL;
	delete nbitmap;

	Changed();*/
}

///////////////////////////////////////////////////////////
/// Resample
///////////////////////////////////////////////////////////
Bitmap* Bitmap::Resample(int scalew, int scaleh, Rect src_rect) {
	double zoom_x = (double)(scalew) / src_rect.width;
	double zoom_y = (double)(scaleh) / src_rect.height;

	Bitmap* resampled = new Bitmap(scalew, scaleh);

	Uint8* src_pixels = (Uint8*)&pixels[0];
	Uint8* dst_pixels = (Uint8*)(&resampled->pixels[0]);

	int row = width * 4;

	for (int yy = 0; yy < scaleh; yy++) {
		int nearest_matchy = (src_rect.y + (int)(yy / zoom_y)) * row;
		for (int xx = 0; xx < scalew; xx++) {
			int nearest_match = nearest_matchy + (src_rect.x + (int)(xx / zoom_x)) * 4;
			dst_pixels[0] = src_pixels[nearest_match];
			dst_pixels[1] = src_pixels[nearest_match + 1];
			dst_pixels[2] = src_pixels[nearest_match + 2];
			dst_pixels[3] = src_pixels[nearest_match + 3];
			dst_pixels += 4;
		}
	}

	return resampled;
}

///////////////////////////////////////////////////////////
/// Rotate
///////////////////////////////////////////////////////////
void Bitmap::Rotate(float angle) {
	/*while (angle > 360)
		angle -= 360;
	while (angle < 360)
		angle += 360;

	if (angle == 0) return;

	SDL_LockSurface(bitmap);

	float radians = angle * 3.14159f / 180.0f;

	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);

	float p1x = -GetHeight() * sine;
	float p1y = GetHeight() * cosine;
	float p2x = GetWidth() * cosine - GetHeight() * sine;
	float p2y = GetHeight() * cosine + GetWidth() * sine;
	float p3x = GetWidth() * cosine;
	float p3y = GetWidth() * sine;
	float minx = min(0, min(p1x, min(p2x, p3x)));
	float miny = min(0, min(p1y, min(p2y, p3y)));
	float maxx = max(p1x, max(p2x, p3x));
	float maxy = max(p1y, max(p2y, p3y));

	int nwidth = (int)ceil(fabs(maxx)-minx);
	int nheight = (int)ceil(fabs(maxy)-miny);

	SDL_Surface* nbitmap = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, nwidth, nheight, 32, rmask, gmask, bmask, amask);

	SDL_LockSurface(nbitmap);

	Uint32* srcpixels = (Uint32*)bitmap->pixels;
	Uint32* dstpixels = (Uint32*)nbitmap->pixels;

	for (int i = 0; i < nbitmap->h; i++) {
		for (int j = 0; j < nbitmap->w; j++) {
			int sx = (int)((j + minx) * cosine + (i + miny) * sine);
			int sy = (int)((i + miny) * cosine - (j + minx) * sine);
			if (sx >= 0 && sx < bitmap->w && sy >= 0 && sy < bitmap->h) {
				dstpixels[0] = srcpixels[sy * bitmap->w + sx];
			} else {
				dstpixels[0] = 0;
			}
			dstpixels++;
		}
	}

	SDL_UnlockSurface(nbitmap);
	SDL_FreeSurface(bitmap);

	bitmap = nbitmap;

	Changed();*/
}

///////////////////////////////////////////////////////////
/// Get Rect
///////////////////////////////////////////////////////////
Rect Bitmap::GetRect() {
	return Rect(0, 0, GetWidth(), GetHeight());
}

