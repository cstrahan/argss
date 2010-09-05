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
#include <string>
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_font.h"
#include "argss_error.h"
#include "bitmap.h"
#include "rect.h"
#include "color.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ABitmap::id;

////////////////////////////////////////////////////////////
/// ARGSS Bitmap ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::ABitmap::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
	else if (argc == 1) {
		Bitmap::New(self, StringValuePtr(argv[0]));
	} else if (argc == 2) {
		Bitmap::New(self, NUM2INT(argv[0]), NUM2INT(argv[1]));
	}
	else raise_argn(argc, 2);
	rb_iv_set(self, "@font", ARGSS::AFont::New());
	ARGSS::ARuby::AddObject(self);
	return self;
}
VALUE ARGSS::ABitmap::rdispose(VALUE self) {
	if (!Bitmap::IsDisposed(self)) {
		Bitmap::Dispose(self);
		ARGSS::ARuby::RemoveObject(self);
		rb_gc_start();
	}
	return self;
}
VALUE ARGSS::ABitmap::rdisposedQ(VALUE self) {
	return INT2BOOL(Bitmap::IsDisposed(self));
}
VALUE ARGSS::ABitmap::rwidth(VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	return INT2NUM(Bitmap::Get(self)->GetWidth());
}
VALUE ARGSS::ABitmap::rheight(VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	return INT2NUM(Bitmap::Get(self)->GetHeight());
}
VALUE ARGSS::ABitmap::rrect(VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	return Bitmap::Get(self)->GetRect().GetARGSS();
}
VALUE ARGSS::ABitmap::rblt(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc < 4) raise_argn(argc, 4);
	else if (argc > 5) raise_argn(argc, 5);
	ARGSS::ABitmap::CheckDisposed(argv[2]);
	if (argc == 5) {
		Bitmap::Get(self)->Blit(NUM2INT(argv[0]), NUM2INT(argv[1]), Bitmap::Get(argv[2]), Rect(argv[3]), NUM2INT(argv[4]));
	} else {
		Bitmap::Get(self)->Blit(NUM2INT(argv[0]), NUM2INT(argv[1]), Bitmap::Get(argv[2]), Rect(argv[3]), 255);
	}
	return self;
}
VALUE ARGSS::ABitmap::rstretch_blt(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc < 3) raise_argn(argc, 3);
	else if (argc > 4) raise_argn(argc, 4);
	ARGSS::ABitmap::CheckDisposed(argv[1]);
	if (argc == 4) {
		Bitmap::Get(self)->StretchBlit(Rect(argv[0]), Bitmap::Get(argv[1]), Rect(argv[2]), NUM2INT(argv[3]));
	} else {
		Bitmap::Get(self)->StretchBlit(Rect(argv[0]), Bitmap::Get(argv[1]), Rect(argv[2]), 255);
	}
	return self;
}
VALUE ARGSS::ABitmap::rfill_rect(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc < 2) raise_argn(argc, 2);
	else if (argc == 2) {
		Bitmap::Get(self)->FillRect(Rect(argv[0]), Color(argv[1]));
	} else if (argc == 5) {
		Bitmap::Get(self)->FillRect(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])), Color(argv[4]));
	}
	else raise_argn(argc, 5);
	return self;
}
VALUE ARGSS::ABitmap::rclear(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc > 1) raise_argn(argc, 1);
	else if (argc == 1) {
		Bitmap::Get(self)->Clear(Color(argv[0]));
	} else {
		Bitmap::Get(self)->Clear();
	}
	return self;
}
VALUE ARGSS::ABitmap::rget_pixel(VALUE self, VALUE x, VALUE y) {
	ARGSS::ABitmap::CheckDisposed(self);
	return Bitmap::Get(self)->GetPixel(NUM2INT(x), NUM2INT(y)).GetARGSS();
}
VALUE ARGSS::ABitmap::rset_pixel(VALUE self, VALUE x, VALUE y, VALUE color) {
	ARGSS::ABitmap::CheckDisposed(self);
	Bitmap::Get(self)->SetPixel(NUM2INT(x), NUM2INT(y), Color(color));
	return self;
}
VALUE ARGSS::ABitmap::rhue_change(VALUE self, VALUE hue) {
	ARGSS::ABitmap::CheckDisposed(self);
	Bitmap::Get(self)->HueChange(NUM2DBL(hue));
	return self;
}
VALUE ARGSS::ABitmap::rsaturation_change(VALUE self, VALUE saturation) {
	ARGSS::ABitmap::CheckDisposed(self);
	Bitmap::Get(self)->SatChange(NUM2DBL(saturation));
	return self;
}
VALUE ARGSS::ABitmap::rluminance_change(VALUE self, VALUE luminance) {
	ARGSS::ABitmap::CheckDisposed(self);
	Bitmap::Get(self)->LumChange(NUM2DBL(luminance));
	return self;
}
VALUE ARGSS::ABitmap::rhsl_change(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc < 3) raise_argn(argc, 3);
	else if (argc > 4) raise_argn(argc, 4);
	if (argc == 4) {
		Bitmap::Get(self)->HSLChange(NUM2DBL(argv[0]), NUM2DBL(argv[1]), NUM2DBL(argv[2]), Rect(argv[3]));
	} else {
		Bitmap::Get(self)->HSLChange(NUM2DBL(argv[0]), NUM2DBL(argv[1]), NUM2DBL(argv[2]));
	}
	return self;
}
VALUE ARGSS::ABitmap::rdraw_text(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	int align = 0;
	if (argc < 2) raise_argn(argc, 2);
	else if (argc < 4) {
		if (argc == 3) {
			align = NUM2INT(argv[2]);
		}
		Bitmap::Get(self)->TextDraw(Rect(argv[0]), StringValuePtr(argv[1]), align);
	} else if (argc == 4) raise_argn(argc, 3);
	else if (argc < 7) {
		if (argc == 6) {
			align = NUM2INT(argv[5]);
		}
		Bitmap::Get(self)->TextDraw(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])), StringValuePtr(argv[4]), align);
	}
	else raise_argn(argc, 6);
	return self;
}
VALUE ARGSS::ABitmap::rtext_size(VALUE self, VALUE str) {
	ARGSS::ABitmap::CheckDisposed(self);
	return Bitmap::Get(self)->GetTextSize(StringValuePtr(str)).GetARGSS();
}
VALUE ARGSS::ABitmap::rgradient_fill_rect(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc < 3) raise_argn(argc, 3);
	else if (argc < 5) {
		bool vertical = false;
		if (argc == 4) {
			vertical = NUM2BOOL(argv[3]);
		}
	Bitmap::Get(self)->GradientFillRect(Rect(argv[0]), Color(argv[1]), Color(argv[2]), vertical);
	} else if (argc < 6) raise_argn(argc, 6);
	else if (argc < 8) {
		bool vertical = false;
		if (argc == 4) {
			vertical = NUM2BOOL(argv[6]);
		}
		Bitmap::Get(self)->GradientFillRect(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])), Color(argv[4]), Color(argv[5]), vertical);
	}
	else raise_argn(argc, 7);
	return self;
}
VALUE ARGSS::ABitmap::rclear_rect(int argc, VALUE* argv, VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	if (argc < 1) raise_argn(argc, 1);
	if (argc == 1) {
		Bitmap::Get(self)->ClearRect(Rect(argv[0]));
	} else if (argc == 4) {
		Bitmap::Get(self)->ClearRect(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])));
	}
	else raise_argn(argc, 4);
	return self;
}
VALUE ARGSS::ABitmap::rblur(VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	Bitmap::Get(self)->Blur();
	return self;
}
VALUE ARGSS::ABitmap::rradial_blur(VALUE self, VALUE angle, VALUE division) {
	ARGSS::ABitmap::CheckDisposed(self);
	Bitmap::Get(self)->RadialBlur(NUM2INT(angle), NUM2INT(division));
	return self;
}
VALUE ARGSS::ABitmap::rfont(VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	return rb_iv_get(self, "@font");
}
VALUE ARGSS::ABitmap::rfontE(VALUE self, VALUE font) {
	ARGSS::ABitmap::CheckDisposed(self);
	Check_Class(font, ARGSS::AFont::id);
	return rb_iv_set(self, "@font", font);;
}
VALUE ARGSS::ABitmap::rdup(VALUE self) {
	ARGSS::ABitmap::CheckDisposed(self);
	int width = Bitmap::Get(self)->GetWidth();
	int height = Bitmap::Get(self)->GetHeight();
	VALUE args[2] = {INT2NUM(width), INT2NUM(height)};
	VALUE bmp = rb_class_new_instance(2, args, id);
	Bitmap::Get(bmp)->Blit(0, 0, Bitmap::Get(self), Rect(0, 0, width, height), 255);
	return bmp;
}

////////////////////////////////////////////////////////////
/// ARGSS Bitmap initialize
////////////////////////////////////////////////////////////
void ARGSS::ABitmap::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_class("Bitmap", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)rdisposedQ, 0);
	rb_define_method(id, "width", (rubyfunc)rwidth, 0);
	rb_define_method(id, "height", (rubyfunc)rheight, 0);
	rb_define_method(id, "rect", (rubyfunc)rrect, 0);
	rb_define_method(id, "blt", (rubyfunc)rblt, -1);
	rb_define_method(id, "stretch_blt", (rubyfunc)rstretch_blt, -1);
	rb_define_method(id, "fill_rect", (rubyfunc)rfill_rect, -1);
	rb_define_method(id, "clear", (rubyfunc)rclear, -1);
	rb_define_method(id, "get_pixel", (rubyfunc)rget_pixel, 2);
	rb_define_method(id, "set_pixel", (rubyfunc)rset_pixel, 3);
	rb_define_method(id, "hue_change", (rubyfunc)rhue_change, 1);
	rb_define_method(id, "saturation_change", (rubyfunc)rsaturation_change, 1);
	rb_define_method(id, "luminance_change", (rubyfunc)rluminance_change, 1);
	rb_define_method(id, "hsl_change", (rubyfunc)rhsl_change, -1);
	rb_define_method(id, "draw_text", (rubyfunc)rdraw_text, -1);
	rb_define_method(id, "text_size", (rubyfunc)rtext_size, 1);
	rb_define_method(id, "gradient_fill_rect", (rubyfunc)rgradient_fill_rect, -1);
	rb_define_method(id, "clear_rect", (rubyfunc)rclear_rect, -1);
	rb_define_method(id, "blur", (rubyfunc)rblur, 0);
	rb_define_method(id, "radial_blur", (rubyfunc)rradial_blur, 2);
	rb_define_method(id, "font", (rubyfunc)rfont, 0);
	rb_define_method(id, "font=", (rubyfunc)rfontE, 1);
	rb_define_method(id, "clone", (rubyfunc)rdup, 0);
	rb_define_method(id, "dup", (rubyfunc)rdup, 0);
}

////////////////////////////////////////////////////////////
/// Check if bitmap isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::ABitmap::CheckDisposed(VALUE self) {
	if (Bitmap::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed bitmap <%i>", self << 1);
	}
}
