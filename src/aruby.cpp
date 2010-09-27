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
#include <stdarg.h>
#include "aruby.h"
#include "rubylibs.h"
#include "options.h"
#include "output.h"
#include "player.h"
#include "config.h"

#include "argss/argss.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARuby::protected_objects;

///////////////////////////////////////////////////////////
// Static code
///////////////////////////////////////////////////////////

// Wrap functions for rb_protect
#if (SCRIPTS_ZLIB == YES)
static VALUE eval_wrap(VALUE arg) {
	return rb_funcall(rb_cObject, rb_intern("eval"), 2, rb_ary_entry(arg, 0), rb_ary_entry(arg, 1));
}
#else
static VALUE require_wrap(VALUE arg) {
	return rb_require(Config::ScriptsPath.c_str());
}
#endif

// Ruby types names for error generating.
static struct types {
	int type;
	const char* name;
} builtin_types[] = {
	{T_NIL, "nil"}, {T_OBJECT, "Object"}, {T_CLASS, "Class"}, {T_ICLASS, "iClass"}, {T_MODULE, "Module"},
	{T_FLOAT, "Float"}, {T_STRING, "String"}, {T_REGEXP, "Regexp"}, {T_ARRAY, "Array"}, {T_FIXNUM, "Fixnum"},
	{T_HASH, "Hash"}, {T_STRUCT, "Struct"}, {T_BIGNUM, "Bignum"}, {T_FILE, "File"}, {T_TRUE, "true"},
	{T_FALSE, "false"}, {T_SYMBOL, "Symbol"}, {T_DATA, "Data"}, {T_MATCH, "MatchData"}, {T_VARMAP, "Varmap"},
	{T_SCOPE, "Scope"}, {T_NODE, "Node"}, {T_UNDEF, "undef"}, {-1, 0}
};

///////////////////////////////////////////////////////////
// Ruby initialize
///////////////////////////////////////////////////////////
void ARuby::Init() {
	ruby_init();
	ruby_init_loadpath();

	protected_objects = rb_hash_new();
	rb_gc_register_address(&protected_objects);

	typedef VALUE (*rubyfunc)(...);
	rb_define_global_function("load_data", (rubyfunc)rload_data, 1);
	rb_define_global_function("save_data", (rubyfunc)rsave_data, 2);

#ifdef HAVE_RUBY_ZLIB
	Init_zlib();
#endif

#ifdef HAVE_RUBY_WIN32API
	Init_Win32API();
#endif

	ARGSS::Init();
}

///////////////////////////////////////////////////////////
// Ruby run
///////////////////////////////////////////////////////////
void ARuby::Run() {
	int error;
	VALUE result;

	#if (SCRIPTS_ZLIB == YES)
		VALUE cZlib = rb_const_get(rb_cObject, rb_intern("Zlib"));
		VALUE cInflate = rb_const_get(cZlib, rb_intern("Inflate"));
		VALUE file = rb_file_open(Config::ScriptsPath.c_str(), "rb");
		VALUE scripts = rb_marshal_load(file);
		RArray* arr = RARRAY(scripts);
		VALUE section_arr;
		VALUE section;
		for (int i = 0; i < arr->len; i++) {
			section_arr = rb_ary_entry(scripts, i);
			section = rb_ary_entry(section_arr, 2);
			section = rb_funcall3(cInflate, rb_intern("inflate"), 1, &section);
			result = rb_protect(eval_wrap, rb_ary_new3(2, StringValuePtr(section), rb_ary_entry(section_arr, 1)), &error);
			if (error) break;
		}
	#else
		result = rb_protect(require_wrap, Qundef, &error);
	#endif

	// Custom error printing
	if (error) {
		VALUE lasterr = rb_gv_get("$!");
		VALUE klass = rb_class_path(CLASS_OF(lasterr));
		VALUE message = rb_obj_as_string(lasterr);

		// Avoid normal ruby exit
		if (CLASS_OF(lasterr) != rb_eSystemExit) {
			std::string report = "RUBY ERROR\n";
			report += (std::string)RSTRING(klass)->ptr;
			report += " - ";
			report += (std::string)RSTRING(message)->ptr;
			if (!NIL_P(ruby_errinfo)) {
				VALUE ary = rb_funcall(ruby_errinfo, rb_intern("backtrace"), 0);
				for (int i = 0; i < RARRAY(ary)->len; i++) {
					report += "\n from ";
					report += RSTRING(RARRAY(ary)->ptr[i])->ptr;
				}
			}
			Output::ErrorStr(report);
			return;
		}
	}
}

///////////////////////////////////////////////////////////
// Exit
///////////////////////////////////////////////////////////
void ARuby::Exit() {
	ruby_finalize();
}

///////////////////////////////////////////////////////////
// AddObject
///////////////////////////////////////////////////////////
void ARuby::AddObject(VALUE id) {
	rb_hash_aset(protected_objects, id, id);
}

///////////////////////////////////////////////////////////
// RemoveObject
///////////////////////////////////////////////////////////
void ARuby::RemoveObject(VALUE id) {
	rb_hash_delete(protected_objects, id);
}

///////////////////////////////////////////////////////////
// Global ruby functions
///////////////////////////////////////////////////////////
VALUE ARuby::rload_data(VALUE self, VALUE filename) {
	VALUE file = rb_file_open(StringValuePtr(filename), "rb");
	VALUE obj = rb_marshal_load(file);
	rb_io_close(file);
	return obj;
}
VALUE ARuby::rsave_data(VALUE self, VALUE obj, VALUE filename) {
	VALUE file = rb_file_open(StringValuePtr(filename), "wb");
	rb_marshal_dump(obj, file);
	rb_io_close(file);
	return Qnil;
}

///////////////////////////////////////////////////////////
// Check_Kind
///////////////////////////////////////////////////////////
void Check_Kind(VALUE o, VALUE c) {
	if (!rb_obj_is_kind_of(o, c)) {
		rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)", rb_class2name(o), rb_class2name(c));
	};
}

///////////////////////////////////////////////////////////
// Check_Types2
///////////////////////////////////////////////////////////
void Check_Types2(VALUE x, VALUE t1, VALUE t2) {
	struct types* type = builtin_types;
	if (x == Qundef) rb_bug("undef leaked to the Ruby space");
	if ((unsigned long)TYPE(x) != t1 && (unsigned long)TYPE(x) != t2) {
		while (type->type >= 0) {
			if ((unsigned long)type->type == t1) {
				const char* etype;
				if (NIL_P(x)) etype = (char*)"nil";
				else if (FIXNUM_P(x)) etype = (char*)"Fixnum";
				else if (SYMBOL_P(x)) etype = (char*)"Symbol";
				else if (rb_special_const_p(x)) etype = RSTRING(rb_obj_as_string(x))->ptr;
				else etype = rb_class2name(x);
				rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)", etype, type->name);
			}
			type++;
		}
		rb_bug("unknown type 0x%x", t1);
	}
}

///////////////////////////////////////////////////////////
// Check_Bool
///////////////////////////////////////////////////////////
void Check_Bool(VALUE x) {
	if (x == Qundef) rb_bug("undef leaked to the Ruby space");
	if (TYPE(x) != T_TRUE && TYPE(x) != T_FALSE) {
		const char* etype;
		if (NIL_P(x)) etype = (char*)"nil";
		else if (FIXNUM_P(x)) etype = (char*)"Fixnum";
		else if (SYMBOL_P(x)) etype = (char*)"Symbol";
		else if (rb_special_const_p(x)) etype = RSTRING(rb_obj_as_string(x))->ptr;
		else etype = rb_class2name(x);
		rb_raise(rb_eTypeError, "wrong argument type %s (expected boolean)", etype);
	}
}

///////////////////////////////////////////////////////////
// Check_Class
///////////////////////////////////////////////////////////
void Check_Class(VALUE x, VALUE c) {
	if (x == Qundef) {rb_bug("undef leaked to the Ruby space");}
	if (rb_class_real(CLASS_OF(x)) != c) {
		struct types* type = builtin_types;
		while (type->type >= 0) {
			if (type->type == TYPE(c)) {
				const char* etype;
				if (NIL_P(x)) etype = (char*)"nil";
				else if (FIXNUM_P(x)) etype = (char*)"Fixnum";
				else if (SYMBOL_P(x)) etype = (char*)"Symbol";
				else if (rb_special_const_p(x)) etype = RSTRING(rb_obj_as_string(x))->ptr;
				else etype = rb_class2name(x);
				rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)", etype, type->name);
			}
			type++;
		}
		rb_bug("unknown type 0x%x", c);
	}
}

///////////////////////////////////////////////////////////
// Check_Classes_N
///////////////////////////////////////////////////////////
void Check_Classes_N(VALUE x, VALUE c) {
	if (x == Qnil) return;
	Check_Class(x, c);
}
