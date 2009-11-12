#include "audio.h"
#include "argss.h"

void Init_Audio()
{
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Audio = rb_define_module("Audio");
    //rb_define_singleton_method(ARGSS_Audio, "", (rubyfunc)argss_audio_, 0);	
}