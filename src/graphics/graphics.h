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

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <map>
#include "graphics/drawable.h"
#include "graphics/zobj.h"
#include "graphics/color.h"

///////////////////////////////////////////////////////////
/// Graphics namespace
///////////////////////////////////////////////////////////
namespace Graphics {
	void Init();
	void InitOpenGL();
	void Exit();
	void RefreshAll();
	void TimerWait();
	void TimerContinue();
	void DrawFrame();

	void Update();
	void Freeze();
	void Transition(int duration, std::string filename, int vague);
	void FrameReset();
	void Wait(int duration);
	void ResizeScreen(int width, int height);
	unsigned long SnapToBitmap();
	void FadeOut(int duration);
	void FadeIn(int duration);
	int GetFrameRate();
	void SetFrameRate(int nframerate);
	int GetFrameCount();
	void SetFrameCount(int nframecount);
	unsigned long GetBackColor();
	void SetBackColor(unsigned long nbackcolor);
	int GetBrightness();
	void SetBrightness(int nbrightness);

	bool SortZObj(ZObj &first, ZObj &second);
	void RegisterZObj(long z, unsigned long id);
	void RegisterZObj(long z, unsigned long id, bool multiz);
	void RemoveZObj(unsigned long id);
	void UpdateZObj(unsigned long id, long z);

	extern int fps;
	extern int framerate;
	extern int framecount;
	extern Color backcolor;
	extern int brightness;
	extern double framerate_interval;
	extern long creation;
	extern long last_tics;
	extern long last_tics_wait;
	extern long next_tics_fps;

	extern std::map<unsigned long, Drawable*> drawable_map;
	extern std::map<unsigned long, Drawable*>::iterator it_drawable_map;

	extern std::list<ZObj> zlist;
	extern std::list<ZObj>::iterator it_zlist;
};

#endif
