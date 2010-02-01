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
#include <string>
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_font.h"
#include "argss_error.h"
#include "bitmap.h"
#include "rect.h"
#include "color.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ABitmap::id;

////////////////////////////////////////////////////////////
/// ARGSS Bitmap ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_bitmap_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
    else if (argc == 1) {
		Bitmap::New(self, StringValuePtr(argv[0]));
    }
    else if (argc == 2) {
		Bitmap::New(self, NUM2INT(argv[0]), NUM2INT(argv[1]));
    }
    else raise_argn(argc, 2);
	rb_iv_set(self, "@font", ARGSS::AFont::New());
	ARGSS::ARuby::AddObject(self);
    return self;
}
static VALUE argss_bitmap_dispose(VALUE self) {
    ARGSS::ABitmap::Check(self);
	Bitmap::Dispose(self);
	ARGSS::ARuby::RemoveObject(self);
	rb_funcall(rb_const_get(rb_cObject, rb_intern("GC")), rb_intern("start"), 0);
    return self;
}
static VALUE argss_bitmap_disposedQ(VALUE self) {
    return INT2BOOL(Bitmap::IsDisposed(self));
}
static VALUE argss_bitmap_width(VALUE self) {
    ARGSS::ABitmap::Check(self);
    return INT2NUM(Bitmap::Get(self)->GetWidth());
}
static VALUE argss_bitmap_height(VALUE self) {
    ARGSS::ABitmap::Check(self);
    return INT2NUM(Bitmap::Get(self)->GetHeight());
}
static VALUE argss_bitmap_rect(VALUE self) {
    ARGSS::ABitmap::Check(self);
	return Bitmap::Get(self)->GetRect().GetARGSS();
}
static VALUE argss_bitmap_blt(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if (argc < 4) raise_argn(argc, 4);
    else if (argc > 5) raise_argn(argc, 5);
    ARGSS::ABitmap::Check(argv[2]);
    if (argc == 5) {
		Bitmap::Get(self)->Blit(NUM2INT(argv[0]), NUM2INT(argv[1]), Bitmap::Get(argv[2]), Rect(argv[3]), NUM2INT(argv[4]));
    }
	else {
		Bitmap::Get(self)->Blit(NUM2INT(argv[0]), NUM2INT(argv[1]), Bitmap::Get(argv[2]), Rect(argv[3]), 255);
	}
    return self;
}
static VALUE argss_bitmap_stretch_blt(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if (argc < 3) raise_argn(argc, 3);
    else if (argc > 4) raise_argn(argc, 4);
    ARGSS::ABitmap::Check(argv[1]);
    if (argc == 4) {
		Bitmap::Get(self)->StretchBlit(Rect(argv[0]), Bitmap::Get(argv[1]), Rect(argv[2]), NUM2INT(argv[3]));
    }
	else {
		Bitmap::Get(self)->StretchBlit(Rect(argv[0]), Bitmap::Get(argv[1]), Rect(argv[2]), 255);
	}
    return self;
}
static VALUE argss_bitmap_fill_rect(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if (argc < 2) raise_argn(argc, 2);
    else if (argc == 2) {
		Bitmap::Get(self)->FillRect(Rect(argv[0]), Color(argv[1]));
    }
    else if (argc == 5) {
		Bitmap::Get(self)->FillRect(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])), Color(argv[4]));
    }
    else raise_argn(argc, 5);
    return self;
}
static VALUE argss_bitmap_clear(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if (argc > 1) raise_argn(argc, 1);
    else if (argc == 1) {
        Bitmap::Get(self)->Clear(Color(argv[0]));
    }
	else {
		Bitmap::Get(self)->Clear();
	}
    return self;
}
static VALUE argss_bitmap_get_pixel(VALUE self, VALUE x, VALUE y) {
    ARGSS::ABitmap::Check(self);
	return Bitmap::Get(self)->GetPixel(NUM2INT(x), NUM2INT(y)).GetARGSS();
}
static VALUE argss_bitmap_set_pixel(VALUE self, VALUE x, VALUE y, VALUE color) {
    ARGSS::ABitmap::Check(self);
	Bitmap::Get(self)->SetPixel(NUM2INT(x), NUM2INT(y), Color(color));
    return self;
}
static VALUE argss_bitmap_hue_change(VALUE self, VALUE hue) {
    ARGSS::ABitmap::Check(self);
    Bitmap::Get(self)->HueChange(NUM2DBL(hue));
    return self;
}
static VALUE argss_bitmap_saturation_change(VALUE self, VALUE saturation) {
    ARGSS::ABitmap::Check(self);
    Bitmap::Get(self)->SatChange(NUM2DBL(saturation));
    return self;
}
static VALUE argss_bitmap_luminance_change(VALUE self, VALUE luminance) {
    ARGSS::ABitmap::Check(self);
    Bitmap::Get(self)->LumChange(NUM2DBL(luminance));
    return self;
}
static VALUE argss_bitmap_hsl_change(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if (argc < 3) raise_argn(argc, 3);
    else if (argc > 4) raise_argn(argc, 4);
    if (argc == 4) {
        Bitmap::Get(self)->HSLChange(NUM2DBL(argv[0]), NUM2DBL(argv[1]), NUM2DBL(argv[2]), Rect(argv[3]));
    }
	else {
		Bitmap::Get(self)->HSLChange(NUM2DBL(argv[0]), NUM2DBL(argv[1]), NUM2DBL(argv[2]));
	}
    return self;
}
static VALUE argss_bitmap_draw_text(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
	int align = 0;
	if (argc < 2) raise_argn(argc, 2);
	else if (argc < 4) {
		if (argc == 3) {
			align = NUM2INT(argv[2]);
		}
		Bitmap::Get(self)->DrawText(Rect(argv[0]), StringValuePtr(argv[1]), align);
	}
	else if (argc == 4) raise_argn(argc, 3);
	else if (argc < 7) {
		if(argc == 6) {
			align = NUM2INT(argv[5]);
		}
		Bitmap::Get(self)->DrawText(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])), StringValuePtr(argv[4]), align);
	}
	else raise_argn(argc, 6);
    return self;
}
static VALUE argss_bitmap_text_size(VALUE self, VALUE str) {
    ARGSS::ABitmap::Check(self);
	return Bitmap::Get(self)->GetTextSize(StringValuePtr(str)).GetARGSS();
}
static VALUE argss_bitmap_gradient_fill_rect(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if (argc < 3) raise_argn(argc, 3);
    else if (argc < 5) {
		bool vertical = false;
		if (argc == 4) {
			vertical = NUM2BOOL(argv[3]);
		}
	Bitmap::Get(self)->GradientFillRect(Rect(argv[0]), Color(argv[1]), Color(argv[2]), vertical);
    }
	else if (argc < 6) raise_argn(argc, 6);
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
static VALUE argss_bitmap_clear_rect(int argc, VALUE *argv, VALUE self) {
    ARGSS::ABitmap::Check(self);
    if(argc < 1) raise_argn(argc, 1);
    if(argc == 1) {
		Bitmap::Get(self)->ClearRect(Rect(argv[0]));
    }
    else if (argc == 4) {
		Bitmap::Get(self)->ClearRect(Rect(NUM2INT(argv[0]), NUM2INT(argv[1]), NUM2INT(argv[2]), NUM2INT(argv[3])));
    }
    else raise_argn(argc, 4);
    return self;
}
static VALUE argss_bitmap_blur(VALUE self) {
	ARGSS::ABitmap::Check(self);
	Bitmap::Get(self)->Blur();
	return self;
}
static VALUE argss_bitmap_radial_blur(VALUE self, VALUE angle, VALUE division) {
	ARGSS::ABitmap::Check(self);
	Bitmap::Get(self)->RadialBlur(NUM2INT(angle), NUM2INT(division));
	return self;
}
static VALUE argss_bitmap_font(VALUE self) {
	ARGSS::ABitmap::Check(self);
    return rb_iv_get(self, "@font");
}
static VALUE argss_bitmap_fontE(VALUE self, VALUE font) {
	ARGSS::ABitmap::Check(self);
	Check_Class(font, ARGSS::AFont::id);
    return rb_iv_set(self, "@font", font);;
}

////////////////////////////////////////////////////////////
/// ARGSS Bitmap initialize
////////////////////////////////////////////////////////////
void ARGSS::ABitmap::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Bitmap", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)argss_bitmap_initialize, -1);
    rb_define_method(id, "dispose", (rubyfunc)argss_bitmap_dispose, 0);
    rb_define_method(id, "disposed?", (rubyfunc)argss_bitmap_disposedQ, 0);
    rb_define_method(id, "width", (rubyfunc)argss_bitmap_width, 0);
    rb_define_method(id, "height", (rubyfunc)argss_bitmap_height, 0);
    rb_define_method(id, "rect", (rubyfunc)argss_bitmap_rect, 0);
    rb_define_method(id, "blt", (rubyfunc)argss_bitmap_blt, -1);
    rb_define_method(id, "stretch_blt", (rubyfunc)argss_bitmap_stretch_blt, -1);
    rb_define_method(id, "fill_rect", (rubyfunc)argss_bitmap_fill_rect, -1);
    rb_define_method(id, "clear", (rubyfunc)argss_bitmap_clear, -1);
    rb_define_method(id, "get_pixel", (rubyfunc)argss_bitmap_get_pixel, 2);
    rb_define_method(id, "set_pixel", (rubyfunc)argss_bitmap_set_pixel, 3);
    rb_define_method(id, "hue_change", (rubyfunc)argss_bitmap_hue_change, 1);
    rb_define_method(id, "saturation_change", (rubyfunc)argss_bitmap_saturation_change, 1);
    rb_define_method(id, "luminance_change", (rubyfunc)argss_bitmap_luminance_change, 1);
    rb_define_method(id, "hsl_change", (rubyfunc)argss_bitmap_hsl_change, -1);
    rb_define_method(id, "draw_text", (rubyfunc)argss_bitmap_draw_text, -1);
    rb_define_method(id, "text_size", (rubyfunc)argss_bitmap_text_size, 1);
	rb_define_method(id, "gradient_fill_rect", (rubyfunc)argss_bitmap_gradient_fill_rect, -1);
	rb_define_method(id, "clear_rect", (rubyfunc)argss_bitmap_clear_rect, -1);
	rb_define_method(id, "blur", (rubyfunc)argss_bitmap_blur, 0);
	rb_define_method(id, "radial_blur", (rubyfunc)argss_bitmap_radial_blur, 2);
	rb_define_method(id, "font", (rubyfunc)argss_bitmap_font, 0);
	rb_define_method(id, "font=", (rubyfunc)argss_bitmap_fontE, 1);
}

////////////////////////////////////////////////////////////
/// Check if bitmap isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::ABitmap::Check(VALUE self) {
    if (Bitmap::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed bitmap <%i>", self);
    }
}
