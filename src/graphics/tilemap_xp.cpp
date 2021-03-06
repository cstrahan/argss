/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include <string>
#include <map>
#include <math.h>
#include "tilemap_xp.h"
#include "aruby.h"
#include "argss/classes/atilemap.h"
#include "graphics/graphics.h"
#include "graphics/viewport.h"
#include "player.h"

///////////////////////////////////////////////////////////
/// Static Variables
///////////////////////////////////////////////////////////
int Tilemap::autotiles_id[6][8][4];

///////////////////////////////////////////////////////////
/// Class Init
///////////////////////////////////////////////////////////
void Tilemap::Init() {
	int temp[192] = {
		26, 27, 32, 33, 04, 27, 32, 33, 26, 05, 32, 33, 04, 05, 32, 33,
		26, 27, 32, 11, 04, 27, 32, 11, 26, 05, 32, 11, 04, 05, 32, 11,
		26, 27, 10, 33, 04, 27, 10, 33, 26, 05, 10, 33, 04, 05, 10, 33,
		26, 27, 10, 11, 04, 27, 10, 11, 26, 05, 10, 11, 04, 05, 10, 11,
		24, 25, 30, 31, 24, 05, 30, 31, 24, 25, 30, 11, 24, 05, 30, 11,
		14, 15, 20, 21, 14, 15, 20, 11, 14, 15, 10, 21, 14, 15, 10, 11,
		28, 29, 34, 35, 28, 29, 10, 35, 04, 29, 34, 35, 04, 29, 10, 35,
		38, 39, 44, 45, 04, 39, 44, 45, 38, 05, 44, 45, 04, 05, 44, 45,
		24, 29, 30, 35, 14, 15, 44, 45, 12, 13, 18, 19, 12, 13, 18, 11,
		16, 17, 22, 23, 16, 17, 10, 23, 40, 41, 46, 47, 04, 41, 46, 47,
		36, 37, 42, 43, 36, 05, 42, 43, 12, 17, 18, 23, 12, 13, 42, 43,
		36, 41, 42, 47, 16, 17, 46, 47, 12, 17, 42, 47, 00, 01, 06, 07
	};
	memcpy(autotiles_id, temp, 192 * sizeof(int));
}

///////////////////////////////////////////////////////////
/// Constructor
///////////////////////////////////////////////////////////
Tilemap::Tilemap(VALUE iid) {
	id = iid;
	viewport = rb_iv_get(id, "@viewport");
	tileset = Qnil;
	autotiles = rb_iv_get(id, "@autotiles");
	map_data = Qnil;
	flash_data = Qnil;
	priorities = Qnil;
	visible = true;
	ox = 0;
	oy = 0;
	autotile_time = 0;
	autotile_frame = 0;
}

///////////////////////////////////////////////////////////
/// Destructor
///////////////////////////////////////////////////////////
Tilemap::~Tilemap() {
	std::map<unsigned long, std::map<int, std::map<int, Bitmap*> > >::iterator it1_autotiles_cache;
	std::map<int, std::map<int, Bitmap*> >::iterator it2_autotiles_cache;
	std::map<int, Bitmap*>::iterator it3_autotiles_cache;
	for (it1_autotiles_cache = autotiles_cache.begin(); it1_autotiles_cache != autotiles_cache.end(); it1_autotiles_cache++) {
		for (it2_autotiles_cache = it1_autotiles_cache->second.begin(); it2_autotiles_cache != it1_autotiles_cache->second.end(); it2_autotiles_cache++) {
			for (it3_autotiles_cache = it2_autotiles_cache->second.begin(); it3_autotiles_cache != it2_autotiles_cache->second.end(); it3_autotiles_cache++) {
				delete it3_autotiles_cache->second;
			}
		}
	}
}

///////////////////////////////////////////////////////////
/// Class Is Tilemap Disposed?
///////////////////////////////////////////////////////////
bool Tilemap::IsDisposed(VALUE id) {
	return Graphics::drawable_map.count(id) == 0;
}

///////////////////////////////////////////////////////////
/// Class New Tilemap
///////////////////////////////////////////////////////////
void Tilemap::New(VALUE id) {
	Graphics::drawable_map[id] = new Tilemap(id);
}

///////////////////////////////////////////////////////////
/// Class Get Tilemap
///////////////////////////////////////////////////////////
Tilemap* Tilemap::Get(VALUE id) {
	return (Tilemap*)Graphics::drawable_map[id];
}

///////////////////////////////////////////////////////////
/// Class Dispose Tilemap
///////////////////////////////////////////////////////////
void Tilemap::Dispose(unsigned long id) {
	if (Tilemap::Get(id)->viewport != Qnil) {
		Viewport::Get(Tilemap::Get(id)->viewport)->RemoveZObj(id);
	} else {
		Graphics::RemoveZObj(id);
	}
	delete Graphics::drawable_map[id];
	std::map<unsigned long, Drawable*>::iterator it = Graphics::drawable_map.find(id);
	Graphics::drawable_map.erase(it);
}

///////////////////////////////////////////////////////////
/// Update
///////////////////////////////////////////////////////////
void Tilemap::Update() {
	autotile_time += 1;
	if (autotile_time == 8) {
		autotile_time = 0;
		autotile_frame += 1;
	}
}

///////////////////////////////////////////////////////////
/// Refresh Bitmaps
///////////////////////////////////////////////////////////
void Tilemap::RefreshBitmaps() {
	std::map<unsigned long, std::map<int, std::map<int, Bitmap*> > >::iterator it1_autotiles_cache;
	std::map<int, std::map<int, Bitmap*> >::iterator it2_autotiles_cache;
	std::map<int, Bitmap*>::iterator it3_autotiles_cache;
	for (it1_autotiles_cache = autotiles_cache.begin(); it1_autotiles_cache != autotiles_cache.end(); it1_autotiles_cache++) {
		for (it2_autotiles_cache = it1_autotiles_cache->second.begin(); it2_autotiles_cache != it1_autotiles_cache->second.end(); it2_autotiles_cache++) {
			for (it3_autotiles_cache = it2_autotiles_cache->second.begin(); it3_autotiles_cache != it2_autotiles_cache->second.end(); it3_autotiles_cache++) {
				it3_autotiles_cache->second->Changed();
			}
		}
	}
}

///////////////////////////////////////////////////////////
/// Draw
///////////////////////////////////////////////////////////
void Tilemap::Draw(long z_level) {
	if (!visible) return;
	if (tileset == Qnil || map_data == Qnil || priorities == Qnil) return;

	if (z_level == 0) {
		RefreshData();
		Bitmap::Get(tileset)->Refresh();
	}

	int width = NUM2INT(rb_iv_get(map_data, "@xsize"));
	int height = NUM2INT(rb_iv_get(map_data, "@ysize"));
	int layers = NUM2INT(rb_iv_get(map_data, "@zsize"));

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (viewport != Qnil) {
		Rect rect = Viewport::Get(viewport)->GetViewportRect();

		glEnable(GL_SCISSOR_TEST);
		glScissor(rect.x, Player::GetHeight() - (rect.y + rect.height), rect.width, rect.height);

		glTranslatef((float)rect.x, (float)rect.y, 0.0f);
	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	int tiles_x = (int)ceil(Player::GetWidth() / 32.0);
	int tiles_y = (int)ceil(Player::GetHeight() / 32.0);

	for (int z = 0; z < layers; z++) {
		for (int y = 0; y <= tiles_y; y++) {
			for (int x = 0; x <= tiles_x; x++) {
				int map_x = ox / 32 + x;
				int map_y = oy / 32 + y;

				if (map_x >= width || map_y >= height) continue;

				TileData tile = data_cache[map_x][map_y][z];

				int tile_z;
				if (tile.priority == 0) {
					tile_z = 0;
				} else {
					tile_z = tile.priority * 32 + y * 32 + z * 32;
					if (map_y == 0 && tile.priority == 1) tile_z += 32;
				}

				if (tile_z == z_level) {
					float dst_x = (float)(x * 32 - ox % 32);
					float dst_y = (float)(y * 32 - oy % 32);
					if (tile.id < 384 && tile.id != 0) {
							VALUE bitmap_id = rb_ary_entry(rb_iv_get(autotiles, "@autotiles"), tile.id / 48 - 1);
							if (Bitmap::IsDisposed(bitmap_id)) continue;
							Bitmap* autotile_bitmap = Bitmap::Get(bitmap_id);
							int tile_id = tile.id % 48;
							int frame = autotile_frame % (autotile_bitmap->GetWidth() / 96);

							if (autotiles_cache.count(bitmap_id) == 0 ||
									autotiles_cache[bitmap_id].count(tile_id) == 0 ||
									autotiles_cache[bitmap_id][tile_id].count(frame) == 0) {
								autotiles_cache[bitmap_id][tile_id][frame] = new Bitmap(32, 32);
								int* tiles = autotiles_id[tile_id >> 3][tile_id & 7];
								for (int i = 0; i < 4; i++) {
									Rect rect(((tiles[i] % 6) << 4) + frame * 96, (tiles[i] / 6) << 4, 16, 16);
									autotiles_cache[bitmap_id][tile_id][frame]->Blit((i % 2) << 4, (i / 2) << 4, autotile_bitmap, rect, 255);
								}
								glPushMatrix();

								autotiles_cache[bitmap_id][tile_id][frame]->Refresh();

								glMatrixMode(GL_MODELVIEW);
								glPopMatrix();
							}
							autotiles_cache[bitmap_id][tile_id][frame]->BindBitmap();

							glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex2f(dst_x, dst_y);
								glTexCoord2f(1.0f, 0.0f); glVertex2f(dst_x + 32.0f, dst_y);
								glTexCoord2f(1.0f, 1.0f); glVertex2f(dst_x + 32.0f, dst_y + 32.0f);
								glTexCoord2f(0.0f, 1.0f); glVertex2f(dst_x, dst_y + 32.0f);
							glEnd();
					} else if (tile.id != 0){
						float src_x = (float)((tile.id - 384) % 8 * 32);
						float src_y = (float)((tile.id - 384) / 8 * 32);

						Bitmap::Get(tileset)->BindBitmap();

						float bmpw = (float)Bitmap::Get(tileset)->GetWidth();
						float bmph = (float)Bitmap::Get(tileset)->GetHeight();

						glBegin(GL_QUADS);
							glTexCoord2f(src_x / bmpw, src_y / bmph);						glVertex2f(dst_x, dst_y);
							glTexCoord2f((src_x + 32.0f) / bmpw, src_y / bmph);				glVertex2f(dst_x + 32.0f, dst_y);
							glTexCoord2f((src_x + 32.0f) / bmpw, (src_y + 32.0f) / bmph);	glVertex2f(dst_x + 32.0f, dst_y + 32.0f);
							glTexCoord2f(src_x / bmpw, (src_y + 32.0f) / bmph);				glVertex2f(dst_x, dst_y + 32.0f);
						glEnd();
					}
				}
			}
		}
	}

	glDisable(GL_SCISSOR_TEST);
}
void Tilemap::Draw(long z, Bitmap* dst_bitmap) {

}

///////////////////////////////////////////////////////////
/// Refresh Data
///////////////////////////////////////////////////////////
void Tilemap::RefreshData() {
	bool update = false;
	if (rb_iv_get(map_data, "@modified") == Qtrue) {
		rb_iv_set(map_data, "@modified", Qfalse);
		update = true;
	}
	if (rb_iv_get(priorities, "@modified") == Qtrue) {
		rb_iv_set(priorities, "@modified", Qfalse);
		update = true;
	}

	if (!update) return;

	int width = NUM2INT(rb_iv_get(map_data, "@xsize"));
	int height = NUM2INT(rb_iv_get(map_data, "@ysize"));
	int layers = NUM2INT(rb_iv_get(map_data, "@zsize"));

	VALUE map_data_array = rb_iv_get(map_data, "@data");
	VALUE priorities_array = rb_iv_get(priorities, "@data");

	data_cache.resize(width);
	for (int x = 0; x < width; x++) {
		data_cache[x].resize(height);
		for (int y = 0; y < height; y++) {
			data_cache[x][y].resize(layers);
			for (int z = 0; z < layers; z++) {
				TileData tile;
				tile.id = NUM2INT(rb_ary_entry(map_data_array, x + y * width + z * width * height));
				tile.priority = NUM2INT(rb_ary_entry(priorities_array, tile.id));
				data_cache[x][y][z] = tile;
			}
		}
	}
}

///////////////////////////////////////////////////////////
/// Properties
///////////////////////////////////////////////////////////
VALUE Tilemap::GetViewport() {
	return viewport;
}
void Tilemap::SetViewport(VALUE nviewport) {
	if (viewport != nviewport) {
		if (viewport != Qnil) {
			Viewport::Get(viewport)->RemoveZObj(id);
		} else {
			Graphics::RemoveZObj(id);
		}
		int height = NUM2INT(rb_iv_get(map_data, "@ysize"));
		if (nviewport != Qnil) {
			for (int i = 0; i < height + 5; i++) {
				Viewport::Get(nviewport)->RegisterZObj(i * 32, id, true);
			}
		} else {
			for (int i = 0; i < height + 5; i++) {
				Graphics::RegisterZObj(i * 32, id, true);
			}
		}
	}
	viewport = nviewport;
}
VALUE Tilemap::GetTileset() {
	return tileset;
}
void Tilemap::SetTileset(VALUE ntileset) {
	tileset = ntileset;
}
VALUE Tilemap::GetMapData() {
	return map_data;
}
void Tilemap::SetMapData(VALUE nmap_data) {
	if (map_data != nmap_data) {
		if (viewport != Qnil) {
			Viewport::Get(viewport)->RemoveZObj(id);
		} else {
			Graphics::RemoveZObj(id);
		}
		if (nmap_data != Qnil) {
			rb_iv_set(nmap_data, "@modified", Qtrue);
			int height = NUM2INT(rb_iv_get(nmap_data, "@ysize"));
			if (viewport != Qnil) {
				for (int i = 0; i < height + 8; i++) {
					Viewport::Get(viewport)->RegisterZObj(i * 32, id, true);
				}
			} else {
				for (int i = 0; i < height + 8; i++) {
					Graphics::RegisterZObj(i * 32, id, true);
				}
			}
		}
	}
	map_data = nmap_data;
}
VALUE Tilemap::GetFlashData() {
	return flash_data;
}
void Tilemap::SetFlashData(VALUE nflash_data) {
	flash_data = nflash_data;
}
VALUE Tilemap::GetPriorities() {
	return priorities;
}
void Tilemap::SetPriorities(VALUE npriorities) {
	if (priorities != npriorities) rb_iv_set(npriorities, "@modified", Qtrue);
	priorities = npriorities;
}
bool Tilemap::GetVisible() {
	return visible;
}
void Tilemap::SetVisible(bool nvisible) {
	visible = nvisible;
}
int Tilemap::GetOx() {
	return ox;
}
void Tilemap::SetOx(int nox) {
	ox = nox;
}
int Tilemap::GetOy() {
	return oy;
}
void Tilemap::SetOy(int noy) {
	oy = noy;
}
