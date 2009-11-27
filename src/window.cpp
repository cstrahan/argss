// Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "window.h"
#include "argss.h"
#include "argss_sdl.h"
#include "aerror.h"
#include "rect.h"
#include "bitmap.h"

void argss_window_check(VALUE self) {
    if (ARGSS_mapWindows.count(self) == 0) {
        rb_raise(ARGSS_Error, "disposed window <%i>", self);
    }
}

static VALUE argss_window_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc == 1) {
        Check_Classes_N(argv[0], ARGSS_Viewport);
		rb_iv_set(self, "@viewport", argv[0]);
		// TODO
    }
    else if (argc == 0) {
        rb_iv_set(self, "@viewport", Qnil);
        ARGSS_CreationTime += 1;
        Z_Obj obj(0, ARGSS_CreationTime, ARGSS_Window, self);
        ARGSS_ZOrder.push_back(obj);
		ARGSS_mapWindows[self].set_id(self);
    }
    else raise_argn(argc, 1);
	rb_iv_set(self, "@windowskin", Qnil);
	rb_iv_set(self, "@contents", Qnil);
	rb_iv_set(self, "@stretch", Qtrue);
	rb_iv_set(self, "@cursor_rect", argss_rect_new2(0, 0, 0, 0));
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
	return self;
}

static VALUE argss_window_dispose(VALUE self) {
    argss_window_check(self);
    ARGSS_mapWindows.erase(self);
    ARGSS_ZOrder.remove_if(remove_zobj_id(self));
    return self;
}
static VALUE argss_window_disposedQ(VALUE self) {
	return INT2BOOL(ARGSS_mapWindows.count(self) == 0);
}
static VALUE argss_window_update(VALUE self) {
    argss_window_check(self);
    ARGSS_mapWindows[self].update();
    return Qnil;
}
static VALUE argss_window_viewport(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@viewport");
}
static VALUE argss_window_viewportE(VALUE self, VALUE viewport) {
    argss_window_check(self);
    Check_Classes_N(viewport, ARGSS_Viewport);
	ARGSS_mapWindows[self].set_viewport(&ARGSS_mapViewports[viewport]);
    return rb_iv_set(self, "@viewport", viewport);
}
static VALUE argss_window_windowskin(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@windowskin");
}
static VALUE argss_window_windowskinE(VALUE self, VALUE windowskin) {
    argss_window_check(self);
    Check_Classes_N(windowskin, ARGSS_Bitmap);
    if (windowskin != Qnil) {
        argss_bitmap_check(windowskin);
        ARGSS_mapWindows[self].set_windowskin(ARGSS_mapBitmaps[windowskin]);
    }
    return rb_iv_set(self, "@windowskin", windowskin);
}
static VALUE argss_window_contents(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@contents");
}
static VALUE argss_window_contentsE(VALUE self, VALUE contents) {
    argss_window_check(self);
    Check_Classes_N(contents, ARGSS_Bitmap);
    if (contents != Qnil) {
        argss_bitmap_check(contents);
        ARGSS_mapWindows[self].set_contents(ARGSS_mapBitmaps[contents]);
    }
    return rb_iv_set(self, "@contents", contents);
}
static VALUE argss_window_stretch(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@stretch");
}
static VALUE argss_window_stretchE(VALUE self, VALUE stretch) {
    argss_window_check(self);
    Check_Bool(stretch);
    ARGSS_mapWindows[self].set_stretch(NUM2BOOL(stretch));
    return rb_iv_set(self, "@stretch", stretch);
}
static VALUE argss_window_cursor_rect(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@cursor_rect");
}
static VALUE argss_window_cursor_rectE(VALUE self, VALUE cursor_rect) {
    argss_window_check(self);
    Check_Class(cursor_rect, ARGSS_Rect);
    ARGSS_mapWindows[self].set_cursor_rect(argss_rect_getsdl(cursor_rect));
    return rb_iv_set(self, "@cursor_rect", cursor_rect);
}
static VALUE argss_window_active(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@active");
}
static VALUE argss_window_activeE(VALUE self, VALUE active) {
    argss_window_check(self);
    Check_Bool(active);
    ARGSS_mapWindows[self].set_active(NUM2BOOL(active));
    return rb_iv_set(self, "@active", active);
}
static VALUE argss_window_visible(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@visible");
}
static VALUE argss_window_visibleE(VALUE self, VALUE visible) {
    argss_window_check(self);
    Check_Bool(visible);
    ARGSS_mapWindows[self].set_visible(NUM2BOOL(visible));
    return rb_iv_set(self, "@visible", visible);
}
static VALUE argss_window_pause(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@pause");
}
static VALUE argss_window_pauseE(VALUE self, VALUE pause) {
    argss_window_check(self);
    Check_Bool(pause);
    ARGSS_mapWindows[self].set_pause(NUM2BOOL(pause));
    return rb_iv_set(self, "@pause", pause);
}
static VALUE argss_window_x(VALUE self) {
    argss_window_check(self);
	return rb_funcall(rb_iv_get(self, "@x"), rb_intern("to_i"), 0, 0);
}
static VALUE argss_window_fx(VALUE self) {
    argss_window_check(self);
    return rb_funcall(rb_iv_get(self, "@x"), rb_intern("to_f"), 0, 0);
}
static VALUE argss_window_xE(VALUE self, VALUE x) {
    argss_window_check(self);
    Check_Kind(x, rb_cNumeric);
	ARGSS_mapWindows[self].set_x(NUM2INT(x));
    return rb_iv_set(self, "@x", x);
}
static VALUE argss_window_y(VALUE self) {
    argss_window_check(self);
	return rb_funcall(rb_iv_get(self, "@y"), rb_intern("to_i"), 0, 0);
}
static VALUE argss_window_fy(VALUE self) {
    argss_window_check(self);
    return rb_funcall(rb_iv_get(self, "@y"), rb_intern("to_f"), 0, 0);
}
static VALUE argss_window_yE(VALUE self, VALUE y) {
    argss_window_check(self);
    Check_Kind(y, rb_cNumeric);
	ARGSS_mapWindows[self].set_y(NUM2INT(y));
    return rb_iv_set(self, "@y", y);
}
static VALUE argss_window_width(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@width");
}
static VALUE argss_window_widthE(VALUE self, VALUE width) {
    argss_window_check(self);
    Check_Type(width, T_FIXNUM);
	ARGSS_mapWindows[self].set_width(NUM2INT(width));
    return rb_iv_set(self, "@width", width);
}
static VALUE argss_window_height(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@height");
}
static VALUE argss_window_heightE(VALUE self, VALUE height) {
    argss_window_check(self);
    Check_Type(height, T_FIXNUM);
	ARGSS_mapWindows[self].set_height(NUM2INT(height));
    return rb_iv_set(self, "@height", height);
}
static VALUE argss_window_z(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@z");
}
static VALUE argss_window_zE(VALUE self, VALUE z) {
    argss_window_check(self);
    Check_Type(z, T_FIXNUM);
	ARGSS_mapWindows[self].set_z(NUM2INT(z));
    return rb_iv_set(self, "@z", z);
}
static VALUE argss_window_ox(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@ox");
}
static VALUE argss_window_oxE(VALUE self, VALUE ox) {
    argss_window_check(self);
    Check_Type(ox, T_FIXNUM);
	ARGSS_mapWindows[self].set_ox(NUM2INT(ox));
    return rb_iv_set(self, "@ox", ox);
}
static VALUE argss_window_oy(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@oy");
}
static VALUE argss_window_oyE(VALUE self, VALUE oy) {
    argss_window_check(self);
    Check_Type(oy, T_FIXNUM);
	ARGSS_mapWindows[self].set_oy(NUM2INT(oy));
    return rb_iv_set(self, "@oy", oy);
}
static VALUE argss_window_opacity(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@opacity");
}
static VALUE argss_window_opacityE(VALUE self, VALUE opacity) {
    argss_window_check(self);
    Check_Type(opacity, T_FIXNUM);
	ARGSS_mapWindows[self].set_opacity(NUM2INT(opacity));
    return rb_iv_set(self, "@opacity", opacity);
}
static VALUE argss_window_back_opacity(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@back_opacity");
}
static VALUE argss_window_back_opacityE(VALUE self, VALUE back_opacity) {
    argss_window_check(self);
    Check_Type(back_opacity, T_FIXNUM);
	ARGSS_mapWindows[self].set_back_opacity(NUM2INT(back_opacity));
    return rb_iv_set(self, "@back_opacity", back_opacity);
}
static VALUE argss_window_contents_opacity(VALUE self) {
    argss_window_check(self);
    return rb_iv_get(self, "@contents_opacity");
}
static VALUE argss_window_contents_opacityE(VALUE self, VALUE contents_opacity) {
    argss_window_check(self);
    Check_Type(contents_opacity, T_FIXNUM);
	ARGSS_mapWindows[self].set_contents_opacity(NUM2INT(contents_opacity));
    return rb_iv_set(self, "@contents_opacity", contents_opacity);
}

void Init_Window() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Window = rb_define_class("Window", rb_cObject);
    rb_define_method(ARGSS_Window, "initialize", (rubyfunc)argss_window_initialize, -1);
	rb_define_method(ARGSS_Window, "dispose", (rubyfunc)argss_window_dispose, 0);
	rb_define_method(ARGSS_Window, "disposed?", (rubyfunc)argss_window_disposedQ, 0);
	rb_define_method(ARGSS_Window, "update", (rubyfunc)argss_window_update, 0);
	rb_define_method(ARGSS_Window, "viewport", (rubyfunc)argss_window_viewport, 0);
	rb_define_method(ARGSS_Window, "viewport=", (rubyfunc)argss_window_viewportE, 1);
	rb_define_method(ARGSS_Window, "windowskin", (rubyfunc)argss_window_windowskin, 0);
	rb_define_method(ARGSS_Window, "windowskin=", (rubyfunc)argss_window_windowskinE, 1);
	rb_define_method(ARGSS_Window, "contents", (rubyfunc)argss_window_contents, 0);
	rb_define_method(ARGSS_Window, "contents=", (rubyfunc)argss_window_contentsE, 1);
	rb_define_method(ARGSS_Window, "stretch", (rubyfunc)argss_window_stretch, 0);
	rb_define_method(ARGSS_Window, "stretch=", (rubyfunc)argss_window_stretchE, 1);
	rb_define_method(ARGSS_Window, "cursor_rect", (rubyfunc)argss_window_cursor_rect, 0);
	rb_define_method(ARGSS_Window, "cursor_rect=", (rubyfunc)argss_window_cursor_rectE, 1);
	rb_define_method(ARGSS_Window, "active", (rubyfunc)argss_window_active, 0);
	rb_define_method(ARGSS_Window, "active=", (rubyfunc)argss_window_activeE, 1);
	rb_define_method(ARGSS_Window, "visible", (rubyfunc)argss_window_visible, 0);
	rb_define_method(ARGSS_Window, "visible=", (rubyfunc)argss_window_visibleE, 1);
	rb_define_method(ARGSS_Window, "pause", (rubyfunc)argss_window_pause, 0);
	rb_define_method(ARGSS_Window, "pause=", (rubyfunc)argss_window_pauseE, 1);
	rb_define_method(ARGSS_Window, "x", (rubyfunc)argss_window_x, 0);
	rb_define_method(ARGSS_Window, "fx", (rubyfunc)argss_window_x, 0);
	rb_define_method(ARGSS_Window, "x=", (rubyfunc)argss_window_xE, 1);
	rb_define_method(ARGSS_Window, "y", (rubyfunc)argss_window_y, 0);
	rb_define_method(ARGSS_Window, "fy", (rubyfunc)argss_window_y, 0);
	rb_define_method(ARGSS_Window, "y=", (rubyfunc)argss_window_yE, 1);
	rb_define_method(ARGSS_Window, "width", (rubyfunc)argss_window_width, 0);
	rb_define_method(ARGSS_Window, "width=", (rubyfunc)argss_window_widthE, 1);
	rb_define_method(ARGSS_Window, "height", (rubyfunc)argss_window_height, 0);
	rb_define_method(ARGSS_Window, "height=", (rubyfunc)argss_window_heightE, 1);
	rb_define_method(ARGSS_Window, "z", (rubyfunc)argss_window_z, 0);
	rb_define_method(ARGSS_Window, "z=", (rubyfunc)argss_window_zE, 1);
	rb_define_method(ARGSS_Window, "ox", (rubyfunc)argss_window_ox, 0);
	rb_define_method(ARGSS_Window, "ox=", (rubyfunc)argss_window_oxE, 1);
	rb_define_method(ARGSS_Window, "oy", (rubyfunc)argss_window_oy, 0);
	rb_define_method(ARGSS_Window, "oy=", (rubyfunc)argss_window_oyE, 1);
	rb_define_method(ARGSS_Window, "opacity", (rubyfunc)argss_window_opacity, 0);
	rb_define_method(ARGSS_Window, "opacity=", (rubyfunc)argss_window_opacityE, 1);
	rb_define_method(ARGSS_Window, "back_opacity", (rubyfunc)argss_window_back_opacity, 0);
	rb_define_method(ARGSS_Window, "back_opacity=", (rubyfunc)argss_window_back_opacityE, 1);
	rb_define_method(ARGSS_Window, "contents_opacity", (rubyfunc)argss_window_contents_opacity, 0);
	rb_define_method(ARGSS_Window, "contents_opacity=", (rubyfunc)argss_window_contents_opacityE, 1);
}
