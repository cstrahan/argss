#include "tilemap.h"
#include "argss.h"

static VALUE argss_tilemap_initialize(int argc, VALUE *argv, VALUE self) {
		return Qnil;
}
	
void Init_Tilemap() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Tilemap = rb_define_class("Tilemap", rb_cObject);
    rb_define_method(ARGSS_Tilemap, "initialize", (rubyfunc)argss_tilemap_initialize, -1);
	
}
