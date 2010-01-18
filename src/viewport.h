//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
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

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <map>
#include "color.h"
#include "rect.h"
#include "tone.h"

////////////////////////////////////////////////////////////
/// Viewport class
////////////////////////////////////////////////////////////
class Viewport {
public:
	Viewport(unsigned long iid);
	~Viewport();
	
	static bool IsDisposed(unsigned long id);
	static void New(unsigned long id);
	static Viewport* Get(unsigned long id);

	void Draw();

	void Dispose();
	void Flash(int duration);
	void Flash(Color color, int duration);
    void Update();
	unsigned long GetRect();
	void SetRect(unsigned long nrect);
	bool GetVisible();
	void SetVisible(bool nvisible);
	int GetZ();
	void SetZ(int nz);
	int GetOx();
	void SetOx(int nox);
	int GetOy();
	void SetOy(int noy);
	unsigned long GetColor();
	void SetColor(unsigned long ncolor);
	unsigned long GetTone();
	void SetTone(unsigned long ntone);

private:
	static std::map<unsigned long, Viewport*> viewports;

	unsigned long id;
	unsigned long rect;
	bool visible;
	int z;
	int ox;
	int oy;
	unsigned long color;
	unsigned long tone;
	
	Color flash_color;
	int flash_duration;
	int flash_frame;
	Rect rect_viewport;
	Rect rect_last;
	Color color_viewport;
	Tone tone_viewport;
	bool needs_refresh;
};

#endif
