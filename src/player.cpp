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
#include "player.h"
#include "graphics.h"
#include "system.h"
#include "output.h"
#include "console.h"
#include "argss_ruby.h"
#include "SDL_ttf.h"

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Player::Init() {
	if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_JOYSTICK | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)) { 
		Output::Error("ARGSS couldn't initialize SDL.\n%s\n", SDL_GetError());
    }

	atexit(SDL_Quit);

	Graphics::SetScreen(SDL_SetVideoMode(System::Width, System::Height, 32, SDL_HWSURFACE));
    if (Graphics::GetScreen() == NULL ) {
		Output::Error("ARGSS couldn't initialize %dx%dx%d video mode.\n%s\n", System::Width, System::Height, 32, SDL_GetError());
    }
	
	if(TTF_Init() == -1) {
		Output::Error("ARGSS couldn't initialize SDL_ttf library.\n%s\n", TTF_GetError());
	}
	
	SDL_WM_SetCaption(System::Title.c_str(), NULL);
}

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Player::Update() {
    SDL_Event evnt;

    while (true) {
        int result = SDL_PollEvent(&evnt);
        if(evnt.type == SDL_QUIT) {
			Exit();
        }
        /*else if(evnt.type == SDL_ACTIVEEVENT) {
			if(evnt.active.type == SDL_APPACTIVE) {
				if(evnt.active.gain) {
					Sys_Focus = false;
					Input_RestartKeys();
					if(Sys_FocusPauseAudio) {
						//Audio_Pause();
					}
				}
				else {
					Sys_Focus = true;
					if(Sys_FocusPauseAudio) {
						//Audio_Play();
					}
				}
			}
        }*/
		if(!result && !(System::FocusPauseGame && !System::Focus)) {
            break;
        }
    }
}

////////////////////////////////////////////////////////////
/// Exit
////////////////////////////////////////////////////////////
void Player::Exit() {
	Console::Free();
    SDL_Quit();
	rb_exit(1);
}
