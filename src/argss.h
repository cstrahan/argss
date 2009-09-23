#ifndef _ARGSS_H_
#define _ARGSS_H_

#include <functional>
//#include <map>
#include <list>
#include <string>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Sprite.hpp>
extern "C" {
    #include "ruby.h"
}
#include "objs.h"

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
extern VALUE ARGSS_Keys;

extern int ARGSS_FrameRate;
extern unsigned long ARGSS_FrameCount;
extern int ARGSS_FPS;

//ARGSS Objects
//extern std::map<VALUE, sf::Image> ARGSS_mapBitmaps;
//extern std::map<VALUE, sf::Sprite> ARGSS_mapSprites;

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
