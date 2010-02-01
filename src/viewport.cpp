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
#include "viewport.h"
#include "sprite.h"
#include "plane.h"
#include "tilemap_xp.h"
#include "window_xp.h"
#include "argss_ruby.h"
#include "argss_viewport.h"
#include "argss_sprite.h"
#include "argss_plane.h"
#include "argss_tilemap.h"
#include "argss_window.h"
#include "graphics.h"

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Viewport::Viewport(VALUE iid) {
	id = iid;
	rect = rb_iv_get(id, "@rect");
	visible = true;
	z = 0;
	ox = 0;
	oy = 0;
	color = rb_iv_get(id, "@color");
	tone = rb_iv_get(id, "@tone");
	flash_duration = 0;
	disposing = false;

	last_dst_rect = Rect(rect);
	viewport = new Bitmap(last_dst_rect.width, last_dst_rect.height);

	Graphics::RegisterZObj(0, id);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Viewport::~Viewport() {
	delete viewport;
}

////////////////////////////////////////////////////////////
/// Class Is Viewport Disposed?
////////////////////////////////////////////////////////////
bool Viewport::IsDisposed(VALUE id) {
	return Graphics::drawable_map.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Viewport
////////////////////////////////////////////////////////////
void Viewport::New(VALUE id) {
	Graphics::drawable_map[id] = new Viewport(id);
}

////////////////////////////////////////////////////////////
/// Class Get Viewport
////////////////////////////////////////////////////////////
Viewport* Viewport::Get(VALUE id) {
	return (Viewport*)Graphics::drawable_map[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Viewport
////////////////////////////////////////////////////////////
void Viewport::Dispose(unsigned long id) {
	delete Graphics::drawable_map[id];
	std::map<unsigned long, Drawable*>::iterator it = Graphics::drawable_map.find(id);
	Graphics::drawable_map.erase(it);

	Graphics::RemoveZObj(id);
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Viewport::Draw(long z) {
	if (!visible) return;

	/*Rect dst_rect(rect);

	if (dst_rect != last_dst_rect) {
		delete viewport;
		viewport = new Bitmap(dst_rect.width, dst_rect.height);
		last_dst_rect = dst_rect;
	}

	viewport->Clear();*/

	zlist.sort(Graphics::SortZObj);
    for(it_zlist = zlist.begin(); it_zlist != zlist.end(); it_zlist++) {
		Graphics::drawable_map[it_zlist->GetId()]->Draw(it_zlist->GetZ());
	}

	/*viewport->ToneChange(Tone(tone));
	if (flash_duration > 0) {
		viewport ->Flash(flash_color, flash_frame, flash_duration);
	}

	viewport->BlitScreen(dst_rect.x - ox, dst_rect.y - oy);*/
}

////////////////////////////////////////////////////////////
/// Update
////////////////////////////////////////////////////////////
void Viewport::Update() {
	if (flash_duration != 0) {
		flash_frame += 1;
		if (flash_duration == flash_frame) {
			flash_duration = 0;
		}
	}
}

////////////////////////////////////////////////////////////
/// Flash
////////////////////////////////////////////////////////////
void Viewport::Flash(int duration){
	flash_color = Color(0, 0, 0, 0);
	flash_duration = duration;
	flash_frame = 0;
}
void Viewport::Flash(Color color, int duration){
	flash_color = color;
	flash_duration = duration;
	flash_frame = 0;
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Viewport::GetRect() {
	return rect;
}
void Viewport::SetRect(VALUE nrect) {
	rect = nrect;
}
bool Viewport::GetVisible() {
	return visible;
}
void Viewport::SetVisible(bool nvisible) {
	visible = nvisible;
}
int Viewport::GetZ() {
	return z;
}
void Viewport::SetZ(int nz) {
	if (z != nz) Graphics::UpdateZObj(id, nz);
	z = nz;
}
int Viewport::GetOx() {
	return ox;
}
void Viewport::SetOx(int nox) {
	ox = nox;
}
int Viewport::GetOy() {
	return oy;
}
void Viewport::SetOy(int noy) {
	oy = noy;
}
VALUE Viewport::GetColor() {
	return color;
}
void Viewport::SetColor(VALUE ncolor) {
	color = ncolor;
}
VALUE Viewport::GetTone() {
	return tone;
}
void Viewport::SetTone(VALUE ntone) {
	tone = ntone;
}

////////////////////////////////////////////////////////////
/// Register ZObj
////////////////////////////////////////////////////////////
void Viewport::RegisterZObj(long z, unsigned long id) {
	Graphics::creation += 1;
	ZObj zobj(z, Graphics::creation, id);
	zlist.push_back(zobj);
}
void Viewport::RegisterZObj(long z, unsigned long id, bool multiz) {
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
void Viewport::RemoveZObj(unsigned long id) {
	if (disposing) return;
	zlist.remove_if(remove_zobj_id(id));
}

////////////////////////////////////////////////////////////
/// Update ZObj Z
////////////////////////////////////////////////////////////
void Viewport::UpdateZObj(unsigned long id, long z) {
	for(it_zlist = zlist.begin(); it_zlist != zlist.end(); it_zlist++) {
		if (it_zlist->GetId() == id) {
			it_zlist->SetZ(z);
			break;
		}
	}
}
