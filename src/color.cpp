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

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "color.h"
#include "argss_color.h"

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Color::Color() {
	red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}
Color::Color(VALUE color) {
	red = NUM2DBL(rb_iv_get(color, "@red"));
    green = NUM2DBL(rb_iv_get(color, "@green"));
    blue = NUM2DBL(rb_iv_get(color, "@blue"));
    alpha = NUM2DBL(rb_iv_get(color, "@alpha"));
}
Color::Color(int ired, int igreen, int iblue, int ialpha) {
	red = ired;
    green = igreen;
    blue = iblue;
    alpha = ialpha;
}
Color::Color(Uint32 color, SDL_PixelFormat* format) {
	Uint8 r, g, b, a;
	SDL_GetRGBA(color, format, &r, &g, &b, &a);
	red = r;
    green = g;
    blue = b;
    alpha = a;
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Color::~Color() { }

////////////////////////////////////////////////////////////
/// Set
////////////////////////////////////////////////////////////
void Color::Set(VALUE color) {
	red = NUM2DBL(rb_iv_get(color, "@red"));
    green = NUM2DBL(rb_iv_get(color, "@green"));
    blue = NUM2DBL(rb_iv_get(color, "@blue"));
    alpha = NUM2DBL(rb_iv_get(color, "@alpha"));
}

////////////////////////////////////////////////////////////
/// Get ARGSS
////////////////////////////////////////////////////////////
unsigned long Color::GetARGSS() {
    VALUE args[4] = {rb_float_new(red), rb_float_new(green), rb_float_new(blue), rb_float_new(alpha)};
	return rb_class_new_instance(4, args, ARGSS::AColor::id);
}

////////////////////////////////////////////////////////////
/// Get Uint32
////////////////////////////////////////////////////////////
Uint32 Color::GetUint32(SDL_PixelFormat* format) {
	return SDL_MapRGBA(format, (Uint8)red, (Uint8)green, (Uint8)blue, (Uint8)alpha);
}

////////////////////////////////////////////////////////////
/// Static Get color
////////////////////////////////////////////////////////////
SDL_Color Color::Get() {
	SDL_Color c = {(int)red, (int)green, (int)blue, (int)alpha};
	return c;
}

////////////////////////////////////////////////////////////
/// Static Get color
////////////////////////////////////////////////////////////
SDL_Color Color::Get(VALUE color) {
	SDL_Color c = {NUM2INT(rb_iv_get(color, "@red")),
					NUM2INT(rb_iv_get(color, "@green")),
					NUM2INT(rb_iv_get(color, "@blue")),
					NUM2INT(rb_iv_get(color, "@alpha"))};
	return c;
}

////////////////////////////////////////////////////////////
/// Static Get ARGSS color
////////////////////////////////////////////////////////////
VALUE Color::GetARGSS(SDL_Color color) {
    VALUE args[4] = {rb_float_new(color.r), rb_float_new(color.g), rb_float_new(color.b), rb_float_new(color.unused)};
	return rb_class_new_instance(4, args, ARGSS::AColor::id);
}

////////////////////////////////////////////////////////////
/// Static Get Uint32 color
////////////////////////////////////////////////////////////
Uint32 Color::GetUint32(VALUE color, SDL_PixelFormat* format) {
	return SDL_MapRGBA(format,
						NUM2INT(rb_iv_get(color, "@red")),
						NUM2INT(rb_iv_get(color, "@green")),
						NUM2INT(rb_iv_get(color, "@blue")),
						NUM2INT(rb_iv_get(color, "@alpha")));
}
Uint32 Color::GetUint32(SDL_Color color, SDL_PixelFormat* format) {
	return SDL_MapRGBA(format, color.r, color.g, color.b, color.unused);
}
