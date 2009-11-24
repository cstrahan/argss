#include "graphics.h"
#include "argss.h"
#include "argss_sdl.h"
#include "sys.h"
#include "aerror.h"
#include "color.h"

static double framerate_interval;

void argss_graphics_draw_frame() {
	SDL_FillRect(screen, &screen->clip_rect, ARGSS_Graphics_BackColor);
	
	VALUE type;
	
	ARGSS_ZOrder.sort(compare_zobj);
    for(ARGSS_itZOrder = ARGSS_ZOrder.begin(); ARGSS_itZOrder != ARGSS_ZOrder.end(); ARGSS_itZOrder++) {
        type = ARGSS_itZOrder->get_type();
		if(type == ARGSS_Sprite) {
                if (ARGSS_mapSprites.count(ARGSS_itZOrder->get_id()) == 1) {
                    ARGSS_mapSprites[ARGSS_itZOrder->get_id()].draw(screen);
                }
		}
		else if(type == ARGSS_Plane) {
			
		}
		else if(type == ARGSS_Window) {
			
		}
		else if(type == ARGSS_Tilemap) {
			
		}
		else if(type == ARGSS_Viewport) {
			
		}
    }
	
	if(SDL_Flip(screen) == -1) {
		rb_raise(ARGSS_Error, "SDL could not flip screen.\n%s\n", SDL_GetError());
	}
}

static VALUE argss_graphics_update(VALUE self) {
	static long t;
	static long tl = SDL_GetTicks() + (long)framerate_interval;
	static long t_fps = tl;
	static long frames = 0;
	static double waitframes = 0;
	static double cyclesleftover;

	argss_update();
	if(waitframes > 0) {
		waitframes -= 1;
		return Qnil;
	}
	t = SDL_GetTicks();
	if((t - tl) >= (long)framerate_interval) {
		cyclesleftover = waitframes;
		waitframes = (double)(t - tl) / framerate_interval - cyclesleftover;
		//tl += (t - tl) - cyclesleftover;
		tl = t;
		argss_graphics_draw_frame();
		
		ARGSS_FrameCount++;
		frames++;
		
		if (t - t_fps >= 1000) {
			t_fps += 1000;
			ARGSS_FPS = frames;
			frames = 0;
			
			char title[255];
			sprintf(title, "%s - %d FPS", Sys_Title.c_str(), ARGSS_FPS);
			SDL_WM_SetCaption(title, NULL);
		}
	}
	else {
		SDL_Delay((long)(framerate_interval) - (t - tl));
	}
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
	framerate_interval = 1000.0 / ARGSS_FrameRate;
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
    ARGSS_Graphics_BackColor = argss_color_getuint32(backcolor, screen->format);
    return backcolor;
}
static VALUE argss_graphics_width(VALUE self) {
    return INT2NUM(Sys_Res[0]);
}
static VALUE argss_graphics_height(VALUE self) {
    return INT2NUM(Sys_Res[1]);
}
static VALUE argss_graphics_wait(VALUE self, VALUE duration) {
	Check_Type(duration, T_FIXNUM);
	for(int frames = NUM2INT(duration); frames > 0; frames--) {
		argss_graphics_update(self);
	}
	return Qnil;
}
void Init_Graphics()
{
    ARGSS_FPS = 0;
    ARGSS_FrameCount = 0;
    ARGSS_FrameRate = 60;
    ARGSS_Graphics_BackColor = 0;
	
	framerate_interval = 1000.0 / ARGSS_FrameRate;
	
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
	rb_define_singleton_method(ARGSS_Graphics, "wait", (rubyfunc)argss_graphics_wait, 1);
}
