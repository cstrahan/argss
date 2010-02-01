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
#include "SDL_opengl.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
int Graphics::fps;
int Graphics::framerate;
int Graphics::framecount;
Uint32 Graphics::backcolor;
int Graphics::brightness;
double Graphics::framerate_interval;
SDL_Surface* Graphics::screen;
std::map<unsigned long, Drawable*> Graphics::drawable_map;
std::map<unsigned long, Drawable*>::iterator Graphics::it_drawable_map;
std::list<ZObj> Graphics::zlist;
std::list<ZObj>::iterator Graphics::it_zlist;
long Graphics::creation;
long Graphics::last_tics;
long Graphics::last_tics_wait;

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
	last_tics = SDL_GetTicks() + (long)framerate_interval;

	Tilemap::Init();
}

////////////////////////////////////////////////////////////
/// Wait
////////////////////////////////////////////////////////////
void Graphics::Wait(){
	last_tics_wait = SDL_GetTicks();
}

////////////////////////////////////////////////////////////
/// Continue
////////////////////////////////////////////////////////////
void Graphics::Continue() {
	last_tics += SDL_GetTicks() - last_tics_wait;
}

////////////////////////////////////////////////////////////
/// Update
////////////////////////////////////////////////////////////
void Graphics::Update() {
	static long t;
	static long t_fps = last_tics;
	static long frames = 0;
	static double waitframes = 0;
	static double cyclesleftover;

	Player::Update();
	/*if (waitframes >= 1) {
		waitframes -= 1;
		return;
	}*/
	t = SDL_GetTicks();
	if((t - last_tics) >= framerate_interval || (framerate_interval - t + last_tics) < 10) {
		cyclesleftover = waitframes;
		waitframes = (double)(t - last_tics) / framerate_interval - cyclesleftover;
		//tl += (t - tl) - cyclesleftover;
		last_tics = t;
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
		SDL_Delay((long)(framerate_interval) - (t - last_tics));
	}
}

////////////////////////////////////////////////////////////
/// Draw Frame
////////////////////////////////////////////////////////////
void Graphics::DrawFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	zlist.sort(SortZObj);
    for(it_zlist = zlist.begin(); it_zlist != zlist.end(); it_zlist++) {
		Graphics::drawable_map[it_zlist->GetId()]->Draw(it_zlist->GetZ());
	}

	SDL_GL_SwapBuffers();
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
	last_tics = SDL_GetTicks();
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
	framerate_interval = 1000.0 / framerate;
}
int Graphics::GetFrameCount() {
	return framecount;
}
void Graphics::SetFrameCount(int nframecount) {
	framecount = nframecount;
}
VALUE Graphics::GetBackColor() {
	return Color(backcolor, screen->format).GetARGSS();
}
void Graphics::SetBackColor(VALUE nbackcolor) {
	backcolor = Color::GetUint32(nbackcolor, screen->format);
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
    else return first.GetCreation() < second.GetCreation();
}

////////////////////////////////////////////////////////////
/// Register ZObj
////////////////////////////////////////////////////////////
void Graphics::RegisterZObj(long z, unsigned long id) {
	creation += 1;
	ZObj zobj(z, creation, id);
	zlist.push_back(zobj);
}
void Graphics::RegisterZObj(long z, unsigned long id, bool multiz) {
	ZObj zobj(z, 999999, id);
	zlist.push_back(zobj);
}

////////////////////////////////////////////////////////////
/// Remove ZObj
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
