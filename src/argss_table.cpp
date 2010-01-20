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
#include "argss_table.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ATable::id;

////////////////////////////////////////////////////////////
/// ARGSS Table ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_table_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc < 1) raise_argn(argc, 1);
    else if (argc > 3) raise_argn(argc, 3);
	rb_iv_set(self, "@dim", INT2NUM(argc));
	int xsize = 1;
	int ysize = 1;
	int zsize = 1;
	switch(argc) {
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
	return self;
}
static VALUE argss_table_resize(int argc, VALUE *argv, VALUE self) {
	int xsize = 1;
	int ysize = 1;
	int zsize = 1;
	switch(argc) {
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
	if(nsize != osize) {
		if(nsize > osize) {
			VALUE arr = rb_ary_new3(nsize - osize, INT2NUM(0));
			rb_ary_concat(rb_iv_get(self, "@data"), arr);
		}
		else {
			VALUE slice_argv[2];
			slice_argv[0] = INT2NUM(nsize);
			slice_argv[1] = INT2NUM(osize);
			
			rb_funcall2(rb_iv_get(self, "@data"), rb_intern("slice!"), 2, slice_argv) ;
		}
	}
	return self;
}
static VALUE argss_table_xsize(VALUE self) {
	return rb_iv_get(self, "@xsize");
}
static VALUE argss_table_ysize(VALUE self) {
	return rb_iv_get(self, "@ysize");
}
static VALUE argss_table_zsize(VALUE self) {
	return rb_iv_get(self, "@zsize");
}
static VALUE argss_table_aref(int argc, VALUE *argv, VALUE self) {
	int dim = NUM2INT(rb_iv_get(self, "@dim"));
	if (argc != dim) raise_argn(argc, dim);
	int x = 1;
	int y = 1;
	int z = 1;
	switch(argc) {
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
	if(x > xsize || y > ysize || z > zsize) {
		return Qnil;
	}
	else {
		return rb_ary_entry(data, x + y * xsize + z * xsize * ysize);
	}
}
static VALUE argss_table_aset(int argc, VALUE *argv, VALUE self) {
	int dim = NUM2INT(rb_iv_get(self, "@dim"));
	if (argc != (dim + 1)) raise_argn(argc, dim + 1);
	int x = 1;
	int y = 1;
	int z = 1;
	switch(argc) {
		case 3:
			z = NUM2INT(argv[2]);
		case 2:
			y = NUM2INT(argv[1]);
		case 1:
			x = NUM2INT(argv[0]);
	}
	int val = NUM2INT(argv[argc - 1]);
	if(val > 65535) val = 65535;
	else if(val < 0) val = 0;
	VALUE data = rb_iv_get(self, "@data");
	int xsize = NUM2INT(rb_iv_get(self, "@xsize"));
	int ysize = NUM2INT(rb_iv_get(self, "@ysize"));
	int zsize = NUM2INT(rb_iv_get(self, "@zsize"));
	if(x < xsize && y < ysize && z < zsize) {
		rb_ary_store(data, x + y * xsize + z * xsize * ysize, INT2NUM(val));
	}
	return argv[argc - 1];
}
static VALUE argss_table_dump(VALUE self) {
    //ToDo
    return self;
}
static VALUE argss_table_load(VALUE str) {
    //ToDo
    return str;
}

////////////////////////////////////////////////////////////
/// ARGSS Console initialize
////////////////////////////////////////////////////////////
void ARGSS::ATable::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("Table", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)argss_table_initialize, -1);
	rb_define_method(id, "resize", (rubyfunc)argss_table_resize, -1);
	rb_define_method(id, "xsize", (rubyfunc)argss_table_xsize, 0);
	rb_define_method(id, "ysize", (rubyfunc)argss_table_ysize, 0);
	rb_define_method(id, "zsize", (rubyfunc)argss_table_zsize, 0);
	rb_define_method(id, "[]", (rubyfunc)argss_table_aref, -1);
	rb_define_method(id, "[]=", (rubyfunc)argss_table_aset, -1);
	rb_define_method(id, "_dump", (rubyfunc)argss_table_dump, -1);
    rb_define_singleton_method(id, "_load", (rubyfunc)argss_table_load, 1);
}

////////////////////////////////////////////////////////////
/// ARGSS Table new ruby instance
////////////////////////////////////////////////////////////
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
