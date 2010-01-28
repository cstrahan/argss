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
#include "argss_color.h"
#include "color.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::AColor::id;

////////////////////////////////////////////////////////////
/// Cap color value between 0 and 255
////////////////////////////////////////////////////////////
double CapColorValue(double v) {
    return (v > 255) ? 255 : (v < 0) ? 0 : v;
}

////////////////////////////////////////////////////////////
/// ARGSS Color ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_color_initialize(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) raise_argn(argc, 3);
    else if (argc > 4) raise_argn(argc, 4);
	rb_iv_set(self, "@red", rb_float_new(CapColorValue(NUM2DBL(argv[0]))));
    rb_iv_set(self, "@green", rb_float_new(CapColorValue(NUM2DBL(argv[1]))));
    rb_iv_set(self, "@blue", rb_float_new(CapColorValue(NUM2DBL(argv[2]))));
    if (argc == 4) {
		rb_iv_set(self, "@alpha", rb_float_new(CapColorValue(NUM2DBL(argv[3]))));
    }
	else {
		rb_iv_set(self, "@alpha", rb_float_new(255));
	}
    return self;
}
static VALUE argss_color_set(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) raise_argn(argc, 3);
    else if (argc > 4) raise_argn(argc, 4);
	rb_iv_set(self, "@red", rb_float_new(CapColorValue(NUM2DBL(argv[0]))));
    rb_iv_set(self, "@green", rb_float_new(CapColorValue(NUM2DBL(argv[1]))));
    rb_iv_set(self, "@blue", rb_float_new(CapColorValue(NUM2DBL(argv[2]))));
    if (argc == 4) {
		rb_iv_set(self, "@alpha", rb_float_new(CapColorValue(NUM2DBL(argv[3]))));
    }
	else {
		rb_iv_set(self, "@alpha", rb_float_new(255));
	}
    return self;
}
static VALUE argss_color_red(VALUE self) {
    return rb_iv_get(self, "@red");
}
static VALUE argss_color_redE(VALUE self, VALUE red) {
    return rb_iv_set(self, "@red", rb_float_new(CapColorValue(NUM2DBL(red))));
}
static VALUE argss_color_green(VALUE self) {
    return rb_iv_get(self, "@green");
}
static VALUE argss_color_greenE(VALUE self, VALUE green) {
    return rb_iv_set(self, "@green", rb_float_new(CapColorValue(NUM2DBL(green))));
}
static VALUE argss_color_blue(VALUE self) {
    return rb_iv_get(self, "@blue");
}
static VALUE argss_color_blueE(VALUE self, VALUE blue) {
    return rb_iv_set(self, "@blue", rb_float_new(CapColorValue(NUM2DBL(blue))));
}
static VALUE argss_color_alpha(VALUE self) {
    return rb_iv_get(self, "@alpha");
}
static VALUE argss_color_alphaE(VALUE self, VALUE alpha) {
    return rb_iv_set(self, "@alpha", rb_float_new(CapColorValue(NUM2DBL(alpha))));
}
static VALUE argss_color_inspect(VALUE self) {
    char str[255];
    long n;
#ifdef MSVC
    n = sprintf_s(str, 255, "(%f, %f, %f, %f)\0",  NUM2DBL(rb_iv_get(self, "@red")),
                                            NUM2DBL(rb_iv_get(self, "@green")),
                                            NUM2DBL(rb_iv_get(self, "@blue")),
                                            NUM2DBL(rb_iv_get(self, "@alpha")));
#else
	n = sprintf(str, "(%f, %f, %f, %f)\0",  NUM2DBL(rb_iv_get(self, "@red")),
                                            NUM2DBL(rb_iv_get(self, "@green")),
                                            NUM2DBL(rb_iv_get(self, "@blue")),
                                            NUM2DBL(rb_iv_get(self, "@alpha")));
#endif
    return rb_str_new(str, n);
}
static VALUE argss_color_dump(int argc, VALUE* argv, VALUE self) {
	if (argc > 1) raise_argn(argc, 1);
	VALUE arr = rb_ary_new3(4, rb_iv_get(self, "@red"), rb_iv_get(self, "@green"), rb_iv_get(self, "@blue"), rb_iv_get(self, "@alpha"));
    return rb_funcall(arr, rb_intern("pack"), 1, rb_str_new2("d4"));
}
static VALUE argss_color_load(VALUE self, VALUE str) {
	VALUE arr = rb_funcall(str, rb_intern("unpack"), 1, rb_str_new2("d4"));
	VALUE args[4] = {rb_ary_entry(arr, 0), rb_ary_entry(arr, 1), rb_ary_entry(arr, 2), rb_ary_entry(arr, 3)};
	VALUE color = rb_class_new_instance(4, args, ARGSS::AColor::id);
    return color;
}

////////////////////////////////////////////////////////////
/// ARGSS Color initialize
////////////////////////////////////////////////////////////
void ARGSS::AColor::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Color", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)argss_color_initialize, -1);
    rb_define_method(id, "set", (rubyfunc)argss_color_set, -1);
    rb_define_method(id, "red", (rubyfunc)argss_color_red, 0);
    rb_define_method(id, "red=", (rubyfunc)argss_color_redE, 1);
    rb_define_method(id, "green", (rubyfunc)argss_color_green, 0);
    rb_define_method(id, "green=", (rubyfunc)argss_color_greenE, 1);
    rb_define_method(id, "blue", (rubyfunc)argss_color_blue, 0);
    rb_define_method(id, "blue=", (rubyfunc)argss_color_blueE, 1);
    rb_define_method(id, "alpha", (rubyfunc)argss_color_alpha, 0);
    rb_define_method(id, "alpha=", (rubyfunc)argss_color_alphaE, 1);
    rb_define_method(id, "inspect", (rubyfunc)argss_color_inspect, 0);
    rb_define_method(id, "_dump", (rubyfunc)argss_color_dump, -1);
    rb_define_singleton_method(id, "_load", (rubyfunc)argss_color_load, 1);
}

////////////////////////////////////////////////////////////
/// ARGSS Color new ruby instance
////////////////////////////////////////////////////////////
VALUE ARGSS::AColor::New() {
	VALUE args[4] = {rb_float_new(0), rb_float_new(0), rb_float_new(0), rb_float_new(255)};
	return rb_class_new_instance(4, args, id);
}
VALUE ARGSS::AColor::New(VALUE color) {
	VALUE args[4] = {rb_iv_get(color, "@red"), rb_iv_get(color, "@green"), rb_iv_get(color, "@blue"), rb_iv_get(color, "@alpha")};
	return rb_class_new_instance(4, args, id);
}
VALUE ARGSS::AColor::New(double r, double g, double b, double a) {
	VALUE args[4] = {rb_float_new(r), rb_float_new(g), rb_float_new(b), rb_float_new(a)};
	return rb_class_new_instance(4, args, id);
}
