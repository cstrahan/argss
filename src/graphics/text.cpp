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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "graphics/text.h"
#include "output.h"
#include "tools/filefinder.h"
#include "argss/classes/aerror.h"
#include FT_GLYPH_H

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
FT_Library Text::library;
std::map<std::string, FT_Face> Text::fonts;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Text::Init() {
	FT_Error err = FT_Init_FreeType(&library);
	if (err) {
		Output::Error("ARGSS couldn't initialize freetype library.\n%d\n", err);
	}
}

////////////////////////////////////////////////////////////
/// Draw text
////////////////////////////////////////////////////////////
Bitmap* Text::Draw(std::string text, std::string font, Color color, int size, bool bold, bool italic, bool shadow) {
	FT_Face face = GetFont(font);

	FT_Error err;

	err = FT_Set_Pixel_Sizes(face, size, size);
	if (err) {
		rb_raise(ARGSS::AError::id, "couldn't set font(%s) size %d.\n%d\n", font.c_str(), size, err);
	}

	err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	if (err) {
		rb_raise(ARGSS::AError::id, "couldn't set font(%s) charmap.\n%d\n", font.c_str(), err);
	}

	FT_Matrix matrix;
	matrix.xx = 0x10000;
	matrix.xy = 0;
	matrix.yx = 0;
	matrix.yy = 0x10000;

	FT_Vector pen;
	pen.x = 0;
	pen.y = 0;

	std::vector<FT_BitmapGlyph> glyphs;

	for (unsigned int i = 0; i < text.length(); i++) {
		FT_Set_Transform(face, &matrix, &pen);

		err = FT_Load_Char(face, text[i], FT_LOAD_TARGET_NORMAL);
		if (err) {
			rb_raise(ARGSS::AError::id, "couldn't load font(%s) char '%s'.\n%d\n", font.c_str(), text[i], err);
		}

		FT_Glyph glyph;
		err = FT_Get_Glyph(face->glyph, &glyph);
		if (err) {
			rb_raise(ARGSS::AError::id, "couldn't get font(%s) char '%s'.\n%d\n", font.c_str(), text[i], err);
		}

		FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);

		glyphs.push_back((FT_BitmapGlyph)glyph);

		pen.x += face->glyph->advance.x;
	}

	int width = 0;
	int height = 0;

	for (unsigned int i = 0; i < glyphs.size(); i++) {
		if (width < glyphs[i]->bitmap.width + glyphs[i]->left) width = glyphs[i]->bitmap.width + glyphs[i]->left;
		if (height < glyphs[i]->bitmap.rows + glyphs[i]->top) height = glyphs[i]->bitmap.rows + glyphs[i]->top;
	}

	int min_y = height;
	for (unsigned int i = 0; i < glyphs.size(); i++) {
		if (min_y > height - glyphs[i]->top) min_y = height - glyphs[i]->top;
	}
	min_y = (int)(((float)min_y + 0.5f) / 2.0f);

	Bitmap* text_bmp = new Bitmap(width, height);
	Uint8* dst_pixels = (Uint8*)text_bmp->GetPixels();
	for (unsigned int i = 0; i < glyphs.size(); i++) {

		long glyph_pixel = 0;

		int left = glyphs[i]->left;
		int top = height - glyphs[i]->top;

		for (int y = 0; y < glyphs[i]->bitmap.rows; y++) {
			for (int x = 0; x < glyphs[i]->bitmap.width; x++) {
				if (top + y - min_y < 0 || left + x < 0) continue;
				if (top + y - min_y > height || left + x > width) continue;
				if ((((left + x) + (top + y - min_y) * width) * 4) >= width * height * 4) continue;

				long pixel = ((left + x) + (top + y - min_y) * width) * 4;
				dst_pixels[pixel + 0] = (Uint8)color.red;
				dst_pixels[pixel + 1] = (Uint8)color.green;
				dst_pixels[pixel + 2] = (Uint8)color.blue;
				dst_pixels[pixel + 3] = glyphs[i]->bitmap.buffer[x + y * glyphs[i]->bitmap.width];
			}
			glyph_pixel += glyphs[i]->bitmap.pitch;
		}
	}

	for (unsigned int i = 0; i < glyphs.size(); i++) {
		FT_Done_Glyph((FT_Glyph)glyphs[i]);
	}

	return text_bmp;
}

////////////////////////////////////////////////////////////
/// Text rect size
////////////////////////////////////////////////////////////
Rect Text::RectSize(std::string text, std::string font, int size) {
	FT_Face face = GetFont(font);

	FT_Error err;

	err = FT_Set_Pixel_Sizes(face, size, size);
	if (err) {
		rb_raise(ARGSS::AError::id, "couldn't set font(%s) size %d.\n%d\n", font.c_str(), size, err);
	}

	err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	if (err) {
		rb_raise(ARGSS::AError::id, "couldn't set font(%s) charmap.\n%d\n", font.c_str(), err);
	}

	int width = 0;
	int height = 0;

	for (unsigned int i = 0; i < text.length(); i++) {
		err = FT_Load_Char(face, text[i], FT_LOAD_TARGET_NORMAL);
		if (err) {
			rb_raise(ARGSS::AError::id, "couldn't load font(%s) char '%s'.\n%d\n", font.c_str(), text[i], err);
		}

		FT_Glyph glyph;
		err = FT_Get_Glyph(face->glyph, &glyph);
		if (err) {
			rb_raise(ARGSS::AError::id, "couldn't get font(%s) char '%s'.\n%d\n", font.c_str(), text[i], err);
		}

		FT_BBox bbox;
		FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &bbox);

		width += bbox.xMax - bbox.xMin;
		if (height < bbox.yMax - bbox.yMin) height = bbox.yMax - bbox.yMin;

		FT_Done_Glyph(glyph);
	}

	return Rect(0, 0, width, height);
}

////////////////////////////////////////////////////////////
/// Get font
////////////////////////////////////////////////////////////
FT_Face Text::GetFont(std::string name) {
	std::string path = FileFinder::FindFont(name);

	if (fonts.count(path) == 0) {
		FT_Error err = FT_New_Face(library, path.c_str(), 0, &fonts[path]);
		if (err) {
			rb_raise(ARGSS::AError::id, "couldn't load font %s.\n%d\n", name.c_str(), err);
		}
	}
	return fonts[path];
}
