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

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "audio.h"
#include "argss_ruby.h"
#include "argss_error.h"
#include "output.h"
#include "filefinder.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
Mix_Music* Audio::bgm;
int Audio::bgm_volume;
Mix_Chunk* Audio::bgs;
int Audio::bgs_channel;
Mix_Chunk* Audio::me;
int Audio::me_channel;
bool Audio::me_stopped_bgm;
std::map<int, Mix_Chunk*> Audio::sounds;
std::map<int, Mix_Chunk*>::iterator Audio::it_sounds;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Audio::Init() {
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		Output::Error("ARGSS couldn't initialize audio.\n%s\n", Mix_GetError());
	}
	bgm = NULL;
	bgs = NULL;
	me = NULL;
	me_stopped_bgm = false;
}

////////////////////////////////////////////////////////////
/// BGM play
////////////////////////////////////////////////////////////
void Audio::BGM_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path == "") {
		VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
		rb_raise(enoent, "No such file or directory - %s", file.c_str());
	}
	if (bgm != NULL) Mix_FreeMusic(bgm);
	bgm = Mix_LoadMUS(path.c_str());
	if (!bgm) {
		rb_raise(ARGSS::AError::id, "couldn't load %s BGM.\n%s\n", file.c_str(), Mix_GetError());
	}
	bgm_volume = volume * MIX_MAX_VOLUME / 100;
	Mix_VolumeMusic(bgm_volume);
	if (!me_stopped_bgm) {
		if (Mix_PlayMusic(bgm, -1) == -1) {
			rb_raise(ARGSS::AError::id, "couldn't play %s BGM.\n%s\n", file.c_str(), Mix_GetError());
		}
	}
}

////////////////////////////////////////////////////////////
/// BGM stop
////////////////////////////////////////////////////////////
void Audio::BGM_Stop() {
	Mix_HaltMusic();
	me_stopped_bgm = false;
}

////////////////////////////////////////////////////////////
/// BGM fade
////////////////////////////////////////////////////////////
void Audio::BGM_Fade(int fade) {
	Mix_FadeOutMusic(fade);
	me_stopped_bgm = false;
}

////////////////////////////////////////////////////////////
/// BGS play
////////////////////////////////////////////////////////////
void Audio::BGS_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path == "") {
		VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
		rb_raise(enoent, "No such file or directory - %s", file.c_str());
	}
	if (bgs != NULL) Mix_FreeChunk(bgs);
	bgs = Mix_LoadWAV(path.c_str());
	if (!bgs) {
		rb_raise(ARGSS::AError::id, "couldn't load %s BGS.\n%s\n", file.c_str(), Mix_GetError());
	}
	bgs_channel = Mix_PlayChannel(-1, bgs, -1);
	Mix_Volume(bgs_channel, volume * MIX_MAX_VOLUME / 100);
	if (bgs_channel == -1) {
		rb_raise(ARGSS::AError::id, "couldn't play %s BGS.\n%s\n", file.c_str(), Mix_GetError());
	}
}

////////////////////////////////////////////////////////////
/// BGS stop
////////////////////////////////////////////////////////////
void Audio::BGS_Stop() {
	if (Mix_Playing(bgs_channel)) Mix_HaltChannel(bgs_channel);
}

////////////////////////////////////////////////////////////
/// BGS fade
////////////////////////////////////////////////////////////
void Audio::BGS_Fade(int fade) {
	Mix_FadeOutChannel(bgs_channel, fade);
}

////////////////////////////////////////////////////////////
/// ME play
////////////////////////////////////////////////////////////
void me_finish(int channel) {
	if (Audio::me_channel == channel) {
		if (Audio::me_stopped_bgm) {
			Mix_VolumeMusic(Audio::bgm_volume);
			Mix_FadeInMusic(Audio::bgm, -1, 1000);
			Audio::me_stopped_bgm = false;
		}
	}
}
void Audio::ME_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path == "") {
		VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
		rb_raise(enoent, "No such file or directory - %s", file.c_str());
	}
	if (me != NULL) Mix_FreeChunk(bgs);
	me = Mix_LoadWAV(path.c_str());
	if (!me) {
		rb_raise(ARGSS::AError::id, "couldn't load %s ME.\n%s\n", file.c_str(), Mix_GetError());
	}
	me_channel = Mix_PlayChannel(-1, me, 0);
	Mix_Volume(me_channel, volume * MIX_MAX_VOLUME / 100);
	if (me_channel == -1) {
		rb_raise(ARGSS::AError::id, "couldn't play %s ME.\n%s\n", file.c_str(), Mix_GetError());
	}
	me_stopped_bgm = Mix_PlayingMusic() == 1;
	Mix_ChannelFinished(me_finish);
}

////////////////////////////////////////////////////////////
/// ME stop
////////////////////////////////////////////////////////////
void Audio::ME_Stop() {
	if (Mix_Playing(me_channel)) Mix_HaltChannel(me_channel);
}

////////////////////////////////////////////////////////////
/// ME fade
////////////////////////////////////////////////////////////
void Audio::ME_Fade(int fade) {
	Mix_FadeOutChannel(me_channel, fade);
}

////////////////////////////////////////////////////////////
/// SE play
////////////////////////////////////////////////////////////
void Audio::SE_Play(std::string file, int volume, int pitch) {
	std::string path = FileFinder::FindMusic(file);
	if (path == "") {
		VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
		rb_raise(enoent, "No such file or directory - %s", file.c_str());
	}
	Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
	if (!sound) {
		rb_raise(ARGSS::AError::id, "couldn't load %s SE.\n%s\n", file.c_str(), Mix_GetError());
	}
	int channel = Mix_PlayChannel(-1, sound, 0);
	Mix_Volume(channel, volume * MIX_MAX_VOLUME / 100);
	if (channel == -1) {
		rb_raise(ARGSS::AError::id, "couldn't play %s SE.\n%s\n", file.c_str(), Mix_GetError());
	}
	sounds[channel] = sound;
}

////////////////////////////////////////////////////////////
/// SE stop
////////////////////////////////////////////////////////////
void Audio::SE_Stop() {
	for(it_sounds = sounds.begin(); it_sounds != sounds.end(); it_sounds++) {
		if (Mix_Playing(it_sounds->first)) Mix_HaltChannel(it_sounds->first);
		Mix_FreeChunk(it_sounds->second);
	}
	sounds.clear();
}
