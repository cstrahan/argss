#include "sys.h"
#include "tools/simpleini/simpleini.h"

void Init_Sys()
{
	CSimpleIniA ini(true, false, false);
    SI_Error rc = ini.LoadFile(".\\ARGSS.ini");
    if (rc < 0) {
        //Error
    }
    Sys_ScriptsPath = ini.GetValue("Game", "Scripts", "NULL");
    if (Sys_ScriptsPath == "NULL") {
        //Error
    }
    Sys_Title = ini.GetValue("Game", "Title", "ARGSS");
    int i, e;
    char rtp[4];
    for(i = 0; i < 3; i++) {
        e = i;
        sprintf(rtp, "RTP%d", ++e);
        Sys_RTPS[e] = ini.GetValue("Game", rtp, "");
    }
    Sys_Res[0] = ini.GetLongValue("Game", "ResW", 640);
    Sys_Res[1] = ini.GetLongValue("Game", "ResH", 480);
    Sys_Res[2] = ini.GetLongValue("Game", "ResC", 32);
    Sys_Focus = true;
    Sys_FocusPauseGame = true;
    Sys_FocusPauseAudio = true;
}
