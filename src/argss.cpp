#include "argss.h"
#include "sys.h"
#include "aruby.h"
#include "argss_sdl.h"
extern "C" {
    #include "ruby.h"
}
#include "aerror.h"
#include "bitmap.h"
#include "color.h"
#include "tone.h"
#include "rect.h"
#include "sprite.h"
#include "console.h"
#include "graphics.h"
#include "input.h"
#include "zobj.h"

void Init_ARGSS()
{
    ruby_init();
	ruby_init_loadpath();
	
    Init_ARuby();

    Init_ARGSSError();
    Init_Color();
    Init_Tone();
    Init_Rect();
    Init_Bitmap();
    Init_Sprite();
    Init_Graphics();
    Init_Console();
    Init_Input();

    ARGSS_CreationTime = 0;

    rb_load_file(Sys_ScriptsPath.c_str());
    ruby_run();
}

void argss_update() {
    SDL_Event event;

    bool result;
	
    while (true) {
        result = SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) {
            FreeConsole();
            SDL_Quit();
			rb_exit(1);
        }
        /*else if(event.type == SDL_ACTIVEEVENT) {
			if(event.active.type == SDL_APPACTIVE) {
				if(event.active.gain) {
					Sys_Focus = false;
					Input_RestartKeys();
					if(Sys_FocusPauseAudio) {
						//Audio_Pause();
					}
				}
				else {
					Sys_Focus = true;
					if(Sys_FocusPauseAudio) {
						//Audio_Play();
					}
				}
			}
        }*/
        if(!result && !(Sys_FocusPauseGame && !Sys_Focus)) {
            break;
        }
    }
}

bool compare_zobj(Z_Obj &first, Z_Obj &second) {
    if (first.get_z() < second.get_z()) {
        return true;
	}
    else if (first.get_z() > second.get_z()) {
        return false;
	}
    else {
        if (first.get_creation() < second.get_creation()) {
            return true;
		}
        else {
            return false;
		}
    }
}
