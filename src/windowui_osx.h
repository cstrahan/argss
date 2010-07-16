/*
 *  windowui_osx.h
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-16.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

#ifndef _WINDOWUI_OSX_H_
#define _WINDOWUI_OSX_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <queue>
#include "SDL.h"
#include "event.h"
#include "inputkeys.h"

////////////////////////////////////////////////////////////
/// WindowUi class
////////////////////////////////////////////////////////////
class WindowUi {
public:
	WindowUi(long iwidth, long iheight, std::string title, bool center, bool fs_flag);
	~WindowUi();
	
	void Dispose();
	void SwapBuffers();
	void Resize(long nwidth, long nheight);
	void SetTitle(std::string title);
	void ToggleFullscreen();
	long GetWidth();
	long GetHeight();
	
	bool IsFullscreen();
	std::vector<bool> GetKeyStates();
	bool GetMouseFocus();
	int GetMouseWheel();
	int GetMousePosX();
	int GetMousePosY();
	bool GetEvent(Event& evnt);
	
private:
	Input::Keys::InputKey VK2IK(SDLKey key);
	
	SDL_Surface* screen;
	
	std::queue<Event> events;
	std::vector<bool> keys;
	bool mouse_focus;
	int mouse_wheel;
	int mouse_x;
	int mouse_y;
	bool fullscreen;
	int width;
	int height;
};

#endif
