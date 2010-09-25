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
#include "argss/classes/afont.h"
#include "argss/classes/acolor.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::AFont::id;

///////////////////////////////////////////////////////////
// ARGSS Font instance methods
///////////////////////////////////////////////////////////
VALUE ARGSS::AFont::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc > 2) raise_argn(argc, 2);
	if (argc >= 1) {
		Check_Types2(argv[0], T_STRING, T_ARRAY);
		rb_iv_set(self, "@name", argv[0]);
	} else {
		rb_iv_set(self, "@name", rb_str_dup(rb_cv_get(ARGSS::AFont::id, "@@default_name")));
	}
	if (argc == 2) {
		Check_Kind(argv[1], rb_cNumeric);
		rb_iv_set(self, "@size", argv[1]);
	} else {
		rb_iv_set(self, "@size", rb_cv_get(ARGSS::AFont::id, "@@default_size"));
	}
	rb_iv_set(self, "@bold", rb_cv_get(ARGSS::AFont::id, "@@default_bold"));
	rb_iv_set(self, "@italic", rb_cv_get(ARGSS::AFont::id, "@@default_italic"));
	rb_iv_set(self, "@color", ARGSS::AColor::New(rb_cv_get(ARGSS::AFont::id, "@@default_color")));
	return self;
}

VALUE ARGSS::AFont::rexistQ(VALUE self) {
	// TODO
	return Qtrue;
}
VALUE ARGSS::AFont::rname(VALUE self) {
	return rb_iv_get(self, "@name");
}
VALUE ARGSS::AFont::rnameE(VALUE self, VALUE name) {
	Check_Types2(name, T_STRING, T_ARRAY);
	rb_iv_set(self, "@name", name);
	return name;
}
VALUE ARGSS::AFont::rsize(VALUE self) {
	return rb_iv_get(self, "@size");
}
VALUE ARGSS::AFont::rsizeE(VALUE self, VALUE size) {
	Check_Kind(size, rb_cNumeric);
	rb_iv_set(self, "@size", size);
	return size;
}
VALUE ARGSS::AFont::rbold(VALUE self) {
	return rb_iv_get(self, "@bold");
}
VALUE ARGSS::AFont::rboldE(VALUE self, VALUE bold) {
	Check_Bool(bold);
	rb_iv_set(self, "@bold", bold);
	return bold;
}
VALUE ARGSS::AFont::ritalic(VALUE self) {
	return rb_iv_get(self, "@italic");
}
VALUE ARGSS::AFont::ritalicE(VALUE self, VALUE italic) {
	Check_Bool(italic);
	rb_iv_set(self, "@italic", italic);
	return italic;
}
VALUE ARGSS::AFont::rcolor(VALUE self) {
	return rb_iv_get(self, "@color");
}
VALUE ARGSS::AFont::rcolorE(VALUE self, VALUE color) {
	Check_Class(color, ARGSS::AColor::id);
	return rb_iv_set(self, "@color", color);
}
VALUE ARGSS::AFont::rshadow(VALUE self) {
	return rb_iv_get(self, "@shadow");
}
VALUE ARGSS::AFont::rshadowE(VALUE self, VALUE shadow) {
	Check_Bool(shadow);
	rb_iv_set(self, "@shadow", shadow);
	return shadow;
}

///////////////////////////////////////////////////////////
// ARGSS Font class methods
///////////////////////////////////////////////////////////
VALUE ARGSS::AFont::rdefault_name(VALUE self) {
	return rb_cv_get(ARGSS::AFont::id, "@@default_name");
}
VALUE ARGSS::AFont::rdefault_nameE(VALUE self, VALUE default_name) {
	Check_Types2(default_name, T_STRING, T_ARRAY);
	rb_cv_set(ARGSS::AFont::id, "@@default_name", default_name);
	return default_name;
}
VALUE ARGSS::AFont::rdefault_size(VALUE self) {
	return rb_cv_get(ARGSS::AFont::id, "@@default_size");
}
VALUE ARGSS::AFont::rdefault_sizeE(VALUE self, VALUE default_size) {
	Check_Kind(default_size, rb_cNumeric);
	rb_cv_set(ARGSS::AFont::id, "@@default_size", default_size);
	return default_size;
}
VALUE ARGSS::AFont::rdefault_bold(VALUE self) {
	return rb_cv_get(ARGSS::AFont::id, "@@default_bold");
}
VALUE ARGSS::AFont::rdefault_boldE(VALUE self, VALUE default_bold) {
	Check_Bool(default_bold);
	rb_cv_set(ARGSS::AFont::id, "@@default_bold", default_bold);
	return default_bold;
}
VALUE ARGSS::AFont::rdefault_italic(VALUE self) {
	return rb_cv_get(ARGSS::AFont::id, "@@default_italic");
}
VALUE ARGSS::AFont::rdefault_italicE(VALUE self, VALUE default_italic) {
	Check_Bool(default_italic);
	rb_cv_set(ARGSS::AFont::id, "@@default_italic", default_italic);
	return default_italic;
}
VALUE ARGSS::AFont::rdefault_color(VALUE self) {
	return rb_cv_get(ARGSS::AFont::id, "@@default_color");
}
VALUE ARGSS::AFont::rdefault_colorE(VALUE self, VALUE default_color) {
	Check_Class(default_color, ARGSS::AColor::id);
	rb_cv_set(ARGSS::AFont::id, "@@default_color", default_color);
	return default_color;
}
VALUE ARGSS::AFont::rdefault_shadow(VALUE self) {
	return rb_cv_get(ARGSS::AFont::id, "@@default_shadow");
}
VALUE ARGSS::AFont::rdefault_shadowE(VALUE self, VALUE default_shadow) {
	Check_Bool(default_shadow);
	rb_cv_set(ARGSS::AFont::id, "@@default_shadow", default_shadow);
	return default_shadow;
}

///////////////////////////////////////////////////////////
/// ARGSS Font initialize
///////////////////////////////////////////////////////////
void ARGSS::AFont::Init() {
	id = rb_define_class("Font", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "exist?", (rubyfunc)rexistQ, 0);
	rb_define_method(id, "name", (rubyfunc)rname, 0);
	rb_define_method(id, "name=", (rubyfunc)rnameE, 1);
	rb_define_method(id, "size", (rubyfunc)rsize, 0);
	rb_define_method(id, "size=", (rubyfunc)rsizeE, 1);
	rb_define_method(id, "bold", (rubyfunc)rbold, 0);
	rb_define_method(id, "bold=", (rubyfunc)rboldE, 1);
	rb_define_method(id, "italic", (rubyfunc)ritalic, 0);
	rb_define_method(id, "italic=", (rubyfunc)ritalicE, 1);
	rb_define_method(id, "color", (rubyfunc)rcolor, 0);
	rb_define_method(id, "color=", (rubyfunc)rcolorE, 1);
	rb_define_method(id, "shadow", (rubyfunc)rshadow, 0);
	rb_define_method(id, "shadow=", (rubyfunc)rshadowE, 1);
	rb_define_singleton_method(id, "default_name", (rubyfunc)rdefault_name, 0);
	rb_define_singleton_method(id, "default_name=", (rubyfunc)rdefault_nameE, 1);
	rb_define_singleton_method(id, "default_size", (rubyfunc)rdefault_size, 0);
	rb_define_singleton_method(id, "default_size=", (rubyfunc)rdefault_sizeE, 1);
	rb_define_singleton_method(id, "default_bold", (rubyfunc)rdefault_bold, 0);
	rb_define_singleton_method(id, "default_bold=", (rubyfunc)rdefault_boldE, 1);
	rb_define_singleton_method(id, "default_italic", (rubyfunc)rdefault_italic, 0);
	rb_define_singleton_method(id, "default_italic=", (rubyfunc)rdefault_italicE, 1);
	rb_define_singleton_method(id, "default_color", (rubyfunc)rdefault_color, 0);
	rb_define_singleton_method(id, "default_color=", (rubyfunc)rdefault_colorE, 1);
	rb_define_singleton_method(id, "default_shadow", (rubyfunc)rdefault_shadow, 0);
	rb_define_singleton_method(id, "default_shadow=", (rubyfunc)rdefault_shadowE, 1);
	rb_cv_set(id, "@@default_name", rb_str_new2("Arial"));
	rb_cv_set(id, "@@default_size", INT2NUM(22));
	rb_cv_set(id, "@@default_bold", Qfalse);
	rb_cv_set(id, "@@default_italic", Qfalse);
	rb_cv_set(id, "@@default_color", ARGSS::AColor::New(255, 255, 255, 255));
	rb_cv_set(id, "@@default_shadow", Qfalse);
}

///////////////////////////////////////////////////////////
// ARGSS Font create new instance
///////////////////////////////////////////////////////////
VALUE ARGSS::AFont::New() {
	return rb_class_new_instance(0, 0, id);
}
