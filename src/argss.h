// Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
