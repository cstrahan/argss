#ifndef _ARGSS_H_
#define _ARGSS_H_

#include <functional>
#include <list>
#include <string>
extern "C" {
    #include "ruby.h"
}
#include "zobj.h"

void Init_ARGSS();

//Classes
extern VALUE ARGSS_Bitmap;
extern VALUE ARGSS_Sprite;
extern VALUE ARGSS_Color;
extern VALUE ARGSS_Font;
extern VALUE ARGSS_Plane;
extern VALUE ARGSS_Rect;
extern VALUE ARGSS_Table;
extern VALUE ARGSS_Tilemap;
extern VALUE ARGSS_Tone;
extern VALUE ARGSS_Viewport;
extern VALUE ARGSS_Window;
extern VALUE ARGSS_Error;

// Modules
extern VALUE ARGSS_Console;
extern VALUE ARGSS_Graphics;
extern VALUE ARGSS_Input;
extern VALUE ARGSS_Audio;

extern int ARGSS_FrameRate;
extern VALUE ARGSS_FrameCount;
extern int ARGSS_FPS;

extern VALUE ARGSS_CreationTime;

extern std::list<Z_Obj> ARGSS_ZOrder;
extern std::list<Z_Obj>::iterator ARGSS_itZOrder;

extern unsigned int ARGSS_Input_StartRepeatTime;
extern unsigned int ARGSS_Input_RepeatTime;

void argss_update();

bool compare_zobj(Z_Obj& first, Z_Obj& second);

struct remove_zobj_id : public std::binary_function<Z_Obj, Z_Obj, bool> {
    remove_zobj_id(VALUE val) : id(val) {}
    bool operator () (Z_Obj &obj) const {return obj.get_id() == id;}
    VALUE id;
};

#endif
