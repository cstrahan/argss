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
#include <string>
#include "argss/modules/aaudio.h"
#include "audio/audio.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::AAudio::id;

///////////////////////////////////////////////////////////
// ARGSS Audio module methods
///////////////////////////////////////////////////////////
VALUE ARGSS::AAudio::rbgm_play(int argc, VALUE* argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
	else if (argc > 3) raise_argn(argc, 3);
	Check_Type(argv[0], T_STRING);
	int volume = 100;
	int pitch = 100;
	if (argc > 1) {
		Check_Kind(argv[1], rb_cNumeric);
		volume = NUM2INT(argv[1]);
		if (argc > 2) {
			Check_Kind(argv[2], rb_cNumeric);
			pitch = NUM2INT(argv[2]);
		}
	}
	Audio::BGM_Play(StringValuePtr(argv[0]), volume, pitch);
	return Qnil;
}
VALUE ARGSS::AAudio::rbgm_stop(VALUE self) {
	Audio::BGM_Stop();
	return Qnil;
}
VALUE ARGSS::AAudio::rbgm_fade(VALUE self, VALUE fade) {
	Check_Kind(fade, rb_cNumeric);
	Audio::BGM_Fade(NUM2INT(fade));
	return Qnil;
}
VALUE ARGSS::AAudio::rbgs_play(int argc, VALUE* argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
	else if (argc > 3) raise_argn(argc, 3);
	Check_Type(argv[0], T_STRING);
	int volume = 100;
	int pitch = 100;
	if (argc > 1) {
		Check_Kind(argv[1], rb_cNumeric);
		volume = NUM2INT(argv[1]);
		if (argc > 2) {
			Check_Kind(argv[2], rb_cNumeric);
			pitch = NUM2INT(argv[2]);
		}
	}
	Audio::BGS_Play(StringValuePtr(argv[0]), volume, pitch);
	return Qnil;
}
VALUE ARGSS::AAudio::rbgs_stop(VALUE self) {
	Audio::BGS_Stop();
	return Qnil;
}
VALUE ARGSS::AAudio::rbgs_fade(VALUE self, VALUE fade) {
	Check_Kind(fade, rb_cNumeric);
	Audio::BGS_Fade(NUM2INT(fade));
	return Qnil;
}
VALUE ARGSS::AAudio::rme_play(int argc, VALUE* argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
	else if (argc > 3) raise_argn(argc, 3);
	Check_Type(argv[0], T_STRING);
	int volume = 100;
	int pitch = 100;
	if (argc > 1) {
		Check_Kind(argv[1], rb_cNumeric);
		volume = NUM2INT(argv[1]);
		if (argc > 2) {
			Check_Kind(argv[2], rb_cNumeric);
			pitch = NUM2INT(argv[2]);
		}
	}
	Audio::ME_Play(StringValuePtr(argv[0]), volume, pitch);
	return Qnil;
}
VALUE ARGSS::AAudio::rme_stop(VALUE self) {
	Audio::ME_Stop();
	return Qnil;
}
VALUE ARGSS::AAudio::rme_fade(VALUE self, VALUE fade) {
	Check_Kind(fade, rb_cNumeric);
	Audio::ME_Fade(NUM2INT(fade));
	return Qnil;
}
VALUE ARGSS::AAudio::rse_play(int argc, VALUE* argv, VALUE self) {
	if (argc == 0) raise_argn(argc, 1);
	else if (argc > 3) raise_argn(argc, 3);
	Check_Type(argv[0], T_STRING);
	int volume = 100;
	int pitch = 100;
	if (argc > 1) {
		Check_Kind(argv[1], rb_cNumeric);
		volume = NUM2INT(argv[1]);
		if (argc > 2) {
			Check_Kind(argv[2], rb_cNumeric);
			pitch = NUM2INT(argv[2]);
		}
	}
	Audio::SE_Play(StringValuePtr(argv[0]), volume, pitch);
	return Qnil;
}
VALUE ARGSS::AAudio::rse_stop(VALUE self) {
	Audio::SE_Stop();
	return Qnil;
}

///////////////////////////////////////////////////////////
// ARGSS Audio initialize
///////////////////////////////////////////////////////////
void ARGSS::AAudio::Init() {
	id = rb_define_module("Audio");
	rb_define_singleton_method(id, "bgm_play", (rubyfunc)rbgm_play, -1);
	rb_define_singleton_method(id, "bgm_stop", (rubyfunc)rbgm_stop, 0);
	rb_define_singleton_method(id, "bgm_fade", (rubyfunc)rbgm_fade, 1);
	rb_define_singleton_method(id, "bgs_play", (rubyfunc)rbgs_play, -1);
	rb_define_singleton_method(id, "bgs_stop", (rubyfunc)rbgs_stop, 0);
	rb_define_singleton_method(id, "bgs_fade", (rubyfunc)rbgs_fade, 1);
	rb_define_singleton_method(id, "me_play", (rubyfunc)rme_play, -1);
	rb_define_singleton_method(id, "me_stop", (rubyfunc)rme_stop, 0);
	rb_define_singleton_method(id, "me_fade", (rubyfunc)rme_fade, 1);
	rb_define_singleton_method(id, "se_play", (rubyfunc)rse_play, -1);
	rb_define_singleton_method(id, "se_stop", (rubyfunc)rse_stop, 0);
}
