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
#include "argss/classes/arect.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ARect::id;

////////////////////////////////////////////////////////////
/// ARGSS Rect ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::ARect::rinitialize(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h) {
	Check_Kind(x, rb_cNumeric);
	Check_Kind(y, rb_cNumeric);
	Check_Kind(w, rb_cNumeric);
	Check_Kind(h, rb_cNumeric);
	rb_iv_set(self, "@x", x);
	rb_iv_set(self, "@y", y);
	rb_iv_set(self, "@width", w);
	rb_iv_set(self, "@height", h);
	return self;
}
VALUE ARGSS::ARect::rset(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h) {
	Check_Kind(x, rb_cNumeric);
	Check_Kind(y, rb_cNumeric);
	Check_Kind(w, rb_cNumeric);
	Check_Kind(h, rb_cNumeric);
	rb_iv_set(self, "@x", x);
	rb_iv_set(self, "@y", y);
	rb_iv_set(self, "@width", w);
	rb_iv_set(self, "@height", h);
	return self;
}
VALUE ARGSS::ARect::rx(VALUE self) {
	return rb_iv_get(self, "@x");
}
VALUE ARGSS::ARect::rxE(VALUE self, VALUE x) {
	Check_Kind(x, rb_cNumeric);
	return rb_iv_set(self, "@x", x);
}
VALUE ARGSS::ARect::ry(VALUE self) {
	return rb_iv_get(self, "@y");
}
VALUE ARGSS::ARect::ryE(VALUE self, VALUE y) {
	Check_Kind(y, rb_cNumeric);
	return rb_iv_set(self, "@y", y);
}
VALUE ARGSS::ARect::rwidth(VALUE self) {
	return rb_iv_get(self, "@width");
}
VALUE ARGSS::ARect::rwidthE(VALUE self, VALUE w) {
	Check_Kind(w, rb_cNumeric);
	return rb_iv_set(self, "@width", w);
}
VALUE ARGSS::ARect::rheight(VALUE self) {
	return rb_iv_get(self, "@height");
}
VALUE ARGSS::ARect::rheightE(VALUE self, VALUE h) {
	Check_Kind(h, rb_cNumeric);
	return rb_iv_set(self, "@height", h);
}
VALUE ARGSS::ARect::rempty(VALUE self) {
	rb_iv_set(self, "@x", INT2NUM(0));
	rb_iv_set(self, "@y", INT2NUM(0));
	rb_iv_set(self, "@width", INT2NUM(0));
	rb_iv_set(self, "@height", INT2NUM(0));
	return self;
}
VALUE ARGSS::ARect::rinspect(VALUE self) {
	char str[255];
	long n;
	n = sprintf(str, "(%i, %i, %i, %i)", NUM2INT(rb_iv_get(self, "@x")),
										NUM2INT(rb_iv_get(self, "@y")),
										NUM2INT(rb_iv_get(self, "@width")),
										NUM2INT(rb_iv_get(self, "@height")));
	return rb_str_new(str, n);
}
VALUE ARGSS::ARect::rdump(int argc, VALUE* argv, VALUE self) {
	if (argc > 1) raise_argn(argc, 1);
	VALUE arr = rb_ary_new3(4, rb_iv_get(self, "@x"), rb_iv_get(self, "@y"), rb_iv_get(self, "@width"), rb_iv_get(self, "@height"));
	return rb_funcall(arr, rb_intern("pack"), 1, rb_str_new2("l4"));
}
VALUE ARGSS::ARect::rload(VALUE self, VALUE str) {
	VALUE arr = rb_funcall(str, rb_intern("unpack"), 1, rb_str_new2("l4"));
	VALUE args[4] = {rb_ary_entry(arr, 0), rb_ary_entry(arr, 1), rb_ary_entry(arr, 2), rb_ary_entry(arr, 3)};
	VALUE rect = rb_class_new_instance(4, args, ARGSS::ARect::id);
	return rect;
}

////////////////////////////////////////////////////////////
/// ARGSS Rect initialize
////////////////////////////////////////////////////////////
void ARGSS::ARect::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_class("Rect", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, 4);
	rb_define_method(id, "set", (rubyfunc)rset, 4);
	rb_define_method(id, "x", (rubyfunc)rx, 0);
	rb_define_method(id, "x=", (rubyfunc)rxE, 1);
	rb_define_method(id, "y", (rubyfunc)ry, 0);
	rb_define_method(id, "y=", (rubyfunc)ryE, 1);
	rb_define_method(id, "width", (rubyfunc)rwidth, 0);
	rb_define_method(id, "width=", (rubyfunc)rwidthE, 1);
	rb_define_method(id, "height", (rubyfunc)rheight, 0);
	rb_define_method(id, "height=", (rubyfunc)rheightE, 1);
	rb_define_method(id, "empty", (rubyfunc)rempty, 0);
	rb_define_method(id, "inspect", (rubyfunc)rinspect, 0);
	rb_define_method(id, "_dump", (rubyfunc)rdump, -1);
	rb_define_singleton_method(id, "_load", (rubyfunc)rload, 1);
}

////////////////////////////////////////////////////////////
/// ARGSS Rect new instance
////////////////////////////////////////////////////////////
VALUE ARGSS::ARect::New(double x, double y, double width, double height) {
	VALUE args[4] = {rb_float_new(x), rb_float_new(y), rb_float_new(width), rb_float_new(height)};
	return rb_class_new_instance(4, args, id);
}
