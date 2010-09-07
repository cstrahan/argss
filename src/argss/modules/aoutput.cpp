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
#include "argss/modules/aoutput.h"
#include "output.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::AOutput::id;
VALUE ARGSS::AOutput::stdout_id;
VALUE ARGSS::AOutput::stderr_id;
VALUE ARGSS::AOutput::stdin_id;

///////////////////////////////////////////////////////////
/// ARGSS Output ruby functions
///////////////////////////////////////////////////////////
VALUE ARGSS::AOutput::rconsole(VALUE self) {
	Output::Console();
	return Qnil;
}
VALUE ARGSS::AOutput::rmsgbox(VALUE self) {
	Output::MsgBox();
	return Qnil;
}
VALUE ARGSS::AOutput::rfile(VALUE self, VALUE file) {
	Output::File(StringValuePtr(file));
	return Qnil;
}
VALUE ARGSS::AOutput::rnone(VALUE self) {
	Output::None();
	return Qnil;
}

///////////////////////////////////////////////////////////
/// ARGSS Stdout, Stderr and Stdin
///////////////////////////////////////////////////////////
VALUE ARGSS::AOutput::rstdout_write(VALUE self, VALUE str) {
	if (TYPE(str) != T_STRING) str = rb_obj_as_string(str);
	if (RSTRING(str)->len == 0) return INT2FIX(0);
	Output::PostStr(StringValuePtr(str));
	return INT2FIX(RSTRING(str)->len);
}
VALUE ARGSS::AOutput::rstderr_write(VALUE self, VALUE str) {
	if (TYPE(str) != T_STRING) str = rb_obj_as_string(str);
	if (RSTRING(str)->len == 0) return INT2FIX(0);
	//Output::ErrorStr(StringValuePtr(str));
	return INT2FIX(RSTRING(str)->len);
}
VALUE ARGSS::AOutput::stdin_gets(int argc, VALUE* argv, VALUE self) {
	std::string str = Output::Gets();
	return rb_str_new(str.c_str(), str.length());
}
VALUE ARGSS::AOutput::stdin_getc(int argc, VALUE* argv, VALUE self) {
	std::string str = Output::Getc();
	return rb_str_new(str.c_str(), str.length());
}

///////////////////////////////////////////////////////////
/// ARGSS Output initialize
///////////////////////////////////////////////////////////
void ARGSS::AOutput::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_module("Output");
	rb_define_singleton_method(id, "console", (rubyfunc)rconsole, 0);
	rb_define_singleton_method(id, "msgbox", (rubyfunc)rmsgbox, 0);
	rb_define_singleton_method(id, "file", (rubyfunc)rfile, 1);
	rb_define_singleton_method(id, "none", (rubyfunc)rnone, 0);

	stdout_id = rb_define_class_under(id, "Stdout", rb_cObject);
	rb_define_method(stdout_id, "write", (rubyfunc)rstdout_write, 1);
	stderr_id = rb_define_class_under(id, "Stderr", rb_cObject);
	rb_define_method(stderr_id, "write", (rubyfunc)rstderr_write, 1);

	rb_gv_set("$stdout", rb_class_new_instance(0, 0, stdout_id));
	rb_gv_set("$stderr", rb_class_new_instance(0, 0, stderr_id));

	stdin_id = rb_define_class_under(id, "Stdin", rb_cObject);
	rb_define_method(stdin_id, "gets", (rubyfunc)stdin_gets, -1);
	rb_define_method(stdin_id, "getc", (rubyfunc)stdin_getc, -1);
	rb_define_global_function("getc", (rubyfunc)stdin_getc, 0);

	rb_gv_set("$stdin", rb_class_new_instance(0, 0, stdin_id));
}
