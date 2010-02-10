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
#include "bitmap.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defines.h"
#include "hslrgb.h"
#include "graphics.h"
#include "system.h"
#include "argss_error.h"
#include "filefinder.h"

////////////////////////////////////////////////////////////
/// Static Variables
////////////////////////////////////////////////////////////
std::map<unsigned long, Bitmap*> Bitmap::bitmaps;

////////////////////////////////////////////////////////////
/// Defines
////////////////////////////////////////////////////////////
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

////////////////////////////////////////////////////////////
/// Constructors
////////////////////////////////////////////////////////////
Bitmap::Bitmap(int width, int height) {
	SDL_Surface* temp;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, rmask, gmask, bmask, amask);
	if (temp == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't create %dx%d image.\n%s\n", width, height, SDL_GetError());
	}
	bitmap = SDL_DisplayFormatAlpha(temp);
	if (bitmap == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't optimize %dx%d image.\n%s\n", width, height, SDL_GetError());
	}
	SDL_FreeSurface(temp);

	gl_bitmap = 0;
}
Bitmap::Bitmap(unsigned long iid, std::string filename) {
	std::string path = FileFinder::FindImage(filename);
	if (path == "") {
		VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
		rb_raise(enoent, "No such file or directory - %s", filename.c_str());
	}
	id = iid;
	SDL_Surface* temp;
	temp = IMG_Load(path.c_str());
	if (temp == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't load %s image.\n%s\n", filename.c_str(), IMG_GetError());
	}
	bitmap = SDL_DisplayFormatAlpha(temp);
	if (bitmap == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't optimize %s image.\n%s\n", filename.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(temp);

	gl_bitmap = 0;
}
Bitmap::Bitmap(unsigned long iid, int width, int height) {
	id = iid;
	SDL_Surface* temp;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, 32, rmask, gmask, bmask, amask);
	if (temp == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't create %dx%d image.\n%s\n", width, height, SDL_GetError());
	}
	bitmap = SDL_DisplayFormatAlpha(temp);
	if (bitmap == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't optimize %dx%d image.\n%s\n", width, height, SDL_GetError());
	}
	SDL_FreeSurface(temp);

	gl_bitmap = 0;
}
Bitmap::Bitmap(Bitmap* source, Rect src_rect) {
	SDL_Surface* temp;
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, src_rect.width, src_rect.height, 32, rmask, gmask, bmask, amask);
	if (temp == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't create %dx%d image.\n%s\n", src_rect.width, src_rect.height, SDL_GetError());
	}
	bitmap = SDL_DisplayFormatAlpha(temp);
	if (bitmap == NULL) {
		rb_raise(ARGSS::AError::id, "couldn't optimize %dx%d image.\n%s\n", src_rect.width, src_rect.height, SDL_GetError());
	}
	SDL_FreeSurface(temp);

	Blit(0, 0, source, src_rect, 255);

	gl_bitmap = 0;
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Bitmap::~Bitmap() {
	if (gl_bitmap > 0)  {
		glDeleteTextures(1, &gl_bitmap);
	}
	SDL_FreeSurface(bitmap);
}

////////////////////////////////////////////////////////////
/// Class Is Bitmap Disposed?
////////////////////////////////////////////////////////////
bool Bitmap::IsDisposed(unsigned long id) {
	return bitmaps.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Bitmap
////////////////////////////////////////////////////////////
void Bitmap::New(unsigned long id, std::string filename) {
	bitmaps[id] = new Bitmap(id, filename);
}
void Bitmap::New(unsigned long id, int width, int height) {
	bitmaps[id] = new Bitmap(id, width, height);
}

////////////////////////////////////////////////////////////
/// Class Get Bitmap
////////////////////////////////////////////////////////////
Bitmap* Bitmap::Get(unsigned long id) {
	return bitmaps[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Bitmap
////////////////////////////////////////////////////////////
void Bitmap::Dispose(unsigned long id) {
	delete bitmaps[id];
	std::map<unsigned long, Bitmap*>::iterator it = bitmaps.find(id);
	bitmaps.erase(it);
}

////////////////////////////////////////////////////////////
/// Class Refresh Bitmaps
////////////////////////////////////////////////////////////
void Bitmap::RefreshBitmaps() {
	std::map<unsigned long, Bitmap*>::iterator it_bitmaps;
	for (it_bitmaps = bitmaps.begin(); it_bitmaps != bitmaps.end(); it_bitmaps++) {
		it_bitmaps->second->Changed();
	}
}

////////////////////////////////////////////////////////////
/// Changed
////////////////////////////////////////////////////////////
void Bitmap::Changed() {
	if (gl_bitmap > 0)  {
		glDeleteTextures(1, &gl_bitmap);
		gl_bitmap = 0;
	}
}

////////////////////////////////////////////////////////////
/// Refresh
////////////////////////////////////////////////////////////
void Bitmap::Refresh() {
	if (gl_bitmap > 0) return;

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_COLOR);
	glLoadIdentity();

	glGenTextures(1, &gl_bitmap);
	glBindTexture(GL_TEXTURE_2D, gl_bitmap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int bpp = bitmap->format->BytesPerPixel;
	int format;

	if (bitmap->format->Rmask == 0x00FF0000) format = GL_BGRA;
	else format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, bpp, bitmap->w, bitmap->h, 0, format, GL_UNSIGNED_BYTE, bitmap->pixels);
}

////////////////////////////////////////////////////////////
/// Get width
////////////////////////////////////////////////////////////
int Bitmap::GetWidth() {
	return bitmap->w;
}

////////////////////////////////////////////////////////////
/// Get height
////////////////////////////////////////////////////////////
int Bitmap::GetHeight() {
	return bitmap->h;
}

////////////////////////////////////////////////////////////
/// Blit
////////////////////////////////////////////////////////////
void Bitmap::Blit(int x, int y, Bitmap* src_bitmap, Rect src_rect, int opacity) {
	SDL_Surface* source = src_bitmap->bitmap;

	if (source->w == 0 || source->h == 0 || GetWidth() == 0 || GetHeight() == 0) return;
	if (x >= GetWidth() || y >= GetHeight()) return;

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
	
	int width = src_rect.width;
    int height = src_rect.height;
    if (x + width  > GetWidth()) width = GetWidth() - x;
    if (y + height > GetHeight()) height = GetHeight() - y;    
    if (width <= 0 || height <= 0)  return;

	SDL_LockSurface(source);
	SDL_LockSurface(bitmap);
	
    int src_stride = source->w * 4;
    int dst_stride = GetWidth() * 4;
    const Uint8* src_pixels = ((Uint8*)source->pixels) + (src_rect.x + src_rect.y * source->w) * 4;
    Uint8* dst_pixels = ((Uint8*)bitmap->pixels) + (x + y * GetWidth()) * 4;

	const int rbyte = MaskGetByte(bitmap->format->Rmask);
	const int gbyte = MaskGetByte(bitmap->format->Gmask);
	const int bbyte = MaskGetByte(bitmap->format->Bmask);
	const int abyte = MaskGetByte(bitmap->format->Amask);

    if (opacity > 255) opacity = 255;
	/*if (opacity >= 255) {
		SDL_Rect offset = {x, y, 0, 0};
		SDL_Rect src_rect_sdl = {src_rect.x, src_rect.y, width, height};
		SDL_SetAlpha(bitmap, SDL_SRCALPHA, bitmap->format->alpha);
		//SDL_SetAlpha(source, SDL_SRCALPHA, source->format->alpha);
		SDL_BlitSurface(source, &src_rect_sdl, bitmap, &offset);
		SDL_SetAlpha(bitmap, 0, bitmap->format->alpha);
		//SDL_SetAlpha(source, 0, source->format->alpha);
	}
	else*/ if (opacity > 0) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				const Uint8* src   = src_pixels + j * 4;
				Uint8*       dst   = dst_pixels + j * 4;

				Uint8 srca = src[abyte] * opacity / 255;
				dst[rbyte] = (dst[rbyte] * (255 - srca) + src[rbyte] * srca) / 255;
				dst[gbyte] = (dst[gbyte] * (255 - srca) + src[gbyte] * srca) / 255;
				dst[bbyte] = (dst[bbyte] * (255 - srca) + src[bbyte] * srca) / 255;
				dst[abyte] = dst[abyte] * (255 - srca) / 255 + srca;
			}
			src_pixels += src_stride;
			dst_pixels += dst_stride;
		}
	}
	
	SDL_UnlockSurface(source);
	SDL_UnlockSurface(bitmap);

	Changed();
}

////////////////////////////////////////////////////////////
/// Stretch blit
////////////////////////////////////////////////////////////
void Bitmap::StretchBlit(Rect dst_rect, Bitmap* src_bitmap, Rect src_rect, int opacity) {
    if (src_rect.width == dst_rect.width && src_rect.height == dst_rect.height) {
		Blit(dst_rect.x, dst_rect.y, src_bitmap, src_rect, opacity);
    }
    else {
		src_rect.Adjust(src_bitmap->GetWidth(), src_bitmap->GetHeight());
		if (src_rect.IsOutOfBounds(src_bitmap->GetWidth(), src_bitmap->GetHeight())) return;

		Bitmap* resampled = src_bitmap->Resample(dst_rect.width, dst_rect.height, src_rect);
		Rect rect(0, 0, dst_rect.width, dst_rect.height);
		Blit(dst_rect.x, dst_rect.y, resampled, rect, opacity);
		delete resampled;
    }

	Changed();
}

////////////////////////////////////////////////////////////
/// Fill rect
////////////////////////////////////////////////////////////
void Bitmap::FillRect(Rect rect, Color color) {
	rect.Adjust(GetWidth(), GetHeight());
	if (rect.IsOutOfBounds(GetWidth(), GetHeight())) return;
	
	SDL_Rect rect_sdl = rect.Get();
	SDL_FillRect(bitmap, &rect_sdl, color.GetUint32(bitmap->format));

	Changed();
}

////////////////////////////////////////////////////////////
/// Clear
////////////////////////////////////////////////////////////
void Bitmap::Clear() {
	SDL_FillRect(bitmap, NULL, 0);

	Changed();
}
void Bitmap::Clear(Color color) {
	SDL_FillRect(bitmap, NULL, color.GetUint32(bitmap->format));

	Changed();
}

////////////////////////////////////////////////////////////
/// Get pixel
////////////////////////////////////////////////////////////
Color Bitmap::GetPixel(int x, int y) {
	if (x < 0 || y < 0) return Color(0, 0, 0, 0);
	if (x >= GetWidth() || y > GetHeight()) return Color(0, 0, 0, 0);
	Uint32 *pixels = (Uint32*)bitmap->pixels;
	return Color(pixels[(y * GetWidth()) + x], bitmap->format);
}

////////////////////////////////////////////////////////////
/// Set pixel
////////////////////////////////////////////////////////////
void Bitmap::SetPixel(int x, int y, Color color) {
	if (x < 0 || y < 0) return;
	if (x >= GetWidth() || y > GetHeight()) return;
	Uint32 *pixels = (Uint32*)bitmap->pixels;
	pixels[(y * GetWidth()) + x] = color.GetUint32(bitmap->format);

	Changed();
}

////////////////////////////////////////////////////////////
/// Hue change
////////////////////////////////////////////////////////////
void Bitmap::HueChange(double hue) {
    Uint32 *pixels = (Uint32*)bitmap->pixels;
	
    for(int y = 0; y < GetHeight(); y++) {
        for(int x = 0; x < GetWidth(); x++) {
			Color color(pixels[(y * GetWidth()) + x], bitmap->format);
			pixels[(y * GetWidth()) + x] = RGBAdjustHSL(color, hue, 0, 1).GetUint32(bitmap->format);
        }
    }

	Changed();
}

////////////////////////////////////////////////////////////
/// Saturation change
////////////////////////////////////////////////////////////
void Bitmap::SatChange(double saturation) {
    Uint32 *pixels = (Uint32*)bitmap->pixels;
    for(int y = 0; y < GetHeight(); y++) {
        for(int x = 0; x < GetWidth(); x++) {
			Color color(pixels[(y * GetWidth()) + x], bitmap->format);
			pixels[(y * GetWidth()) + x] = RGBAdjustHSL(color, 0, saturation, 1).GetUint32(bitmap->format);
        }
    }

	Changed();
}

////////////////////////////////////////////////////////////
/// Luminance change
////////////////////////////////////////////////////////////
void Bitmap::LumChange(double luminance) {
    Uint32 *pixels = (Uint32*)bitmap->pixels;
    for(int y = 0; y < GetHeight(); y++) {
        for(int x = 0; x < GetWidth(); x++) {
			Color color(pixels[(y * GetWidth()) + x], bitmap->format);
			pixels[(y * GetWidth()) + x] = RGBAdjustHSL(color, 0, 0, luminance).GetUint32(bitmap->format);
        }
    }

	Changed();
}

////////////////////////////////////////////////////////////
/// HSL change
////////////////////////////////////////////////////////////
void Bitmap::HSLChange(double h, double s, double l) {
    Uint32 *pixels = (Uint32*)bitmap->pixels;
    for(int y = 0; y < GetHeight(); y++) {
        for(int x = 0; x < GetWidth(); x++) {
			Color color(pixels[(y * GetWidth()) + x], bitmap->format);
			Color col2 = RGBAdjustHSL(color, h, s, l);
			pixels[(y * GetWidth()) + x] = RGBAdjustHSL(color, h, s, l).GetUint32(bitmap->format);
        }
    }

	Changed();
}
void Bitmap::HSLChange(double h, double s, double l, Rect rect) {
    Uint32 *pixels = (Uint32*)bitmap->pixels;

	if (GetWidth() == 0 || GetHeight() == 0) return;

	rect.Adjust(GetWidth(), GetHeight());
	if (rect.IsOutOfBounds(GetWidth(), GetHeight())) return;

    for(int y = rect.y; y < rect.y + rect.height; y++) {
        for(int x = rect.x; x < rect.x + rect.width; x++) {
			Color color(pixels[(y * GetWidth()) + x], bitmap->format);
			pixels[(y * GetWidth()) + x] = RGBAdjustHSL(color, h, s, l).GetUint32(bitmap->format);
        }
    }

	Changed();
}

////////////////////////////////////////////////////////////
/// Draw text
////////////////////////////////////////////////////////////
void Bitmap::DrawText(Rect rect, std::string text, int align) {
	if (text.length() == 0) return;
	if (rect.IsOutOfBounds(GetWidth(), GetHeight())) return;
	
	VALUE font_id = rb_iv_get(id, "@font");
	VALUE name_id = rb_iv_get(font_id, "@name");
	std::string name = FileFinder::FindFont(StringValuePtr(name_id));
	TTF_Font* ttf_font = TTF_OpenFont(name.c_str(), NUM2INT(rb_iv_get(font_id, "@size")));
	if (!ttf_font) {
		rb_raise(ARGSS::AError::id, "couldn't open font %s size %d.\n%s\n", name.c_str(), NUM2INT(rb_iv_get(font_id, "@size")), TTF_GetError());
	}
	int style = 0;
    if (NUM2BOOL(rb_iv_get(font_id, "@bold"))) style |= TTF_STYLE_BOLD;
	if (NUM2BOOL(rb_iv_get(font_id, "@italic"))) style |= TTF_STYLE_ITALIC;
	TTF_SetFontStyle(ttf_font, style);

	Color color = Color(rb_iv_get(font_id, "@color"));
	
	SDL_Surface *text_surface;
	if (!(text_surface = TTF_RenderUTF8_Blended(ttf_font, text.c_str(), color.Get()))) {
		rb_raise(ARGSS::AError::id, "couldn't draw text %s with Font(%x).\n%s\n", text.c_str(), font_id, TTF_GetError());
	}
	
	Bitmap* text_bmp = new Bitmap(1, 1);
	SDL_FreeSurface(text_bmp->bitmap);
	text_bmp->bitmap = text_surface;

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
		}
		else if (align == 2) {
			x += rect.width - text_bmp->GetWidth();
		}
	}
	Blit(x, y, text_bmp, src_rect, (int)color.alpha);
	delete text_bmp;
	TTF_CloseFont(ttf_font);

	Changed();
}

////////////////////////////////////////////////////////////
/// Get text size
////////////////////////////////////////////////////////////
Rect Bitmap::GetTextSize(std::string text) {
	unsigned long font_id = rb_iv_get(id, "@font");
	unsigned long name_id = rb_iv_get(font_id, "@name");
	std::string name = FileFinder::FindFont(StringValuePtr(name_id));
	TTF_Font* ttf_font = TTF_OpenFont(name.c_str(), NUM2INT(rb_iv_get(font_id, "@size")));
	if (!ttf_font) {
		rb_raise(ARGSS::AError::id, "couldn't open font %s size %d.\n%s\n", name.c_str(), NUM2INT(rb_iv_get(font_id, "@size")), TTF_GetError());
	}
	int style = 0;
    if (NUM2BOOL(rb_iv_get(font_id, "@bold"))) style |= TTF_STYLE_BOLD;
	if (NUM2BOOL(rb_iv_get(font_id, "@italic"))) style |= TTF_STYLE_ITALIC;
	TTF_SetFontStyle(ttf_font, style);
	
	int w, h;
	if (TTF_SizeUTF8(ttf_font, text.c_str(), &w, &h)) {
		rb_raise(ARGSS::AError::id, "couldn't determine text size for Font(%x).\n%s\n", text.c_str(), font_id, TTF_GetError());
	}
	TTF_CloseFont(ttf_font);
    return Rect(0, 0, w, h);
}

////////////////////////////////////////////////////////////
/// Gradient fill rect
////////////////////////////////////////////////////////////
void Bitmap::GradientFillRect(Rect rect, Color color1, Color color2, bool vertical) {
	// TODO
}

////////////////////////////////////////////////////////////
/// Clear Rect
////////////////////////////////////////////////////////////
void Bitmap::ClearRect(Rect rect) {
	// TODO
}

////////////////////////////////////////////////////////////
/// Blur
////////////////////////////////////////////////////////////
void Bitmap::Blur() {
	// TODO
}

////////////////////////////////////////////////////////////
/// Radial Blur
////////////////////////////////////////////////////////////
void Bitmap::RadialBlur(int angle, int division) {
	// TODO
}

////////////////////////////////////////////////////////////
/// Tone change
////////////////////////////////////////////////////////////
void Bitmap::ToneChange(Tone tone) {
	if (tone.red == 0 && tone.green == 0 && tone.blue == 0 && tone.gray == 0) return;

	SDL_LockSurface(bitmap);

	Uint8 *pixels = (Uint8 *)bitmap->pixels;
	
	const int rbyte = MaskGetByte(bitmap->format->Rmask);
	const int gbyte = MaskGetByte(bitmap->format->Gmask);
	const int bbyte = MaskGetByte(bitmap->format->Bmask);

	if (tone.gray == 0) {
		for (int i = 0; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8 *pixel = pixels;
				pixel[rbyte] = (Uint8)max(min(pixel[rbyte] + tone.red, 255), 0);
				pixel[gbyte] = (Uint8)max(min(pixel[gbyte] + tone.green, 255), 0);
				pixel[bbyte] = (Uint8)max(min(pixel[bbyte] + tone.blue, 255), 0);
				pixels += 4;
			}
		}
	}
	else {
		double factor = (255 - tone.gray) / 255.0;
		double gray;
		for (int i = 0; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8 *pixel = pixels;
				
				gray = pixel[rbyte] * 0.299 + pixel[gbyte] * 0.587 + pixel[bbyte] * 0.114;
				pixel[rbyte] = (Uint8)max(min((pixel[rbyte] - gray) * factor + gray + tone.red + 0.5, 255), 0);
				pixel[gbyte] = (Uint8)max(min((pixel[gbyte] - gray) * factor + gray + tone.green + 0.5, 255), 0);
				pixel[bbyte] = (Uint8)max(min((pixel[bbyte] - gray) * factor + gray + tone.blue + 0.5, 255), 0);
				pixels += 4;
			}
		}
	}
	SDL_UnlockSurface(bitmap);

	Changed();
}

////////////////////////////////////////////////////////////
/// Opacity change
////////////////////////////////////////////////////////////
void Bitmap::OpacityChange(int opacity, int bush_depth) {
	if (opacity >= 255 && bush_depth <= 0) return;

	SDL_LockSurface(bitmap);
	
	Uint8 *pixels = (Uint8 *)bitmap->pixels;
	
	int start_bush = max(GetHeight() - bush_depth, 0);

	const int abyte = MaskGetByte(bitmap->format->Amask);
	
	if (opacity < 255) {
		for (int i = 0; i < start_bush; i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8 *pixel = pixels;
				pixel[abyte] = pixel[abyte] * opacity / 255;
				pixels += 4;
			}
		}
		for (int i = start_bush; i< GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8 *pixel = pixels;
				pixel[abyte] = (pixel[abyte] / 2) * opacity / 255;
				pixels += 4;
			}
		}
	}
	else {
		pixels += start_bush * GetWidth() * 4;
		for (int i = start_bush; i < GetHeight(); i++) {
			for (int j = 0; j < GetWidth(); j++) {
				Uint8 *pixel = pixels;
				pixel[abyte] = pixel[abyte] / 2;
				pixels += 4;
			}
		}
	}
	SDL_UnlockSurface(bitmap);

	Changed();
}

////////////////////////////////////////////////////////////
/// Flip
////////////////////////////////////////////////////////////
void Bitmap::Flip(bool flipx, bool flipy) {
	if (!(flipx || flipy)) return;

	SDL_LockSurface(bitmap);
	
	Bitmap* temp_bmp = new Bitmap(GetWidth(), GetHeight());
	SDL_Surface* temp = temp_bmp->bitmap;

	SDL_LockSurface(temp);
	
	Uint32* srcpixels = (Uint32*)bitmap->pixels;
	Uint32* dstpixels = (Uint32*)temp->pixels;
	
	if (flipx && flipy) {
		long srcpixel = 0;
		long dstpixel = GetWidth() + (GetHeight() - 1) * GetWidth() - 1;
		for(int i = 0; i < GetHeight(); i++) {
			for(int j = 0; j < GetWidth(); j++) {
				dstpixels[dstpixel] = srcpixels[srcpixel];
				
				srcpixel += 1;
				dstpixel -= 1;
			}
		}
	}
	else if (flipx) {
		long srcpixel = 0;
		long dstpixel = GetWidth() - 1;
		for(int i = 0; i < GetHeight(); i++) {
			for(int j = 0; j < GetWidth(); j++) {
				dstpixels[dstpixel] = srcpixels[srcpixel];
				
				srcpixel += 1;
				dstpixel -= 1;
			}
			dstpixel += GetWidth() * 2;
		}
	}
	else if (flipy) {
		dstpixels += (GetHeight() - 1) * GetWidth();
		for(int i = 0; i < GetHeight(); i++) {
			memcpy(dstpixels, srcpixels,  GetWidth() * 4);
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

	Changed();
}

////////////////////////////////////////////////////////////
/// Zoom
////////////////////////////////////////////////////////////
void Bitmap::Zoom(double zoom_x, double zoom_y) {
	if (zoom_x == 1.0 && zoom_y == 1.0) return;

	SDL_LockSurface(bitmap);
	
	int scalew = (int)(GetWidth() * zoom_x);
	int scaleh = (int)(GetHeight() * zoom_y);
	
	Bitmap* nbitmap = new Bitmap(scalew, scaleh);
	SDL_Surface* surface = nbitmap->bitmap;
		
	SDL_LockSurface(surface);
	
	Uint8* srcpixels = (Uint8*)bitmap->pixels;
	Uint8* dstpixels = (Uint8*)surface->pixels;

	int row = GetWidth() * 4;

	for(int yy = 0; yy < surface->h; yy++) {
		int nearest_matchy = (int)(yy / zoom_y) * row;
		for(int xx = 0; xx < surface->w; xx++) {
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

	Changed();
}

////////////////////////////////////////////////////////////
/// Resample
////////////////////////////////////////////////////////////
Bitmap* Bitmap::Resample(int scalew, int scaleh, Rect src_rect) {
	double zoom_x = (double)(scalew) / src_rect.width;
	double zoom_y = (double)(scaleh) / src_rect.height;

	Bitmap* resampled = new Bitmap(scalew, scaleh);
	SDL_Surface* surface = resampled->bitmap;

	SDL_LockSurface(bitmap);
	SDL_LockSurface(surface);
	
	Uint8* srcpixels = (Uint8*)bitmap->pixels;
	Uint8* dstpixels = (Uint8*)surface->pixels;

	int row = GetWidth() * 4;

	for(int yy = 0; yy < scaleh; yy++) {
		int nearest_matchy = (src_rect.y + (int)(yy / zoom_y)) * row;
		for(int xx = 0; xx < scalew; xx++) {
			int nearest_match = nearest_matchy + (src_rect.x + (int)(xx / zoom_x)) * 4;
			dstpixels[0] = srcpixels[nearest_match];
			dstpixels[1] = srcpixels[nearest_match + 1];
			dstpixels[2] = srcpixels[nearest_match + 2];
			dstpixels[3] = srcpixels[nearest_match + 3];
			dstpixels += 4;
		}
	}
	
	SDL_UnlockSurface(bitmap);
	SDL_UnlockSurface(surface);

	return resampled;
}

////////////////////////////////////////////////////////////
/// Rotate
////////////////////////////////////////////////////////////
void Bitmap::Rotate(float angle) {
	while (angle > 360)
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

	for(int i = 0; i < nbitmap->h; i++) {
		for(int j = 0; j < nbitmap->w; j++) {
			int sx = (int)((j + minx) * cosine + (i + miny) * sine); 
			int sy = (int)((i + miny) * cosine - (j + minx) * sine); 
			if (sx >= 0 && sx < bitmap->w && sy >= 0 && sy < bitmap->h) {
				dstpixels[0] = srcpixels[sy * bitmap->w + sx];
			}
			else {
				dstpixels[0] = 0;
			}
			dstpixels++;
		}
	}
	
	SDL_UnlockSurface(nbitmap);
	SDL_FreeSurface(bitmap);
	
	bitmap = nbitmap;
	
	Changed();
}

////////////////////////////////////////////////////////////
/// Get Rect
////////////////////////////////////////////////////////////
Rect Bitmap::GetRect() {
	return Rect(0, 0, GetWidth(), GetHeight());
}

////////////////////////////////////////////////////////////
/// Get Rect
////////////////////////////////////////////////////////////
int Bitmap::MaskGetByte(Uint32 mask) {
	switch (mask)
	{
		case 0xFF000000:
			return 3;
		case 0x00FF0000:
			return 2;
		case 0x0000FF00:
			return 1;
		default:
			return 0;
	}
}
