#include "sys.h"
#include "simpleini.h"

void Init_Sys()
{
	Sys_Res[0] = 640;
	Sys_Res[1] = 480;
	Sys_Res[2] = 32;
	CSimpleIniA ini(true, false, false);
    SI_Error rc = ini.LoadFile(".\\ARGSS.ini");
    if (rc < 0) {
        fprintf(stderr, "ARGSS could not open \"ARGSS.ini\" file.\n");
		exit(-1);
    }
    Sys_ScriptsPath = ini.GetValue("Game", "Scripts", "NULL");
    if (Sys_ScriptsPath == "NULL") {
        fprintf(stderr, "ARGSS could not find the scripts path on \"ARGSS.ini\".\n");
		exit(-1);
    }
    Sys_Title = ini.GetValue("Game", "Title", "ARGSS");
    int i;
    char rtp[4];
    for(i = 0; i < 3; i++) {
        sprintf(rtp, "RTP%d", i + 1);
        Sys_RTPS[i] = ini.GetValue("Game", rtp, "");
    }
    Sys_Res[0] = ini.GetLongValue("Game", "ResW", 640);
    Sys_Res[1] = ini.GetLongValue("Game", "ResH", 480);
    Sys_Res[2] = ini.GetLongValue("Game", "ResC", 32);
    Sys_Focus = true;
    Sys_FocusPauseGame = true;
    Sys_FocusPauseAudio = true;
}
