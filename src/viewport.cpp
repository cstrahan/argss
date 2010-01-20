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
#include "argss_ruby.h"
#include "argss_viewport.h"
#include "graphics.h"

////////////////////////////////////////////////////////////
/// Static Variables
////////////////////////////////////////////////////////////
std::map<unsigned long, Viewport*> Viewport::viewports;

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Viewport::Viewport(VALUE iid) {
	id = iid;
	rect = rb_iv_get(id, "@rect");
	visible = false;
	z = 0;
	ox = 0;
	oy = 0;
	color = rb_iv_get(id, "@color");
	tone = rb_iv_get(id, "@tone");
	flash_duration = 0;

	Graphics::RegisterZObj(0, ARGSS::AViewport::id, id);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Viewport::~Viewport() {

}

////////////////////////////////////////////////////////////
/// Class Is Viewport Disposed?
////////////////////////////////////////////////////////////
bool Viewport::IsDisposed(VALUE id) {
	return viewports.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Viewport
////////////////////////////////////////////////////////////
void Viewport::New(VALUE id) {
	viewports[id] = new Viewport(id);
}

////////////////////////////////////////////////////////////
/// Class Get Viewport
////////////////////////////////////////////////////////////
Viewport* Viewport::Get(VALUE id) {
	return viewports[id];
}

////////////////////////////////////////////////////////////
/// Dispose
////////////////////////////////////////////////////////////
void Viewport::Dispose() {
	viewports.erase(id);
	Graphics::RemoveZObj(id);
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Viewport::Draw() {

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
		needs_refresh = true;
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
