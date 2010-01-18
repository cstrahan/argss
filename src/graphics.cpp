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

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>
#include "graphics.h"
#include "argss_ruby.h"
#include "argss_error.h"
#include "argss_sprite.h"
#include "argss_window.h"
#include "argss_plane.h"
#include "argss_tilemap.h"
#include "argss_viewport.h"
#include "sprite.h"
#include "window_xp.h"
#include "plane.h"
#include "tilemap_xp.h"
#include "viewport.h"
#include "system.h"
#include "player.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
int Graphics::fps;
int Graphics::framerate;
int Graphics::framecount;
unsigned long Graphics::backcolor;
int Graphics::brightness;
double Graphics::framerate_interval;
SDL_Surface* Graphics::screen;
std::list<ZObj> Graphics::zlist;
std::list<ZObj>::iterator Graphics::it_zlist;
long Graphics::creation;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Graphics::Init() {
	fps = 0;
	framerate = 60;
	framecount = 0;
	backcolor = Qnil;
	brightness = 0;
	creation = 0;
	framerate_interval = 1000.0 / framerate;
}

////////////////////////////////////////////////////////////
/// Update
////////////////////////////////////////////////////////////
void Graphics::Update() {
	static long t;
	static long tl = SDL_GetTicks() + (long)framerate_interval;
	static long t_fps = tl;
	static long frames = 0;
	static double waitframes = 0;
	static double cyclesleftover;

	Player::Update();
	if (waitframes >= 1) {
		waitframes -= 1;
		return;
	}
	t = SDL_GetTicks();
	if((t - tl) >= (long)framerate_interval || (framerate_interval - t + tl) < 10) {
		cyclesleftover = waitframes;
		waitframes = (double)(t - tl) / framerate_interval - cyclesleftover;
		//tl += (t - tl) - cyclesleftover;
		tl = t;
		DrawFrame();
		
		framecount++;
		frames++;
		
		if (t - t_fps >= 1000) {
			t_fps += 1000;
			fps = frames;
			frames = 0;
			
			char title[255];
#ifdef MSVC
			sprintf_s(title, 255, "%s - %d FPS", System::Title.c_str(), fps);
#else
			sprintf(title, "%s - %d FPS", System::Title.c_str(), fps);
#endif
			SDL_WM_SetCaption(title, NULL);
		}
	}
	else {
		SDL_Delay((long)(framerate_interval) - (t - tl));
	}
}

////////////////////////////////////////////////////////////
/// Draw Frame
////////////////////////////////////////////////////////////
void Graphics::DrawFrame() {
	// Color::GetUint32(backcolor, screen->format)

	SDL_FillRect(screen, &screen->clip_rect, 0);

	zlist.sort(SortZObj);
    for(it_zlist = zlist.begin(); it_zlist != zlist.end(); it_zlist++) {
        VALUE type = it_zlist->GetType();
		if (type == ARGSS::ASprite::id) {
			Sprite::Get(it_zlist->GetId())->Draw();
		}
		else if (type == ARGSS::AWindow::id) {
			Window::Get(it_zlist->GetId())->Draw();
		}
		else if (type == ARGSS::APlane::id) {
			Plane::Get(it_zlist->GetId())->Draw();
		}
		else if (type == ARGSS::ATilemap::id) {
			//Tilemap::Get(it_zlist->GetId())->Draw();
		}
		else if (type == ARGSS::AViewport::id) {
				Viewport::Get(it_zlist->GetId())->Draw();
		}
		else {
				// Error
		}
    }
	
	if(SDL_Flip(screen) == -1) {
		rb_raise(ARGSS::AError::id, "SDL could not flip screen.\n%s\n", SDL_GetError());
	}
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::Freeze() {
	// TODO
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::Transition(int duration, std::string filename, int vague) {
	// TODO
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::FrameReset() {
	// TODO
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::Wait(int duration) {
	for(int i = duration; i > 0; i--) {
		Update();
	}
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::ResizeScreen(int width, int height) {
	// TODO
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
VALUE Graphics::SnapToBitmap() {
	return Qnil;
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::FadeOut(int duration) {
	// TODO
}

////////////////////////////////////////////////////////////
/// 
////////////////////////////////////////////////////////////
void Graphics::FadeIn(int duration) {
	// TODO
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
int Graphics::GetFrameRate() {
	return framerate;
}
void Graphics::SetFrameRate(int nframerate) {
	framerate = nframerate;
}
int Graphics::GetFrameCount() {
	return framecount;
}
void Graphics::SetFrameCount(int nframecount) {
	framecount = nframecount;
}
VALUE Graphics::GetBackColor() {
	return backcolor;
}
void Graphics::SetBackColor(VALUE nbackcolor) {
	backcolor = nbackcolor;
}
int Graphics::GetBrightness() {
	return brightness;
}
void Graphics::SetBrightness(int nbrightness) {
	brightness = nbrightness;
}
SDL_Surface* Graphics::GetScreen() {
	return screen;
}
void Graphics::SetScreen(SDL_Surface* nscreen) {
	screen = nscreen;
}

////////////////////////////////////////////////////////////
/// Sort ZObj
////////////////////////////////////////////////////////////
bool Graphics::SortZObj(ZObj &first, ZObj &second) {
    if (first.GetZ() < second.GetZ()) return true;
    else if (first.GetZ() > second.GetZ()) return false;
    else {
        if (first.GetCreation() < second.GetCreation()) return true;
        else return false;
    }
}
////////////////////////////////////////////////////////////
/// Sort ZObj
////////////////////////////////////////////////////////////
void Graphics::RegisterZObj(long z, unsigned long type, unsigned long id) {
	creation += 1;
	ZObj zobj(z, creation, type, id);
	zlist.push_back(zobj);
}

////////////////////////////////////////////////////////////
/// Sort ZObj
////////////////////////////////////////////////////////////
struct remove_zobj_id : public std::binary_function<ZObj, ZObj, bool> {
	remove_zobj_id(VALUE val) : id(val) {}
	bool operator () (ZObj &obj) const {return obj.GetId() == id;}
	unsigned long id;
};
void Graphics::RemoveZObj(unsigned long id) {
	zlist.remove_if(remove_zobj_id(id));
}

////////////////////////////////////////////////////////////
/// Update ZObj Z
////////////////////////////////////////////////////////////
void Graphics::UpdateZObj(unsigned long id, long z) {
	for(it_zlist = zlist.begin(); it_zlist != zlist.end(); it_zlist++) {
		if (it_zlist->GetId() == id) {
			it_zlist->SetZ(z);
			break;
		}
	}
}
