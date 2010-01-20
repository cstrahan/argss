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
#include "sprite.h"
#include "argss_ruby.h"
#include "argss_sprite.h"
#include "graphics.h"
#include "system.h"

////////////////////////////////////////////////////////////
/// Static Variables
////////////////////////////////////////////////////////////
std::map<unsigned long, Sprite*> Sprite::sprites;

////////////////////////////////////////////////////////////
/// Defines
////////////////////////////////////////////////////////////
#define max(a, b)	(((a) > (b)) ? (a) : (b))
#define min(a, b)	(((a) < (b)) ? (a) : (b))

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Sprite::Sprite(VALUE iid) {
	id = iid;
	viewport = rb_iv_get(id, "@viewport");
	src_rect = rb_iv_get(id, "@src_rect");
	bitmap = Qnil;
	visible = true;
	x = 0;
	y = 0;
	z = 0;
	ox = 0;
	oy = 0;
	zoom_x = 1.0;
	zoom_y = 1.0;
	angle = 0;
	flipx = false;
	flipy = false;
	bush_depth = 0;
	opacity = 255;
	blend_type = 0;
	color = rb_iv_get(id, "@color");
	tone = rb_iv_get(id, "@tone");
	sprite = NULL;
	flash_duration = 0;

	Graphics::RegisterZObj(0, ARGSS::ASprite::id, id);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Sprite::~Sprite() {
	delete sprite;
}

////////////////////////////////////////////////////////////
/// Class Is Sprite Disposed?
////////////////////////////////////////////////////////////
bool Sprite::IsDisposed(VALUE id) {
	return sprites.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Sprite
////////////////////////////////////////////////////////////
void Sprite::New(VALUE id) {
	sprites[id] = new Sprite(id);
}

////////////////////////////////////////////////////////////
/// Class Get Sprite
////////////////////////////////////////////////////////////
Sprite* Sprite::Get(VALUE id) {
	return sprites[id];
}

////////////////////////////////////////////////////////////
/// Dispose
////////////////////////////////////////////////////////////
void Sprite::Dispose() {
	sprites.erase(id);
	Graphics::RemoveZObj(id);
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Sprite::Draw() {
	if (!visible) return;
	if (GetWidth() <= 0 || GetHeight() <= 0) return;
	if (x < -GetWidth() || x > System::Width || y < -GetHeight() || y > System::Height) return;
	if (!bitmap) return;
	
	src_rect_sprite = Rect(src_rect);
	if (src_rect_sprite != src_rect_last) {
		src_rect_last = src_rect_sprite;
		needs_refresh = true;
	}
	
	if (needs_refresh) Refresh();
	
	sprite->BlitScreen(x - ox, y - oy);
}

////////////////////////////////////////////////////////////
/// Refresh
////////////////////////////////////////////////////////////
void Sprite::Refresh() {
	needs_refresh = false;

	tone_sprite.Set(tone);

	delete sprite;
	
	sprite = new Bitmap(Bitmap::Get(bitmap), src_rect_sprite);
		
	sprite->ToneChange(tone);
	sprite->OpacityChange(opacity, bush_depth);
	sprite->Flip(flipx, flipy);
	sprite->Zoom(zoom_x, zoom_y);
	sprite->Rotate(angle);

	if (flash_duration > 0) {
		sprite->Flash(flash_color, flash_frame, flash_duration);
	}
}

////////////////////////////////////////////////////////////
/// Get Width
////////////////////////////////////////////////////////////
int Sprite::GetWidth() {
	return NUM2INT(rb_iv_get(src_rect, "@width"));
}

////////////////////////////////////////////////////////////
/// Get Height
////////////////////////////////////////////////////////////
int Sprite::GetHeight() {
	return NUM2INT(rb_iv_get(src_rect, "@height"));
}

////////////////////////////////////////////////////////////
/// Update
////////////////////////////////////////////////////////////
void Sprite::Update() {
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
void Sprite::Flash(int duration){
	flash_color = Color(0, 0, 0, 0);
	flash_duration = duration;
	flash_frame = 0;
}
void Sprite::Flash(Color color, int duration){
	flash_color = color;
	flash_duration = duration;
	flash_frame = 0;
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Sprite::GetViewport() {
	return viewport;
}
void Sprite::SetViewport(VALUE nviewport) {
	viewport = nviewport;
}
VALUE Sprite::GetBitmap() {
	return bitmap;
}
void Sprite::SetBitmap(VALUE nbitmap) {
	if (bitmap != nbitmap) needs_refresh = true;
	bitmap = nbitmap;
}
VALUE Sprite::GetSrcRect() {
	return src_rect;
}
void Sprite::SetSrcRect(VALUE nsrc_rect) {
	if (src_rect != nsrc_rect) needs_refresh = true;
	src_rect = nsrc_rect;
}
bool Sprite::GetVisible() {
	return visible;
}
void Sprite::SetVisible(bool nvisible) {
	visible = nvisible;
}
int Sprite::GetX() {
	return x;
}
void Sprite::SetX(int nx) {
	x = nx;
}
int Sprite::GetY() {
	return y;
}
void Sprite::SetY(int ny) {
	y = ny;
}
int Sprite::GetZ() {
	return z;
}
void Sprite::SetZ(int nz) {
	if (z != nz) Graphics::UpdateZObj(id, nz);
	z = nz;
	
}
int Sprite::GetOx() {
	return ox;
}
void Sprite::SetOx(int nox) {
	if (ox != nox) needs_refresh = true;
	ox = nox;
}
int Sprite::GetOy() {
	return oy;
}
void Sprite::SetOy(int noy) {
	if (oy != noy) needs_refresh = true;
	oy = noy;
}
double Sprite::GetZoomX() {
	return zoom_x;
}
void Sprite::SetZoomX(double nzoom_x) {
	if (zoom_x != nzoom_x) needs_refresh = true;
	zoom_x = nzoom_x;
}
double Sprite::GetZoomY() {
	return zoom_y;
}
void Sprite::SetZoomY(double nzoom_y) {
	if (zoom_y != nzoom_y) needs_refresh = true;
	zoom_y = nzoom_y;
}
double Sprite::GetAngle() {
	return angle;
}
void Sprite::SetAngle(double nangle) {
	if (angle != nangle) needs_refresh = true;
	angle = nangle;
}
bool Sprite::GetFlipX() {
	return flipx;
}
void Sprite::SetFlipX(bool nflipx) {
	if (flipx != nflipx) needs_refresh = true;
	flipx = nflipx;
}
bool Sprite::GetFlipY() {
	return flipy;
}
void Sprite::SetFlipY(bool nflipy) {
	if (flipy != nflipy) needs_refresh = true;
	flipy = nflipy;
}
int Sprite::GetBushDepth() {
	return bush_depth;
}
void Sprite::SetBushDepth(int nbush_depth) {
	if (bush_depth != nbush_depth) needs_refresh = true;
	bush_depth = nbush_depth;
}
int Sprite::GetOpacity() {
	return opacity;
}
void Sprite::SetOpacity(int nopacity) {
	opacity = nopacity;
}
int Sprite::GetBlendType() {
	return blend_type;
}
void Sprite::SetBlendType(int nblend_type) {
	blend_type = nblend_type;
}
VALUE Sprite::GetColor() {
	return color;
}
void Sprite::SetColor(VALUE ncolor) {
	color = ncolor;
}
VALUE Sprite::GetTone() {
	return tone;
}
void Sprite::SetTone(VALUE ntone) {
	if (tone != ntone) needs_refresh = true;
	tone = ntone;
}
