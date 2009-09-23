#include "argss.h"
#include "sys.h"
#include "aruby.h"
#include "sfml.h"
extern "C" {
    #include "ruby.h"
}
#include "classes/aerror.h"
#include "classes/bitmap.h"
#include "classes/color.h"
#include "classes/tone.h"
#include "classes/rect.h"
#include "classes/sprite.h"
#include "modules/console.h"
#include "modules/graphics.h"
#include "modules/input.h"

void Init_ARGSS()
{
    ruby_init();

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
    sf::Event Event;
    bool result;
    while (true) {
        result = SFML_Window.GetEvent(Event);
        if(Event.Type == sf::Event::Closed) {
            rb_exit(1);
            FreeConsole();
            SFML_Window.Close();
        }
        else if(Event.Type == sf::Event::LostFocus) {
            Sys_Focus = false;
            Input_RestartKeys();
            if(Sys_FocusPauseAudio) {
                //Audio_Pause();
            }
        }
        else if(Event.Type == sf::Event::GainedFocus) {
            Sys_Focus = true;
            if(Sys_FocusPauseAudio) {
                //Audio_Play();
            }
        }
        if(!result && !(Sys_FocusPauseGame && !Sys_Focus)) {
            break;
        }
    }
}

bool compare_zobj(Z_Obj &first, Z_Obj &second) {
    if (first.get_z() < second.get_z()) {
        return true;}
    else if (first.get_z() > second.get_z()) {
        return false;}
    else {
        if (first.get_creation() < second.get_creation()) {
            return true;}
        else {
            return false;}
    }
}
