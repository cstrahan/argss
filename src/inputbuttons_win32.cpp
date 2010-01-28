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

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
std::map< int, std::vector<int> > Input::buttons;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Input::InitButtons() {
	unsigned char data[1024];
	int n = Registry::ReadBinValue(HKEY_CURRENT_USER, "SOFTWARE\\Enterbrain\\RGSS", "ButtonAssign", data);
	if (n > 0) {
		for (int i = 11; i < 19; i++) {
			for (int j = 0; j < 15; j++) {
				if (i == data[10 + j]) {
					if (j == 0) buttons[i].push_back(SDLK_SPACE);
					if (j == 1) buttons[i].push_back(SDLK_RETURN);
					if (j == 2) buttons[i].push_back(SDLK_ESCAPE);
					if (j == 3) buttons[i].push_back(SDLK_KP0);
					if (j == 4) {
						buttons[i].push_back(SDLK_LSHIFT);
						buttons[i].push_back(SDLK_RSHIFT);
					}
					if (j == 5) buttons[i].push_back(SDLK_z);
					if (j == 6) buttons[i].push_back(SDLK_x);
					if (j == 7) buttons[i].push_back(SDLK_c);
					if (j == 8) buttons[i].push_back(SDLK_v);
					if (j == 9) buttons[i].push_back(SDLK_b);
					if (j == 10) buttons[i].push_back(SDLK_a);
					if (j == 11) buttons[i].push_back(SDLK_s);
					if (j == 12) buttons[i].push_back(SDLK_d);
					if (j == 13) buttons[i].push_back(SDLK_q);
					if (j == 14) buttons[i].push_back(SDLK_w);
				}
			}
		}
	}
	else {
		buttons[11].push_back(SDLK_z);
		buttons[11].push_back(SDLK_LSHIFT);
		buttons[11].push_back(SDLK_RSHIFT);
		buttons[12].push_back(SDLK_x);
		buttons[12].push_back(SDLK_KP0);
		buttons[12].push_back(SDLK_ESCAPE);
		buttons[13].push_back(SDLK_SPACE);
		buttons[13].push_back(SDLK_RETURN);
		buttons[13].push_back(SDLK_c);
		buttons[14].push_back(SDLK_a);
		buttons[15].push_back(SDLK_s);
		buttons[16].push_back(SDLK_d);
		buttons[17].push_back(SDLK_q);
		buttons[18].push_back(SDLK_w);
	}
	buttons[2].push_back(SDLK_DOWN);
	buttons[4].push_back(SDLK_LEFT);
	buttons[6].push_back(SDLK_RIGHT);
	buttons[8].push_back(SDLK_UP);
	buttons[21].push_back(SDLK_LSHIFT);
	buttons[21].push_back(SDLK_RSHIFT);
	buttons[22].push_back(SDLK_LCTRL);
	buttons[22].push_back(SDLK_RCTRL);
	buttons[23].push_back(SDLK_LALT);
	buttons[23].push_back(SDLK_LSHIFT);
	buttons[25].push_back(SDLK_F5);
	buttons[26].push_back(SDLK_F6);
	buttons[27].push_back(SDLK_F7);
	buttons[28].push_back(SDLK_F8);
	buttons[29].push_back(SDLK_F9);
}
