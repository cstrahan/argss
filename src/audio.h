//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
///         All rights reserved.
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

#ifndef _AUDIO_H_
#define _AUDIO_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_mixer.h"

////////////////////////////////////////////////////////////
/// Audio namespace
////////////////////////////////////////////////////////////
namespace Audio {
	void Init();
	void Pause();
	void Continue();

	void BGM_Play(std::string file, int volume, int pitch);
	void BGM_Stop();
	void BGM_Fade(int fade);
	void BGS_Play(std::string file, int volume, int pitch);
	void BGS_Stop();
	void BGS_Fade(int fade);
	void ME_Play(std::string file, int volume, int pitch);
	void ME_Stop();
	void ME_Fade(int fade);
	void SE_Play(std::string file, int volume, int pitch);
	void SE_Stop();
	
	extern Mix_Music* bgm;
	extern int bgm_volume;
	extern bool bgm_playing;
	extern Mix_Chunk* bgs;
	extern int bgs_channel;
	extern Mix_Music* me;
	extern bool me_playing;
	extern std::map<int, Mix_Chunk*> sounds;
	extern std::map<int, Mix_Chunk*>::iterator it_sounds;
};

#endif
