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
#include "argss_sprite.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_tone.h"
#include "argss_rect.h"
#include "argss_error.h"
#include "sprite.h"
#include "color.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ASprite::id;

////////////////////////////////////////////////////////////
/// ARGSS Sprite ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_sprite_initialize(int argc, VALUE *argv, VALUE self) {
    if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
    }
    else if (argc == 0) {
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
	ARGSS::ARuby::AddObject(self);
    return self;
}
static VALUE argss_sprite_dispose(VALUE self) {
    ARGSS::ASprite::Check(self);
	Sprite::Get(self)->Dispose();
	ARGSS::ARuby::RemoveObject(self);
    return self;
}
static VALUE argss_sprite_disposedQ(VALUE self) {
    return INT2BOOL(Sprite::IsDisposed(self));
}
static VALUE argss_sprite_flash(VALUE self, VALUE color, VALUE duration) {
    ARGSS::ASprite::Check(self);
	if (color == Qnil) {
		Sprite::Get(self)->Flash(NUM2INT(duration));
	}
	else {
		Sprite::Get(self)->Flash(Color(color), NUM2INT(duration));
	}
    return Qnil;
}
static VALUE argss_sprite_update(VALUE self) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->Update();
    return Qnil;
}
static VALUE argss_sprite_width(VALUE self) {
    ARGSS::ASprite::Check(self);
	return rb_iv_get(rb_iv_get(self, "@src_rect"), "@width");
}
static VALUE argss_sprite_height(VALUE self) {
    ARGSS::ASprite::Check(self);
	return rb_iv_get(rb_iv_get(self, "@src_rect"), "@height");
}
static VALUE argss_sprite_viewport(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@viewport");
}
static VALUE argss_sprite_viewportE(VALUE self, VALUE viewport) {
    ARGSS::ASprite::Check(self);
    Check_Classes_N(viewport, ARGSS::AViewport::id);
	if (viewport != Qnil) ARGSS::AViewport::Check(viewport);
	Sprite::Get(self)->SetViewport(viewport);
    return rb_iv_set(self, "@viewport", viewport);
}
static VALUE argss_sprite_bitmap(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@bitmap");
}
static VALUE argss_sprite_bitmapE(VALUE self, VALUE bitmap) {
    ARGSS::ASprite::Check(self);
	Check_Classes_N(bitmap, ARGSS::ABitmap::id);
	if (bitmap != Qnil) {
		VALUE src_rect = rb_iv_get(self, "@src_rect");
		rb_iv_set(src_rect, "@x", INT2NUM(0));
		rb_iv_set(src_rect, "@y", INT2NUM(0));
		if (!Bitmap::IsDisposed(bitmap)) {
			rb_iv_set(src_rect, "@width", INT2NUM(Bitmap::Get(bitmap)->GetWidth()));
			rb_iv_set(src_rect, "@height", INT2NUM(Bitmap::Get(bitmap)->GetHeight()));
		}
		else {
			rb_iv_set(src_rect, "@width", INT2NUM(0));
			rb_iv_set(src_rect, "@height", INT2NUM(0));
		}
	}
	Sprite::Get(self)->SetBitmap(bitmap);
    return rb_iv_set(self, "@bitmap", bitmap);
}
static VALUE argss_sprite_src_rect(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@src_rect");
}
static VALUE argss_sprite_src_rectE(VALUE self, VALUE src_rect) {
    ARGSS::ASprite::Check(self);
	Check_Class(src_rect, ARGSS::ARect::id);
    Sprite::Get(self)->SetSrcRect(src_rect);
    return rb_iv_set(self, "@src_rect", src_rect);
}
static VALUE argss_sprite_visible(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@visible");
}
static VALUE argss_sprite_visibleE(VALUE self, VALUE visible) {
    ARGSS::ASprite::Check(self);
	Sprite::Get(self)->SetVisible(NUM2BOOL(visible));
    return rb_iv_set(self, "@visible", visible);
}
static VALUE argss_sprite_x(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_funcall(rb_iv_get(self, "@x"), rb_intern("to_i"), 0, 0);
}
static VALUE argss_sprite_fx(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_funcall(rb_iv_get(self, "@x"), rb_intern("to_f"), 0, 0);
}
static VALUE argss_sprite_xE(VALUE self, VALUE x) {
    ARGSS::ASprite::Check(self);
	Sprite::Get(self)->SetX(NUM2INT(x));
    return rb_iv_set(self, "@x", x);
}
static VALUE argss_sprite_y(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_funcall(rb_iv_get(self, "@y"), rb_intern("to_i"), 0, 0);
}
static VALUE argss_sprite_fy(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_funcall(rb_iv_get(self, "@y"), rb_intern("to_f"), 0, 0);
}
static VALUE argss_sprite_yE(VALUE self, VALUE y) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetY(NUM2INT(y));
    return rb_iv_set(self, "@y", y);
}
static VALUE argss_sprite_z(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@z");
}
static VALUE argss_sprite_zE(VALUE self, VALUE z) {
    ARGSS::ASprite::Check(self);
	Sprite::Get(self)->SetZ(NUM2INT(z));
    return rb_iv_set(self, "@z", rb_funcall(z, rb_intern("to_i"), 0, 0));
}
static VALUE argss_sprite_ox(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@ox");
}
static VALUE argss_sprite_oxE(VALUE self, VALUE ox) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetOx(NUM2INT(ox));
    return rb_iv_set(self, "@ox", ox);
}
static VALUE argss_sprite_oy(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@oy");
}
static VALUE argss_sprite_oyE(VALUE self, VALUE oy) {
    ARGSS::ASprite::Check(self);
	Sprite::Get(self)->SetOy(NUM2INT(oy));
    return rb_iv_set(self, "@oy", oy);
}
static VALUE argss_sprite_zoom_x(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@zoom_x");
}
static VALUE argss_sprite_zoom_xE(VALUE self, VALUE zoom_x) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetZoomX(NUM2DBL(zoom_x));
    return rb_iv_set(self, "@zoom_x", rb_Float(zoom_x));
}
static VALUE argss_sprite_zoom_y(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@zoom_y");
}
static VALUE argss_sprite_zoom_yE(VALUE self, VALUE zoom_y) {
    ARGSS::ASprite::Check(self);
	Sprite::Get(self)->SetZoomY(NUM2DBL(zoom_y));
    return rb_iv_set(self, "@zoom_y", rb_Float(zoom_y));
}
static VALUE argss_sprite_angle(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@angle");
}
static VALUE argss_sprite_angleE(VALUE self, VALUE angle) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetAngle(NUM2DBL(angle));
    return rb_iv_set(self, "@angle", rb_Float(angle));
}
static VALUE argss_sprite_mirror(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@flipx");
}
static VALUE argss_sprite_mirrorE(VALUE self, VALUE mirror) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetFlipX(NUM2BOOL(mirror));
    return rb_iv_set(self, "@flipx", mirror);
}
static VALUE argss_sprite_flipx(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@flipx");
}
static VALUE argss_sprite_flipxE(VALUE self, VALUE flipx) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetFlipX(NUM2BOOL(flipx));
    return rb_iv_set(self, "@flipx", flipx);
}
static VALUE argss_sprite_flipy(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@flipy");
}
static VALUE argss_sprite_flipyE(VALUE self, VALUE flipy) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetFlipY(NUM2BOOL(flipy));
    return rb_iv_set(self, "@flipy", flipy);
}
static VALUE argss_sprite_bush_depth(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@bush_depth");
}
static VALUE argss_sprite_bush_depthE(VALUE self, VALUE bush_depth) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetBushDepth(NUM2INT(bush_depth));
    return rb_iv_set(self, "@bush_depth", bush_depth);
}
static VALUE argss_sprite_opacity(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@opacity");
}
static VALUE argss_sprite_opacityE(VALUE self, VALUE opacity) {
    ARGSS::ASprite::Check(self);
    Sprite::Get(self)->SetOpacity(NUM2INT(opacity));
    return rb_iv_set(self, "@opacity", opacity);
}
static VALUE argss_sprite_blend_type(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@blend_type");
}
static VALUE argss_sprite_blend_typeE(VALUE self, VALUE blend_type) {
    ARGSS::ASprite::Check(self);
	int type = NUM2INT(blend_type);
	if (type < 0 || type > 3) type = 0;
	Sprite::Get(self)->SetBlendType(type);
    return rb_iv_set(self, "@blend_type", INT2NUM(type));
}
static VALUE argss_sprite_color(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@color");
}
static VALUE argss_sprite_colorE(VALUE self, VALUE color) {
    ARGSS::ASprite::Check(self);
    Check_Class(color, ARGSS::AColor::id);
    Sprite::Get(self)->SetColor(color);
    return rb_iv_set(self, "@color", color);
}
static VALUE argss_sprite_tone(VALUE self) {
    ARGSS::ASprite::Check(self);
    return rb_iv_get(self, "@tone");
}
static VALUE argss_sprite_toneE(VALUE self, VALUE tone) {
    ARGSS::ASprite::Check(self);
	Check_Class(tone, ARGSS::ATone::id);
	Sprite::Get(self)->SetTone(tone);
    return rb_iv_set(self, "@tone", tone);
}

////////////////////////////////////////////////////////////
/// ARGSS Sprite initialize
////////////////////////////////////////////////////////////
void ARGSS::ASprite::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Sprite", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)argss_sprite_initialize, -1);
    rb_define_method(id, "dispose", (rubyfunc)argss_sprite_dispose, 0);
    rb_define_method(id, "disposed?", (rubyfunc)argss_sprite_disposedQ, 0);
    rb_define_method(id, "flash", (rubyfunc)argss_sprite_flash, 2);
    rb_define_method(id, "update", (rubyfunc)argss_sprite_update, 0);
	rb_define_method(id, "width", (rubyfunc)argss_sprite_width, 0);
	rb_define_method(id, "height", (rubyfunc)argss_sprite_height, 0);
    rb_define_method(id, "viewport", (rubyfunc)argss_sprite_viewport, 0);
    rb_define_method(id, "viewport=", (rubyfunc)argss_sprite_viewportE, 1);
    rb_define_method(id, "bitmap", (rubyfunc)argss_sprite_bitmap, 0);
    rb_define_method(id, "bitmap=", (rubyfunc)argss_sprite_bitmapE, 1);
    rb_define_method(id, "src_rect", (rubyfunc)argss_sprite_src_rect, 0);
    rb_define_method(id, "src_rect=", (rubyfunc)argss_sprite_src_rectE, 1);
    rb_define_method(id, "visible", (rubyfunc)argss_sprite_visible, 0);
    rb_define_method(id, "visible=", (rubyfunc)argss_sprite_visibleE, 1);
    rb_define_method(id, "x", (rubyfunc)argss_sprite_x, 0);
    rb_define_method(id, "fx", (rubyfunc)argss_sprite_fx, 0);
    rb_define_method(id, "x=", (rubyfunc)argss_sprite_xE, 1);
    rb_define_method(id, "y", (rubyfunc)argss_sprite_y, 0);
    rb_define_method(id, "fy", (rubyfunc)argss_sprite_fy, 0);
    rb_define_method(id, "y=", (rubyfunc)argss_sprite_yE, 1);
    rb_define_method(id, "z", (rubyfunc)argss_sprite_z, 0);
    rb_define_method(id, "z=", (rubyfunc)argss_sprite_zE, 1);
    rb_define_method(id, "ox", (rubyfunc)argss_sprite_ox, 0);
    rb_define_method(id, "ox=", (rubyfunc)argss_sprite_oxE, 1);
    rb_define_method(id, "oy", (rubyfunc)argss_sprite_oy, 0);
    rb_define_method(id, "oy=", (rubyfunc)argss_sprite_oyE, 1);
    rb_define_method(id, "zoom_x", (rubyfunc)argss_sprite_zoom_x, 0);
    rb_define_method(id, "zoom_x=", (rubyfunc)argss_sprite_zoom_xE, 1);
    rb_define_method(id, "zoom_y", (rubyfunc)argss_sprite_zoom_y, 0);
    rb_define_method(id, "zoom_y=", (rubyfunc)argss_sprite_zoom_yE, 1);
    rb_define_method(id, "angle", (rubyfunc)argss_sprite_angle, 0);
    rb_define_method(id, "angle=", (rubyfunc)argss_sprite_angleE, 1);
    rb_define_method(id, "mirror", (rubyfunc)argss_sprite_mirror, 0);
    rb_define_method(id, "mirror=", (rubyfunc)argss_sprite_mirrorE, 1);
    rb_define_method(id, "flipx", (rubyfunc)argss_sprite_flipx, 0);
    rb_define_method(id, "flipx=", (rubyfunc)argss_sprite_flipxE, 1);
    rb_define_method(id, "flipy", (rubyfunc)argss_sprite_flipy, 0);
    rb_define_method(id, "flipy=", (rubyfunc)argss_sprite_flipyE, 1);
    rb_define_method(id, "bush_depth", (rubyfunc)argss_sprite_bush_depth, 0);
    rb_define_method(id, "bush_depth=", (rubyfunc)argss_sprite_bush_depthE, 1);
    rb_define_method(id, "opacity", (rubyfunc)argss_sprite_opacity, 0);
    rb_define_method(id, "opacity=", (rubyfunc)argss_sprite_opacityE, 1);
    rb_define_method(id, "blend_type", (rubyfunc)argss_sprite_blend_type, 0);
    rb_define_method(id, "blend_type=", (rubyfunc)argss_sprite_blend_typeE, 1);
    rb_define_method(id, "color", (rubyfunc)argss_sprite_color, 0);
    rb_define_method(id, "color=", (rubyfunc)argss_sprite_colorE, 1);
    rb_define_method(id, "tone", (rubyfunc)argss_sprite_tone, 0);
    rb_define_method(id, "tone=", (rubyfunc)argss_sprite_toneE, 1);
}

////////////////////////////////////////////////////////////
/// Check if sprite isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::ASprite::Check(VALUE self) {
    if (Sprite::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed sprite <%i>", self);
    }
}
