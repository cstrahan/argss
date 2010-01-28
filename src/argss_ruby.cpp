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
#include <string>
#include "argss_ruby.h"
#include "options.h"
#include "system.h"
#include "player.h"
#include "output.h"

////////////////////////////////////////////////////////////
/// Global variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ARuby::protected_objects;

////////////////////////////////////////////////////////////
/// ARGSS Ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_load_data(VALUE self, VALUE filename) {
	VALUE mMarshal = rb_const_get(rb_cObject, rb_intern("Marshal"));
	VALUE file = rb_funcall(rb_cFile, rb_intern("open"), 2, filename, rb_str_new2("rb"));
	VALUE obj = rb_funcall(mMarshal, rb_intern("load"), 1, file);
	rb_funcall(file, rb_intern("close"), 0);
	return obj;
}
static VALUE argss_save_data(VALUE self, VALUE obj, VALUE filename) {
	VALUE mMarshal = rb_const_get(rb_cObject, rb_intern("Marshal"));
	VALUE file = rb_funcall(rb_cFile, rb_intern("open"), 2, filename, rb_str_new2("wb"));
	rb_funcall(mMarshal, rb_intern("dump"), 2, obj, file);
	rb_funcall(file, rb_intern("close"), 0);
	return Qnil;
}

////////////////////////////////////////////////////////////
/// ARGSS Ruby initialize
////////////////////////////////////////////////////////////
void ARGSS::ARuby::Init() {
	ruby_init();
	ruby_init_loadpath();
	atexit(ruby_finalize);
	protected_objects = rb_hash_new();
	rb_gc_register_address(&protected_objects);

	typedef VALUE (*rubyfunc)(...);
	rb_define_global_function("load_data", (rubyfunc)argss_load_data, 1);
	rb_define_global_function("save_data", (rubyfunc)argss_save_data, 2);
}

////////////////////////////////////////////////////////////
/// ARGSS Ruby run
////////////////////////////////////////////////////////////
VALUE require_wrap(VALUE arg) {
    return rb_require(System::ScriptsPath.c_str());
}
void ARGSS::ARuby::Run() {
	int error;
	VALUE result;
	/*if (SCRIPTS_ZLIB) {
		VALUE mMarshal = rb_const_get(rb_cObject, rb_intern("Marshal"));
		VALUE cZlib = rb_const_get(rb_cObject, rb_intern("Zlib"));
		VALUE cInflate = rb_const_get(cZlib, rb_intern("Inflate"));
		VALUE args[2] = {rb_str_new(System::ScriptsPath.c_str(), System::ScriptsPath.size()), rb_str_new("rb", 2)};
		VALUE file = rb_class_new_instance(2, args, rb_cFile);
		VALUE scripts = rb_funcall3(mMarshal, rb_intern("load"), 1, &file);
		RArray* arr = RARRAY(scripts);
		VALUE section_arr;
		VALUE section;
		for (int i = 0; i < arr->len; i++) {
			section_arr = rb_ary_entry(scripts, i);
			section = rb_ary_entry(section_arr, 2);
			Output::PostStr(StringValuePtr(section));
			section = rb_funcall3(cInflate, rb_intern("inflate"), 1, &section);
			Output::PostStr(StringValuePtr(section));
			result = rb_eval_string_protect(StringValuePtr(section), &error);
		}
	}
	else {*/
		result = rb_protect(require_wrap, 0, &error);
	//}
	if (error) {
		VALUE lasterr = rb_gv_get("$!");
		VALUE klass = rb_class_path(CLASS_OF(lasterr));
		VALUE message = rb_obj_as_string(lasterr);
		if (CLASS_OF(lasterr) != rb_eSystemExit) {
			std::string report = "RUBY ERROR\n";
			report += (std::string)RSTRING(klass)->ptr;
			report += " - ";
			report += (std::string)RSTRING(message)->ptr;
			if (!NIL_P(ruby_errinfo)) {
				VALUE ary = rb_funcall(ruby_errinfo, rb_intern("backtrace"), 0);
				for (int i = 0; i < RARRAY(ary)->len; i++) {
					report += "\n  from ";
					report += RSTRING(RARRAY(ary)->ptr[i])->ptr;
				}
			}
			Output::ErrorStr(report);
		}
	}
	Player::Exit();
}

////////////////////////////////////////////////////////////
/// Int vetor to Ruby Array
////////////////////////////////////////////////////////////
VALUE ARGSS::ARuby::IntVectorToRArr(std::vector<int> vector) {
	VALUE* values = new VALUE[vector.size()];;
	for (unsigned int i = 0; i < vector.size(); i++) {
		values[i] = INT2NUM(vector[i]);
	}
	VALUE arr = rb_ary_new4(vector.size(), values);
	delete values;
	return arr;
}

////////////////////////////////////////////////////////////
/// Int vetor to Ruby Array
////////////////////////////////////////////////////////////
void ARGSS::ARuby::AddObject(VALUE id) {
	rb_hash_aset(protected_objects, id, id);
}

////////////////////////////////////////////////////////////
/// Int vetor to Ruby Array
////////////////////////////////////////////////////////////
void ARGSS::ARuby::RemoveObject(VALUE id) {
	rb_hash_delete(protected_objects, id);
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Check_Kind(VALUE o, VALUE c) {
    if (!rb_obj_is_kind_of(o, c)) {
        rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)",
            rb_obj_classname(o), rb_obj_classname(c));
    };
}

static struct types {
    int type;
    const char *name;
} builtin_types[] = {
    {T_NIL,	"nil"},
    {T_OBJECT,	"Object"},
    {T_CLASS,	"Class"},
    {T_ICLASS,	"iClass"},	/* internal use: mixed-in module holder */
    {T_MODULE,	"Module"},
    {T_FLOAT,	"Float"},
    {T_STRING,	"String"},
    {T_REGEXP,	"Regexp"},
    {T_ARRAY,	"Array"},
    {T_FIXNUM,	"Fixnum"},
    {T_HASH,	"Hash"},
    {T_STRUCT,	"Struct"},
    {T_BIGNUM,	"Bignum"},
    {T_FILE,	"File"},
    {T_TRUE,	"true"},
    {T_FALSE,	"false"},
    {T_SYMBOL,	"Symbol"},	/* :symbol */
    {T_DATA,	"Data"},	/* internal use: wrapped C pointers */
    {T_MATCH,	"MatchData"},	/* data of $~ */
    {T_VARMAP,	"Varmap"},	/* internal use: dynamic variables */
    {T_SCOPE,	"Scope"},	/* internal use: variable scope */
    {T_NODE,	"Node"},	/* internal use: syntax tree node */
    {T_UNDEF,	"undef"},	/* internal use: #undef; should not happen */
    {-1,	0}
};

void Check_Types2(VALUE x, VALUE t1, VALUE t2)
{
    struct types *type = builtin_types;
    if (x == Qundef) {rb_bug("undef leaked to the Ruby space");}
    if (TYPE(x) != t1 && TYPE(x) != t2) {
        while (type->type >= 0) {
            if (type->type == t1) {
                char *etype;
                if (NIL_P(x)) {etype = (char *)"nil";}
                else if (FIXNUM_P(x)) {etype = (char *)"Fixnum";}
                else if (SYMBOL_P(x)) {etype = (char *)"Symbol";}
                else if (rb_special_const_p(x)) {etype = RSTRING(rb_obj_as_string(x))->ptr;}
                else {etype = rb_obj_classname(x);}
                rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)",
                     etype, type->name);
            }
            type++;
        }
        rb_bug("unknown type 0x%x", t1);
    }
}

void Check_Bool(VALUE x) {
    if (x == Qundef) {rb_bug("undef leaked to the Ruby space");}
    if (TYPE(x) != T_TRUE && TYPE(x) != T_FALSE) {
        char *etype;
        if (NIL_P(x)) {etype = (char *)"nil";}
        else if (FIXNUM_P(x)) {etype = (char *)"Fixnum";}
        else if (SYMBOL_P(x)) {etype = (char *)"Symbol";}
        else if (rb_special_const_p(x)) {etype = RSTRING(rb_obj_as_string(x))->ptr;}
        else {etype = rb_obj_classname(x);}
        rb_raise(rb_eTypeError, "wrong argument type %s (expected boolean)", etype);
    }
}

void Check_Class(VALUE x, VALUE t)
{
    if (x == Qundef) {rb_bug("undef leaked to the Ruby space");}
    if (rb_class_real(CLASS_OF(x)) != t) {
        struct types *type = builtin_types;
        while (type->type >= 0) {
            if (type->type == TYPE(t)) {
                char *etype;
                if (NIL_P(x)) {etype = (char *)"nil";}
                else if (FIXNUM_P(x)) {etype = (char *)"Fixnum";}
                else if (SYMBOL_P(x)) {etype = (char *)"Symbol";}
                else if (rb_special_const_p(x)) {etype = RSTRING(rb_obj_as_string(x))->ptr;}
                else {etype = rb_obj_classname(x);}
                rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)",
                     etype, type->name);
            }
            type++;
        }
        rb_bug("unknown type 0x%x", t);
    }
}

void Check_Classes_N(VALUE x, VALUE type)
{
    if (x == Qnil) return;
	Check_Class(x, type);
}
