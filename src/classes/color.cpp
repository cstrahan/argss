#include "color.h"
#include <string>
#include "../argss.h"
#include "aerror.h"

double valuecapcolor(double v) {
    return (v > 255) ? 255 : (v < 0) ? 0 : v;
}

sf::Color argss_color_getsf(VALUE self) {
    return sf::Color(NUM2INT(rb_iv_get(self, "@red")),
                    NUM2INT(rb_iv_get(self, "@green")),
                    NUM2INT(rb_iv_get(self, "@blue")),
                    NUM2INT(rb_iv_get(self, "@alpha")));
}

VALUE argss_color_new(VALUE r, VALUE g, VALUE b, VALUE a) {
    VALUE args[4] = {r, g, b, a};
    return rb_class_new_instance(4, args, ARGSS_Color);
}
VALUE argss_color_new2(float r, float g, float b, float a) {
    VALUE args[4] = {rb_float_new(r), rb_float_new(g), rb_float_new(b), rb_float_new(a)};
    return rb_class_new_instance(4, args, ARGSS_Color);
}
VALUE argss_color_new3(sf::Color color) {
    VALUE args[4] = {rb_float_new(color.r), rb_float_new(color.g), rb_float_new(color.b), rb_float_new(color.a)};
    return rb_class_new_instance(4, args, ARGSS_Color);
}

static VALUE argss_color_initialize(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) {raise_argn(argc, 3);}
    else if (argc > 4) {raise_argn(argc, 4);}
    Check_Kind(argv[0], rb_cNumeric);
    Check_Kind(argv[1], rb_cNumeric);
    Check_Kind(argv[2], rb_cNumeric);
    double red = valuecapcolor(NUM2DBL(argv[0]));
    double green = valuecapcolor(NUM2DBL(argv[1]));
    double blue = valuecapcolor(NUM2DBL(argv[2]));
    double alpha = 255;
    if (argc == 4) {
        Check_Kind(argv[3], rb_cNumeric);
        alpha = valuecapcolor(NUM2DBL(argv[3]));
    }
    rb_iv_set(self, "@red", rb_float_new(red));
    rb_iv_set(self, "@green", rb_float_new(green));
    rb_iv_set(self, "@blue", rb_float_new(blue));
    rb_iv_set(self, "@alpha", rb_float_new(alpha));
    return self;
}
static VALUE argss_color_set(int argc, VALUE *argv, VALUE self) {
    if (argc < 3) {raise_argn(argc, 3);}
    else if (argc > 4) {raise_argn(argc, 4);}
    Check_Kind(argv[0], rb_cNumeric);
    Check_Kind(argv[1], rb_cNumeric);
    Check_Kind(argv[2], rb_cNumeric);
    double red = valuecapcolor(NUM2DBL(argv[0]));
    double green = valuecapcolor(NUM2DBL(argv[1]));
    double blue = valuecapcolor(NUM2DBL(argv[2]));
    double alpha = 255;
    if (argc == 4) {
        Check_Kind(argv[3], rb_cNumeric);
        alpha = valuecapcolor(NUM2DBL(argv[3]));
    }
    rb_iv_set(self, "@red", rb_float_new(red));
    rb_iv_set(self, "@green", rb_float_new(green));
    rb_iv_set(self, "@blue", rb_float_new(blue));
    rb_iv_set(self, "@alpha", rb_float_new(alpha));
    return self;
}
static VALUE argss_color_red(VALUE self) {
    return rb_iv_get(self, "@red");
}
static VALUE argss_color_redE(VALUE self, VALUE r) {
    Check_Kind(r, rb_cNumeric);
    return rb_iv_set(self, "@red", rb_float_new(valuecapcolor(NUM2DBL(r))));
}
static VALUE argss_color_green(VALUE self) {
    return rb_iv_get(self, "@green");
}
static VALUE argss_color_greenE(VALUE self, VALUE g) {
    Check_Kind(g, rb_cNumeric);
    return rb_iv_set(self, "@green", rb_float_new(valuecapcolor(NUM2DBL(g))));
}
static VALUE argss_color_blue(VALUE self) {
    return rb_iv_get(self, "@blue");
}
static VALUE argss_color_blueE(VALUE self, VALUE b) {
    Check_Kind(b, rb_cNumeric);
    return rb_iv_set(self, "@blue", rb_float_new(valuecapcolor(NUM2DBL(b))));
}
static VALUE argss_color_alpha(VALUE self) {
    return rb_iv_get(self, "@alpha");
}
static VALUE argss_color_alphaE(VALUE self, VALUE a) {
    Check_Kind(a, rb_cNumeric);
    return rb_iv_set(self, "@alpha", rb_float_new(valuecapcolor(NUM2DBL(a))));
}
static VALUE argss_color_inspect(VALUE self) {
    char str[255];
    long n;
    n = sprintf(str, "(%f, %f, %f, %f)",  NUM2DBL(rb_iv_get(self, "@red")),
                                            NUM2DBL(rb_iv_get(self, "@green")),
                                            NUM2DBL(rb_iv_get(self, "@blue")),
                                            NUM2DBL(rb_iv_get(self, "@alpha")));
    std::string str2 = str;
    return rb_str_new(str2.c_str(), n);
}
static VALUE argss_color_dump(VALUE self) {
    //ToDo
    return self;
}
static VALUE argss_color_load(VALUE str) {
    //ToDo
    return str;
}

void Init_Color() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Color = rb_define_class("Color", rb_cObject);
    rb_define_method(ARGSS_Color, "initialize", (rubyfunc)argss_color_initialize, -1);
    rb_define_method(ARGSS_Color, "set", (rubyfunc)argss_color_set, -1);
    rb_define_method(ARGSS_Color, "red", (rubyfunc)argss_color_red, 0);
    rb_define_method(ARGSS_Color, "red=", (rubyfunc)argss_color_redE, 1);
    rb_define_method(ARGSS_Color, "green", (rubyfunc)argss_color_green, 0);
    rb_define_method(ARGSS_Color, "green=", (rubyfunc)argss_color_greenE, 1);
    rb_define_method(ARGSS_Color, "blue", (rubyfunc)argss_color_blue, 0);
    rb_define_method(ARGSS_Color, "blue=", (rubyfunc)argss_color_blueE, 1);
    rb_define_method(ARGSS_Color, "alpha", (rubyfunc)argss_color_alpha, 0);
    rb_define_method(ARGSS_Color, "alpha=", (rubyfunc)argss_color_alphaE, 1);
    rb_define_method(ARGSS_Color, "inspect", (rubyfunc)argss_color_inspect, 0);
    rb_define_method(ARGSS_Color, "_dump", (rubyfunc)argss_color_dump, -1);
    rb_define_singleton_method(ARGSS_Color, "_load", (rubyfunc)argss_color_load, 1);
}
