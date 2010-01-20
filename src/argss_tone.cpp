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
#include "argss_tone.h"
#include "tone.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ATone::id;

////////////////////////////////////////////////////////////
/// Cap tone value between 0 and 255
////////////////////////////////////////////////////////////
double CapToneValue(double v) {
    return (v > 255) ? 255 : (v < -255) ? -255 : v;
}

////////////////////////////////////////////////////////////
/// ARGSS Tone ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_tone_initialize(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) raise_argn(argc, 3);
    else if (argc > 4) raise_argn(argc, 4);
	rb_iv_set(self, "@red", rb_float_new(CapToneValue(NUM2DBL(argv[0]))));
    rb_iv_set(self, "@green", rb_float_new(CapToneValue(NUM2DBL(argv[1]))));
    rb_iv_set(self, "@blue", rb_float_new(CapToneValue(NUM2DBL(argv[2]))));
    if (argc == 4) {
		rb_iv_set(self, "@gray", rb_float_new(CapToneValue(NUM2DBL(argv[3]))));
    }
	else {
		rb_iv_set(self, "@gray", rb_float_new(0));
	}
    return self;
}
static VALUE argss_tone_set(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) raise_argn(argc, 3);
    else if (argc > 4) raise_argn(argc, 4);
	rb_iv_set(self, "@red", rb_float_new(CapToneValue(NUM2DBL(argv[0]))));
    rb_iv_set(self, "@green", rb_float_new(CapToneValue(NUM2DBL(argv[1]))));
    rb_iv_set(self, "@blue", rb_float_new(CapToneValue(NUM2DBL(argv[2]))));
    if (argc == 4) {
		rb_iv_set(self, "@gray", rb_float_new(CapToneValue(NUM2DBL(argv[3]))));
    }
	else {
		rb_iv_set(self, "@gray", rb_float_new(255));
	}
    return self;
}
static VALUE argss_tone_red(VALUE self) {
    return rb_iv_get(self, "@red");
}
static VALUE argss_tone_redE(VALUE self, VALUE r) {
    return rb_iv_set(self, "@red", rb_float_new(CapToneValue(NUM2DBL(r))));
}
static VALUE argss_tone_green(VALUE self) {
    return rb_iv_get(self, "@green");
}
static VALUE argss_tone_greenE(VALUE self, VALUE g) {
    return rb_iv_set(self, "@green", rb_float_new(CapToneValue(NUM2DBL(g))));
}
static VALUE argss_tone_blue(VALUE self) {
    return rb_iv_get(self, "@blue");
}
static VALUE argss_tone_blueE(VALUE self, VALUE b) {
    return rb_iv_set(self, "@blue", rb_float_new(CapToneValue(NUM2DBL(b))));
}
static VALUE argss_tone_gray(VALUE self) {
    return rb_iv_get(self, "@gray");
}
static VALUE argss_tone_grayE(VALUE self, VALUE g) {
    return rb_iv_set(self, "@gray", rb_float_new(CapToneValue(NUM2DBL(g))));
}
static VALUE argss_tone_inspect(VALUE self) {
    char str[255];
    long n;
#ifdef MSVC
    n = sprintf_s(str, 255, "(%f, %f, %f, %f)",  NUM2DBL(rb_iv_get(self, "@red")),
                                            NUM2DBL(rb_iv_get(self, "@green")),
                                            NUM2DBL(rb_iv_get(self, "@blue")),
                                            NUM2DBL(rb_iv_get(self, "@gray")));
#else
	n = sprintf(str, "(%f, %f, %f, %f)",  NUM2DBL(rb_iv_get(self, "@red")),
                                            NUM2DBL(rb_iv_get(self, "@green")),
                                            NUM2DBL(rb_iv_get(self, "@blue")),
                                            NUM2DBL(rb_iv_get(self, "@gray")));
#endif
    return rb_str_new(str, n);
}
static VALUE argss_tone_dump(VALUE self) {
    //ToDo
    return self;
}
static VALUE argss_tone_load(VALUE str) {
    //ToDo
    return str;
}

////////////////////////////////////////////////////////////
/// ARGSS Tone initialize
////////////////////////////////////////////////////////////
void ARGSS::ATone::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Tone", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)argss_tone_initialize, -1);
    rb_define_method(id, "set", (rubyfunc)argss_tone_set, -1);
    rb_define_method(id, "red", (rubyfunc)argss_tone_red, 0);
    rb_define_method(id, "red=", (rubyfunc)argss_tone_redE, 1);
    rb_define_method(id, "green", (rubyfunc)argss_tone_green, 0);
    rb_define_method(id, "green=", (rubyfunc)argss_tone_greenE, 1);
    rb_define_method(id, "blue", (rubyfunc)argss_tone_blue, 0);
    rb_define_method(id, "blue=", (rubyfunc)argss_tone_blueE, 1);
    rb_define_method(id, "gray", (rubyfunc)argss_tone_gray, 0);
    rb_define_method(id, "gray=", (rubyfunc)argss_tone_grayE, 1);
    rb_define_method(id, "inspect", (rubyfunc)argss_tone_inspect, 0);
    rb_define_method(id, "_dump", (rubyfunc)argss_tone_dump, -1);
    rb_define_singleton_method(id, "_load", (rubyfunc)argss_tone_load, 1);
}

////////////////////////////////////////////////////////////
/// ARGSS Tone new ruby instance
////////////////////////////////////////////////////////////
VALUE ARGSS::ATone::New(double r, double g, double b, double gray) {
	VALUE args[4] = {rb_float_new(r), rb_float_new(g), rb_float_new(b), rb_float_new(gray)};
	return rb_class_new_instance(4, args, id);
}
VALUE ARGSS::ATone::New() {
	VALUE args[4] = {rb_float_new(0), rb_float_new(0), rb_float_new(0), rb_float_new(0)};
	return rb_class_new_instance(4, args, id);
}
