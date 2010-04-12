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
#include "viewport.h"
#include "rect.h"
#include "player.h"

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Plane::Plane(VALUE iid) {
	id = iid;
	viewport = rb_iv_get(id, "@viewport");
	bitmap = Qnil;
	visible = true;
	z = 0;
	ox = 0;
	oy = 0;
	zoom_x = 1.0;
	zoom_y = 1.0;
	opacity = 255;
	blend_type = 0;
	color = rb_iv_get(id, "@color");
	tone = rb_iv_get(id, "@tone");

	if (viewport != Qnil) {
		Viewport::Get(viewport)->RegisterZObj(0, id);
	}
	else {
		Graphics::RegisterZObj(0, id);
	}
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
	return Graphics::drawable_map.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Plane
////////////////////////////////////////////////////////////
void Plane::New(VALUE id) {
	Graphics::drawable_map[id] = new Plane(id);
}

////////////////////////////////////////////////////////////
/// Class Get Plane
////////////////////////////////////////////////////////////
Plane* Plane::Get(VALUE id) {
	return (Plane*)Graphics::drawable_map[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Plane
////////////////////////////////////////////////////////////
void Plane::Dispose(unsigned long id) {
	if (Plane::Get(id)->viewport != Qnil) {
		Viewport::Get(Plane::Get(id)->viewport)->RemoveZObj(id);
	}
	else {
		Graphics::RemoveZObj(id);
	}
	delete Graphics::drawable_map[id];
	std::map<unsigned long, Drawable*>::iterator it = Graphics::drawable_map.find(id);
	Graphics::drawable_map.erase(it);
}

////////////////////////////////////////////////////////////
/// Refresh Bitmaps
////////////////////////////////////////////////////////////
void Plane::RefreshBitmaps() {
	
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Plane::Draw(long z) {
	if (!visible) return;
	if (bitmap == Qnil) return;

	Bitmap* bmp = Bitmap::Get(bitmap);
	bmp->Refresh();

	glEnable(GL_TEXTURE_2D);

	bmp->BindBitmap();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float rectw, recth;

	if (viewport != Qnil) {
		Rect rect = Viewport::Get(viewport)->GetViewportRect();

		glEnable(GL_SCISSOR_TEST);
		glScissor(rect.x, Player::GetHeight() - (rect.y + rect.height), rect.width, rect.height);

		rectw = (float)rect.width;
		recth = (float)rect.height;

		glTranslatef((float)rect.x, (float)rect.y, 0.0f);
	}
	else {
		rectw = (float)Player::GetWidth();
		recth = (float)Player::GetHeight();
	}

	glColor4f(1.0f, 1.0f, 1.0f, opacity / 255.0f);
	
	glEnable(GL_BLEND);
	switch(blend_type) {
		case 1:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case 2:
			glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE_MINUS_SRC_COLOR);
			break;
		default:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	float bmpw = bmp->GetWidth() * zoom_x;
	float bmph = bmp->GetHeight() * zoom_y;
	int r_ox = -ox % (int)bmpw;
	int r_oy = -oy % (int)bmph;
	float tilesx = ceil(rectw / bmpw) + ceil(r_ox / bmpw);
	float tilesy = ceil(recth / bmph) + ceil(r_oy / bmph);
	while (r_ox > 0) r_ox -= (int)bmpw;
	while (r_oy > 0) r_oy -= (int)bmph;
	glBegin(GL_QUADS);
		for (float i = r_ox / bmpw; i < tilesx; i++) {
			for (float j = r_oy / bmph; j < tilesy; j++) {
				glTexCoord2f(0.0f, 0.0f);  glVertex2f(i * bmpw, j * bmph);
				glTexCoord2f(1.0f, 0.0f);  glVertex2f((i + 1) * bmpw, j * bmph);
				glTexCoord2f(1.0f, 1.0f);  glVertex2f((i + 1) * bmpw, (j + 1) * bmph);
				glTexCoord2f(0.0f, 1.0f);  glVertex2f(i * bmpw, (j + 1) * bmph);
			}
		}
	glEnd();

	glDisable(GL_SCISSOR_TEST);
}
void Plane::Draw(long z, Bitmap* dst_bitmap) {

}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Plane::GetViewport() {
	return viewport;
}
void Plane::SetViewport(VALUE nviewport) {
	if (viewport != nviewport) {
		if (nviewport != Qnil) {
			Graphics::RemoveZObj(id);
			Viewport::Get(nviewport)->RegisterZObj(0, id);
		}
		else {
			if (viewport != Qnil) Viewport::Get(viewport)->RemoveZObj(id);
			Graphics::RegisterZObj(0, id);
		}
	}
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
	if (z != nz) {
		if (viewport != Qnil) {
			Viewport::Get(viewport)->UpdateZObj(id, nz);
		}
		else {
			Graphics::UpdateZObj(id, nz);
		}
	}
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
float Plane::GetZoomX() {
	return zoom_x;
}
void Plane::SetZoomX(float nzoom_x) {
	if (zoom_x != nzoom_x) needs_refresh = true;
	zoom_x = nzoom_x;
}
float Plane::GetZoomY() {
	return zoom_y;
}
void Plane::SetZoomY(float nzoom_y) {
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
