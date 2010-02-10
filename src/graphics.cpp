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
#include "system.h"
#include "player.h"
#include "output.h"
#include "sprite.h"
#include "tilemap.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
int Graphics::fps;
int Graphics::framerate;
int Graphics::framecount;
Color Graphics::backcolor;
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
	if (TTF_Init() == -1) {
		Output::Error("ARGSS couldn't initialize SDL_ttf library.\n%s\n", TTF_GetError());
	}

	fps = 0;
	framerate = 60;
	framecount = 0;
	backcolor = Color(0, 0, 0, 0);
	brightness = 255;
	creation = 0;
	framerate_interval = 1000.0 / framerate;
	last_tics = SDL_GetTicks() + (long)framerate_interval;

	InitOpenGL();

	Tilemap::Init();
}

////////////////////////////////////////////////////////////
/// Initialize OpengGL
////////////////////////////////////////////////////////////
void Graphics::InitOpenGL() {
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glViewport(0, 0, Player::GetWidth(), Player::GetHeight());
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Player::GetWidth(), Player::GetHeight(), 0, -1, 1); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);

	glClearColor((GLclampf)(backcolor.red / 255.0f),
				 (GLclampf)(backcolor.green / 255.0f),
				 (GLclampf)(backcolor.blue / 255.0f),
				 (GLclampf)(backcolor.alpha / 255.0f));
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}

////////////////////////////////////////////////////////////
/// Refresh all graphic objects
////////////////////////////////////////////////////////////
void Graphics::RefreshAll() {
	for (it_drawable_map = drawable_map.begin(); it_drawable_map != drawable_map.end(); it_drawable_map++) {
		it_drawable_map->second->RefreshBitmaps();
	}
	Bitmap::RefreshBitmaps();
}

////////////////////////////////////////////////////////////
/// Wait
////////////////////////////////////////////////////////////
void Graphics::TimerWait(){
	last_tics_wait = SDL_GetTicks();
}

////////////////////////////////////////////////////////////
/// Continue
////////////////////////////////////////////////////////////
void Graphics::TimerContinue() {
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
	if ((t - last_tics) >= framerate_interval || (framerate_interval - t + last_tics) < 10) {
		cyclesleftover = waitframes;
		//waitframes = (double)(t - last_tics) / framerate_interval - cyclesleftover;
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
	glClear(GL_COLOR_BUFFER_BIT);

    for (it_zlist = zlist.begin(); it_zlist != zlist.end(); it_zlist++) {
		Graphics::drawable_map[it_zlist->GetId()]->Draw(it_zlist->GetZ());
	}

	if (brightness < 255) {
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor4f(0.0f, 0.0f, 0.0f, (GLfloat)(1.0f - brightness / 255.0f));
		glBegin(GL_QUADS);
			glVertex2i(0, 0);
			glVertex2i(0, Player::GetHeight());
			glVertex2i(Player::GetWidth(), Player::GetHeight());
			glVertex2i(Player::GetWidth(), 0);
		glEnd();
	}
	
	SDL_GL_SwapBuffers();
}

////////////////////////////////////////////////////////////
/// Freeze screen
////////////////////////////////////////////////////////////
void Graphics::Freeze() {
	// TODO
}

////////////////////////////////////////////////////////////
/// Transition effect
////////////////////////////////////////////////////////////
void Graphics::Transition(int duration, std::string filename, int vague) {
	// TODO
}

////////////////////////////////////////////////////////////
/// Reset frames
////////////////////////////////////////////////////////////
void Graphics::FrameReset() {
	last_tics = SDL_GetTicks();
}

////////////////////////////////////////////////////////////
/// Wait frames
////////////////////////////////////////////////////////////
void Graphics::Wait(int duration) {
	for(int i = duration; i > 0; i--) {
		Update();
	}
}

////////////////////////////////////////////////////////////
/// Resize screen
////////////////////////////////////////////////////////////
void Graphics::ResizeScreen(int width, int height) {
	Player::ResizeWindow(width, height);

	glViewport(0, 0, width, height);
	glShadeModel(GL_FLAT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}

////////////////////////////////////////////////////////////
/// Snap scree to bitmap
////////////////////////////////////////////////////////////
VALUE Graphics::SnapToBitmap() {
	return Qnil;
}

////////////////////////////////////////////////////////////
/// Fade out
////////////////////////////////////////////////////////////
void Graphics::FadeOut(int duration) {
	int n = brightness / duration;
	for (;duration > 0; duration--) {
		brightness -= n;
		Update();
	}
	if (brightness > 0) {
		brightness = 0;
		Update();
	}
}


////////////////////////////////////////////////////////////
/// Fade in
////////////////////////////////////////////////////////////
void Graphics::FadeIn(int duration) {
	int n = 255 / duration;
	for (;duration > 0; duration--) {
		brightness += n;
		Update();
	}
	if (brightness < 255) {
		brightness = 255;
		Update();
	}
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
	return backcolor.GetARGSS();
}
void Graphics::SetBackColor(VALUE nbackcolor) {
	backcolor = Color(nbackcolor);
	glClearColor((GLclampf)(backcolor.red / 255.0f),
				 (GLclampf)(backcolor.green / 255.0f),
				 (GLclampf)(backcolor.blue / 255.0f),
				 (GLclampf)(backcolor.alpha / 255.0f));
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
	zlist.sort(SortZObj);
}
void Graphics::RegisterZObj(long z, unsigned long id, bool multiz) {
	ZObj zobj(z, 999999, id);
	zlist.push_back(zobj);
	zlist.sort(SortZObj);
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
	zlist.remove_if (remove_zobj_id(id));
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
	zlist.sort(SortZObj);
}
