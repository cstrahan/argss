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
#include "input/input.h"
#include "input/buttons.h"
#include "aruby.h"
#include "argss/modules/ainput.h"
#include "player.h"
#include "output.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
std::vector<int> Input::press_time;
std::vector<bool> Input::triggered;
std::vector<bool> Input::repeated;
std::vector<bool> Input::released;
int Input::dir4;
int Input::dir8;
int Input::start_repeat_time;
int Input::repeat_time;
std::vector< std::vector<int> > Input::dirkeys;

///////////////////////////////////////////////////////////
/// Initialize
///////////////////////////////////////////////////////////
void Input::Init() {
	press_time.resize(Keys::KEYS_COUNT, 0);
	triggered.resize(Keys::KEYS_COUNT, false);
	repeated.resize(Keys::KEYS_COUNT, false);
	released.resize(Keys::KEYS_COUNT, false);

	dir4 = 0;
	dir8 = 0;

	start_repeat_time = 20;
	repeat_time = 10;

	InitButtons();

	dirkeys.resize(10);
	dirkeys[1].push_back(Keys::KP1);
	dirkeys[2].push_back(Keys::KP2);
	dirkeys[2].push_back(Keys::DOWN);
	dirkeys[3].push_back(Keys::KP3);
	dirkeys[4].push_back(Keys::KP4);
	dirkeys[4].push_back(Keys::LEFT);
	dirkeys[6].push_back(Keys::KP6);
	dirkeys[6].push_back(Keys::RIGHT);
	dirkeys[7].push_back(Keys::KP7);
	dirkeys[8].push_back(Keys::KP8);
	dirkeys[8].push_back(Keys::UP);
	dirkeys[9].push_back(Keys::KP9);
}

///////////////////////////////////////////////////////////
/// Update keys state
///////////////////////////////////////////////////////////
void Input::Update() {
	Player::Update();

	std::vector<bool> keystates = Player::main_window->GetKeyStates();
	for (unsigned int i = 0; i < press_time.size(); ++i) {
		if (keystates[i]) {
			press_time[i] += 1;
			released[i] = false;
		} else {
			if (press_time[i] > 0) {
				released[i] = true;
			} else {
				released[i] = false;
			}
			press_time[i] = 0;
		}
		if (press_time[i] > 0) {
			if (press_time[i] == 1) {
				triggered[i] = true;
			} else {
				triggered[i] = false;
			}
			if (press_time[i] == 1 || (press_time[i] >= start_repeat_time &&
											press_time[i] % repeat_time == 0)) {
				repeated[i] = true;
			} else {
				repeated[i] = false;
			}
			} else {
			triggered[i] = false;
			repeated[i] = false;
		}
	}

	int dirpress[10];
	for (int i = 1; i < 10; i++) {
		dirpress[i] = 0;
		if (i != 5) {
			int presstime;
			for (unsigned int e = 0; e < dirkeys[i].size(); e++) {
				presstime = press_time[dirkeys[i][e]];
				if (presstime > dirpress[i]) {
					dirpress[i] = presstime;
				}
			}
		}
	}

	dirpress[1]	+= (dirpress[2] > 0 && dirpress[4] > 0) ? dirpress[2] + dirpress[4] : 0;
	dirpress[3]	+= (dirpress[2] > 0 && dirpress[6] > 0) ? dirpress[2] + dirpress[6] : 0;
	dirpress[7]	+= (dirpress[8] > 0 && dirpress[4] > 0) ? dirpress[8] + dirpress[4] : 0;
	dirpress[9]	+= (dirpress[8] > 0 && dirpress[6] > 0) ? dirpress[8] + dirpress[6] : 0;

	dir4 = 0;
	dir8 = 0;

	if (!(dirpress[2] > 0 && dirpress[8] > 0) && !(dirpress[4] > 0 && dirpress[6] > 0)) {
		int e = 0;
		for (int i = 0; i < 4; i++) {
			if (dirpress[(i + 1) * 2] > 0) {
				if (e == 0 || dirpress[(i + 1) * 2] < e) {
					dir4 = (i + 1) * 2;
					e = dirpress[(i + 1) * 2];
				}
			}
		}
		dir8 = dir4;
		if (dirpress[9] > 0) dir8 = 9;
		else if (dirpress[7] > 0) dir8 = 7;
		else if (dirpress[3] > 0) dir8 = 3;
		else if (dirpress[1] > 0) dir8 = 1;
	}
}

///////////////////////////////////////////////////////////
/// Clear keys state
///////////////////////////////////////////////////////////
void Input::ClearKeys() {
	for (unsigned int i = 0; i < press_time.size(); i++) {
		press_time[i] = 0;
		triggered[i] = false;
		repeated[i] = false;
		released[i] = false;
	}
	dir4 = 0;
	dir8 = 0;
}

///////////////////////////////////////////////////////////
/// Is pressed?
///////////////////////////////////////////////////////////
bool Input::IsPressed(VALUE button) {
	if (NUM2INT(button) < 1000) {
		int key = NUM2INT(button);
		if (buttons.count(key) == 0) return false;
		for (unsigned int i = 0; i < buttons[key].size(); i++) {
			if (press_time[buttons[key][i]] > 0) return true;
		}
		return false;
	}
	return press_time[NUM2KEY(button)] > 0;
}

///////////////////////////////////////////////////////////
/// Is triggered?
///////////////////////////////////////////////////////////
bool Input::IsTriggered(VALUE button) {
	if (NUM2INT(button) < 1000) {
		int key = NUM2INT(button);
		if (buttons.count(key) == 0) return false;
		for (unsigned int i = 0; i < buttons[key].size(); i++) {
			if (triggered[buttons[key][i]]) return true;
		}
		return false;
	}
	return triggered[NUM2KEY(button)];
}

///////////////////////////////////////////////////////////
/// Is repeated?
///////////////////////////////////////////////////////////
bool Input::IsRepeated(VALUE button) {
	if (NUM2INT(button) < 1000) {
		int key = NUM2INT(button);
		if (buttons.count(key) == 0) return false;
		std::vector<int> a = buttons[key];
		for (unsigned int i = 0; i < buttons[key].size(); i++) {
			if (repeated[buttons[key][i]]) return true;
		}
		return false;
	}
	return repeated[NUM2KEY(button)];
}

///////////////////////////////////////////////////////////
/// Is released?
///////////////////////////////////////////////////////////
bool Input::IsReleased(VALUE button) {
	if (NUM2INT(button) < 1000) {
		int key = NUM2INT(button);
		if (buttons.count(key) == 0) return false;
		for (unsigned int i = 0; i < buttons[key].size(); i++) {
			if (released[buttons[key][i]]) return true;
		}
		return false;
	}
	return released[NUM2KEY(button)];
}

///////////////////////////////////////////////////////////
/// Get pressed keys
///////////////////////////////////////////////////////////
VALUE Input::GetPressed() {
	VALUE arr = rb_ary_new();
	for (unsigned int i = 0; i < press_time.size(); i++) {
		if (press_time[i] > 0) {
			rb_ary_push(arr, KEY2NUM(i));
		}
	}
	return arr;
}

///////////////////////////////////////////////////////////
/// Get triggered keys
///////////////////////////////////////////////////////////
VALUE Input::GetTriggered() {
	VALUE arr = rb_ary_new();
	for (unsigned int i = 0; i < triggered.size(); i++) {
		if (triggered[i]) {
			rb_ary_push(arr, KEY2NUM(i));
		}
	}
	return arr;
}

///////////////////////////////////////////////////////////
/// Get repeated keys
///////////////////////////////////////////////////////////
VALUE Input::GetRepeated() {
	VALUE arr = rb_ary_new();
	for (unsigned int i = 0; i < repeated.size(); i++) {
		if (repeated[i]) {
			rb_ary_push(arr, KEY2NUM(i));
		}
	}
	return arr;
}

///////////////////////////////////////////////////////////
/// Get released keys
///////////////////////////////////////////////////////////
VALUE Input::GetReleased() {
	VALUE arr = rb_ary_new();
	for (unsigned int i = 0; i < released.size(); i++) {
		if (released[i]) {
			rb_ary_push(arr, KEY2NUM(i));
		}
	}
	return arr;
}
