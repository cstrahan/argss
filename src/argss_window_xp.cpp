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
#include "argss_window_xp.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_rect.h"
#include "argss_error.h"
#include "window_xp.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::AWindow::id;

////////////////////////////////////////////////////////////
/// Cap opacity value between 0 and 255
////////////////////////////////////////////////////////////
int CapOpacityValue(int v) {
	return (v > 255) ? 255 : (v < 0) ? 0 : v;
}

////////////////////////////////////////////////////////////
/// ARGSS Window ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::AWindow::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
	} else if (argc == 0) {
		rb_iv_set(self, "@viewport", Qnil);
	}
	else raise_argn(argc, 1);
	rb_iv_set(self, "@windowskin", Qnil);
	rb_iv_set(self, "@contents", Qnil);
	rb_iv_set(self, "@stretch", Qtrue);
	rb_iv_set(self, "@cursor_rect", ARGSS::ARect::New(0, 0, 0, 0));
	rb_iv_set(self, "@active", Qtrue);
	rb_iv_set(self, "@visible", Qtrue);
	rb_iv_set(self, "@pause", Qfalse);
	rb_iv_set(self, "@x", INT2NUM(0));
	rb_iv_set(self, "@y", INT2NUM(0));
	rb_iv_set(self, "@width", INT2NUM(0));
	rb_iv_set(self, "@height", INT2NUM(0));
	rb_iv_set(self, "@z", INT2NUM(0));
	rb_iv_set(self, "@ox", INT2NUM(0));
	rb_iv_set(self, "@oy", INT2NUM(0));
	rb_iv_set(self, "@opacity", INT2NUM(255));
	rb_iv_set(self, "@back_opacity", INT2NUM(255));
	rb_iv_set(self, "@contents_opacity", INT2NUM(255));
	Window::New(self);
	ARGSS::ARuby::AddObject(self);
	return self;
}
VALUE ARGSS::AWindow::rdispose(VALUE self) {
	if (!Window::IsDisposed(self)) {
		ARGSS::AWindow::CheckDisposed(self);
		Window::Dispose(self);
		ARGSS::ARuby::RemoveObject(self);
		rb_gc_start();
	}
	return self;
}
VALUE ARGSS::AWindow::rdisposedQ(VALUE self) {
	return INT2BOOL(Window::IsDisposed(self));
}
VALUE ARGSS::AWindow::rupdate(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->Update();
	return Qnil;
}
VALUE ARGSS::AWindow::rviewport(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@viewport");
}
VALUE ARGSS::AWindow::rviewportE(VALUE self, VALUE viewport) {
	ARGSS::AWindow::CheckDisposed(self);
	Check_Classes_N(viewport, ARGSS::AViewport::id);
	Window::Get(self)->SetViewport(viewport);
	return rb_iv_set(self, "@viewport", viewport);
}
VALUE ARGSS::AWindow::rwindowskin(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@windowskin");
}
VALUE ARGSS::AWindow::rwindowskinE(VALUE self, VALUE windowskin) {
	ARGSS::AWindow::CheckDisposed(self);
	Check_Classes_N(windowskin, ARGSS::ABitmap::id);
	Window::Get(self)->SetWindowskin(windowskin);
	return rb_iv_set(self, "@windowskin", windowskin);
}
VALUE ARGSS::AWindow::rcontents(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@contents");
}
VALUE ARGSS::AWindow::rcontentsE(VALUE self, VALUE contents) {
	ARGSS::AWindow::CheckDisposed(self);
	Check_Classes_N(contents, ARGSS::ABitmap::id);
	Window::Get(self)->SetContents(contents);
	return rb_iv_set(self, "@contents", contents);
}
VALUE ARGSS::AWindow::rstretch(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@stretch");
}
VALUE ARGSS::AWindow::rstretchE(VALUE self, VALUE stretch) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetStretch(NUM2BOOL(stretch));
	return rb_iv_set(self, "@stretch", stretch);
}
VALUE ARGSS::AWindow::rcursor_rect(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@cursor_rect");
}
VALUE ARGSS::AWindow::rcursor_rectE(VALUE self, VALUE cursor_rect) {
	ARGSS::AWindow::CheckDisposed(self);
	Check_Class(cursor_rect, ARGSS::ARect::id);
	Window::Get(self)->SetCursorRect(cursor_rect);
	return rb_iv_set(self, "@cursor_rect", cursor_rect);
}
VALUE ARGSS::AWindow::ractive(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@active");
}
VALUE ARGSS::AWindow::ractiveE(VALUE self, VALUE active) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetActive(NUM2BOOL(active));
	return rb_iv_set(self, "@active", active);
}
VALUE ARGSS::AWindow::rvisible(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@visible");
}
VALUE ARGSS::AWindow::rvisibleE(VALUE self, VALUE visible) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
VALUE ARGSS::AWindow::rpause(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@pause");
}
VALUE ARGSS::AWindow::rpauseE(VALUE self, VALUE pause) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetPause(NUM2BOOL(pause));
	return rb_iv_set(self, "@pause", pause);
}
VALUE ARGSS::AWindow::rx(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_to_int(rb_iv_get(self, "@x"));
}
VALUE ARGSS::AWindow::rfx(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_Float(rb_iv_get(self, "@x"));
}
VALUE ARGSS::AWindow::rxE(VALUE self, VALUE x) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetX(NUM2INT(x));
	return rb_iv_set(self, "@x", x);
}
VALUE ARGSS::AWindow::ry(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_to_int(rb_iv_get(self, "@y"));
}
VALUE ARGSS::AWindow::rfy(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_Float(rb_iv_get(self, "@y"));
}
VALUE ARGSS::AWindow::ryE(VALUE self, VALUE y) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetY(NUM2INT(y));
	return rb_iv_set(self, "@y", y);
}
VALUE ARGSS::AWindow::rwidth(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@width");
}
VALUE ARGSS::AWindow::rwidthE(VALUE self, VALUE width) {
	ARGSS::AWindow::CheckDisposed(self);
	int w = NUM2INT(width);
	if (w < 0) w = 0;
	Window::Get(self)->SetWidth(w);
	return rb_iv_set(self, "@width", INT2NUM(w));
}
VALUE ARGSS::AWindow::rheight(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@height");
}
VALUE ARGSS::AWindow::rheightE(VALUE self, VALUE height) {
	ARGSS::AWindow::CheckDisposed(self);
	int h = NUM2INT(height);
	if (h < 0) h = 0;
	Window::Get(self)->SetHeight(h);
	return rb_iv_set(self, "@height", INT2NUM(h));
}
VALUE ARGSS::AWindow::rz(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@z");
}
VALUE ARGSS::AWindow::rzE(VALUE self, VALUE z) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetZ(NUM2INT(z));
	return rb_iv_set(self, "@z", z);
}
VALUE ARGSS::AWindow::rox(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@ox");
}
VALUE ARGSS::AWindow::roxE(VALUE self, VALUE ox) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
VALUE ARGSS::AWindow::roy(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@oy");
}
VALUE ARGSS::AWindow::royE(VALUE self, VALUE oy) {
	ARGSS::AWindow::CheckDisposed(self);
	Window::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}
VALUE ARGSS::AWindow::ropacity(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@opacity");
}
VALUE ARGSS::AWindow::ropacityE(VALUE self, VALUE opacity) {
	ARGSS::AWindow::CheckDisposed(self);
	opacity = CapOpacityValue(NUM2INT(opacity));
	Window::Get(self)->SetOpacity(opacity);
	return rb_iv_set(self, "@opacity", INT2NUM(opacity));
}
VALUE ARGSS::AWindow::rback_opacity(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@back_opacity");
}
VALUE ARGSS::AWindow::rback_opacityE(VALUE self, VALUE back_opacity) {
	ARGSS::AWindow::CheckDisposed(self);
	back_opacity = CapOpacityValue(NUM2INT(back_opacity));
	Window::Get(self)->SetBackOpacity(back_opacity);
	return rb_iv_set(self, "@back_opacity", INT2NUM(back_opacity));
}
VALUE ARGSS::AWindow::rcontents_opacity(VALUE self) {
	ARGSS::AWindow::CheckDisposed(self);
	return rb_iv_get(self, "@contents_opacity");
}
VALUE ARGSS::AWindow::rcontents_opacityE(VALUE self, VALUE contents_opacity) {
	ARGSS::AWindow::CheckDisposed(self);
	contents_opacity = CapOpacityValue(NUM2INT(contents_opacity));
	Window::Get(self)->SetContentsOpacity(contents_opacity);
	return rb_iv_set(self, "@contents_opacity", INT2NUM(contents_opacity));
}

////////////////////////////////////////////////////////////
/// ARGSS Window initialize
////////////////////////////////////////////////////////////
void ARGSS::AWindow::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_class("Window", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)rdisposedQ, 0);
	rb_define_method(id, "update", (rubyfunc)rupdate, 0);
	rb_define_method(id, "viewport", (rubyfunc)rviewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)rviewportE, 1);
	rb_define_method(id, "windowskin", (rubyfunc)rwindowskin, 0);
	rb_define_method(id, "windowskin=", (rubyfunc)rwindowskinE, 1);
	rb_define_method(id, "contents", (rubyfunc)rcontents, 0);
	rb_define_method(id, "contents=", (rubyfunc)rcontentsE, 1);
	rb_define_method(id, "stretch", (rubyfunc)rstretch, 0);
	rb_define_method(id, "stretch=", (rubyfunc)rstretchE, 1);
	rb_define_method(id, "cursor_rect", (rubyfunc)rcursor_rect, 0);
	rb_define_method(id, "cursor_rect=", (rubyfunc)rcursor_rectE, 1);
	rb_define_method(id, "active", (rubyfunc)ractive, 0);
	rb_define_method(id, "active=", (rubyfunc)ractiveE, 1);
	rb_define_method(id, "visible", (rubyfunc)rvisible, 0);
	rb_define_method(id, "visible=", (rubyfunc)rvisibleE, 1);
	rb_define_method(id, "pause", (rubyfunc)rpause, 0);
	rb_define_method(id, "pause=", (rubyfunc)rpauseE, 1);
	rb_define_method(id, "x", (rubyfunc)rx, 0);
	rb_define_method(id, "fx", (rubyfunc)rx, 0);
	rb_define_method(id, "x=", (rubyfunc)rxE, 1);
	rb_define_method(id, "y", (rubyfunc)ry, 0);
	rb_define_method(id, "fy", (rubyfunc)ry, 0);
	rb_define_method(id, "y=", (rubyfunc)ryE, 1);
	rb_define_method(id, "width", (rubyfunc)rwidth, 0);
	rb_define_method(id, "width=", (rubyfunc)rwidthE, 1);
	rb_define_method(id, "height", (rubyfunc)rheight, 0);
	rb_define_method(id, "height=", (rubyfunc)rheightE, 1);
	rb_define_method(id, "z", (rubyfunc)rz, 0);
	rb_define_method(id, "z=", (rubyfunc)rzE, 1);
	rb_define_method(id, "ox", (rubyfunc)rox, 0);
	rb_define_method(id, "ox=", (rubyfunc)roxE, 1);
	rb_define_method(id, "oy", (rubyfunc)roy, 0);
	rb_define_method(id, "oy=", (rubyfunc)royE, 1);
	rb_define_method(id, "opacity", (rubyfunc)ropacity, 0);
	rb_define_method(id, "opacity=", (rubyfunc)ropacityE, 1);
	rb_define_method(id, "back_opacity", (rubyfunc)rback_opacity, 0);
	rb_define_method(id, "back_opacity=", (rubyfunc)rback_opacityE, 1);
	rb_define_method(id, "contents_opacity", (rubyfunc)rcontents_opacity, 0);
	rb_define_method(id, "contents_opacity=", (rubyfunc)rcontents_opacityE, 1);
}

////////////////////////////////////////////////////////////
/// Check if window isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::AWindow::CheckDisposed(VALUE self) {
	if (Window::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed window <%i>", self);
	}
}
