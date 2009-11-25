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

#include "font.h"
#include <string>
extern "C" {
    #include "ruby.h"
}
#include "argss.h"
#include "argss_sdl.h"
#include "aerror.h"
#include "color.h"

VALUE argss_font_new() {
	return rb_class_new_instance(0, 0, ARGSS_Font);
}

TTF_Font* argss_font_getttf(VALUE self) {
	VALUE name_id = rb_iv_get(self, "@name");
	char* name = StringValuePtr(name_id);
	TTF_Font* font = TTF_OpenFont(name, NUM2INT(rb_iv_get(self, "@size")));
	if(!font) {
		rb_raise(ARGSS_Error, "SDL could not load font %s size %d.\n%s\n", name, NUM2INT(rb_iv_get(self, "@size")), TTF_GetError());
	}
	int style = 0;
    if(NUM2BOOL(rb_iv_get(self, "@bold"))) style |= TTF_STYLE_BOLD;
	if(NUM2BOOL(rb_iv_get(self, "@italic"))) style |= TTF_STYLE_ITALIC;
	TTF_SetFontStyle(font, style);
	return font;
}

static VALUE argss_font_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc > 2) {raise_argn(argc, 2);}
	if (argc >= 1) {
		Check_Types2(argv[0], T_STRING, T_ARRAY);
		rb_iv_set(self, "@name", argv[0]);
	}
	else {
		rb_iv_set(self, "@name", rb_cv_get(ARGSS_Font, "@@default_name"));
	}
	if (argc == 2) {
		Check_Type(argv[1], T_FIXNUM);
		rb_iv_set(self, "@size", argv[1]);
	}
	else {
		rb_iv_set(self, "@size", rb_cv_get(ARGSS_Font, "@@default_size"));
	}
	rb_iv_set(self, "@bold", rb_cv_get(ARGSS_Font, "@@default_bold"));
	rb_iv_set(self, "@italic", rb_cv_get(ARGSS_Font, "@@default_italic"));
	rb_iv_set(self, "@color", rb_cv_get(ARGSS_Font, "@@default_color"));
	return self;
}

static VALUE argss_font_existQ(VALUE self) {
	// TODO
	return Qtrue;
}

static VALUE argss_font_name(VALUE self) {
	return rb_iv_get(self, "@name");
}
static VALUE argss_font_nameE(VALUE self, VALUE name) {
	Check_Types2(name, T_STRING, T_ARRAY);
	rb_iv_set(self, "@name", name);
	return name;
}
static VALUE argss_font_size(VALUE self) {
	return rb_iv_get(self, "@size");
}
static VALUE argss_font_sizeE(VALUE self, VALUE size) {
	Check_Type(size, T_FIXNUM);
	rb_iv_set(self, "@size", size);
	return size; 
}
static VALUE argss_font_bold(VALUE self) {
	return rb_iv_get(self, "@bold");
}
static VALUE argss_font_boldE(VALUE self, VALUE bold) {
	Check_Bool(bold);
	rb_iv_set(self, "@bold", bold);
	return bold;
}
static VALUE argss_font_italic(VALUE self) {
	return rb_iv_get(self, "@italic");
}
static VALUE argss_font_italicE(VALUE self, VALUE italic) {
	Check_Bool(italic);
	rb_iv_set(self, "@italic", italic);
	return italic;
}
static VALUE argss_font_color(VALUE self) {
	return rb_iv_get(self, "@color");
}
static VALUE argss_font_colorE(VALUE self, VALUE color) {
	Check_Class(color, ARGSS_Color);
	return rb_iv_set(self, "@color", color);
}

static VALUE argss_font_default_name(VALUE self) {
	return rb_cv_get(ARGSS_Font, "@@default_name");
}
static VALUE argss_font_default_nameE(VALUE self, VALUE default_name) {
	Check_Types2(default_name, T_STRING, T_ARRAY);
	rb_cv_set(ARGSS_Font, "@@default_name", default_name);
	return default_name;
}
static VALUE argss_font_default_size(VALUE self) {
	return rb_cv_get(ARGSS_Font, "@@default_size");
}
static VALUE argss_font_default_sizeE(VALUE self, VALUE default_size) {
	Check_Type(default_size, T_FIXNUM);
	rb_cv_set(ARGSS_Font, "@@default_size", default_size);
	return default_size;
}
static VALUE argss_font_default_bold(VALUE self) {
	return rb_cv_get(ARGSS_Font, "@@default_bold");
}
static VALUE argss_font_default_boldE(VALUE self, VALUE default_bold) {
	Check_Bool(default_bold);
	rb_cv_set(ARGSS_Font, "@@default_bold", default_bold);
	return default_bold;
}
static VALUE argss_font_default_italic(VALUE self) {
	return rb_cv_get(ARGSS_Font, "@@default_italic");
}
static VALUE argss_font_default_italicE(VALUE self, VALUE default_italic) {
	Check_Bool(default_italic);
	rb_cv_set(ARGSS_Font, "@@default_italic", default_italic);
	return default_italic;
}
static VALUE argss_font_default_color(VALUE self) {
	return rb_cv_get(ARGSS_Font, "@@default_color");
}
static VALUE argss_font_default_colorE(VALUE self, VALUE default_color) {
	Check_Class(default_color, ARGSS_Color);
	rb_cv_set(ARGSS_Font, "@@default_color", default_color);
	return default_color;
}

void Init_Font() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Font = rb_define_class("Font", rb_cObject);
    rb_define_method(ARGSS_Font, "initialize", (rubyfunc)argss_font_initialize, -1);
	rb_define_method(ARGSS_Font, "exist?", (rubyfunc)argss_font_existQ, 0);
	rb_define_method(ARGSS_Font, "name", (rubyfunc)argss_font_name, 0);
	rb_define_method(ARGSS_Font, "name=", (rubyfunc)argss_font_nameE, 1);
	rb_define_method(ARGSS_Font, "size", (rubyfunc)argss_font_size, 0);
	rb_define_method(ARGSS_Font, "size=", (rubyfunc)argss_font_sizeE, 1);
	rb_define_method(ARGSS_Font, "bold", (rubyfunc)argss_font_bold, 0);
	rb_define_method(ARGSS_Font, "bold=", (rubyfunc)argss_font_boldE, 1);
	rb_define_method(ARGSS_Font, "italic", (rubyfunc)argss_font_italic, 0);
	rb_define_method(ARGSS_Font, "italic=", (rubyfunc)argss_font_italicE, 1);
	rb_define_method(ARGSS_Font, "color", (rubyfunc)argss_font_color, 0);
	rb_define_method(ARGSS_Font, "color=", (rubyfunc)argss_font_colorE, 1);
	rb_define_singleton_method(ARGSS_Font, "default_name", (rubyfunc)argss_font_default_name, 0);
	rb_define_singleton_method(ARGSS_Font, "default_name=", (rubyfunc)argss_font_default_nameE, 1);
	rb_define_singleton_method(ARGSS_Font, "default_size", (rubyfunc)argss_font_default_size, 0);
	rb_define_singleton_method(ARGSS_Font, "default_size=", (rubyfunc)argss_font_default_sizeE, 1);
	rb_define_singleton_method(ARGSS_Font, "default_bold", (rubyfunc)argss_font_default_bold, 0);
	rb_define_singleton_method(ARGSS_Font, "default_bold=", (rubyfunc)argss_font_default_boldE, 1);
	rb_define_singleton_method(ARGSS_Font, "default_italic", (rubyfunc)argss_font_default_italic, 0);
	rb_define_singleton_method(ARGSS_Font, "default_italic=", (rubyfunc)argss_font_default_italicE, 1);
	rb_define_singleton_method(ARGSS_Font, "default_color", (rubyfunc)argss_font_default_color, 0);
	rb_define_singleton_method(ARGSS_Font, "default_color=", (rubyfunc)argss_font_default_colorE, 1);
	
	rb_cv_set(ARGSS_Font, "@@default_name", rb_str_new2("Arial.ttf\0"));
	rb_cv_set(ARGSS_Font, "@@default_size", INT2NUM(22));
	rb_cv_set(ARGSS_Font, "@@default_bold", Qfalse);
	rb_cv_set(ARGSS_Font, "@@default_italic", Qfalse);
	rb_cv_set(ARGSS_Font, "@@default_color", argss_color_new2(255, 255, 255, 255));
}
