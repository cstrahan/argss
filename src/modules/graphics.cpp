#include <windows.h>
#include "graphics.h"
#include "../argss.h"
#include "../sfmlargss.h"
#include "../sfml.h"
#include "../sys.h"
#include "../classes/aerror.h"
#include "../classes/color.h"

static VALUE argss_graphics_update(VALUE self) {
    SFML_Window.Clear(ARGSS_Graphics_BackColor);

    argss_update();

    ARGSS_ZOrder.sort(compare_zobj);
    for(ARGSS_itZOrder = ARGSS_ZOrder.begin(); ARGSS_itZOrder != ARGSS_ZOrder.end(); ARGSS_itZOrder++) {
        if (ARGSS_itZOrder->get_type() == ARGSS_Sprite) {
                if (ARGSS_mapSprites.count(ARGSS_itZOrder->get_id()) == 1) {
                    SFML_Window.Draw(ARGSS_mapSprites[ARGSS_itZOrder->get_id()]);
                }
        }
        //else if (ARGSS_itZOrder.type == ARGSS_Plane) {}
        //else if (ARGSS_itZOrder.type ==  ARGSS_Window) {}
        //else if (ARGSS_itZOrder.type ==  ARGSS_Tilemap) {}
        //else if (ARGSS_itZOrder.type ==  ARGSS_Viewport) {}
    }
    ARGSS_FrameCount++;
    static int frames = 0;
	frames++;
    if (SFML_Clock.GetElapsedTime() > 1) {
        ARGSS_FPS = frames;
        frames = 0;
        SFML_Clock.Reset();
		char title[255];
        sprintf(title, "%s - %d FPS", Sys_Title.c_str(), ARGSS_FPS);
        SFML_Window.SetWindowTitle(title);
    }
    SFML_Window.Display();
    return Qnil;
}
static VALUE argss_graphics_freeze(VALUE self) {
    //ToDo
    return Qnil;
}
static VALUE argss_graphics_transition(int argc, VALUE *argv, VALUE self) {
    //ToDo
    return Qnil;
}
static VALUE argss_graphics_frame_reset(VALUE self) {
    //What's this for? ToDo
    return Qnil;
}
static VALUE argss_graphics_frame_rate(VALUE self) {
    return INT2FIX(ARGSS_FrameRate);
}
static VALUE argss_graphics_frame_rateE(VALUE self, VALUE framerate) {
    Check_Type(framerate, T_FIXNUM);
    ARGSS_FrameRate = NUM2INT(framerate);
    SFML_Window.SetFramerateLimit(ARGSS_FrameRate);
    return framerate;
}
static VALUE argss_graphics_frame_count(VALUE self) {
    return INT2FIX(ARGSS_FrameCount);
}
static VALUE argss_graphics_frame_countE(VALUE self, VALUE framecount) {
    Check_Type(framecount, T_FIXNUM);
    ARGSS_FrameCount = NUM2INT(framecount);
    return framecount;
}
static VALUE argss_graphics_fps(VALUE self) {
    return INT2FIX(ARGSS_FPS);
}
static VALUE argss_graphics_backcolor(VALUE self) {
    return argss_color_new3(ARGSS_Graphics_BackColor);
}
static VALUE argss_graphics_backcolorE(VALUE self, VALUE backcolor) {
    Check_Class(backcolor, ARGSS_Color);
    ARGSS_Graphics_BackColor = argss_color_getsf(backcolor);
    return backcolor;
}
static VALUE argss_graphics_width(VALUE self) {
    return INT2NUM(Sys_Res[0]);
}
static VALUE argss_graphics_height(VALUE self) {
    return INT2NUM(Sys_Res[1]);
}

void Init_Graphics()
{
    ARGSS_FPS = 0;
    ARGSS_FrameCount = 0;
    ARGSS_FrameRate = 60;
    ARGSS_Graphics_BackColor = sf::Color(0, 0, 0, 0);
    SFML_Window.SetFramerateLimit(ARGSS_FrameRate);

    typedef VALUE (*rubyfunc)(...);
    ARGSS_Graphics = rb_define_module("Graphics");
    rb_define_singleton_method(ARGSS_Graphics, "update", (rubyfunc)argss_graphics_update, 0);
    rb_define_singleton_method(ARGSS_Graphics, "freeze", (rubyfunc)argss_graphics_freeze, 0);
    rb_define_singleton_method(ARGSS_Graphics, "transition", (rubyfunc)argss_graphics_transition, -1);
    rb_define_singleton_method(ARGSS_Graphics, "frame_reset", (rubyfunc)argss_graphics_frame_reset, 0);
    rb_define_singleton_method(ARGSS_Graphics, "frame_rate", (rubyfunc)argss_graphics_frame_rate, 0);
    rb_define_singleton_method(ARGSS_Graphics, "frame_rate=", (rubyfunc)argss_graphics_frame_rateE, 1);
    rb_define_singleton_method(ARGSS_Graphics, "frame_count", (rubyfunc)argss_graphics_frame_count, 0);
    rb_define_singleton_method(ARGSS_Graphics, "frame_count=", (rubyfunc)argss_graphics_frame_countE, 1);
    rb_define_singleton_method(ARGSS_Graphics, "fps", (rubyfunc)argss_graphics_fps, 0);
    rb_define_singleton_method(ARGSS_Graphics, "backcolor", (rubyfunc)argss_graphics_backcolor, 0);
    rb_define_singleton_method(ARGSS_Graphics, "backcolor=", (rubyfunc)argss_graphics_backcolorE, 1);
    rb_define_singleton_method(ARGSS_Graphics, "width", (rubyfunc)argss_graphics_width, 0);
    rb_define_singleton_method(ARGSS_Graphics, "height", (rubyfunc)argss_graphics_height, 0);
}
