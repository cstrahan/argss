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
VALUE ARGSS::ATone::rinitialize(int argc, VALUE *argv, VALUE self) {
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
VALUE ARGSS::ATone::rset(int argc, VALUE *argv, VALUE self) {
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
VALUE ARGSS::ATone::rred(VALUE self) {
    return rb_iv_get(self, "@red");
}
VALUE ARGSS::ATone::rredE(VALUE self, VALUE r) {
    return rb_iv_set(self, "@red", rb_float_new(CapToneValue(NUM2DBL(r))));
}
VALUE ARGSS::ATone::rgreen(VALUE self) {
    return rb_iv_get(self, "@green");
}
VALUE ARGSS::ATone::rgreenE(VALUE self, VALUE g) {
    return rb_iv_set(self, "@green", rb_float_new(CapToneValue(NUM2DBL(g))));
}
VALUE ARGSS::ATone::rblue(VALUE self) {
    return rb_iv_get(self, "@blue");
}
VALUE ARGSS::ATone::rblueE(VALUE self, VALUE b) {
    return rb_iv_set(self, "@blue", rb_float_new(CapToneValue(NUM2DBL(b))));
}
VALUE ARGSS::ATone::rgray(VALUE self) {
    return rb_iv_get(self, "@gray");
}
VALUE ARGSS::ATone::rgrayE(VALUE self, VALUE g) {
    return rb_iv_set(self, "@gray", rb_float_new(CapToneValue(NUM2DBL(g))));
}
VALUE ARGSS::ATone::rinspect(VALUE self) {
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
VALUE ARGSS::ATone::rdump(int argc, VALUE* argv, VALUE self) {
	if (argc > 1) raise_argn(argc, 1);
	VALUE arr = rb_ary_new3(4, rb_iv_get(self, "@red"), rb_iv_get(self, "@green"), rb_iv_get(self, "@blue"), rb_iv_get(self, "@gray"));
    return rb_funcall(arr, rb_intern("pack"), 1, rb_str_new2("d4"));
}
VALUE ARGSS::ATone::rload(VALUE self, VALUE str) {
	VALUE arr = rb_funcall(str, rb_intern("unpack"), 1, rb_str_new2("d4"));
	VALUE args[4] = {rb_ary_entry(arr, 0), rb_ary_entry(arr, 1), rb_ary_entry(arr, 2), rb_ary_entry(arr, 3)};
	VALUE tone = rb_class_new_instance(4, args, ARGSS::ATone::id);
    return tone;
}

////////////////////////////////////////////////////////////
/// ARGSS Tone initialize
////////////////////////////////////////////////////////////
void ARGSS::ATone::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Tone", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
    rb_define_method(id, "set", (rubyfunc)rset, -1);
    rb_define_method(id, "red", (rubyfunc)rred, 0);
    rb_define_method(id, "red=", (rubyfunc)rredE, 1);
    rb_define_method(id, "green", (rubyfunc)rgreen, 0);
    rb_define_method(id, "green=", (rubyfunc)rgreenE, 1);
    rb_define_method(id, "blue", (rubyfunc)rblue, 0);
    rb_define_method(id, "blue=", (rubyfunc)rblueE, 1);
    rb_define_method(id, "gray", (rubyfunc)rgray, 0);
    rb_define_method(id, "gray=", (rubyfunc)rgrayE, 1);
    rb_define_method(id, "inspect", (rubyfunc)rinspect, 0);
    rb_define_method(id, "_dump", (rubyfunc)rdump, -1);
    rb_define_singleton_method(id, "_load", (rubyfunc)rload, 1);
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
