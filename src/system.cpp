//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///     * Redistributions of source code must retain the above copyright
///       notice, this list of conditions and the following disclaimer.
///     * Redistributions in binary form must reproduce the above copyright
///       notice, this list of conditions and the following disclaimer in the
///       documentation and/or other materials provided with the distribution.
///
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
/// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
/// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
/// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
/// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
/// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "system.h"
#include "log.h"
#include "options.h"
#include "simpleini.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
std::string System::Title;
std::string System::ScriptsPath;
std::string System::RTPS[3];
int System::Width;
int System::Height;
bool System::Focus;
bool System::FocusPauseGame;
bool System::FocusPauseAudio;

////////////////////////////////////////////////////////////
/// Initialize system
////////////////////////////////////////////////////////////
void System::Init() {
	Title = GAME_TITLE;
	ScriptsPath = SCRIPTS_PATH;
	RTPS[0] = RTP1;
	RTPS[1] = RTP2;
	RTPS[2] = RTP3;
	Width = SCREEN_WIDTH;
	Height = SCREEN_HEIGHT;
	Focus = true;
	FocusPauseGame = PAUSE_GAME_WHEN_FOCUS_LOST;
	FocusPauseAudio = PAUSE_AUDIO_WHEN_FOCUS_LOST;
	if(READ_INI_GAME_TITLE || READ_INI_SCRIPTS_PATH || READ_INI_SCREEN_SIZE || READ_INI_RTPS) {
		CSimpleIniA ini(true, false, false);
		SI_Error rc = ini.LoadFile(INI_NAME);
		if (rc < 0) {
			std::string str = "ARGSS could not open \"";
			str += INI_NAME;
			str += "\" file.";
			Log::Warning(str);
		}
		if(READ_INI_SCRIPTS_PATH) {
			ScriptsPath = ini.GetValue("Game", "Scripts", SCRIPTS_PATH);
		}
		if(READ_INI_GAME_TITLE) {
			Title = ini.GetValue("Game", "Title", GAME_TITLE);
		}
		if(READ_INI_RTPS) {
			RTPS[0] = ini.GetValue("Game", "RTP1", RTP1);
			RTPS[1] = ini.GetValue("Game", "RTP2", RTP2);
			RTPS[2] = ini.GetValue("Game", "RTP3", RTP3);
		}
		if(READ_INI_SCREEN_SIZE) {
			Width = ini.GetLongValue("Game", "Width", Width);
			Height = ini.GetLongValue("Game", "Height", Height);
		}
	}
}
