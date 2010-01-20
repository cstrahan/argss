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
#include "argss_tilemap_xp.h"
#include "argss_tilemapautotiles_xp.h"
#include "argss_viewport.h"
#include "argss_bitmap.h"
#include "argss_table.h"
#include "argss_error.h"
#include "tilemap_xp.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ATilemap::id;

////////////////////////////////////////////////////////////
/// ARGSS Tilemap ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_tilemap_initialize(int argc, VALUE *argv, VALUE self) {
	if (argc == 1) {
		Check_Classes_N(argv[0], ARGSS::AViewport::id);
		rb_iv_set(self, "@viewport", argv[0]);
    }
    else if (argc == 0) {
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
static VALUE argss_tilemap_dispose(VALUE self) {
	ARGSS::ATilemap::Check(self);
	Tilemap::Get(self)->Dispose();
	ARGSS::ARuby::RemoveObject(self);
    return self;
}
static VALUE argss_tilemap_disposeQ(VALUE self) {
	return INT2BOOL(Tilemap::IsDisposed(self));
}
static VALUE argss_tilemap_update(VALUE self) {
	ARGSS::ATilemap::Check(self);
	Tilemap::Get(self)->Update();
	return Qnil;
}
static VALUE argss_tilemap_viewport(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@viewport");
}
static VALUE argss_tilemap_viewportE(VALUE self, VALUE viewport) {
    ARGSS::ATilemap::Check(self);
	Check_Classes_N(viewport, ARGSS::AViewport::id);
	Tilemap::Get(self)->SetViewport(viewport);
	return rb_iv_set(self, "@viewport", viewport);
}
static VALUE argss_tilemap_tileset(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@tileset");
}
static VALUE argss_tilemap_tilesetE(VALUE self, VALUE tileset) {
    ARGSS::ATilemap::Check(self);
	Check_Classes_N(tileset, ARGSS::ABitmap::id);
	Tilemap::Get(self)->SetTileset(tileset);
	return rb_iv_set(self, "@tileset", tileset);
}
static VALUE argss_tilemap_autotiles(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@autotiles");
}
static VALUE argss_tilemap_map_data(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@map_data");
}
static VALUE argss_tilemap_map_dataE(VALUE self, VALUE map_data) {
    ARGSS::ATilemap::Check(self);
	Check_Classes_N(map_data, ARGSS::ATable::id);
	Tilemap::Get(self)->SetMapData(map_data);
	return rb_iv_set(self, "@map_data", map_data);
}
static VALUE argss_tilemap_flash_data(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@flash_data");
}
static VALUE argss_tilemap_flash_dataE(VALUE self, VALUE flash_data) {
    ARGSS::ATilemap::Check(self);
	Check_Classes_N(flash_data, ARGSS::ATable::id);
	Tilemap::Get(self)->SetFlashData(flash_data);
	return rb_iv_set(self, "@flash_data", flash_data);
}
static VALUE argss_tilemap_priorities(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@priorities");
}
static VALUE argss_tilemap_prioritiesE(VALUE self, VALUE priorities) {
    ARGSS::ATilemap::Check(self);
	Check_Classes_N(priorities, ARGSS::ATable::id);
	Tilemap::Get(self)->SetPriorities(priorities);
	return rb_iv_set(self, "@priorities", priorities);
}
static VALUE argss_tilemap_visible(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@visible");
}
static VALUE argss_tilemap_visibleE(VALUE self, VALUE visible) {
    ARGSS::ATilemap::Check(self);
	Tilemap::Get(self)->SetVisible(NUM2BOOL(visible));
    return rb_iv_set(self, "@visible", visible);
}
static VALUE argss_tilemap_ox(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@ox");
}
static VALUE argss_tilemap_oxE(VALUE self, VALUE ox) {
    ARGSS::ATilemap::Check(self);
    Tilemap::Get(self)->SetOx(NUM2INT(ox));
    return rb_iv_set(self, "@ox", ox);
}
static VALUE argss_tilemap_oy(VALUE self) {
	ARGSS::ATilemap::Check(self);
	return rb_iv_get(self, "@oy");
}
static VALUE argss_tilemap_oyE(VALUE self, VALUE oy) {
    ARGSS::ATilemap::Check(self);
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
    rb_define_method(id, "initialize", (rubyfunc)argss_tilemap_initialize, -1);
    rb_define_method(id, "dispose", (rubyfunc)argss_tilemap_dispose, 0);
    rb_define_method(id, "disposed?", (rubyfunc)argss_tilemap_disposeQ, 0);
    rb_define_method(id, "update", (rubyfunc)argss_tilemap_update, 0);
	rb_define_method(id, "viewport", (rubyfunc)argss_tilemap_viewport, 0);
	rb_define_method(id, "viewport=", (rubyfunc)argss_tilemap_viewportE, 1);
    rb_define_method(id, "tileset", (rubyfunc)argss_tilemap_tileset, 0);
	rb_define_method(id, "tileset=", (rubyfunc)argss_tilemap_tilesetE, 1);
    rb_define_method(id, "autotiles", (rubyfunc)argss_tilemap_autotiles, 0);
    rb_define_method(id, "map_data", (rubyfunc)argss_tilemap_map_data, 0);
	rb_define_method(id, "map_data=", (rubyfunc)argss_tilemap_map_dataE, 1);
    rb_define_method(id, "flash_data", (rubyfunc)argss_tilemap_flash_data, 0);
	rb_define_method(id, "flash_data=", (rubyfunc)argss_tilemap_flash_dataE, 1);
    rb_define_method(id, "priorities", (rubyfunc)argss_tilemap_priorities, 0);
	rb_define_method(id, "priorities=", (rubyfunc)argss_tilemap_prioritiesE, 1);
    rb_define_method(id, "visible", (rubyfunc)argss_tilemap_visible, 0);
	rb_define_method(id, "visible=", (rubyfunc)argss_tilemap_visibleE, 1);
    rb_define_method(id, "ox", (rubyfunc)argss_tilemap_ox, 0);
	rb_define_method(id, "ox=", (rubyfunc)argss_tilemap_oxE, 1);
    rb_define_method(id, "oy", (rubyfunc)argss_tilemap_oy, 0);
	rb_define_method(id, "oy=", (rubyfunc)argss_tilemap_oyE, 1);
}

////////////////////////////////////////////////////////////
/// Check if tilemap isn't disposed
////////////////////////////////////////////////////////////
void ARGSS::ATilemap::Check(VALUE self) {
    if (Tilemap::IsDisposed(self)) {
		rb_raise(ARGSS::AError::id, "disposed tilemap <%i>", self);
    }
}
