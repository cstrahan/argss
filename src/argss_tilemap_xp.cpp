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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include "argss_tilemap_xp.h"
#include "argss_tilemapautotiles_xp.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_table.h"
#include "argss_error.h"
#include "tilemap_xp.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ATilemap::id;

////////////////////////////////////////////////////////////
/// ARGSS Tilemap ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::ATilemap::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
	} else if (argc == 0) {
		rb_iv_set(self, "@viewport", Qnil);
	}
	else raise_argn(argc, 1);
	rb_iv_set(self, "@tileset", Qnil);
	rb_iv_set(self, "@autotiles", ARGSS::ATilemapAutotiles::New());
	rb_iv_set(self, "@map_data", Qnil);
	rb_iv_set(self, "@flash_data", Qnil);
	rb_iv_set(self, "@priorities", Qnil);
	rb_iv_set(self, "@visible", Qtrue);
	rb_iv_set(self, "@ox", INT2NUM(0));
	rb_iv_set(self, "@oy", INT2NUM(0));
	Tilemap::New(self);
	ARGSS::ARuby::AddObject(self);
	return self;
}
VALUE ARGSS::ATilemap::rdispose(VALUE self) {
	if (!Tilemap::IsDisposed(self)) {
		ARGSS::ATilemap::CheckDisposed(self);
		Tilemap::Dispose(self);
		ARGSS::ARuby::RemoveObject(self);
		rb_gc_start();
	}
	return self;
}
VALUE ARGSS::ATilemap::rdisposeQ(VALUE self) {
	return INT2BOOL(Tilemap::IsDisposed(self));
}
VALUE ARGSS::ATilemap::rupdate(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	Tilemap::Get(self)->Update();
	return Qnil;
}
VALUE ARGSS::ATilemap::rviewport(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@viewport");
}
VALUE ARGSS::ATilemap::rviewportE(VALUE self, VALUE viewport) {
	ARGSS::ATilemap::CheckDisposed(self);
	Check_Classes_N(viewport, ARGSS::AViewport::id);
	Tilemap::Get(self)->SetViewport(viewport);
	return rb_iv_set(self, "@viewport", viewport);
}
VALUE ARGSS::ATilemap::rtileset(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@tileset");
}
VALUE ARGSS::ATilemap::rtilesetE(VALUE self, VALUE tileset) {
	ARGSS::ATilemap::CheckDisposed(self);
	Check_Classes_N(tileset, ARGSS::ABitmap::id);
	Tilemap::Get(self)->SetTileset(tileset);
	return rb_iv_set(self, "@tileset", tileset);
}
VALUE ARGSS::ATilemap::rautotiles(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@autotiles");
}
VALUE ARGSS::ATilemap::rmap_data(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@map_data");
}
VALUE ARGSS::ATilemap::rmap_dataE(VALUE self, VALUE map_data) {
	ARGSS::ATilemap::CheckDisposed(self);
	Check_Classes_N(map_data, ARGSS::ATable::id);
	Tilemap::Get(self)->SetMapData(map_data);
	return rb_iv_set(self, "@map_data", map_data);
}
VALUE ARGSS::ATilemap::rflash_data(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@flash_data");
}
VALUE ARGSS::ATilemap::rflash_dataE(VALUE self, VALUE flash_data) {
	ARGSS::ATilemap::CheckDisposed(self);
	Check_Classes_N(flash_data, ARGSS::ATable::id);
	Tilemap::Get(self)->SetFlashData(flash_data);
	return rb_iv_set(self, "@flash_data", flash_data);
}
VALUE ARGSS::ATilemap::rpriorities(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@priorities");
}
VALUE ARGSS::ATilemap::rprioritiesE(VALUE self, VALUE priorities) {
	ARGSS::ATilemap::CheckDisposed(self);
	Check_Classes_N(priorities, ARGSS::ATable::id);
	Tilemap::Get(self)->SetPriorities(priorities);
	return rb_iv_set(self, "@priorities", priorities);
}
VALUE ARGSS::ATilemap::rvisible(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@visible");
}
VALUE ARGSS::ATilemap::rvisibleE(VALUE self, VALUE visible) {
	ARGSS::ATilemap::CheckDisposed(self);
	Tilemap::Get(self)->SetVisible(NUM2BOOL(visible));
	return rb_iv_set(self, "@visible", visible);
}
VALUE ARGSS::ATilemap::rox(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@ox");
}
VALUE ARGSS::ATilemap::roxE(VALUE self, VALUE ox) {
	ARGSS::ATilemap::CheckDisposed(self);
	Tilemap::Get(self)->SetOx(NUM2INT(ox));
	return rb_iv_set(self, "@ox", ox);
}
VALUE ARGSS::ATilemap::roy(VALUE self) {
	ARGSS::ATilemap::CheckDisposed(self);
	return rb_iv_get(self, "@oy");
}
VALUE ARGSS::ATilemap::royE(VALUE self, VALUE oy) {
	ARGSS::ATilemap::CheckDisposed(self);
	Tilemap::Get(self)->SetOy(NUM2INT(oy));
	return rb_iv_set(self, "@oy", oy);
}

////////////////////////////////////////////////////////////
/// ARGSS Tilemap initialize
////////////////////////////////////////////////////////////
void ARGSS::ATilemap::Init() {
	ARGSS::ATilemapAutotiles::Init();
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_class("Tilemap", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "disposed?", (rubyfunc)rdisposeQ, 0);
	rb_define_method(id, "update", (rubyfunc)rupdate, 0);
	rb_define_method(id, "viewport", (rubyfunc)rviewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)rviewportE, 1);
	rb_define_method(id, "tileset", (rubyfunc)rtileset, 0);
	rb_define_method(id, "tileset=", (rubyfunc)rtilesetE, 1);
	rb_define_method(id, "autotiles", (rubyfunc)rautotiles, 0);
	rb_define_method(id, "map_data", (rubyfunc)rmap_data, 0);
	rb_define_method(id, "map_data=", (rubyfunc)rmap_dataE, 1);
	rb_define_method(id, "flash_data", (rubyfunc)rflash_data, 0);
	rb_define_method(id, "flash_data=", (rubyfunc)rflash_dataE, 1);
	rb_define_method(id, "priorities", (rubyfunc)rpriorities, 0);
	rb_define_method(id, "priorities=", (rubyfunc)rprioritiesE, 1);
	rb_define_method(id, "visible", (rubyfunc)rvisible, 0);
	rb_define_method(id, "visible=", (rubyfunc)rvisibleE, 1);
	rb_define_method(id, "ox", (rubyfunc)rox, 0);
	rb_define_method(id, "ox=", (rubyfunc)roxE, 1);
	rb_define_method(id, "oy", (rubyfunc)roy, 0);
	rb_define_method(id, "oy=", (rubyfunc)royE, 1);
}

////////////////////////////////////////////////////////////
/// Check if tilemap isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::ATilemap::CheckDisposed(VALUE self) {
	if (Tilemap::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed tilemap <%i>", self);
	}
}
