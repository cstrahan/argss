/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "audio/sdl/audio_sdl.h"
#include "argss/classes/aerror.h"
#include "tools/filefinder.h"
#include "output.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
Mix_Music* Audio::bgm;
int Audio::bgm_volume;
bool Audio::bgm_playing;
Mix_Chunk* Audio::bgs;
int Audio::bgs_channel;
Mix_Music* Audio::me;
bool Audio::me_playing;
std::map<int, Mix_Chunk*> Audio::sounds;
std::map<int, Mix_Chunk*>::iterator Audio::it_sounds;

///////////////////////////////////////////////////////////
// Initialize
///////////////////////////////////////////////////////////
void Audio::Init() {
	// Starts the SDL sudio subsystem
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
		Output::Error("ARGSS couldn't initialize audio.\n%s\n", SDL_GetError());
	}

	// Opens audio for playback
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		Output::Error("ARGSS couldn't initialize audio.\n%s\n", Mix_GetError());
	}

	bgm = NULL;
	bgs = NULL;
	me = NULL;
	bgm_playing = false;
	me_playing = false;
}

///////////////////////////////////////////////////////////
// Audio Pause
///////////////////////////////////////////////////////////
void Audio::Pause() {
	// TODO
}

///////////////////////////////////////////////////////////
// Audio Continue
///////////////////////////////////////////////////////////
void Audio::Continue() {
	// TODO
}

///////////////////////////////////////////////////////////
// ME finish callback
///////////////////////////////////////////////////////////
void Audio::ME_finish() {
	Mix_VolumeMusic(Audio::bgm_volume);
	Mix_FadeInMusic(Audio::bgm, -1, 1000);
	Audio::bgm_playing = true;
	Audio::me_playing = false;
	Mix_HookMusicFinished(NULL);
}

///////////////////////////////////////////////////////////
// BGM play
///////////////////////////////////////////////////////////
void Audio::BGM_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path.empty()) ARGSS::AError::FileNotFound(file);

	if (bgm != NULL) Mix_FreeMusic(bgm);

	bgm = Mix_LoadMUS(path.c_str());
	if (!bgm) ARGSS::AError::AudioNotLoad("BGM", file, Mix_GetError());

	bgm_volume = volume * MIX_MAX_VOLUME / 100;
	if (me_playing) {
		Mix_HookMusicFinished(ME_finish);
	} else {
		bgm_playing = true;
		Mix_VolumeMusic(bgm_volume);
		if (Mix_PlayMusic(bgm, -1) == -1) ARGSS::AError::AudioNotPlay("BGM", file, Mix_GetError());

		Mix_HookMusicFinished(NULL);
	}
}

///////////////////////////////////////////////////////////
// BGM stop
///////////////////////////////////////////////////////////
void Audio::BGM_Stop() {
	if (bgm_playing) {
		Mix_HaltMusic();
		bgm_playing = false;
	}
	Mix_HookMusicFinished(NULL);
}

///////////////////////////////////////////////////////////
// BGM fade
///////////////////////////////////////////////////////////
void Audio::BGM_Fade(int fade) {
	if (bgm_playing) {
		Mix_FadeOutMusic(fade);
		bgm_playing = false;
	}
	Mix_HookMusicFinished(NULL);
}

///////////////////////////////////////////////////////////
// BGS play
///////////////////////////////////////////////////////////
void Audio::BGS_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path.empty()) ARGSS::AError::FileNotFound(file);

	if (bgs != NULL) Mix_FreeChunk(bgs);

	bgs = Mix_LoadWAV(path.c_str());
	if (!bgs) ARGSS::AError::AudioNotLoad("BGS", file, Mix_GetError());

	bgs_channel = Mix_PlayChannel(-1, bgs, -1);
	Mix_Volume(bgs_channel, volume * MIX_MAX_VOLUME / 100);
	if (bgs_channel == -1) ARGSS::AError::AudioNotPlay("BGS", file, Mix_GetError());
}

///////////////////////////////////////////////////////////
// BGS stop
///////////////////////////////////////////////////////////
void Audio::BGS_Stop() {
	if (Mix_Playing(bgs_channel)) Mix_HaltChannel(bgs_channel);
}

///////////////////////////////////////////////////////////
// BGS fade
///////////////////////////////////////////////////////////
void Audio::BGS_Fade(int fade) {
	Mix_FadeOutChannel(bgs_channel, fade);
}

///////////////////////////////////////////////////////////
// ME play
///////////////////////////////////////////////////////////
void Audio::ME_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path.empty()) ARGSS::AError::FileNotFound(file);

	if (me != NULL) Mix_FreeMusic(me);
	me = Mix_LoadMUS(path.c_str());
	if (!me) ARGSS::AError::AudioNotLoad("ME", file, Mix_GetError());

	Mix_VolumeMusic(volume * MIX_MAX_VOLUME / 100);
	if (Mix_PlayMusic(me, 1) == -1) ARGSS::AError::AudioNotPlay("ME", file, Mix_GetError());

	me_playing = true;
	if (bgm_playing) {
		bgm_playing = false;
		Mix_HookMusicFinished(ME_finish);
	}
}

///////////////////////////////////////////////////////////
// ME stop
///////////////////////////////////////////////////////////
void Audio::ME_Stop() {
	if (me_playing) {
		Mix_HaltMusic();
		me_playing = false;
	}
}

///////////////////////////////////////////////////////////
// ME fade
///////////////////////////////////////////////////////////
void Audio::ME_Fade(int fade) {
	if (me_playing) {
		Mix_FadeOutMusic(fade);
		me_playing = false;
	}
}

///////////////////////////////////////////////////////////
// SE play
///////////////////////////////////////////////////////////
void Audio::SE_Play(std::string file, int volume, int pitch) {
	it_sounds = sounds.begin();
	while (it_sounds != sounds.end()) {
		if (!Mix_Playing(it_sounds->first)) {
			Mix_FreeChunk(it_sounds->second);
			sounds.erase(it_sounds++);
		} else {
			it_sounds++;
		}
	}
	if (sounds.size() >= 7) return;

	std::string path = FileFinder::FindMusic(file);
	if (path.empty()) ARGSS::AError::FileNotFound(file);

	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	if (!sound) ARGSS::AError::AudioNotLoad("SE", file, Mix_GetError());

	int channel = Mix_PlayChannel(-1, sound, 0);
	Mix_Volume(channel, volume * MIX_MAX_VOLUME / 100);
	if (channel == -1) ARGSS::AError::AudioNotPlay("SE", file, Mix_GetError());

	sounds[channel] = sound;
}

///////////////////////////////////////////////////////////
// SE stop
///////////////////////////////////////////////////////////
void Audio::SE_Stop() {
	for (it_sounds = sounds.begin(); it_sounds != sounds.end(); it_sounds++) {
		if (Mix_Playing(it_sounds->first)) Mix_HaltChannel(it_sounds->first);
		Mix_FreeChunk(it_sounds->second);
	}
	sounds.clear();
}
