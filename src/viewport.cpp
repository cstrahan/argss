#include "viewport.h"
#include "argss.h"

static VALUE argss_viewport_initialize(int argc, VALUE *argv, VALUE self) {
	return Qnil;
}

void Init_Viewport() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Viewport = rb_define_class("Viewport", rb_cObject);
    rb_define_method(ARGSS_Viewport, "initialize", (rubyfunc)argss_viewport_initialize, -1);
	
}
