#include "window.h"
#include "argss.h"

static VALUE argss_window_initialize(int argc, VALUE *argv, VALUE self) {
	return Qnil;
}

void Init_Window() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Window = rb_define_class("Window", rb_cObject);
    rb_define_method(ARGSS_Window, "initialize", (rubyfunc)argss_window_initialize, -1);
	
}
