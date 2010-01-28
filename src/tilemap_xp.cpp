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
#include <map>
#include "tilemap_xp.h"
#include "argss_ruby.h"
#include "argss_tilemap.h"
#include "graphics.h"

////////////////////////////////////////////////////////////
/// Static Variables
////////////////////////////////////////////////////////////
std::map<unsigned long, Tilemap*> Tilemap::tilemaps;

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
Tilemap::Tilemap(VALUE iid) {
	id = iid;
	viewport = rb_iv_get(id, "@viewport");
	tileset = Qnil;
	autotiles = rb_iv_get(id, "@autotiles");
	map_data = Qnil;
	flash_data = Qnil;
	priorities = Qnil;
	visible = false;
	ox = 0;
	oy = 0;

	Graphics::RegisterZObj(0, ARGSS::ATilemap::id, id);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
Tilemap::~Tilemap() {

}

////////////////////////////////////////////////////////////
/// Class Is Tilemap Disposed?
////////////////////////////////////////////////////////////
bool Tilemap::IsDisposed(VALUE id) {
	return tilemaps.count(id) == 0;
}

////////////////////////////////////////////////////////////
/// Class New Tilemap
////////////////////////////////////////////////////////////
void Tilemap::New(VALUE id) {
	tilemaps[id] = new Tilemap(id);
}

////////////////////////////////////////////////////////////
/// Class Get Tilemap
////////////////////////////////////////////////////////////
Tilemap* Tilemap::Get(VALUE id) {
	return tilemaps[id];
}

////////////////////////////////////////////////////////////
/// Class Dispose Tilemap
////////////////////////////////////////////////////////////
void Tilemap::Dispose(unsigned long id) {
	delete tilemaps[id];
	std::map<unsigned long, Tilemap*>::iterator it = tilemaps.find(id);
	tilemaps.erase(it);
	Graphics::RemoveZObj(id);
}

////////////////////////////////////////////////////////////
/// Update
////////////////////////////////////////////////////////////
void Tilemap::Update() {

}

////////////////////////////////////////////////////////////
/// Draw
////////////////////////////////////////////////////////////
void Tilemap::Draw(int z) {

}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
VALUE Tilemap::GetViewport() {
	return viewport;
}
void Tilemap::SetViewport(VALUE nviewport) {
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
