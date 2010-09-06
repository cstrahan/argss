/*
 *  windowui_osx.cpp
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-16.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "windowui_osx.h"
#include "output.h"
#include "options.h"
#include "SDL.h"
#include "argss.h"

////////////////////////////////////////////////////////////
/// Definitions
////////////////////////////////////////////////////////////
#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN 523
#endif
#ifndef WM_XBUTTONUP
#define WM_XBUTTONUP 524
#endif
#ifndef XBUTTON1
#define XBUTTON1 1
#endif
#ifndef XBUTTON2
#define XBUTTON2 2
#endif

////////////////////////////////////////////////////////////
/// Event Process
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
WindowUi::WindowUi(long iwidth, long iheight, std::string title, bool center, bool fs_flag) {
	keys.resize(Input::Keys::KEYS_COUNT, false);
	mouse_focus = false;
	mouse_wheel = 0;
	mouse_x = 0;
	mouse_y = 0;
	width = iwidth;
	height = iheight;
	fullscreen = fs_flag;
	
	// Init SDL; apparently this doesn't need to be done in WIN32
	Uint8  video_bpp = 32;
	Uint32 videoflags = SDL_SWSURFACE | SDL_RESIZABLE | SDL_OPENGL;
	int done;
	SDL_Event event;
	
	// Initialize the SDL library
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		Output::Error("Couldn't initialize SDL: %s", SDL_GetError());
		exit(1);
	}
	
	// Set resolution
	screen = SDL_SetVideoMode(iwidth, iheight, video_bpp, videoflags);
	if (screen == NULL) {
		Output::Error("Couldn't set %dx%dx%d video mode: %s", iwidth, iheight, video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	if (fullscreen)	{
		// Put into fullscreen
		ToggleFullscreen();
	}
	
	// Set the window name
	SetTitle(GAME_TITLE);
	
	// Test code
	done = 0;
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
WindowUi::~WindowUi() {

}

////////////////////////////////////////////////////////////
/// Swap Buffers
////////////////////////////////////////////////////////////
void WindowUi::SwapBuffers() {
	SDL_GL_SwapBuffers();
}

////////////////////////////////////////////////////////////
/// Dispose
////////////////////////////////////////////////////////////
void WindowUi::Dispose() {
	// Clean up SDL uses with Cocoa
	SDL_Quit();
}

////////////////////////////////////////////////////////////
/// Resize
////////////////////////////////////////////////////////////
void WindowUi::Resize(long nwidth, long nheight) {
	if (width != nwidth && height != nheight) {
		width = nwidth;
		height = nheight;
	}
}

////////////////////////////////////////////////////////////
/// Set title
////////////////////////////////////////////////////////////
void WindowUi::SetTitle(std::string title) {
	SDL_WM_SetCaption(title.c_str(), "");
}

////////////////////////////////////////////////////////////
/// Toggle fullscreen
////////////////////////////////////////////////////////////
void WindowUi::ToggleFullscreen() {
	if(fullscreen) fullscreen = false;
	else fullscreen = true;
	SDL_WM_ToggleFullScreen(screen);
}

////////////////////////////////////////////////////////////
/// Get Width
////////////////////////////////////////////////////////////
long WindowUi::GetWidth() {
	return width;
}

////////////////////////////////////////////////////////////
/// Get Height
////////////////////////////////////////////////////////////
long WindowUi::GetHeight() {
	return height;
}

////////////////////////////////////////////////////////////
/// Get Event
////////////////////////////////////////////////////////////
bool WindowUi::GetEvent(Event& evnt) {
	SDL_Event evt;
	int rc;
	
	// Get the event off of the queue
	rc = SDL_PollEvent(&evt);
	
	if(rc == 0) {
		return false;
	}
	
	// Process the event
	switch(evt.type) {
		case SDL_ACTIVEEVENT: {
			// Active events are launched when the application
			// gains or loses focus of one or more of the following:
			//	application focus: when the app is minimized/iconified
			//	keyboard focus: when the app gains or loses keyboard focus
			//	mouse focus: when the mouse leaves or enters the app window
			// vgvgvgf doesn't handle mouse focus so I won't either
			SDL_ActiveEvent tmpEvt = evt.active;
			if(tmpEvt.state == SDL_APPACTIVE) {
				evnt.type = (tmpEvt.gain) ? Event::GainFocus : Event::LostFocus;
			}
			if(tmpEvt.state == SDL_APPMOUSEFOCUS) {
				mouse_focus = (bool)tmpEvt.gain; // 0: lost focus. 1: gained focus
			}
			return true;
		}
		case SDL_KEYDOWN: {
			// When a key is pressed on the keyboard
			SDL_KeyboardEvent tmpEvt = evt.key;
			evnt.type = Event::KeyDown;
			switch (tmpEvt.keysym.mod) {
				case KMOD_SHIFT:
					evnt.param1 = Input::Keys::SHIFT;
					events.push(evnt);
				case KMOD_CTRL:
					evnt.param1 = Input::Keys::CTRL;
					events.push(evnt);
				case KMOD_ALT:
					evnt.param1 = Input::Keys::ALT;
					events.push(evnt);
			}
			evnt.param1 = VK2IK(tmpEvt.keysym.sym);
			events.push(evnt);
			keys[evnt.param1] = true;
			return true;
		}
		case SDL_KEYUP: {
			// When a key is pressed on the keyboard
			SDL_KeyboardEvent tmpEvt = evt.key;
			evnt.type = Event::KeyUp;
			switch (tmpEvt.keysym.mod) {
				case KMOD_SHIFT:
					evnt.param1 = Input::Keys::SHIFT;
					events.push(evnt);
				case KMOD_CTRL:
					evnt.param1 = Input::Keys::CTRL;
					events.push(evnt);
				case KMOD_ALT:
					evnt.param1 = Input::Keys::ALT;
					events.push(evnt);
			}
			evnt.param1 = VK2IK(tmpEvt.keysym.sym);
			events.push(evnt);
			keys[evnt.param1] = true;
			return true;
		}
		case SDL_MOUSEMOTION: {
			SDL_MouseMotionEvent tmpEvt = evt.motion;
			mouse_focus = true;
			mouse_x = tmpEvt.xrel;
			mouse_y = tmpEvt.yrel;
			return true;
		}
		case SDL_MOUSEBUTTONDOWN: {
			SDL_MouseButtonEvent tmpEvt = evt.button;
			Input::Keys::InputKey k;
			switch(tmpEvt.button) {
				case SDL_BUTTON_LEFT: k = Input::Keys::MOUSE_LEFT; break;
				case SDL_BUTTON_RIGHT: k = Input::Keys::MOUSE_RIGHT; break;
				case SDL_BUTTON_MIDDLE: k = Input::Keys::MOUSE_MIDDLE; break;
				default: k = Input::Keys::InputKey(0); break;
			}
			keys[k] = true;
			return true;
		}
		case SDL_MOUSEBUTTONUP: {
			SDL_MouseButtonEvent tmpEvt = evt.button;
			Input::Keys::InputKey k;
			switch(tmpEvt.button) {
				case SDL_BUTTON_LEFT: k = Input::Keys::MOUSE_LEFT; break;
				case SDL_BUTTON_RIGHT: k = Input::Keys::MOUSE_RIGHT; break;
				case SDL_BUTTON_MIDDLE: k = Input::Keys::MOUSE_MIDDLE; break;
				default: k = Input::Keys::InputKey(0); break;
			}
			keys[k] = false;
			return true;
		}
		case SDL_JOYAXISMOTION:
			return true;
		case SDL_JOYBALLMOTION:
			return true;
		case SDL_JOYHATMOTION:
			return true;
		case SDL_JOYBUTTONDOWN:
			return true;
		case SDL_JOYBUTTONUP:
			return true;
		case SDL_QUIT:
			ARGSS::Exit();
			WindowUi::Dispose();
			return true;
		case SDL_SYSWMEVENT:
			return true;
		case SDL_VIDEORESIZE:
			return true;
		case SDL_VIDEOEXPOSE:
			return true;
		case SDL_USEREVENT:
			return true;
	}
	
	return false;
}

////////////////////////////////////////////////////////////
/// Process events
////////////////////////////////////////////////////////////
/*int WindowUi::ProccesEvents(SDL_Event* evt) {
	Event event;
	
	// Handle event type and push it on the event list
	
	
	return 1;
}*/

////////////////////////////////////////////////////////////
/// Virtual Keys to InputKey
////////////////////////////////////////////////////////////
Input::Keys::InputKey WindowUi::VK2IK(SDLKey key) {
	switch(key)
	{
		case SDLK_BACKSPACE : return Input::Keys::BACKSPACE;
		case SDLK_TAB : return Input::Keys::TAB;
		case SDLK_CLEAR : return Input::Keys::CLEAR;
		case SDLK_RETURN : return Input::Keys::RETURN;
		case SDLK_PAUSE : return Input::Keys::PAUSE;
		case SDLK_ESCAPE : return Input::Keys::ESCAPE;
		case SDLK_SPACE : return Input::Keys::SPACE;
		case SDLK_PAGEUP : return Input::Keys::PGUP;
		case SDLK_PAGEDOWN : return Input::Keys::PGDN;
		case SDLK_END : return Input::Keys::ENDS;
		case SDLK_HOME : return Input::Keys::HOME;
		case SDLK_LEFT : return Input::Keys::LEFT;
		case SDLK_UP : return Input::Keys::UP;
		case SDLK_RIGHT : return Input::Keys::RIGHT;
		case SDLK_DOWN : return Input::Keys::DOWN;
		case SDLK_PRINT : return Input::Keys::SNAPSHOT;
		case SDLK_INSERT : return Input::Keys::INSERT;
		case SDLK_DELETE : return Input::Keys::DEL;
		/*case 1019 : return Input::Keys::SHIFT; // Apparently there's none it has to be R or L*/
		case SDLK_LSHIFT : return Input::Keys::LSHIFT;
		case SDLK_RSHIFT : return Input::Keys::RSHIFT;
		/*case 1022 : return Input::Keys::CTRL; // Same problem as SHIFT */ 
		case SDLK_LCTRL : return Input::Keys::LCTRL;
		case SDLK_RCTRL : return Input::Keys::RCTRL;
		/*case 1025 : return Input::Keys::ALT; // Same problem as SHIFT */
		case SDLK_LALT : return Input::Keys::LALT;
		case SDLK_RALT : return Input::Keys::RALT;
		case SDLK_0 : return Input::Keys::N0;
		case SDLK_1 : return Input::Keys::N1;
		case SDLK_2 : return Input::Keys::N2;
		case SDLK_3 : return Input::Keys::N3;
		case SDLK_4 : return Input::Keys::N4;
		case SDLK_5 : return Input::Keys::N5;
		case SDLK_6 : return Input::Keys::N6;
		case SDLK_7 : return Input::Keys::N7;
		case SDLK_8 : return Input::Keys::N8;
		case SDLK_9 : return Input::Keys::N9;
		case SDLK_a : return Input::Keys::A;
		case SDLK_b : return Input::Keys::B;
		case SDLK_c : return Input::Keys::C;
		case SDLK_d : return Input::Keys::D;
		case SDLK_e : return Input::Keys::E;
		case SDLK_f : return Input::Keys::F;
		case SDLK_g : return Input::Keys::G;
		case SDLK_h : return Input::Keys::H;
		case SDLK_i : return Input::Keys::I;
		case SDLK_j : return Input::Keys::J;
		case SDLK_k : return Input::Keys::K;
		case SDLK_l : return Input::Keys::L;
		case SDLK_m : return Input::Keys::M;
		case SDLK_n : return Input::Keys::N;
		case SDLK_o : return Input::Keys::O;
		case SDLK_p : return Input::Keys::P;
		case SDLK_q : return Input::Keys::Q;
		case SDLK_r : return Input::Keys::R;
		case SDLK_s : return Input::Keys::S;
		case SDLK_t : return Input::Keys::T;
		case SDLK_u : return Input::Keys::U;
		case SDLK_v : return Input::Keys::V;
		case SDLK_w : return Input::Keys::W;
		case SDLK_x : return Input::Keys::X;
		case SDLK_y : return Input::Keys::Y;
		case SDLK_z : return Input::Keys::Z;
		case SDLK_LSUPER : return Input::Keys::LOS;
		case SDLK_RSUPER : return Input::Keys::ROS;
		/*case 1066 : return Input::Keys::APPS; // What are these? */
		case SDLK_KP0 : return Input::Keys::KP0;
		case SDLK_KP1 : return Input::Keys::KP1;
		case SDLK_KP2 : return Input::Keys::KP2;
		case SDLK_KP3 : return Input::Keys::KP3;
		case SDLK_KP4 : return Input::Keys::KP4;
		case SDLK_KP5 : return Input::Keys::KP5;
		case SDLK_KP6 : return Input::Keys::KP6;
		case SDLK_KP7 : return Input::Keys::KP7;
		case SDLK_KP8 : return Input::Keys::KP8;
		case SDLK_KP9 : return Input::Keys::KP9;
		case SDLK_KP_MULTIPLY: case SDLK_ASTERISK: return Input::Keys::MULTIPLY;
		case SDLK_KP_PLUS: case SDLK_PLUS: return Input::Keys::ADD; 
		case SDLK_COMMA : return Input::Keys::SEPARATOR;
		case SDLK_KP_MINUS: case SDLK_MINUS : return Input::Keys::SUBTRACT;
		case SDLK_PERIOD : return Input::Keys::DECIMAL;
		case SDLK_KP_DIVIDE: case SDLK_SLASH : return Input::Keys::DIVIDE;
		case SDLK_F1 : return Input::Keys::F1;
		case SDLK_F2 : return Input::Keys::F2;
		case SDLK_F3 : return Input::Keys::F3;
		case SDLK_F4 : return Input::Keys::F4;
		case SDLK_F5 : return Input::Keys::F5;
		case SDLK_F6 : return Input::Keys::F6;
		case SDLK_F7 : return Input::Keys::F7;
		case SDLK_F8 : return Input::Keys::F8;
		case SDLK_F9 : return Input::Keys::F9;
		case SDLK_F10 : return Input::Keys::F10;
		case SDLK_F11 : return Input::Keys::F11;
		case SDLK_F12 : return Input::Keys::F12;
		case SDLK_CAPSLOCK : return Input::Keys::CAPS_LOCK;
		case SDLK_NUMLOCK : return Input::Keys::NUM_LOCK;
		case SDLK_SCROLLOCK : return Input::Keys::SCROLL_LOCK;
	}
	
	return Input::Keys::InputKey(0);
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
bool WindowUi::IsFullscreen() {
	return fullscreen;
}
std::vector<bool> WindowUi::GetKeyStates() {
	return keys;
}
bool WindowUi::GetMouseFocus() {
	return mouse_focus;
}
int WindowUi::GetMouseWheel() {
	return mouse_wheel;
}
int WindowUi::GetMousePosX() {
	return mouse_x;
}
int WindowUi::GetMousePosY() {
	return mouse_y;
}
