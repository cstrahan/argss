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
#include "argss_plane.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_tone.h"
#include "argss_error.h"
#include "plane.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::APlane::id;

////////////////////////////////////////////////////////////
/// ARGSS Plane ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::APlane::rinitialize(int argc, VALUE *argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
	} else if (argc == 0) {
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
	ARGSS::ARuby::AddObject(self);
	return self;
}
VALUE ARGSS::APlane::rdispose(VALUE self) {
	if (!Plane::IsDisposed(self)) {
		ARGSS::APlane::CheckDisposed(self);
		Plane::Dispose(self);
		ARGSS::ARuby::RemoveObject(self);
		rb_gc_start();
	}
	return self;
}
VALUE ARGSS::APlane::rdisposedQ(VALUE self) {
	return INT2BOOL(Plane::IsDisposed(self));
}
VALUE ARGSS::APlane::rviewport(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@viewport");
}
VALUE ARGSS::APlane::rviewportE(VALUE self, VALUE viewport) {
	ARGSS::APlane::CheckDisposed(self);
	Check_Classes_N(viewport, ARGSS::AViewport::id);
	Plane::Get(self)->SetViewport(viewport);
	return rb_iv_set(self, "@viewport", viewport);
}
VALUE ARGSS::APlane::rbitmap(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@bitmap");
}
VALUE ARGSS::APlane::rbitmapE(VALUE self, VALUE bitmap) {
	ARGSS::APlane::CheckDisposed(self);
	Check_Classes_N(bitmap, ARGSS::ABitmap::id);
	Plane::Get(self)->SetBitmap(bitmap);
	return rb_iv_set(self, "@bitmap", bitmap);
}
VALUE ARGSS::APlane::rvisible(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@visible");
}
VALUE ARGSS::APlane::rvisibleE(VALUE self, VALUE visible) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
VALUE ARGSS::APlane::rz(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@z");
}
VALUE ARGSS::APlane::rzE(VALUE self, VALUE z) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetZ(NUM2INT(z));
	return rb_iv_set(self, "@z", z);
}
VALUE ARGSS::APlane::rox(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@ox");
}
VALUE ARGSS::APlane::roxE(VALUE self, VALUE ox) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
VALUE ARGSS::APlane::roy(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@oy");
}
VALUE ARGSS::APlane::royE(VALUE self, VALUE oy) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}
VALUE ARGSS::APlane::rzoom_x(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@zoom_x");
}
VALUE ARGSS::APlane::rzoom_xE(VALUE self, VALUE zoom_x) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetZoomX((float)NUM2DBL(zoom_x));
	return rb_iv_set(self, "@zoom_x", zoom_x);
}
VALUE ARGSS::APlane::rzoom_y(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@zoom_y");
}
VALUE ARGSS::APlane::rzoom_yE(VALUE self, VALUE zoom_y) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetZoomY((float)NUM2DBL(zoom_y));
	return rb_iv_set(self, "@zoom_y", zoom_y);
}
VALUE ARGSS::APlane::ropacity(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@opacity");
}
VALUE ARGSS::APlane::ropacityE(VALUE self, VALUE opacity) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetOpacity(NUM2INT(opacity));
	return rb_iv_set(self, "@opacity", opacity);
}
VALUE ARGSS::APlane::rblend_type(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@blend_type");
}
VALUE ARGSS::APlane::rblend_typeE(VALUE self, VALUE blend_type) {
	ARGSS::APlane::CheckDisposed(self);
	Plane::Get(self)->SetBlendType(NUM2INT(blend_type));
	return rb_iv_set(self, "@blend_type", blend_type);
}
VALUE ARGSS::APlane::rcolor(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@color");
}
VALUE ARGSS::APlane::rcolorE(VALUE self, VALUE color) {
	ARGSS::APlane::CheckDisposed(self);
	Check_Class(color, ARGSS::AColor::id);
	Plane::Get(self)->SetColor(color);
	return rb_iv_set(self, "@color", color);
}
VALUE ARGSS::APlane::rtone(VALUE self) {
	ARGSS::APlane::CheckDisposed(self);
	return rb_iv_get(self, "@tone");
}
VALUE ARGSS::APlane::rtoneE(VALUE self, VALUE tone) {
	ARGSS::APlane::CheckDisposed(self);
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
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)rdisposedQ, 0);
	rb_define_method(id, "viewport", (rubyfunc)rviewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)rviewportE, 1);
	rb_define_method(id, "bitmap", (rubyfunc)rbitmap, 0);
	rb_define_method(id, "bitmap=", (rubyfunc)rbitmapE, 1);
	rb_define_method(id, "visible", (rubyfunc)rvisible, 0);
	rb_define_method(id, "visible=", (rubyfunc)rvisibleE, 1);
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
	rb_define_method(id, "opacity", (rubyfunc)ropacity, 0);
	rb_define_method(id, "opacity=", (rubyfunc)ropacityE, 1);
	rb_define_method(id, "blend_type", (rubyfunc)rblend_type, 0);
	rb_define_method(id, "blend_type=", (rubyfunc)rblend_typeE, 1);
	rb_define_method(id, "color", (rubyfunc)rcolor, 0);
	rb_define_method(id, "color=", (rubyfunc)rcolorE, 1);
	rb_define_method(id, "tone", (rubyfunc)rtone, 0);
	rb_define_method(id, "tone=", (rubyfunc)rtoneE, 1);
}

////////////////////////////////////////////////////////////
/// Check if plane isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::APlane::CheckDisposed(VALUE self) {
	if (Plane::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed plane <%i>", self);
	}
}
