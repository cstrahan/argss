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
VALUE ARGSS::AColor::rinitialize(int argc, VALUE *argv, VALUE self) {
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
VALUE ARGSS::AColor::rset(int argc, VALUE *argv, VALUE self) {
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
VALUE ARGSS::AColor::rred(VALUE self) {
    return rb_iv_get(self, "@red");
}
VALUE ARGSS::AColor::rredE(VALUE self, VALUE red) {
    return rb_iv_set(self, "@red", rb_float_new(CapColorValue(NUM2DBL(red))));
}
VALUE ARGSS::AColor::rgreen(VALUE self) {
    return rb_iv_get(self, "@green");
}
VALUE ARGSS::AColor::rgreenE(VALUE self, VALUE green) {
    return rb_iv_set(self, "@green", rb_float_new(CapColorValue(NUM2DBL(green))));
}
VALUE ARGSS::AColor::rblue(VALUE self) {
    return rb_iv_get(self, "@blue");
}
VALUE ARGSS::AColor::rblueE(VALUE self, VALUE blue) {
    return rb_iv_set(self, "@blue", rb_float_new(CapColorValue(NUM2DBL(blue))));
}
VALUE ARGSS::AColor::ralpha(VALUE self) {
    return rb_iv_get(self, "@alpha");
}
VALUE ARGSS::AColor::ralphaE(VALUE self, VALUE alpha) {
    return rb_iv_set(self, "@alpha", rb_float_new(CapColorValue(NUM2DBL(alpha))));
}
VALUE ARGSS::AColor::rinspect(VALUE self) {
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
VALUE ARGSS::AColor::rdump(int argc, VALUE* argv, VALUE self) {
	if (argc > 1) raise_argn(argc, 1);
	VALUE arr = rb_ary_new3(4, rb_iv_get(self, "@red"), rb_iv_get(self, "@green"), rb_iv_get(self, "@blue"), rb_iv_get(self, "@alpha"));
    return rb_funcall(arr, rb_intern("pack"), 1, rb_str_new2("d4"));
}
VALUE ARGSS::AColor::rload(VALUE self, VALUE str) {
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
    rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
    rb_define_method(id, "set", (rubyfunc)rset, -1);
    rb_define_method(id, "red", (rubyfunc)rred, 0);
    rb_define_method(id, "red=", (rubyfunc)rredE, 1);
    rb_define_method(id, "green", (rubyfunc)rgreen, 0);
    rb_define_method(id, "green=", (rubyfunc)rgreenE, 1);
    rb_define_method(id, "blue", (rubyfunc)rblue, 0);
    rb_define_method(id, "blue=", (rubyfunc)rblueE, 1);
    rb_define_method(id, "alpha", (rubyfunc)ralpha, 0);
    rb_define_method(id, "alpha=", (rubyfunc)ralphaE, 1);
    rb_define_method(id, "inspect", (rubyfunc)rinspect, 0);
    rb_define_method(id, "_dump", (rubyfunc)rdump, -1);
    rb_define_singleton_method(id, "_load", (rubyfunc)rload, 1);
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
