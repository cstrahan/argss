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
#include "argss_viewport.h"
#include "argss_rect.h"
#include "argss_color.h"
#include "argss_tone.h"
#include "argss_error.h"
#include "viewport.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::AViewport::id;

////////////////////////////////////////////////////////////
/// ARGSS Viewport ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_viewport_initialize(int argc, VALUE *argv, VALUE self) {
	ARGSS::ARuby::AddObject(self);
	return self;
}
static VALUE argss_viewport_dispose(VALUE self) {
	ARGSS::AViewport::Check(self);
	Viewport::Get(self)->Dispose();
	ARGSS::ARuby::RemoveObject(self);
    return self;
}
static VALUE argss_viewport_disposedQ(VALUE self) {
	return INT2BOOL(Viewport::IsDisposed(self));
}
static VALUE argss_viewport_flash(VALUE self, VALUE color, VALUE duration) {
    ARGSS::AViewport::Check(self);
	if (color == Qnil) {
		Viewport::Get(self)->Flash(NUM2INT(duration));
	}
	else {
		Viewport::Get(self)->Flash(Color(color), NUM2INT(duration));
	}
    return Qnil;
}
static VALUE argss_viewport_update(VALUE self) {
    ARGSS::AViewport::Check(self);
    Viewport::Get(self)->Update();
    return Qnil;
}
static VALUE argss_viewport_rect(VALUE self) {
    ARGSS::AViewport::Check(self);
    return rb_iv_get(self, "@rect");
}
static VALUE argss_viewport_rectE(VALUE self, VALUE rect) {
    ARGSS::AViewport::Check(self);
	Check_Class(rect, ARGSS::ARect::id);
    Viewport::Get(self)->SetRect(rect);
    return rb_iv_set(self, "@rect", rect);
}
static VALUE argss_viewport_visible(VALUE self) {
    ARGSS::AViewport::Check(self);
	return rb_iv_get(self, "@visible");
}
static VALUE argss_viewport_visibleE(VALUE self, VALUE visible) {
    ARGSS::AViewport::Check(self);
	Viewport::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
static VALUE argss_viewport_z(VALUE self) {
    ARGSS::AViewport::Check(self);
	return rb_iv_get(self, "@z");
}
static VALUE argss_viewport_zE(VALUE self, VALUE z) {
    ARGSS::AViewport::Check(self);
	Viewport::Get(self)->SetZ(NUM2INT(z));
	return rb_iv_set(self, "@z", z);
}
static VALUE argss_viewport_ox(VALUE self) {
    ARGSS::AViewport::Check(self);
	return rb_iv_get(self, "@ox");
}
static VALUE argss_viewport_oxE(VALUE self, VALUE ox) {
    ARGSS::AViewport::Check(self);
	Viewport::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
static VALUE argss_viewport_oy(VALUE self) {
    ARGSS::AViewport::Check(self);
	return rb_iv_get(self, "@oy");
}
static VALUE argss_viewport_oyE(VALUE self, VALUE oy) {
    ARGSS::AViewport::Check(self);
	Viewport::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}
static VALUE argss_viewport_color(VALUE self) {
    ARGSS::AViewport::Check(self);
	return rb_iv_get(self, "@color");
}
static VALUE argss_viewport_colorE(VALUE self, VALUE color) {
    ARGSS::AViewport::Check(self);
	Check_Class(color, ARGSS::AColor::id);
	Viewport::Get(self)->SetColor(color);
	return rb_iv_set(self, "@color", color);
}
static VALUE argss_viewport_tone(VALUE self) {
    ARGSS::AViewport::Check(self);
	return rb_iv_get(self, "@tone");
}
static VALUE argss_viewport_toneE(VALUE self, VALUE tone) {
    ARGSS::AViewport::Check(self);
	Check_Class(tone, ARGSS::ATone::id);
	Viewport::Get(self)->SetTone(tone);
	return rb_iv_set(self, "@tone", tone);
}

////////////////////////////////////////////////////////////
/// ARGSS Viewport initialize
////////////////////////////////////////////////////////////
void ARGSS::AViewport::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Viewport", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)argss_viewport_initialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)argss_viewport_dispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)argss_viewport_disposedQ, 0);
	rb_define_method(id, "flash", (rubyfunc)argss_viewport_flash, 2);
	rb_define_method(id, "update", (rubyfunc)argss_viewport_update, 0);
	rb_define_method(id, "rect", (rubyfunc)argss_viewport_rect, 0);
	rb_define_method(id, "rect=", (rubyfunc)argss_viewport_rectE, 1);
	rb_define_method(id, "visible", (rubyfunc)argss_viewport_visible, 0);
	rb_define_method(id, "visible=", (rubyfunc)argss_viewport_visibleE, 1);
	rb_define_method(id, "z", (rubyfunc)argss_viewport_z, 0);
	rb_define_method(id, "z=", (rubyfunc)argss_viewport_zE, 1);
	rb_define_method(id, "ox", (rubyfunc)argss_viewport_ox, 0);
	rb_define_method(id, "ox=", (rubyfunc)argss_viewport_oxE, 1);
	rb_define_method(id, "oy", (rubyfunc)argss_viewport_oy, 0);
	rb_define_method(id, "oy=", (rubyfunc)argss_viewport_oyE, 1);
	rb_define_method(id, "color", (rubyfunc)argss_viewport_color, 0);
	rb_define_method(id, "color=", (rubyfunc)argss_viewport_colorE, 1);
	rb_define_method(id, "tone", (rubyfunc)argss_viewport_tone, 0);
	rb_define_method(id, "tone=", (rubyfunc)argss_viewport_toneE, 1);
}

////////////////////////////////////////////////////////////
/// Check if plane isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::AViewport::Check(VALUE self) {
    if (Viewport::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed viewport <%i>", self);
    }
}
