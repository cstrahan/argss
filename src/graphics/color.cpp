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
#include "graphics/color.h"
#include "argss/classes/acolor.h"

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Color::Color() {
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;
	alpha = 0.0f;
}
Color::Color(VALUE color) {
	red = (float)NUM2DBL(rb_iv_get(color, "@red"));
	green = (float)NUM2DBL(rb_iv_get(color, "@green"));
	blue = (float)NUM2DBL(rb_iv_get(color, "@blue"));
	alpha = (float)NUM2DBL(rb_iv_get(color, "@alpha"));
}
Color::Color(int ired, int igreen, int iblue, int ialpha) {
	red = (float)ired;
	green = (float)igreen;
	blue = (float)iblue;
	alpha = (float)ialpha;
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Color::~Color() { }

////////////////////////////////////////////////////////////
/// Set
////////////////////////////////////////////////////////////
void Color::Set(VALUE color) {
	red = (float)NUM2DBL(rb_iv_get(color, "@red"));
	green = (float)NUM2DBL(rb_iv_get(color, "@green"));
	blue = (float)NUM2DBL(rb_iv_get(color, "@blue"));
	alpha = (float)NUM2DBL(rb_iv_get(color, "@alpha"));
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
Uint32 Color::GetUint32() {
	return ((Uint8)red) + (((Uint8)green) << 8) + (((Uint8)blue) << 16) + (((Uint8)alpha) << 24);
}

////////////////////////////////////////////////////////////
/// Static create Color from Uint32
////////////////////////////////////////////////////////////
Color Color::NewUint32(Uint32 color) {
	int r = (color & 0x000000ff);
	int g = (color & 0x0000ff00) >> 8;
	int b = (color & 0x00ff0000) >> 16;
	int a = (color & 0xff000000) >> 24;
	return Color(r, g, b, a);
}
