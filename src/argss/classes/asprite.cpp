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
#include <string>
#include "argss/classes/asprite.h"
#include "argss/classes/abitmap.h"
#include "argss/classes/acolor.h"
#include "argss/classes/aerror.h"
#include "argss/classes/arect.h"
#include "argss/classes/atone.h"
#include "argss/classes/aviewport.h"
#include "graphics/color.h"
#include "graphics/sprite.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::ASprite::id;

///////////////////////////////////////////////////////////
// ARGSS Sprite instance methods
///////////////////////////////////////////////////////////
VALUE ARGSS::ASprite::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
	} else if (argc == 0) {
		rb_iv_set(self, "@viewport", Qnil);
	}
	else raise_argn(argc, 1);
	rb_iv_set(self, "@bitmap", Qnil);
	rb_iv_set(self, "@src_rect", ARGSS::ARect::New(0, 0, 0, 0));
	rb_iv_set(self, "@visible", Qtrue);
	rb_iv_set(self, "@x", INT2NUM(0));
	rb_iv_set(self, "@y", INT2NUM(0));
	rb_iv_set(self, "@z", INT2NUM(0));
	rb_iv_set(self, "@ox", INT2NUM(0));
	rb_iv_set(self, "@oy", INT2NUM(0));
	rb_iv_set(self, "@zoom_x", rb_float_new(1.0f));
	rb_iv_set(self, "@zoom_y", rb_float_new(1.0f));
	rb_iv_set(self, "@angle", rb_float_new(0.0f));
	rb_iv_set(self, "@flipx", Qfalse);
	rb_iv_set(self, "@flipy", Qfalse);
	rb_iv_set(self, "@bush_depth", INT2NUM(0));
	rb_iv_set(self, "@opacity", INT2NUM(255));
	rb_iv_set(self, "@blend_type", INT2NUM(0));
	rb_iv_set(self, "@color", ARGSS::AColor::New());
	rb_iv_set(self, "@tone", ARGSS::ATone::New());
	Sprite::New(self);
	ARuby::AddObject(self);
	return self;
}
VALUE ARGSS::ASprite::rdispose(VALUE self) {
	if (!Sprite::IsDisposed(self)) {
		Sprite::Dispose(self);
		ARuby::RemoveObject(self);
	}
	return self;
}
VALUE ARGSS::ASprite::rdisposedQ(VALUE self) {
	return BOOL2NUM(Sprite::IsDisposed(self));
}
VALUE ARGSS::ASprite::rflash(VALUE self, VALUE color, VALUE duration) {
	ARGSS::ASprite::CheckDisposed(self);
	if (color == Qnil) {
		Sprite::Get(self)->Flash(NUM2INT(duration));
	} else {
		Sprite::Get(self)->Flash(Color(color), NUM2INT(duration));
	}
	return Qnil;
}
VALUE ARGSS::ASprite::rupdate(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->Update();
	return Qnil;
}
VALUE ARGSS::ASprite::rwidth(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(rb_iv_get(self, "@src_rect"), "@width");
}
VALUE ARGSS::ASprite::rheight(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(rb_iv_get(self, "@src_rect"), "@height");
}
VALUE ARGSS::ASprite::rviewport(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@viewport");
}
VALUE ARGSS::ASprite::rviewportE(VALUE self, VALUE viewport) {
	ARGSS::ASprite::CheckDisposed(self);
	Check_Classes_N(viewport, ARGSS::AViewport::id);
	if (viewport != Qnil) ARGSS::AViewport::CheckDisposed(viewport);
	Sprite::Get(self)->SetViewport(viewport);
	return rb_iv_set(self, "@viewport", viewport);
}
VALUE ARGSS::ASprite::rbitmap(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@bitmap");
}
VALUE ARGSS::ASprite::rbitmapE(VALUE self, VALUE bitmap) {
	ARGSS::ASprite::CheckDisposed(self);
	Check_Classes_N(bitmap, ARGSS::ABitmap::id);
	if (bitmap != Qnil) {
		VALUE src_rect = rb_iv_get(self, "@src_rect");
		rb_iv_set(src_rect, "@x", INT2NUM(0));
		rb_iv_set(src_rect, "@y", INT2NUM(0));
		if (!Bitmap::IsDisposed(bitmap)) {
			rb_iv_set(src_rect, "@width", INT2NUM(Bitmap::Get(bitmap)->GetWidth()));
			rb_iv_set(src_rect, "@height", INT2NUM(Bitmap::Get(bitmap)->GetHeight()));
		} else {
			rb_iv_set(src_rect, "@width", INT2NUM(0));
			rb_iv_set(src_rect, "@height", INT2NUM(0));
		}
	}
	Sprite::Get(self)->SetBitmap(bitmap);
	return rb_iv_set(self, "@bitmap", bitmap);
}
VALUE ARGSS::ASprite::rsrc_rect(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@src_rect");
}
VALUE ARGSS::ASprite::rsrc_rectE(VALUE self, VALUE src_rect) {
	ARGSS::ASprite::CheckDisposed(self);
	Check_Class(src_rect, ARGSS::ARect::id);
	Sprite::Get(self)->SetSrcRect(src_rect);
	return rb_iv_set(self, "@src_rect", src_rect);
}
VALUE ARGSS::ASprite::rvisible(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@visible");
}
VALUE ARGSS::ASprite::rvisibleE(VALUE self, VALUE visible) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
VALUE ARGSS::ASprite::rx(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_to_int(rb_iv_get(self, "@x"));
}
VALUE ARGSS::ASprite::rfx(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_Float(rb_iv_get(self, "@x"));
}
VALUE ARGSS::ASprite::rxE(VALUE self, VALUE x) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetX(NUM2INT(x));
	return rb_iv_set(self, "@x", x);
}
VALUE ARGSS::ASprite::ry(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_to_int(rb_iv_get(self, "@y"));
}
VALUE ARGSS::ASprite::rfy(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_Float(rb_iv_get(self, "@y"));
}
VALUE ARGSS::ASprite::ryE(VALUE self, VALUE y) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetY(NUM2INT(y));
	return rb_iv_set(self, "@y", y);
}
VALUE ARGSS::ASprite::rz(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@z");
}
VALUE ARGSS::ASprite::rzE(VALUE self, VALUE z) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetZ(NUM2INT(z));
	return rb_iv_set(self, "@z", rb_to_int(z));
}
VALUE ARGSS::ASprite::rox(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@ox");
}
VALUE ARGSS::ASprite::roxE(VALUE self, VALUE ox) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
VALUE ARGSS::ASprite::roy(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@oy");
}
VALUE ARGSS::ASprite::royE(VALUE self, VALUE oy) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}
VALUE ARGSS::ASprite::rzoom_x(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@zoom_x");
}
VALUE ARGSS::ASprite::rzoom_xE(VALUE self, VALUE zoom_x) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetZoomX((float)NUM2DBL(zoom_x));
	return rb_iv_set(self, "@zoom_x", rb_Float(zoom_x));
}
VALUE ARGSS::ASprite::rzoom_y(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@zoom_y");
}
VALUE ARGSS::ASprite::rzoom_yE(VALUE self, VALUE zoom_y) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetZoomY((float)NUM2DBL(zoom_y));
	return rb_iv_set(self, "@zoom_y", rb_Float(zoom_y));
}
VALUE ARGSS::ASprite::rangle(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@angle");
}
VALUE ARGSS::ASprite::rangleE(VALUE self, VALUE angle) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetAngle((float)NUM2DBL(angle));
	return rb_iv_set(self, "@angle", rb_Float(angle));
}
VALUE ARGSS::ASprite::rmirror(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@flipx");
}
VALUE ARGSS::ASprite::rmirrorE(VALUE self, VALUE mirror) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetFlipX(NUM2BOOL(mirror));
	return rb_iv_set(self, "@flipx", mirror);
}
VALUE ARGSS::ASprite::rflipx(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@flipx");
}
VALUE ARGSS::ASprite::rflipxE(VALUE self, VALUE flipx) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetFlipX(NUM2BOOL(flipx));
	return rb_iv_set(self, "@flipx", flipx);
}
VALUE ARGSS::ASprite::rflipy(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@flipy");
}
VALUE ARGSS::ASprite::rflipyE(VALUE self, VALUE flipy) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetFlipY(NUM2BOOL(flipy));
	return rb_iv_set(self, "@flipy", flipy);
}
VALUE ARGSS::ASprite::rbush_depth(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@bush_depth");
}
VALUE ARGSS::ASprite::rbush_depthE(VALUE self, VALUE bush_depth) {
	ARGSS::ASprite::CheckDisposed(self);
	Sprite::Get(self)->SetBushDepth(NUM2INT(bush_depth));
	return rb_iv_set(self, "@bush_depth", bush_depth);
}
VALUE ARGSS::ASprite::ropacity(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@opacity");
}
VALUE ARGSS::ASprite::ropacityE(VALUE self, VALUE opacity) {
	ARGSS::ASprite::CheckDisposed(self);
	int opacity_temp = NUM2INT(opacity);
	if (opacity_temp < 0) opacity_temp = 0;
	else if (opacity_temp > 255) opacity_temp = 255;
	Sprite::Get(self)->SetOpacity(opacity_temp);
	return rb_iv_set(self, "@opacity", INT2NUM(opacity_temp));
}
VALUE ARGSS::ASprite::rblend_type(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@blend_type");
}
VALUE ARGSS::ASprite::rblend_typeE(VALUE self, VALUE blend_type) {
	ARGSS::ASprite::CheckDisposed(self);
	int type = NUM2INT(blend_type);
	if (type < 0 || type > 3) type = 0;
	Sprite::Get(self)->SetBlendType(type);
	return rb_iv_set(self, "@blend_type", INT2NUM(type));
}
VALUE ARGSS::ASprite::rcolor(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@color");
}
VALUE ARGSS::ASprite::rcolorE(VALUE self, VALUE color) {
	ARGSS::ASprite::CheckDisposed(self);
	Check_Class(color, ARGSS::AColor::id);
	Sprite::Get(self)->SetColor(color);
	return rb_iv_set(self, "@color", color);
}
VALUE ARGSS::ASprite::rtone(VALUE self) {
	ARGSS::ASprite::CheckDisposed(self);
	return rb_iv_get(self, "@tone");
}
VALUE ARGSS::ASprite::rtoneE(VALUE self, VALUE tone) {
	ARGSS::ASprite::CheckDisposed(self);
	Check_Class(tone, ARGSS::ATone::id);
	Sprite::Get(self)->SetTone(tone);
	return rb_iv_set(self, "@tone", tone);
}

///////////////////////////////////////////////////////////
// ARGSS Sprite initialize
///////////////////////////////////////////////////////////
void ARGSS::ASprite::Init() {
	id = rb_define_class("Sprite", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)rdisposedQ, 0);
	rb_define_method(id, "flash", (rubyfunc)rflash, 2);
	rb_define_method(id, "update", (rubyfunc)rupdate, 0);
	rb_define_method(id, "width", (rubyfunc)rwidth, 0);
	rb_define_method(id, "height", (rubyfunc)rheight, 0);
	rb_define_method(id, "viewport", (rubyfunc)rviewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)rviewportE, 1);
	rb_define_method(id, "bitmap", (rubyfunc)rbitmap, 0);
	rb_define_method(id, "bitmap=", (rubyfunc)rbitmapE, 1);
	rb_define_method(id, "src_rect", (rubyfunc)rsrc_rect, 0);
	rb_define_method(id, "src_rect=", (rubyfunc)rsrc_rectE, 1);
	rb_define_method(id, "visible", (rubyfunc)rvisible, 0);
	rb_define_method(id, "visible=", (rubyfunc)rvisibleE, 1);
	rb_define_method(id, "x", (rubyfunc)rx, 0);
	rb_define_method(id, "fx", (rubyfunc)rfx, 0);
	rb_define_method(id, "x=", (rubyfunc)rxE, 1);
	rb_define_method(id, "y", (rubyfunc)ry, 0);
	rb_define_method(id, "fy", (rubyfunc)rfy, 0);
	rb_define_method(id, "y=", (rubyfunc)ryE, 1);
	rb_define_method(id, "z", (rubyfunc)rz, 0);
	rb_define_method(id, "z=", (rubyfunc)rzE, 1);
	rb_define_method(id, "ox", (rubyfunc)rox, 0);
	rb_define_method(id, "ox=", (rubyfunc)roxE, 1);
	rb_define_method(id, "oy", (rubyfunc)roy, 0);
	rb_define_method(id, "oy=", (rubyfunc)royE, 1);
	rb_define_method(id, "zoom_x", (rubyfunc)rzoom_x, 0);
	rb_define_method(id, "zoom_x=", (rubyfunc)rzoom_xE, 1);
	rb_define_method(id, "zoom_y", (rubyfunc)rzoom_y, 0);
	rb_define_method(id, "zoom_y=", (rubyfunc)rzoom_yE, 1);
	rb_define_method(id, "angle", (rubyfunc)rangle, 0);
	rb_define_method(id, "angle=", (rubyfunc)rangleE, 1);
	rb_define_method(id, "mirror", (rubyfunc)rmirror, 0);
	rb_define_method(id, "mirror=", (rubyfunc)rmirrorE, 1);
	rb_define_method(id, "flipx", (rubyfunc)rflipx, 0);
	rb_define_method(id, "flipx=", (rubyfunc)rflipxE, 1);
	rb_define_method(id, "flipy", (rubyfunc)rflipy, 0);
	rb_define_method(id, "flipy=", (rubyfunc)rflipyE, 1);
	rb_define_method(id, "bush_depth", (rubyfunc)rbush_depth, 0);
	rb_define_method(id, "bush_depth=", (rubyfunc)rbush_depthE, 1);
	rb_define_method(id, "opacity", (rubyfunc)ropacity, 0);
	rb_define_method(id, "opacity=", (rubyfunc)ropacityE, 1);
	rb_define_method(id, "blend_type", (rubyfunc)rblend_type, 0);
	rb_define_method(id, "blend_type=", (rubyfunc)rblend_typeE, 1);
	rb_define_method(id, "color", (rubyfunc)rcolor, 0);
	rb_define_method(id, "color=", (rubyfunc)rcolorE, 1);
	rb_define_method(id, "tone", (rubyfunc)rtone, 0);
	rb_define_method(id, "tone=", (rubyfunc)rtoneE, 1);
}

///////////////////////////////////////////////////////////
// CheckDisposed
///////////////////////////////////////////////////////////
void ARGSS::ASprite::CheckDisposed(VALUE id) {
	if (Sprite::IsDisposed(id)) {
		rb_raise(ARGSS::AError::id, "disposed sprite <%i>", id);
	}
}
