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
    int i, e;
    char rtp[4];
    for(i = 0; i < 3; i++) {
		e = i + 1;
        sprintf(rtp, "RTP%d", e);
        Sys_RTPS[i] = ini.GetValue("Game", rtp, "");
    }
    Sys_Res[0] = ini.GetLongValue("Game", "ResW", 640);
    Sys_Res[1] = ini.GetLongValue("Game", "ResH", 480);
    Sys_Res[2] = ini.GetLongValue("Game", "ResC", 32);
    Sys_Focus = true;
    Sys_FocusPauseGame = true;
    Sys_FocusPauseAudio = true;
}
