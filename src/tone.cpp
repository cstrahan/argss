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

#include "tone.h"
#include <string>
#include "argss.h"
#include "aerror.h"

double valuecaptone(double v) {
    return (v > 255) ? 255 : (v < -255) ? -255 : v;
}

SDL_Tone argss_tone_getsdl(unsigned long self) {
	SDL_Tone tone;
	tone.r = NUM2INT(rb_iv_get(self, "@red"));
	tone.g = NUM2INT(rb_iv_get(self, "@green"));
	tone.b = NUM2INT(rb_iv_get(self, "@blue"));
	tone.gray = NUM2INT(rb_iv_get(self, "@gray"));
	return tone;
}
VALUE argss_tone_new(VALUE r, VALUE gn, VALUE b, VALUE gy) {
    VALUE args[4] = {r, gn, b, gy};
    return rb_class_new_instance(4, args, ARGSS_Tone);
}
VALUE argss_tone_new2(float r, float gn, float b, float gy) {
    VALUE args[4] = {rb_float_new(r), rb_float_new(gn), rb_float_new(b), rb_float_new(gy)};
    return rb_class_new_instance(4, args, ARGSS_Tone);
}

static VALUE argss_tone_initialize(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) {raise_argn(argc, 3);}
    else if (argc > 4) {raise_argn(argc, 4);}
    Check_Kind(argv[0], rb_cNumeric);
    Check_Kind(argv[1], rb_cNumeric);
    Check_Kind(argv[2], rb_cNumeric);
    double red = valuecaptone(NUM2DBL(argv[0]));
    double green = valuecaptone(NUM2DBL(argv[1]));
    double blue = valuecaptone(NUM2DBL(argv[2]));
    double gray = 0;
    if (argc == 4) {
        Check_Kind(argv[3], rb_cNumeric);
        gray = valuecaptone(NUM2DBL(argv[3]));
    }
    rb_iv_set(self, "@red", rb_float_new(red));
    rb_iv_set(self, "@green", rb_float_new(green));
    rb_iv_set(self, "@blue", rb_float_new(blue));
    rb_iv_set(self, "@gray", rb_float_new(gray));
    return self;
}
static VALUE argss_tone_set(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) {raise_argn(argc, 3);}
    else if (argc > 4) {raise_argn(argc, 4);}
    Check_Kind(argv[0], rb_cNumeric);
    Check_Kind(argv[1], rb_cNumeric);
    Check_Kind(argv[2], rb_cNumeric);
    double red = valuecaptone(NUM2DBL(argv[0]));
    double green = valuecaptone(NUM2DBL(argv[1]));
    double blue = valuecaptone(NUM2DBL(argv[2]));
    double gray = 0;
    if (argc == 4) {
        Check_Kind(argv[3], rb_cNumeric);
        gray = valuecaptone(NUM2DBL(argv[3]));
    }
    rb_iv_set(self, "@red", rb_float_new(red));
    rb_iv_set(self, "@green", rb_float_new(green));
    rb_iv_set(self, "@blue", rb_float_new(blue));
    rb_iv_set(self, "@gray", rb_float_new(gray));
    return self;
}
static VALUE argss_tone_red(VALUE self) {
    return rb_iv_get(self, "@red");
}
static VALUE argss_tone_redE(VALUE self, VALUE r) {
    Check_Kind(r, rb_cNumeric);
    return rb_iv_set(self, "@red", rb_float_new(valuecaptone(NUM2DBL(r))));
}
static VALUE argss_tone_green(VALUE self) {
    return rb_iv_get(self, "@green");
}
static VALUE argss_tone_greenE(VALUE self, VALUE g) {
    Check_Kind(g, rb_cNumeric);
    return rb_iv_set(self, "@green", rb_float_new(valuecaptone(NUM2DBL(g))));
}
static VALUE argss_tone_blue(VALUE self) {
    return rb_iv_get(self, "@blue");
}
static VALUE argss_tone_blueE(VALUE self, VALUE b) {
    Check_Kind(b, rb_cNumeric);
    return rb_iv_set(self, "@blue", rb_float_new(valuecaptone(NUM2DBL(b))));
}
static VALUE argss_tone_gray(VALUE self) {
    return rb_iv_get(self, "@gray");
}
static VALUE argss_tone_grayE(VALUE self, VALUE g) {
    Check_Kind(g, rb_cNumeric);
    return rb_iv_set(self, "@gray", rb_float_new(valuecaptone(NUM2DBL(g))));
}
static VALUE argss_tone_inspect(VALUE self) {
    char str[255];
    long n;
    n = sprintf(str, "(%f, %f, %f, %f)",  NUM2DBL(rb_iv_get(self, "@red")),
                                            NUM2DBL(rb_iv_get(self, "@green")),
                                            NUM2DBL(rb_iv_get(self, "@blue")),
                                            NUM2DBL(rb_iv_get(self, "@gray")));
    std::string str2 = str;
    return rb_str_new(str2.c_str(), n);
}
static VALUE argss_tone_dump(VALUE self) {
    //ToDo
    return self;
}
static VALUE argss_tone_load(VALUE str) {
    //ToDo
    return str;
}

void Init_Tone() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Tone = rb_define_class("Tone", rb_cObject);
    rb_define_method(ARGSS_Tone, "initialize", (rubyfunc)argss_tone_initialize, -1);
    rb_define_method(ARGSS_Tone, "set", (rubyfunc)argss_tone_set, -1);
    rb_define_method(ARGSS_Tone, "red", (rubyfunc)argss_tone_red, 0);
    rb_define_method(ARGSS_Tone, "red=", (rubyfunc)argss_tone_redE, 1);
    rb_define_method(ARGSS_Tone, "green", (rubyfunc)argss_tone_green, 0);
    rb_define_method(ARGSS_Tone, "green=", (rubyfunc)argss_tone_greenE, 1);
    rb_define_method(ARGSS_Tone, "blue", (rubyfunc)argss_tone_blue, 0);
    rb_define_method(ARGSS_Tone, "blue=", (rubyfunc)argss_tone_blueE, 1);
    rb_define_method(ARGSS_Tone, "gray", (rubyfunc)argss_tone_gray, 0);
    rb_define_method(ARGSS_Tone, "gray=", (rubyfunc)argss_tone_grayE, 1);
    rb_define_method(ARGSS_Tone, "inspect", (rubyfunc)argss_tone_inspect, 0);
    rb_define_method(ARGSS_Tone, "_dump", (rubyfunc)argss_tone_dump, -1);
    rb_define_singleton_method(ARGSS_Tone, "_load", (rubyfunc)argss_tone_load, 1);
}
