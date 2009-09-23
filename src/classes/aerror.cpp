#include "aerror.h"
#include "../argss.h"

void Init_ARGSSError() {
    ARGSS_Error = rb_define_class("ARGSSError", rb_eStandardError);
}

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

void Check_Types2(VALUE x, int t1, int t2)
{
    struct types *type = builtin_types;
    if (x == Qundef) {rb_bug("undef leaked to the Ruby space");}
    if (TYPE(x) != t1 && TYPE(x) != t2) {
        while (type->type >= 0) {
            if (type->type == t1) {
                char *etype;
                if (NIL_P(x)) {etype = "nil";}
                else if (FIXNUM_P(x)) {etype = "Fixnum";}
                else if (SYMBOL_P(x)) {etype = "Symbol";}
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
        if (NIL_P(x)) {etype = "nil";}
        else if (FIXNUM_P(x)) {etype = "Fixnum";}
        else if (SYMBOL_P(x)) {etype = "Symbol";}
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
                if (NIL_P(x)) {etype = "nil";}
                else if (FIXNUM_P(x)) {etype = "Fixnum";}
                else if (SYMBOL_P(x)) {etype = "Symbol";}
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

void Check_Classes(VALUE x, int argc, VALUE *types)
{
    if (x == Qundef) {rb_bug("undef leaked to the Ruby space");}
    int i;
    VALUE clss = rb_class_real(CLASS_OF(x));
    for (i=0; i < argc; i++) {
        if (clss == types[i]) {
            return;
        }
    }
    struct types *type = builtin_types;
    while (type->type >= 0) {
        if (type->type == TYPE(types[0])) {
            char *etype;
            if (NIL_P(x)) {etype = "nil";}
            else if (FIXNUM_P(x)) {etype = "Fixnum";}
            else if (SYMBOL_P(x)) {etype = "Symbol";}
            else if (rb_special_const_p(x)) {etype = RSTRING(rb_obj_as_string(x))->ptr;}
            else {etype = rb_obj_classname(x);}
            rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)",
                 etype, type->name);
        }
        type++;
    }
    rb_bug("unknown type 0x%x", types[0]);
}

void Check_Classes_N(VALUE x, VALUE type)
{
    VALUE argv[2] = {type, Qnil};
    Check_Classes(x, 2, argv);
}
