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
#include "viewport.h"
#include "player.h"
#include "graphics.h"
#include "system.h"
#include "SDL_opengl.h"

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
	flash_needs_refresh = false;

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
Sprite::~Sprite() {
	delete sprite;
	if (flash_texture > 0) {
		glDeleteTextures(1, &flash_texture);
		flash_texture = 0;
	}
}

////////////////////////////////////////////////////////////
/// Class Is Sprite Disposed?
////////////////////////////////////////////////////////////
bool Sprite::IsDisposed(VALUE id) {
	return Graphics::drawable_map.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Sprite
////////////////////////////////////////////////////////////
void Sprite::New(VALUE id) {
	Graphics::drawable_map[id] = new Sprite(id);
}

////////////////////////////////////////////////////////////
/// Class Get Sprite
////////////////////////////////////////////////////////////
Sprite* Sprite::Get(VALUE id) {
	return (Sprite*)Graphics::drawable_map[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Sprite
////////////////////////////////////////////////////////////
void Sprite::Dispose(unsigned long id) {
	if (Sprite::Get(id)->viewport != Qnil) {
		Viewport::Get(Sprite::Get(id)->viewport)->RemoveZObj(id);
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
void Sprite::RefreshBitmaps() {
	if (sprite != NULL) sprite->Changed();
}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Sprite::Draw(long z) {
	if (!visible) return;
	if (bitmap == Qnil) return;

	src_rect_sprite = Rect(src_rect);

	int width = src_rect_sprite.width;
	int height = src_rect_sprite.height;
	if (width <= 0 || height <= 0)
	if (x < -width || x > Player::GetWidth() || y < -height || y > Player::GetHeight()) return;
	if (zoom_x == 0 || zoom_y == 0 || opacity == 0) return;
	if (flash_duration > 0 && flash_color.red == -1) return;

	Refresh();

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, sprite->gl_bitmap);

	glTranslatef((float)x, (float)y, 0.0f);

	if (viewport != Qnil) {
		Rect rect = Viewport::Get(viewport)->GetViewportRect();

		glEnable(GL_SCISSOR_TEST);
		glScissor(rect.x, Player::GetHeight() - (rect.y + rect.height), rect.width, rect.height);

		glTranslatef((float)rect.x, (float)rect.y, 0.0f);
	}

	glRotatef((float)angle, 0.0f, 0.0f, 1.0f);
	glTranslatef((float)-ox * zoom_x, (float)-oy * zoom_y, 0.0f);

	glColor4f(1.0f, 1.0f, 1.0f, opacity / 255.0f);

	float corners[4][2] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
	if (flipx && flipy) {
		corners[0][0] = 1.0f; corners[0][1] = 1.0f;
		corners[1][0] = 0.0f; corners[1][1] = 1.0f;
		corners[2][0] = 0.0f; corners[2][1] = 0.0f;
		corners[3][0] = 1.0f; corners[3][1] = 0.0f;
	}
	else if (flipx) {
		corners[0][0] = 1.0f; corners[0][1] = 0.0f;
		corners[1][0] = 0.0f; corners[1][1] = 0.0f;
		corners[2][0] = 0.0f; corners[2][1] = 1.0f;
		corners[3][0] = 1.0f; corners[3][1] = 1.0f;
	}
	else if (flipy) {
		corners[0][0] = 0.0f; corners[0][1] = 1.0f;
		corners[1][0] = 1.0f; corners[1][1] = 1.0f;
		corners[2][0] = 1.0f; corners[2][1] = 0.0f;
		corners[3][0] = 0.0f; corners[3][1] = 0.0f;
	}

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

	if (bush_depth == 0) {
		glBegin(GL_QUADS);
			glTexCoord2f(corners[0][0], corners[0][1]); glVertex2f(0.0f, 0.0f);
			glTexCoord2f(corners[1][0], corners[1][1]); glVertex2f(width * zoom_x, 0.0f);
			glTexCoord2f(corners[2][0], corners[2][1]); glVertex2f(width * zoom_x, height  * zoom_y);
			glTexCoord2f(corners[3][0], corners[3][1]); glVertex2f(0.0f, height * zoom_y);
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
				glVertex2f(0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
				glVertex2f(width * zoom_x, 0.0f);
			glTexCoord2f(1.0f, 1.0f - bush_depth / (float)height);
				glVertex2f(width * zoom_x, (height - bush_depth)  * zoom_y);
			glTexCoord2f(0.0f, 1.0f - bush_depth / (float)height);
				glVertex2f(0.0f, (height - bush_depth) * zoom_y);
		glEnd();

		glColor4f(1.0f, 1.0f, 1.0f, 0.5f * (opacity / 255.0f));
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, (1.0f - bush_depth / (float)height));
				glVertex2f(0.0f, (height - bush_depth)  * zoom_y);
			glTexCoord2f(1.0f, (1.0f - bush_depth / (float)height));
				glVertex2f(width * zoom_x, (height - bush_depth)  * zoom_y);
			glTexCoord2f(1.0f, 1.0f);
				glVertex2f(width * zoom_x, height  * zoom_y);
			glTexCoord2f(0.0f, 1.0f);
				glVertex2f(0.0f, height * zoom_y);
		glEnd();
	}

	if (flash_duration > 0) {
		glBindTexture(GL_TEXTURE_2D, flash_texture);
		GLfloat alpha = ((float)flash_color.alpha / 255.0f) * (1.0f - flash_frame / (float)flash_duration);
		glColor4f((float)flash_color.red / 255.0f, (GLfloat)flash_color.green / 255.0f, (float)flash_color.blue / 255.0f, alpha);
		glBegin(GL_QUADS);
			glTexCoord2f(corners[0][0], corners[0][1]); glVertex2f(0.0f, 0.0f);
			glTexCoord2f(corners[1][0], corners[1][1]); glVertex2f(width * zoom_x, 0.0f);
			glTexCoord2f(corners[2][0], corners[2][1]); glVertex2f(width * zoom_x, height  * zoom_y);
			glTexCoord2f(corners[3][0], corners[3][1]); glVertex2f(0.0f, height * zoom_y);
		glEnd();
	}

	glDisable(GL_SCISSOR_TEST);
}
void Sprite::Draw(long z, Bitmap* dst_bitmap) {
	/*if (!visible) return;
	if (GetWidth() <= 0 || GetHeight() <= 0) return;
	if (x < -GetWidth() || x > dst_bitmap->GetWidth() || y < -GetHeight() || y > dst_bitmap->GetHeight()) return;
	if (!bitmap) return;
	
	src_rect_sprite = Rect(src_rect);
	if (src_rect_sprite != src_rect_last) {
		src_rect_last = src_rect_sprite;
		needs_refresh = true;
	}
	
	if (needs_refresh) Refresh();
	
	dst_bitmap->Blit(x - ox, y - oy, sprite, sprite->GetRect(), 255);*/
}

////////////////////////////////////////////////////////////
/// Refresh
////////////////////////////////////////////////////////////
void Sprite::Refresh() {
	if (src_rect_sprite != src_rect_last) {
		src_rect_last = src_rect_sprite;
		needs_refresh = true;
		flash_needs_refresh = true;
	}

	if (needs_refresh) {
		needs_refresh = false;

		delete sprite;

		sprite = new Bitmap(Bitmap::Get(bitmap), src_rect_sprite);

		sprite->ToneChange(Tone(tone));
	}
	if (flash_needs_refresh) {
		flash_needs_refresh = false;
		RefreshFlash();
	}

	sprite->Refresh();
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
			if (flash_texture > 0) {
				glDeleteTextures(1, &flash_texture);
				flash_texture = 0;
			}
		}
	}
}

////////////////////////////////////////////////////////////
/// Flash
////////////////////////////////////////////////////////////
void Sprite::Flash(int duration){
	flash_color = Color(-1, -1, -1, -1);
	flash_duration = duration;
	flash_frame = 0;
}
void Sprite::Flash(Color color, int duration){
	flash_color = color;
	flash_duration = duration;
	flash_frame = 0;
	flash_needs_refresh = true;
}
void Sprite::RefreshFlash() {
	if (flash_texture > 0) glDeleteTextures(1, &flash_texture);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &flash_texture);
	glBindTexture(GL_TEXTURE_2D, flash_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPixelTransferf(GL_RED_BIAS, 255.0f);
	glPixelTransferf(GL_GREEN_BIAS, 255.0f);
	glPixelTransferf(GL_BLUE_BIAS, 255.0f);

	int bpp = sprite->bitmap->format->BytesPerPixel;
	int format;

	if (sprite->bitmap->format->Rmask == 0x00FF0000) format = GL_BGRA;
	else format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, bpp, sprite->GetWidth(), sprite->GetHeight(), 0, format, GL_UNSIGNED_BYTE, sprite->bitmap->pixels);

	glPixelTransferf(GL_RED_BIAS, 0.0f);
	glPixelTransferf(GL_GREEN_BIAS, 0.0f);
	glPixelTransferf(GL_BLUE_BIAS, 0.0f);
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Sprite::GetViewport() {
	return viewport;
}
void Sprite::SetViewport(VALUE nviewport) {
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
VALUE Sprite::GetBitmap() {
	return bitmap;
}
void Sprite::SetBitmap(VALUE nbitmap) {
	if (bitmap != nbitmap) {
		needs_refresh = true;
		flash_needs_refresh = true;
	}
	bitmap = nbitmap;
}
VALUE Sprite::GetSrcRect() {
	return src_rect;
}
void Sprite::SetSrcRect(VALUE nsrc_rect) {
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
int Sprite::GetOx() {
	return ox;
}
void Sprite::SetOx(int nox) {
	ox = nox;
}
int Sprite::GetOy() {
	return oy;
}
void Sprite::SetOy(int noy) {
	oy = noy;
}
float Sprite::GetZoomX() {
	return zoom_x;
}
void Sprite::SetZoomX(float nzoom_x) {
	zoom_x = nzoom_x;
}
float Sprite::GetZoomY() {
	return zoom_y;
}
void Sprite::SetZoomY(float nzoom_y) {
	zoom_y = nzoom_y;
}
float Sprite::GetAngle() {
	return angle;
}
void Sprite::SetAngle(float nangle) {
	angle = nangle;
}
bool Sprite::GetFlipX() {
	return flipx;
}
void Sprite::SetFlipX(bool nflipx) {
	flipx = nflipx;
}
bool Sprite::GetFlipY() {
	return flipy;
}
void Sprite::SetFlipY(bool nflipy) {
	flipy = nflipy;
}
int Sprite::GetBushDepth() {
	return bush_depth;
}
void Sprite::SetBushDepth(int nbush_depth) {
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
