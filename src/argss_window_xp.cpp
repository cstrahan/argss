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
#include "argss_window_xp.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_color.h"
#include "argss_rect.h"
#include "argss_error.h"
#include "window_xp.h"

////////////////////////////////////////////////////////////
/// Global Variables
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
static VALUE argss_window_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
    }
    else if (argc == 0) {
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
	return self;
}
static VALUE argss_window_dispose(VALUE self) {
    ARGSS::AWindow::Check(self);
    Window::Get(self)->Dispose();
    return self;
}
static VALUE argss_window_disposedQ(VALUE self) {
	return INT2BOOL(Window::IsDisposed(self));
}
static VALUE argss_window_update(VALUE self) {
    ARGSS::AWindow::Check(self);
    Window::Get(self)->Update();
    return Qnil;
}
static VALUE argss_window_viewport(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@viewport");
}
static VALUE argss_window_viewportE(VALUE self, VALUE viewport) {
    ARGSS::AWindow::Check(self);
    Check_Classes_N(viewport, ARGSS::AViewport::id);
	Window::Get(self)->SetViewport(viewport);
    return rb_iv_set(self, "@viewport", viewport);
}
static VALUE argss_window_windowskin(VALUE self) {
	ARGSS::AWindow::Check(self);
	return rb_iv_get(self, "@windowskin");
}
static VALUE argss_window_windowskinE(VALUE self, VALUE windowskin) {
	ARGSS::AWindow::Check(self);
	Check_Classes_N(windowskin, ARGSS::ABitmap::id);
	Window::Get(self)->SetWindowskin(windowskin);
    return rb_iv_set(self, "@windowskin", windowskin);
}
static VALUE argss_window_contents(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@contents");
}
static VALUE argss_window_contentsE(VALUE self, VALUE contents) {
	ARGSS::AWindow::Check(self);
	Check_Classes_N(contents, ARGSS::ABitmap::id);
	Window::Get(self)->SetContents(contents);
	return rb_iv_set(self, "@contents", contents);
}
static VALUE argss_window_stretch(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@stretch");
}
static VALUE argss_window_stretchE(VALUE self, VALUE stretch) {
    ARGSS::AWindow::Check(self);
    Window::Get(self)->SetStretch(NUM2BOOL(stretch));
    return rb_iv_set(self, "@stretch", stretch);
}
static VALUE argss_window_cursor_rect(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@cursor_rect");
}
static VALUE argss_window_cursor_rectE(VALUE self, VALUE cursor_rect) {
    ARGSS::AWindow::Check(self);
	Check_Class(cursor_rect, ARGSS::ARect::id);
    Window::Get(self)->SetCursorRect(cursor_rect);
    return rb_iv_set(self, "@cursor_rect", cursor_rect);
}
static VALUE argss_window_active(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@active");
}
static VALUE argss_window_activeE(VALUE self, VALUE active) {
    ARGSS::AWindow::Check(self);
    Window::Get(self)->SetActive(NUM2BOOL(active));
    return rb_iv_set(self, "@active", active);
}
static VALUE argss_window_visible(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@visible");
}
static VALUE argss_window_visibleE(VALUE self, VALUE visible) {
    ARGSS::AWindow::Check(self);
    Window::Get(self)->SetVisible(NUM2BOOL(visible));
    return rb_iv_set(self, "@visible", visible);
}
static VALUE argss_window_pause(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@pause");
}
static VALUE argss_window_pauseE(VALUE self, VALUE pause) {
    ARGSS::AWindow::Check(self);
    Window::Get(self)->SetPause(NUM2BOOL(pause));
    return rb_iv_set(self, "@pause", pause);
}
static VALUE argss_window_x(VALUE self) {
    ARGSS::AWindow::Check(self);
	return rb_funcall(rb_iv_get(self, "@x"), rb_intern("to_i"), 0, 0);
}
static VALUE argss_window_fx(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_funcall(rb_iv_get(self, "@x"), rb_intern("to_f"), 0, 0);
}
static VALUE argss_window_xE(VALUE self, VALUE x) {
    ARGSS::AWindow::Check(self);
	Window::Get(self)->SetX(NUM2INT(x));
    return rb_iv_set(self, "@x", x);
}
static VALUE argss_window_y(VALUE self) {
    ARGSS::AWindow::Check(self);
	return rb_funcall(rb_iv_get(self, "@y"), rb_intern("to_i"), 0, 0);
}
static VALUE argss_window_fy(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_funcall(rb_iv_get(self, "@y"), rb_intern("to_f"), 0, 0);
}
static VALUE argss_window_yE(VALUE self, VALUE y) {
    ARGSS::AWindow::Check(self);
	Window::Get(self)->SetY(NUM2INT(y));
    return rb_iv_set(self, "@y", y);
}
static VALUE argss_window_width(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@width");
}
static VALUE argss_window_widthE(VALUE self, VALUE width) {
    ARGSS::AWindow::Check(self);
	int w = NUM2INT(width);
	if (w < 0) w = 0;
	Window::Get(self)->SetWidth(w);
    return rb_iv_set(self, "@width", INT2NUM(w));
}
static VALUE argss_window_height(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@height");
}
static VALUE argss_window_heightE(VALUE self, VALUE height) {
    ARGSS::AWindow::Check(self);
	int h = NUM2INT(height);
	if (h < 0) h = 0;
	Window::Get(self)->SetHeight(h);
    return rb_iv_set(self, "@height", INT2NUM(h));
}
static VALUE argss_window_z(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@z");
}
static VALUE argss_window_zE(VALUE self, VALUE z) {
    ARGSS::AWindow::Check(self);
	Window::Get(self)->SetZ(NUM2INT(z));
    return rb_iv_set(self, "@z", z);
}
static VALUE argss_window_ox(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@ox");
}
static VALUE argss_window_oxE(VALUE self, VALUE ox) {
    ARGSS::AWindow::Check(self);
	Window::Get(self)->SetOx(NUM2INT(ox));
    return rb_iv_set(self, "@ox", ox);
}
static VALUE argss_window_oy(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@oy");
}
static VALUE argss_window_oyE(VALUE self, VALUE oy) {
    ARGSS::AWindow::Check(self);
	Window::Get(self)->SetOy(NUM2INT(oy));
    return rb_iv_set(self, "@oy", oy);
}
static VALUE argss_window_opacity(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@opacity");
}
static VALUE argss_window_opacityE(VALUE self, VALUE opacity) {
    ARGSS::AWindow::Check(self);
	opacity = CapOpacityValue(NUM2INT(opacity));
	Window::Get(self)->SetOpacity(opacity);
    return rb_iv_set(self, "@opacity", INT2NUM(opacity));
}
static VALUE argss_window_back_opacity(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@back_opacity");
}
static VALUE argss_window_back_opacityE(VALUE self, VALUE back_opacity) {
    ARGSS::AWindow::Check(self);
	back_opacity = CapOpacityValue(NUM2INT(back_opacity));
	Window::Get(self)->SetBackOpacity(back_opacity);
    return rb_iv_set(self, "@back_opacity", INT2NUM(back_opacity));
}
static VALUE argss_window_contents_opacity(VALUE self) {
    ARGSS::AWindow::Check(self);
    return rb_iv_get(self, "@contents_opacity");
}
static VALUE argss_window_contents_opacityE(VALUE self, VALUE contents_opacity) {
    ARGSS::AWindow::Check(self);
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
    rb_define_method(id, "initialize", (rubyfunc)argss_window_initialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)argss_window_dispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)argss_window_disposedQ, 0);
	rb_define_method(id, "update", (rubyfunc)argss_window_update, 0);
	rb_define_method(id, "viewport", (rubyfunc)argss_window_viewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)argss_window_viewportE, 1);
	rb_define_method(id, "windowskin", (rubyfunc)argss_window_windowskin, 0);
	rb_define_method(id, "windowskin=", (rubyfunc)argss_window_windowskinE, 1);
	rb_define_method(id, "contents", (rubyfunc)argss_window_contents, 0);
	rb_define_method(id, "contents=", (rubyfunc)argss_window_contentsE, 1);
	rb_define_method(id, "stretch", (rubyfunc)argss_window_stretch, 0);
	rb_define_method(id, "stretch=", (rubyfunc)argss_window_stretchE, 1);
	rb_define_method(id, "cursor_rect", (rubyfunc)argss_window_cursor_rect, 0);
	rb_define_method(id, "cursor_rect=", (rubyfunc)argss_window_cursor_rectE, 1);
	rb_define_method(id, "active", (rubyfunc)argss_window_active, 0);
	rb_define_method(id, "active=", (rubyfunc)argss_window_activeE, 1);
	rb_define_method(id, "visible", (rubyfunc)argss_window_visible, 0);
	rb_define_method(id, "visible=", (rubyfunc)argss_window_visibleE, 1);
	rb_define_method(id, "pause", (rubyfunc)argss_window_pause, 0);
	rb_define_method(id, "pause=", (rubyfunc)argss_window_pauseE, 1);
	rb_define_method(id, "x", (rubyfunc)argss_window_x, 0);
	rb_define_method(id, "fx", (rubyfunc)argss_window_x, 0);
	rb_define_method(id, "x=", (rubyfunc)argss_window_xE, 1);
	rb_define_method(id, "y", (rubyfunc)argss_window_y, 0);
	rb_define_method(id, "fy", (rubyfunc)argss_window_y, 0);
	rb_define_method(id, "y=", (rubyfunc)argss_window_yE, 1);
	rb_define_method(id, "width", (rubyfunc)argss_window_width, 0);
	rb_define_method(id, "width=", (rubyfunc)argss_window_widthE, 1);
	rb_define_method(id, "height", (rubyfunc)argss_window_height, 0);
	rb_define_method(id, "height=", (rubyfunc)argss_window_heightE, 1);
	rb_define_method(id, "z", (rubyfunc)argss_window_z, 0);
	rb_define_method(id, "z=", (rubyfunc)argss_window_zE, 1);
	rb_define_method(id, "ox", (rubyfunc)argss_window_ox, 0);
	rb_define_method(id, "ox=", (rubyfunc)argss_window_oxE, 1);
	rb_define_method(id, "oy", (rubyfunc)argss_window_oy, 0);
	rb_define_method(id, "oy=", (rubyfunc)argss_window_oyE, 1);
	rb_define_method(id, "opacity", (rubyfunc)argss_window_opacity, 0);
	rb_define_method(id, "opacity=", (rubyfunc)argss_window_opacityE, 1);
	rb_define_method(id, "back_opacity", (rubyfunc)argss_window_back_opacity, 0);
	rb_define_method(id, "back_opacity=", (rubyfunc)argss_window_back_opacityE, 1);
	rb_define_method(id, "contents_opacity", (rubyfunc)argss_window_contents_opacity, 0);
	rb_define_method(id, "contents_opacity=", (rubyfunc)argss_window_contents_opacityE, 1);
}

////////////////////////////////////////////////////////////
/// Check if window isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::AWindow::Check(VALUE self) {
    if (Window::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed window <%i>", self);
    }
}
