#include "rect.h"
#include <string>
extern "C" {
    #include "ruby.h"
}
#include "../argss.h"
#include "aerror.h"

sf::IntRect argss_rect_intrect(VALUE rect) {
    int x = NUM2INT(rb_iv_get(rect, "@x"));
    int y = NUM2INT(rb_iv_get(rect, "@y"));
    int width = NUM2INT(rb_iv_get(rect, "@width"));
    int height = NUM2INT(rb_iv_get(rect, "@height"));
    return sf::IntRect(x, y, x + width, y + height);
}

sf::FloatRect argss_rect_floatrect(VALUE rect) {
    double x = NUM2DBL(rb_iv_get(rect, "@x"));
    double y = NUM2DBL(rb_iv_get(rect, "@y"));
    double width = NUM2DBL(rb_iv_get(rect, "@width"));
    double height = NUM2DBL(rb_iv_get(rect, "@height"));
    return sf::FloatRect(x, y, x + width, y + height);
}

VALUE argss_rect_new(VALUE x, VALUE y, VALUE w, VALUE h) {
    VALUE args[4] = {x, y, w, h};
    return rb_class_new_instance(4, args, ARGSS_Rect);
}
VALUE argss_rect_new2(int x, int y, int w, int h) {
    VALUE args[4] = {INT2NUM(x), INT2NUM(y), INT2NUM(w), INT2NUM(h)};
    return rb_class_new_instance(4, args, ARGSS_Rect);
}

static VALUE argss_rect_initialize(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h) {
    Check_Kind(x, rb_cNumeric);
    Check_Kind(y, rb_cNumeric);
    Check_Kind(w, rb_cNumeric);
    Check_Kind(h, rb_cNumeric);
    rb_iv_set(self, "@x", x);
    rb_iv_set(self, "@y", y);
    rb_iv_set(self, "@width", w);
    rb_iv_set(self, "@height", h);
    return self;
}
static VALUE argss_rect_set(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h) {
    Check_Kind(x, rb_cNumeric);
    Check_Kind(y, rb_cNumeric);
    Check_Kind(w, rb_cNumeric);
    Check_Kind(h, rb_cNumeric);
    rb_iv_set(self, "@x", x);
    rb_iv_set(self, "@y", y);
    rb_iv_set(self, "@width", w);
    rb_iv_set(self, "@height", h);
    return self;
}
static VALUE argss_rect_x(VALUE self) {
    return rb_iv_get(self, "@x");
}
static VALUE argss_rect_xE(VALUE self, VALUE x) {
    Check_Kind(x, rb_cNumeric);
    return rb_iv_set(self, "@x", x);
}
static VALUE argss_rect_y(VALUE self) {
    return rb_iv_get(self, "@y");
}
static VALUE argss_rect_yE(VALUE self, VALUE y) {
    Check_Kind(y, rb_cNumeric);
    return rb_iv_set(self, "@y", y);
}
static VALUE argss_rect_width(VALUE self) {
    return rb_iv_get(self, "@width");
}
static VALUE argss_rect_widthE(VALUE self, VALUE w) {
    Check_Kind(w, rb_cNumeric);
    return rb_iv_set(self, "@width", w);
}
static VALUE argss_rect_height(VALUE self) {
    return rb_iv_get(self, "@height");
}
static VALUE argss_rect_heightE(VALUE self, VALUE h) {
    Check_Kind(h, rb_cNumeric);
    return rb_iv_set(self, "@height", h);
}
static VALUE argss_rect_inspect(VALUE self) {
    char str[255];
    long n;
    n = sprintf(str, "(%i, %i, %i, %i)",  NUM2INT(rb_iv_get(self, "@x")),
                                            NUM2INT(rb_iv_get(self, "@y")),
                                            NUM2INT(rb_iv_get(self, "@width")),
                                            NUM2INT(rb_iv_get(self, "@height")));
    std::string str2 = str;
    return rb_str_new(str2.c_str(), n);
}
static VALUE argss_rect_dump(VALUE self) {
    //ToDo
    return self;
}
static VALUE argss_rect_load(VALUE str) {
    //ToDo
    return str;
}

void Init_Rect() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Rect = rb_define_class("Rect", rb_cObject);
    rb_define_method(ARGSS_Rect, "initialize", (rubyfunc)argss_rect_initialize, 4);
    rb_define_method(ARGSS_Rect, "set", (rubyfunc)argss_rect_set, 4);
    rb_define_method(ARGSS_Rect, "x", (rubyfunc)argss_rect_x, 0);
    rb_define_method(ARGSS_Rect, "x=", (rubyfunc)argss_rect_xE, 1);
    rb_define_method(ARGSS_Rect, "y", (rubyfunc)argss_rect_y, 0);
    rb_define_method(ARGSS_Rect, "y=", (rubyfunc)argss_rect_yE, 1);
    rb_define_method(ARGSS_Rect, "width", (rubyfunc)argss_rect_width, 0);
    rb_define_method(ARGSS_Rect, "width=", (rubyfunc)argss_rect_widthE, 1);
    rb_define_method(ARGSS_Rect, "height", (rubyfunc)argss_rect_height, 0);
    rb_define_method(ARGSS_Rect, "height=", (rubyfunc)argss_rect_heightE, 1);
    rb_define_method(ARGSS_Rect, "inspect", (rubyfunc)argss_rect_inspect, 0);
    rb_define_method(ARGSS_Rect, "_dump", (rubyfunc)argss_rect_dump, -1);
    rb_define_singleton_method(ARGSS_Rect, "_load", (rubyfunc)argss_rect_load, 1);
}
