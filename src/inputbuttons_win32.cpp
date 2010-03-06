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
#include "inputbuttons_win32.h"
#include "inputkeys.h"
#include "registry.h"
#include "options.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
std::map< int, std::vector<int> > Input::buttons;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Input::InitButtons() {
	bool standard = true;
	
	if (READ_BUTTON_ASSIGMENT) {
		unsigned char data[1024];
		int n = Registry::ReadBinValue(HKEY_CURRENT_USER, READ_BUTTON_ASSIGMENT_KEY, READ_BUTTON_ASSIGMENT_VALUE, data);
		if (n > 0) {
			for (int i = 11; i < 19; i++) {
				for (int j = 0; j < 15; j++) {
					if (JOYSTICK_SUPPORT && j < 10) {
						if (i == data[j]) {
							if (j == 0) buttons[i].push_back(Keys::JOY_1);
							if (j == 1) buttons[i].push_back(Keys::JOY_2);
							if (j == 2) buttons[i].push_back(Keys::JOY_3);
							if (j == 3) buttons[i].push_back(Keys::JOY_4);
							if (j == 4) buttons[i].push_back(Keys::JOY_5);
							if (j == 5) buttons[i].push_back(Keys::JOY_6);
							if (j == 6) buttons[i].push_back(Keys::JOY_7);
							if (j == 7) buttons[i].push_back(Keys::JOY_8);
							if (j == 8) buttons[i].push_back(Keys::JOY_9);
							if (j == 9) buttons[i].push_back(Keys::JOY_10);
						}
					}
					if (i == data[10 + j]) {
						if (j == 0) buttons[i].push_back(Keys::SPACE);
						if (j == 1) buttons[i].push_back(Keys::RETURN);
						if (j == 2) buttons[i].push_back(Keys::ESCAPE);
						if (j == 3) buttons[i].push_back(Keys::KP0);
						if (j == 4) buttons[i].push_back(Keys::SHIFT);
						if (j == 5) buttons[i].push_back(Keys::Z);
						if (j == 6) buttons[i].push_back(Keys::X);
						if (j == 7) buttons[i].push_back(Keys::C);
						if (j == 8) buttons[i].push_back(Keys::V);
						if (j == 9) buttons[i].push_back(Keys::B);
						if (j == 10) buttons[i].push_back(Keys::A);
						if (j == 11) buttons[i].push_back(Keys::S);
						if (j == 12) buttons[i].push_back(Keys::D);
						if (j == 13) buttons[i].push_back(Keys::Q);
						if (j == 14) buttons[i].push_back(Keys::W);
					}
				}
			}
			standard = false;
		}
	}
	if (standard) {
		buttons[11].push_back(Keys::Z);
		buttons[11].push_back(Keys::SHIFT);
		buttons[12].push_back(Keys::X);
		buttons[12].push_back(Keys::KP0);
		buttons[12].push_back(Keys::ESCAPE);
		buttons[13].push_back(Keys::SPACE);
		buttons[13].push_back(Keys::RETURN);
		buttons[13].push_back(Keys::C);
		buttons[14].push_back(Keys::A);
		buttons[15].push_back(Keys::S);
		buttons[16].push_back(Keys::D);
		buttons[17].push_back(Keys::Q);
		buttons[18].push_back(Keys::W);
		if (JOYSTICK_SUPPORT) {
			buttons[11].push_back(Keys::JOY_1);
			buttons[12].push_back(Keys::JOY_2);
			buttons[13].push_back(Keys::JOY_3);
			buttons[14].push_back(Keys::JOY_4);
			buttons[15].push_back(Keys::JOY_5);
			buttons[16].push_back(Keys::JOY_6);
			buttons[17].push_back(Keys::JOY_7);
			buttons[18].push_back(Keys::JOY_8);
		}
	}
	buttons[2].push_back(Keys::DOWN);
	buttons[4].push_back(Keys::LEFT);
	buttons[6].push_back(Keys::RIGHT);
	buttons[8].push_back(Keys::UP);
	buttons[21].push_back(Keys::SHIFT);
	buttons[22].push_back(Keys::CTRL);
	buttons[23].push_back(Keys::ALT);
	buttons[25].push_back(Keys::F5);
	buttons[26].push_back(Keys::F6);
	buttons[27].push_back(Keys::F7);
	buttons[28].push_back(Keys::F8);
	buttons[29].push_back(Keys::F9);
}
