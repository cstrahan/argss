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
#include "argss/classes/aviewport.h"
#include "argss/classes/arect.h"
#include "argss/classes/acolor.h"
#include "argss/classes/atone.h"
#include "argss/classes/aerror.h"
#include "graphics/viewport.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::AViewport::id;

////////////////////////////////////////////////////////////
/// ARGSS Viewport ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::AViewport::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
	else if (argc > 1 && argc < 4) raise_argn(argc, 4);
	if (argc == 1) rb_iv_set(self, "@rect", argv[0]);
	else rb_iv_set(self, "@rect", ARGSS::ARect::New(argv[0], argv[1], argv[2], argv[3]));
	rb_iv_set(self, "@visible", Qtrue);
	rb_iv_set(self, "@z", INT2NUM(0));
	rb_iv_set(self, "@ox", INT2NUM(0));
	rb_iv_set(self, "@oy", INT2NUM(0));
	rb_iv_set(self, "@color", ARGSS::AColor::New(0, 0, 0, 0));
	rb_iv_set(self, "@tone", ARGSS::ATone::New());
	Viewport::New(self);
	ARGSS::ARuby::AddObject(self);
	return self;
}
VALUE ARGSS::AViewport::rdispose(VALUE self) {
	if (!Viewport::IsDisposed(self)) {
		ARGSS::AViewport::CheckDisposed(self);
		Viewport::Dispose(self);
		ARGSS::ARuby::RemoveObject(self);
		rb_gc_start();
	}
	return self;
}
VALUE ARGSS::AViewport::rdisposedQ(VALUE self) {
	return INT2BOOL(Viewport::IsDisposed(self));
}
VALUE ARGSS::AViewport::rflash(VALUE self, VALUE color, VALUE duration) {
	ARGSS::AViewport::CheckDisposed(self);
	if (color == Qnil) {
		Viewport::Get(self)->Flash(NUM2INT(duration));
	} else {
		Viewport::Get(self)->Flash(Color(color), NUM2INT(duration));
	}
	return Qnil;
}
VALUE ARGSS::AViewport::rupdate(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	Viewport::Get(self)->Update();
	return Qnil;
}
VALUE ARGSS::AViewport::rrect(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@rect");
}
VALUE ARGSS::AViewport::rrectE(VALUE self, VALUE rect) {
	ARGSS::AViewport::CheckDisposed(self);
	Check_Class(rect, ARGSS::ARect::id);
	Viewport::Get(self)->SetRect(rect);
	return rb_iv_set(self, "@rect", rect);
}
VALUE ARGSS::AViewport::rvisible(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@visible");
}
VALUE ARGSS::AViewport::rvisibleE(VALUE self, VALUE visible) {
	ARGSS::AViewport::CheckDisposed(self);
	Viewport::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
VALUE ARGSS::AViewport::rz(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@z");
}
VALUE ARGSS::AViewport::rzE(VALUE self, VALUE z) {
	ARGSS::AViewport::CheckDisposed(self);
	Viewport::Get(self)->SetZ(NUM2INT(z));
	return rb_iv_set(self, "@z", z);
}
VALUE ARGSS::AViewport::rox(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@ox");
}
VALUE ARGSS::AViewport::roxE(VALUE self, VALUE ox) {
	ARGSS::AViewport::CheckDisposed(self);
	Viewport::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
VALUE ARGSS::AViewport::roy(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@oy");
}
VALUE ARGSS::AViewport::royE(VALUE self, VALUE oy) {
	ARGSS::AViewport::CheckDisposed(self);
	Viewport::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}
VALUE ARGSS::AViewport::rcolor(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@color");
}
VALUE ARGSS::AViewport::rcolorE(VALUE self, VALUE color) {
	ARGSS::AViewport::CheckDisposed(self);
	Check_Class(color, ARGSS::AColor::id);
	Viewport::Get(self)->SetColor(color);
	return rb_iv_set(self, "@color", color);
}
VALUE ARGSS::AViewport::rtone(VALUE self) {
	ARGSS::AViewport::CheckDisposed(self);
	return rb_iv_get(self, "@tone");
}
VALUE ARGSS::AViewport::rtoneE(VALUE self, VALUE tone) {
	ARGSS::AViewport::CheckDisposed(self);
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
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)rdisposedQ, 0);
	rb_define_method(id, "flash", (rubyfunc)rflash, 2);
	rb_define_method(id, "update", (rubyfunc)rupdate, 0);
	rb_define_method(id, "rect", (rubyfunc)rrect, 0);
	rb_define_method(id, "rect=", (rubyfunc)rrectE, 1);
	rb_define_method(id, "visible", (rubyfunc)rvisible, 0);
	rb_define_method(id, "visible=", (rubyfunc)rvisibleE, 1);
	rb_define_method(id, "z", (rubyfunc)rz, 0);
	rb_define_method(id, "z=", (rubyfunc)rzE, 1);
	rb_define_method(id, "ox", (rubyfunc)rox, 0);
	rb_define_method(id, "ox=", (rubyfunc)roxE, 1);
	rb_define_method(id, "oy", (rubyfunc)roy, 0);
	rb_define_method(id, "oy=", (rubyfunc)royE, 1);
	rb_define_method(id, "color", (rubyfunc)rcolor, 0);
	rb_define_method(id, "color=", (rubyfunc)rcolorE, 1);
	rb_define_method(id, "tone", (rubyfunc)rtone, 0);
	rb_define_method(id, "tone=", (rubyfunc)rtoneE, 1);
}

////////////////////////////////////////////////////////////
/// Check if plane isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::AViewport::CheckDisposed(VALUE self) {
	if (Viewport::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed viewport <%i>", self);
	}
}
