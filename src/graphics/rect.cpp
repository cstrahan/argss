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
#include "graphics/rect.h"
#include "argss/classes/arect.h"

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Rect::Rect() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}
Rect::Rect(VALUE rect) {
	x = NUM2INT(rb_iv_get(rect, "@x"));
	y = NUM2INT(rb_iv_get(rect, "@y"));
	width = NUM2INT(rb_iv_get(rect, "@width"));
	height = NUM2INT(rb_iv_get(rect, "@height"));
}
Rect::Rect(int ix, int iy, int iwidth, int iheight) {
	x = ix;
	y = iy;
	width = iwidth;
	height = iheight;
}
////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Rect::~Rect() { }

////////////////////////////////////////////////////////////
/// != operator
////////////////////////////////////////////////////////////
bool Rect::operator!=(const Rect &other) const {
	return x != other.x || y != other.y || width != other.width || height != other.height;
}

////////////////////////////////////////////////////////////
/// Set rect values
////////////////////////////////////////////////////////////
void Rect::Set(int nx, int ny, int nwidth, int nheight) {
	x = nx;
	y = ny;
	width = nwidth;
	height = nheight;
}

////////////////////////////////////////////////////////////
/// Get ARGSS rect
////////////////////////////////////////////////////////////
VALUE Rect::GetARGSS() {
	VALUE args[4] = {INT2NUM(x), INT2NUM(y), INT2NUM(width), INT2NUM(height)};
	return rb_class_new_instance(4, args, ARGSS::ARect::id);
}
////////////////////////////////////////////////////////////
/// Adjust Rect
////////////////////////////////////////////////////////////
void Rect::Adjust(int awidth, int aheight) {
	if (x < 0) {
		width += x;
		x = 0;
	}
	if (y < 0) {
		height += y;
		y = 0;
	}
	if (x < awidth && y < aheight) {
		if (awidth < x + width) width = awidth - x;
		if (aheight < y + height) height = aheight - y;
	}
}

////////////////////////////////////////////////////////////
/// Adjust Rect
////////////////////////////////////////////////////////////
bool Rect::IsOutOfBounds(int awidth, int aheight) {
	if (width <= 0 || height <= 0) return true;
	if (x >= awidth || y >= aheight) return true;
	if (x + width <= 0 || y + height <= 0) return true;
	return false;
}
