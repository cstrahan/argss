#ifndef _MAIN_H_
#define _MAIN_H_

#include <functional>
#include <map>
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "objs.h"

sf::RenderWindow SFML_Window;
sf::Clock SFML_Clock;

std::string Sys_ScriptsPath;
std::string Sys_Title;
std::string Sys_RTPS[3];
int Sys_Res[3] = {640, 480};

// Options
bool Sys_Focus;
bool Sys_FocusPauseGame;
bool Sys_FocusPauseAudio;

//Classes
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

// Modules
unsigned long ARGSS_Console;
unsigned long ARGSS_Graphics;
unsigned long ARGSS_Input;
unsigned long ARGSS_Audio;

int ARGSS_FrameRate;
unsigned long ARGSS_FrameCount;
int ARGSS_FPS;

//ARGSS Objects
std::map<unsigned long, sf::Image> ARGSS_mapBitmaps;
std::map<unsigned long, sf::Sprite> ARGSS_mapSprites;

unsigned long ARGSS_CreationTime;

std::list<Z_Obj> ARGSS_ZOrder;
std::list<Z_Obj>::iterator ARGSS_itZOrder;

sf::Color ARGSS_Graphics_BackColor;

unsigned int ARGSS_Input_StartRepeatTime;
unsigned int ARGSS_Input_RepeatTime;

#endif
