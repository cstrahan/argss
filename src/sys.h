#ifndef _SYS_H_
#define _SYS_H_

#include <string>

extern std::string Sys_ScriptsPath;
extern std::string Sys_Title;
extern std::string Sys_RTPS[3];
extern int Sys_Res[3];

extern bool Sys_Focus;
extern bool Sys_FocusPauseGame;
extern bool Sys_FocusPauseAudio;

void Init_Sys();

#endif
