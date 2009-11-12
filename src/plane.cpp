#include "plane.h"
#include "argss.h"
#include "argss_sdl.h"

static VALUE argss_plane_initialize(int argc, VALUE *argv, VALUE self) {
	return Qnil;
}

void Init_Plane() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Plane = rb_define_class("Plane", rb_cObject);
    rb_define_method(ARGSS_Plane, "initialize", (rubyfunc)argss_plane_initialize, -1);
	
}
