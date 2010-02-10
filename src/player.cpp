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
#include "options.h"
#include "system.h"
#include "output.h"
#include "input.h"
#include "graphics.h"
#include "audio.h"
#include "argss.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
SDL_Surface* Player::mainwindow;
bool Player::focus;
bool Player::alt_pressing;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Player::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) { 
		Output::Error("ARGSS couldn't initialize SDL.\n%s\n", SDL_GetError());
    }

	mainwindow = SDL_SetVideoMode(System::Width, System::Height, 32, SDL_OPENGL);
	if (mainwindow == NULL ) {
		Output::Error("ARGSS couldn't initialize %dx%dx%d video mode.\n%s\n", System::Width, System::Height, 32, SDL_GetError());
    }
	
	focus = true;

	SDL_WM_SetCaption(System::Title.c_str(), NULL);
}

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Player::Update() {
    SDL_Event evnt;

    while (true) {
        int result = SDL_PollEvent(&evnt);
        if (evnt.type == SDL_QUIT) {
			Exit();
        }
		else if (evnt.type == SDL_ACTIVEEVENT && PAUSE_GAME_WHEN_FOCUS_LOST) {
			if (evnt.active.state & SDL_APPACTIVE || evnt.active.state & SDL_APPINPUTFOCUS) {
				if (evnt.active.gain && !focus) {
					focus = true;
					Graphics::TimerContinue();
					if (PAUSE_AUDIO_WHEN_FOCUS_LOST) {
						Audio::Continue();
					}
				}
				else if (focus) {
					focus = false;
					Input::ClearKeys();
					Graphics::TimerWait();
					if (PAUSE_AUDIO_WHEN_FOCUS_LOST) {
						Audio::Pause();
					}
				}
			}
		}
		else if (evnt.type == SDL_KEYDOWN) {
			if (evnt.key.keysym.sym == SDLK_LALT) {
				alt_pressing = true;
			}
			else if (evnt.key.keysym.sym == SDLK_RETURN && alt_pressing) {
				ToggleFullscreen();
			}
        }
		else if (evnt.type == SDL_KEYUP) {
			if (evnt.key.keysym.sym == SDLK_LALT) {
				alt_pressing = false;
			}
        }

		if (!result && !(PAUSE_GAME_WHEN_FOCUS_LOST && !focus)) {
            break;
        }
    }
}

////////////////////////////////////////////////////////////
/// Exit
////////////////////////////////////////////////////////////
void Player::Exit() {
	Output::None();
    SDL_Quit();
	ARGSS::Exit();
}

////////////////////////////////////////////////////////////
/// Switch fullscreen
////////////////////////////////////////////////////////////
void Player::ToggleFullscreen() {
	Uint32 flags = mainwindow->flags;
	SDL_FreeSurface(mainwindow);
	mainwindow = SDL_SetVideoMode(0, 0, 32, flags ^ SDL_FULLSCREEN);
	if (mainwindow == NULL) {
		mainwindow = SDL_SetVideoMode(0, 0, 32, flags);
	}
	Graphics::InitOpenGL();
	Graphics::RefreshAll();
}

////////////////////////////////////////////////////////////
/// Resize window
////////////////////////////////////////////////////////////
void Player::ResizeWindow(int width, int height) {
	mainwindow = SDL_SetVideoMode(width, height, 0, mainwindow->flags);
}

////////////////////////////////////////////////////////////
/// Get window width
////////////////////////////////////////////////////////////
int Player::GetWidth() {
	return mainwindow->w;
}

////////////////////////////////////////////////////////////
/// Get window height
////////////////////////////////////////////////////////////
int Player::GetHeight() {
	return mainwindow->h;
}

////////////////////////////////////////////////////////////
/// Wait
////////////////////////////////////////////////////////////
void Player::Wait() {
	//Graphics::TimerWait();
}

////////////////////////////////////////////////////////////
/// Continue
////////////////////////////////////////////////////////////
void Player::Continue() {
	//Graphics::TimerContinue();
}
