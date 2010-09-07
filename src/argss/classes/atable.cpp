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
#include <string>
#include "argss/classes/atable.h"
#include "output.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::ATable::id;

///////////////////////////////////////////////////////////
/// ARGSS Table ruby functions
///////////////////////////////////////////////////////////
VALUE ARGSS::ATable::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc < 1) raise_argn(argc, 1);
	else if (argc > 3) raise_argn(argc, 3);
	rb_iv_set(self, "@dim", INT2NUM(argc));
	int xsize = 1;
	int ysize = 1;
	int zsize = 1;
	switch (argc) {
	case 3:
		zsize = NUM2INT(argv[2]);
	case 2:
		ysize = NUM2INT(argv[1]);
	case 1:
		xsize = NUM2INT(argv[0]);
	}
	rb_iv_set(self, "@xsize", INT2NUM(xsize));
	rb_iv_set(self, "@ysize", INT2NUM(ysize));
	rb_iv_set(self, "@zsize", INT2NUM(zsize));
	VALUE arr = rb_ary_new3(xsize * ysize * zsize, INT2NUM(0));
	rb_iv_set(self, "@data", arr);
	rb_iv_set(self, "@modified", Qtrue);
	return self;
}
VALUE ARGSS::ATable::rresize(int argc, VALUE* argv, VALUE self) {
	int xsize = 1;
	int ysize = 1;
	int zsize = 1;
	switch (argc) {
	case 3:
		zsize = NUM2INT(argv[2]);
	case 2:
		ysize = NUM2INT(argv[1]);
	case 1:
		xsize = NUM2INT(argv[0]);
	}
	int nsize = xsize * ysize * zsize;
	int osize;
	osize = NUM2INT(rb_iv_get(self, "@xsize")) * NUM2INT(rb_iv_get(self, "@xsize")) *
			NUM2INT(rb_iv_get(self, "@xsize"));
	if (nsize != osize) {
		if (nsize > osize) {
			VALUE arr = rb_ary_new3(nsize - osize, INT2NUM(0));
			rb_ary_concat(rb_iv_get(self, "@data"), arr);
		} else {
			VALUE slice_argv[2];
			slice_argv[0] = INT2NUM(nsize);
			slice_argv[1] = INT2NUM(osize);
			rb_funcall2(rb_iv_get(self, "@data"), rb_intern("slice!"), 2, slice_argv);
		}
		rb_iv_set(self, "@modified", Qtrue);
	}
	return self;
}
VALUE ARGSS::ATable::rxsize(VALUE self) {
	return rb_iv_get(self, "@xsize");
}
VALUE ARGSS::ATable::rysize(VALUE self) {
	return rb_iv_get(self, "@ysize");
}
VALUE ARGSS::ATable::rzsize(VALUE self) {
	return rb_iv_get(self, "@zsize");
}
VALUE ARGSS::ATable::raref(int argc, VALUE* argv, VALUE self) {
	int dim = NUM2INT(rb_iv_get(self, "@dim"));
	if (argc != dim) raise_argn(argc, dim);
	int x = 0;
	int y = 0;
	int z = 0;
	switch (argc) {
	case 3:
		z = NUM2INT(argv[2]);
	case 2:
		y = NUM2INT(argv[1]);
	case 1:
		x = NUM2INT(argv[0]);
	}
	VALUE data = rb_iv_get(self, "@data");
	int xsize = NUM2INT(rb_iv_get(self, "@xsize"));
	int ysize = NUM2INT(rb_iv_get(self, "@ysize"));
	int zsize = NUM2INT(rb_iv_get(self, "@zsize"));
	if (x >= xsize || y >= ysize || z >= zsize) {
		return Qnil;
	} else {
		return rb_ary_entry(data, x + y * xsize + z * xsize * ysize);
	}
}
VALUE ARGSS::ATable::raset(int argc, VALUE* argv, VALUE self) {
	int dim = NUM2INT(rb_iv_get(self, "@dim"));
	if (argc != (dim + 1)) raise_argn(argc, dim + 1);
	int x = 0;
	int y = 0;
	int z = 0;
	switch (argc) {
	case 3:
		z = NUM2INT(argv[2]);
	case 2:
		y = NUM2INT(argv[1]);
	case 1:
		x = NUM2INT(argv[0]);
	}
	int val = NUM2INT(argv[argc - 1]);
	if (val > 65535) val = 65535;
	else if (val < 0) val = 0;
	VALUE data = rb_iv_get(self, "@data");
	int xsize = NUM2INT(rb_iv_get(self, "@xsize"));
	int ysize = NUM2INT(rb_iv_get(self, "@ysize"));
	int zsize = NUM2INT(rb_iv_get(self, "@zsize"));
	if (x < xsize && y < ysize && z < zsize) {
		if (INT2NUM(val) != rb_ary_entry(data, x + y * xsize + z * xsize * ysize)) {
			rb_iv_set(self, "@modified", Qtrue);
		}
		rb_ary_store(data, x + y * xsize + z * xsize * ysize, INT2NUM(val));
	}
	return argv[argc - 1];
}
VALUE ARGSS::ATable::rdump(int argc, VALUE* argv, VALUE self) {
	if (argc > 1) raise_argn(argc, 1);
	VALUE str = rb_str_new2("");
	VALUE xsize = rb_iv_get(self, "@xsize");
	VALUE ysize = rb_iv_get(self, "@ysize");
	VALUE zsize = rb_iv_get(self, "@zsize");
	unsigned long items = NUM2INT(xsize) * NUM2INT(ysize) * NUM2INT(zsize);
	VALUE arr = rb_ary_new3(5, rb_iv_get(self, "@dim"), xsize, ysize, zsize, INT2NUM(items));
	rb_str_concat(str, rb_funcall(arr, rb_intern("pack"), 1, rb_str_new2("L5")));
	rb_str_concat(str, rb_funcall(rb_iv_get(self, "@data"), rb_intern("pack"), 1, rb_str_times(rb_str_new2("S"), INT2NUM(items))));
	return str;
}
VALUE ARGSS::ATable::rload(VALUE self, VALUE str) {
	VALUE arr = rb_funcall(str, rb_intern("unpack"), 1, rb_str_new2("L5"));
	int dim = NUM2INT(rb_ary_entry(arr, 0));
	unsigned long items = NUM2INT(rb_ary_entry(arr, 4));
	VALUE args[3] = {rb_ary_entry(arr, 1), rb_ary_entry(arr, 2), rb_ary_entry(arr, 3)};
	VALUE table = rb_class_new_instance(dim, args, ARGSS::ATable::id);
	VALUE data = rb_funcall(rb_str_substr(str, 20, items * 2), rb_intern("unpack"), 1, rb_str_times(rb_str_new2("S"), INT2NUM(items)));
	rb_iv_set(table, "@data", data);
	return table;
}

///////////////////////////////////////////////////////////
/// ARGSS Console initialize
///////////////////////////////////////////////////////////
void ARGSS::ATable::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_class("Table", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "resize", (rubyfunc)rresize, -1);
	rb_define_method(id, "xsize", (rubyfunc)rxsize, 0);
	rb_define_method(id, "ysize", (rubyfunc)rysize, 0);
	rb_define_method(id, "zsize", (rubyfunc)rzsize, 0);
	rb_define_method(id, "[]", (rubyfunc)raref, -1);
	rb_define_method(id, "[]=", (rubyfunc)raset, -1);
	rb_define_method(id, "_dump", (rubyfunc)rdump, -1);
	rb_define_singleton_method(id, "_load", (rubyfunc)rload, 1);
}

///////////////////////////////////////////////////////////
/// ARGSS Table new ruby instance
///////////////////////////////////////////////////////////
VALUE ARGSS::ATable::New(int xsize) {
	VALUE args[1] = {INT2NUM(xsize)};
	return rb_class_new_instance(1, args, id);
}
VALUE ARGSS::ATable::New(int xsize, int ysize) {
	VALUE args[2] = {INT2NUM(xsize), INT2NUM(ysize)};
	return rb_class_new_instance(2, args, id);
}
VALUE ARGSS::ATable::New(int xsize, int ysize, int zsize) {
	VALUE args[3] = {INT2NUM(xsize), INT2NUM(ysize), INT2NUM(zsize)};
	return rb_class_new_instance(3, args, id);
}
