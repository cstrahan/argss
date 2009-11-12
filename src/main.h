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
