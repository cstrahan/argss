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
#include "argss_plane.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_tone.h"
#include "argss_error.h"
#include "plane.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::APlane::id;

////////////////////////////////////////////////////////////
/// ARGSS Plane ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_plane_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
    }
    else if (argc == 0) {
        rb_iv_set(self, "@viewport", Qnil);
    }
    else raise_argn(argc, 1);
	rb_iv_set(self, "@bitmap", Qnil);
    rb_iv_set(self, "@visible", Qtrue);
    rb_iv_set(self, "@z", INT2NUM(0));
    rb_iv_set(self, "@ox", INT2NUM(0));
	rb_iv_set(self, "@oy", INT2NUM(0));
	rb_iv_set(self, "@zoom_x", rb_float_new(1.0f));
    rb_iv_set(self, "@zoom_y", rb_float_new(1.0f));
	rb_iv_set(self, "@opacity", INT2NUM(255));
    rb_iv_set(self, "@blend_type", INT2NUM(0));
	rb_iv_set(self, "@color", ARGSS::AColor::New());
    rb_iv_set(self, "@tone", ARGSS::ATone::New());
	Plane::New(self);
	return self;
}
static VALUE argss_plane_dispose(VALUE self) {
	ARGSS::APlane::Check(self);
	Plane::Get(self)->Dispose();
    return self;
}
static VALUE argss_plane_disposedQ(VALUE self) {
	return INT2BOOL(Plane::IsDisposed(self));
}
static VALUE argss_plane_viewport(VALUE self) {
	ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@viewport");
}
static VALUE argss_plane_viewportE(VALUE self, VALUE viewport) {
    ARGSS::APlane::Check(self);
	Check_Classes_N(viewport, ARGSS::AViewport::id);
	Plane::Get(self)->SetViewport(viewport);
	return rb_iv_set(self, "@viewport", viewport);
}
static VALUE argss_plane_bitmap(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@bitmap");
}
static VALUE argss_plane_bitmapE(VALUE self, VALUE bitmap) {
    ARGSS::APlane::Check(self);
	Check_Classes_N(bitmap, ARGSS::ABitmap::id);
	Plane::Get(self)->SetBitmap(bitmap);
	return rb_iv_set(self, "@bitmap", bitmap);
}
static VALUE argss_plane_visible(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@visible");
}
static VALUE argss_plane_visibleE(VALUE self, VALUE visible) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
static VALUE argss_plane_z(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@z");
}
static VALUE argss_plane_zE(VALUE self, VALUE z) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetZ(NUM2INT(z));
	return rb_iv_set(self, "@z", z);
}
static VALUE argss_plane_ox(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@ox");
}
static VALUE argss_plane_oxE(VALUE self, VALUE ox) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
static VALUE argss_plane_oy(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@oy");
}
static VALUE argss_plane_oyE(VALUE self, VALUE oy) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}
static VALUE argss_plane_zoom_x(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@zoom_x");
}
static VALUE argss_plane_zoom_xE(VALUE self, VALUE zoom_x) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetZoomX(NUM2DBL(zoom_x));
	return rb_iv_set(self, "@zoom_x", zoom_x);
}
static VALUE argss_plane_zoom_y(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@zoom_y");
}
static VALUE argss_plane_zoom_yE(VALUE self, VALUE zoom_y) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetZoomY(NUM2DBL(zoom_y));
	return rb_iv_set(self, "@zoom_y", zoom_y);
}
static VALUE argss_plane_opacity(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@opacity");
}
static VALUE argss_plane_opacityE(VALUE self, VALUE opacity) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetOpacity(NUM2INT(opacity));
	return rb_iv_set(self, "@opacity", opacity);
}
static VALUE argss_plane_blend_type(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@blend_type");
}
static VALUE argss_plane_blend_typeE(VALUE self, VALUE blend_type) {
    ARGSS::APlane::Check(self);
	Plane::Get(self)->SetBlendType(NUM2INT(blend_type));
	return rb_iv_set(self, "@blend_type", blend_type);
}
static VALUE argss_plane_color(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@color");
}
static VALUE argss_plane_colorE(VALUE self, VALUE color) {
    ARGSS::APlane::Check(self);
	Check_Class(color, ARGSS::AColor::id);
	Plane::Get(self)->SetColor(color);
	return rb_iv_set(self, "@color", color);
}
static VALUE argss_plane_tone(VALUE self) {
    ARGSS::APlane::Check(self);
	return rb_iv_get(self, "@tone");
}
static VALUE argss_plane_toneE(VALUE self, VALUE tone) {
    ARGSS::APlane::Check(self);
	Check_Class(tone, ARGSS::ATone::id);
	Plane::Get(self)->SetTone(tone);
	return rb_iv_set(self, "@tone", tone);
}

////////////////////////////////////////////////////////////
/// ARGSS Plane initialize
////////////////////////////////////////////////////////////
void ARGSS::APlane::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Plane", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)argss_plane_initialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)argss_plane_dispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)argss_plane_disposedQ, 0);
	rb_define_method(id, "viewport", (rubyfunc)argss_plane_viewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)argss_plane_viewportE, 1);
	rb_define_method(id, "bitmap", (rubyfunc)argss_plane_bitmap, 0);
	rb_define_method(id, "bitmap=", (rubyfunc)argss_plane_bitmapE, 1);
	rb_define_method(id, "visible", (rubyfunc)argss_plane_visible, 0);
	rb_define_method(id, "visible=", (rubyfunc)argss_plane_visibleE, 1);
	rb_define_method(id, "z=", (rubyfunc)argss_plane_z, 0);
	rb_define_method(id, "z", (rubyfunc)argss_plane_zE, 1);
	rb_define_method(id, "ox", (rubyfunc)argss_plane_ox, 0);
	rb_define_method(id, "ox=", (rubyfunc)argss_plane_oxE, 1);
	rb_define_method(id, "oy", (rubyfunc)argss_plane_oy, 0);
	rb_define_method(id, "oy=", (rubyfunc)argss_plane_oyE, 1);
	rb_define_method(id, "zoom_x", (rubyfunc)argss_plane_zoom_x, 0);
	rb_define_method(id, "zoom_x=", (rubyfunc)argss_plane_zoom_xE, 1);
	rb_define_method(id, "zoom_y", (rubyfunc)argss_plane_zoom_y, 0);
	rb_define_method(id, "zoom_y=", (rubyfunc)argss_plane_zoom_yE, 1);
	rb_define_method(id, "opacity", (rubyfunc)argss_plane_opacity, 0);
	rb_define_method(id, "opacity=", (rubyfunc)argss_plane_opacityE, 1);
	rb_define_method(id, "blend_type", (rubyfunc)argss_plane_blend_type, 0);
	rb_define_method(id, "blend_type=", (rubyfunc)argss_plane_blend_typeE, 1);
	rb_define_method(id, "color", (rubyfunc)argss_plane_color, 0);
	rb_define_method(id, "color=", (rubyfunc)argss_plane_colorE, 1);
	rb_define_method(id, "tone", (rubyfunc)argss_plane_tone, 0);
	rb_define_method(id, "tone=", (rubyfunc)argss_plane_toneE, 1);
}

////////////////////////////////////////////////////////////
/// Check if plane isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::APlane::Check(VALUE self) {
	if (Plane::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed plane <%i>", self);
    }
}
