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
#include "plane.h"
#include "argss_ruby.h"
#include "argss_plane.h"
#include "graphics.h"

////////////////////////////////////////////////////////////
/// Static Variables
////////////////////////////////////////////////////////////
std::map<unsigned long, Plane*> Plane::planes;

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Plane::Plane(VALUE iid) {
	id = iid;
	viewport = rb_iv_get(id, "@viewport");
	bitmap = Qnil;
	visible = false;
	z = 0;
	ox = 0;
	oy = 0;
	zoom_x = 1.0;
	zoom_y = 1.0;
	opacity = 255;
	blend_type = 0;
	color = rb_iv_get(id, "@color");
	tone = rb_iv_get(id, "@tone");

	Graphics::RegisterZObj(0, ARGSS::APlane::id, id);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Plane::~Plane() {

}

////////////////////////////////////////////////////////////
/// Class Is Plane Disposed?
////////////////////////////////////////////////////////////
bool Plane::IsDisposed(VALUE id) {
	return planes.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Plane
////////////////////////////////////////////////////////////
void Plane::New(VALUE id) {
	planes[id] = new Plane(id);
}

////////////////////////////////////////////////////////////
/// Class Get Plane
////////////////////////////////////////////////////////////
Plane* Plane::Get(VALUE id) {
	return planes[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Plane
////////////////////////////////////////////////////////////
void Plane::Dispose(unsigned long id) {
	delete planes[id];
	std::map<unsigned long, Plane*>::iterator it = planes.find(id);
	planes.erase(it);
	Graphics::RemoveZObj(id);
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Plane::Draw() {

}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Plane::GetViewport() {
	return viewport;
}
void Plane::SetViewport(VALUE nviewport) {
	viewport = nviewport;
}
VALUE Plane::GetBitmap() {
	return bitmap;
}
void Plane::SetBitmap(VALUE nbitmap) {
	if (bitmap != nbitmap) needs_refresh = true;
	bitmap = nbitmap;
}
bool Plane::GetVisible() {
	return visible;
}
void Plane::SetVisible(bool nvisible) {
	visible = nvisible;
}
int Plane::GetZ() {
	return z;
}
void Plane::SetZ(int nz) {
	if (z != nz) Graphics::UpdateZObj(id, nz);
	z = nz;
}
int Plane::GetOx() {
	return ox;
}
void Plane::SetOx(int nox) {
	ox = nox;
}
int Plane::GetOy() {
	return oy;
}
void Plane::SetOy(int noy) {
	oy = noy;
}
double Plane::GetZoomX() {
	return zoom_x;
}
void Plane::SetZoomX(double nzoom_x) {
	if (zoom_x != nzoom_x) needs_refresh = true;
	zoom_x = nzoom_x;
}
double Plane::GetZoomY() {
	return zoom_y;
}
void Plane::SetZoomY(double nzoom_y) {
	if (zoom_y != nzoom_y) needs_refresh = true;
	zoom_y = nzoom_y;
}
int Plane::GetOpacity() {
	return opacity;
}
void Plane::SetOpacity(int nopacity) {
	if (opacity != nopacity) needs_refresh = true;
	opacity = nopacity;
}
int Plane::GetBlendType() {
	return blend_type;
}
void Plane::SetBlendType(int nblend_type) {
	blend_type = nblend_type;
}
VALUE Plane::GetColor() {
	return color;
}
void Plane::SetColor(VALUE ncolor) {
	color = ncolor;
}
VALUE Plane::GetTone() {
	return tone;
}
void Plane::SetTone(VALUE ntone) {
	if (tone != ntone) needs_refresh = true;
	tone = ntone;
}
