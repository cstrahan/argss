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

#ifndef _MAIN_H_
#define _MAIN_H_

#include <string>
#include <list>
#include <map>
#include "SDL.h"
#include "sdl_sprite.h"
#include "sdl_viewport.h"
#include "sdl_plane.h"
#include "sdl_window.h"
#include "sdl_tilemap.h"
#include "zobj.h"

std::string Sys_ScriptsPath;
std::string Sys_Title;
std::string Sys_RTPS[3];
int Sys_Res[3];

bool Sys_Focus;
bool Sys_FocusPauseGame;
bool Sys_FocusPauseAudio;

unsigned long ARGSS_Bitmap;
unsigned long ARGSS_Sprite;
unsigned long ARGSS_Color;
unsigned long ARGSS_Font;
unsigned long ARGSS_Plane;
unsigned long ARGSS_Rect;
unsigned long ARGSS_Table;
unsigned long ARGSS_Tilemap;
unsigned long ARGSS_Tone;
unsigned long ARGSS_Viewport;
unsigned long ARGSS_Window;
unsigned long ARGSS_Error;

unsigned long ARGSS_Console;
unsigned long ARGSS_Graphics;
unsigned long ARGSS_Input;
unsigned long ARGSS_Audio;

int ARGSS_FrameRate;
unsigned long ARGSS_FrameCount;
int ARGSS_FPS;

unsigned long ARGSS_CreationTime;

std::list<Z_Obj> ARGSS_ZOrder;
std::list<Z_Obj>::iterator ARGSS_itZOrder;

unsigned int ARGSS_Input_StartRepeatTime;
unsigned int ARGSS_Input_RepeatTime;

SDL_Surface* screen;

std::map<unsigned long, SDL_Surface*> ARGSS_mapBitmaps;
std::map<unsigned long, SDL_Sprite> ARGSS_mapSprites;
std::map<unsigned long, SDL_Viewport> ARGSS_mapViewports;
std::map<unsigned long, SDL_Plane> ARGSS_mapPlanes;
std::map<unsigned long, SDL_Window> ARGSS_mapWindows;
std::map<unsigned long, SDL_Tilemap> ARGSS_mapTilemaps;
Uint32 ARGSS_Graphics_BackColor;

#endif
