#include "aruby.h"
#include "argss.h"

void Init_ARuby()
{
    typedef VALUE (*rubyfunc)(...);
    //rb_define_global_function("sleep", (rubyfunc)aruby_sleep, 1);
    //rb_define_global_function("init_console", (rubyfunc)aruby_init_console, 0);
    //rb_define_method(rb_mKernel, "p", aruby_p, -1);
}
