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
#include "argss_rpg.h"
#include "argss_rpg_cache.h"
#include "argss_bitmap.h"
#include "argss_rect.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ARPG::ACache::id;

////////////////////////////////////////////////////////////
/// ARGSS RPG::Cache ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_rpg_cache_load_bitmap(int argc, VALUE* argv, VALUE self) {
	if (argc > 3) raise_argn(argc, 3);
	else if (argc < 2) raise_argn(argc, 2);
	VALUE hue = argv[2];
	if (argc == 2) hue = INT2NUM(0);
	VALUE path = rb_str_concat(rb_str_dup(argv[0]), argv[1]);
	VALUE cache = rb_iv_get(ARGSS::ARPG::ACache::id, "@cache");
	VALUE cache_path;
	if ((rb_funcall(cache, rb_intern("include?"), 1, path) == Qfalse) ||
		(rb_funcall(rb_hash_aref(cache, path), rb_intern("disposed?"), 0) == Qtrue)) {
		if (RSTRING(argv[0])->len > 0) {
			cache_path = rb_hash_aset(cache, path, rb_class_new_instance(1, &path, ARGSS::ABitmap::id));
		}
		else {
			VALUE args[2] = {INT2NUM(32), INT2NUM(32)};
			cache_path = rb_hash_aset(cache, path, rb_class_new_instance(2, args, ARGSS::ABitmap::id));
		}
	}
	else {
		cache_path = rb_hash_aref(cache, path);
	}
	if (hue == INT2NUM(0)) {
		return cache_path;
	}
	else {
		VALUE key = rb_ary_new3(2, path, hue);
		VALUE cache_key;
		if ((rb_funcall(cache, rb_intern("include?"), 1, key) == Qfalse) ||
			(rb_funcall(rb_hash_aref(cache, key), rb_intern("disposed?"), 0) == Qtrue)) {
			cache_key = rb_hash_aset(cache, key, rb_obj_clone(cache_path));
			rb_funcall(cache_key, rb_intern("hue_change"), 1, hue);
		}
		else {
			cache_key = rb_hash_aref(cache, key);
		}
		return cache_key;
	}
}
static VALUE argss_rpg_cache_animation(VALUE self, VALUE filename, VALUE hue) {
	VALUE args[3] = {rb_str_new2("Graphics/Animations/"), filename, hue};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_autotile(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Autotiles/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_battleback(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Battlebacks/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_battler(VALUE self, VALUE filename, VALUE hue) {
	VALUE args[3] = {rb_str_new2("Graphics/Battlers/"), filename, hue};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_character(VALUE self, VALUE filename, VALUE hue) {
	VALUE args[3] = {rb_str_new2("Graphics/Characters/"), filename, hue};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_fog(VALUE self, VALUE filename, VALUE hue) {
	VALUE args[3] = {rb_str_new2("Graphics/Fogs/"), filename, hue};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_gameover(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Gameovers/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_icon(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Icons/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_panorama(VALUE self, VALUE filename, VALUE hue) {
	VALUE args[3] = {rb_str_new2("Graphics/Panoramas/"), filename, hue};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_picture(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Pictures/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_tileset(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Tilesets/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_title(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Titles/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_windowskin(VALUE self, VALUE filename) {
	VALUE args[3] = {rb_str_new2("Graphics/Windowskins/"), filename, INT2NUM(0)};
	return argss_rpg_cache_load_bitmap(3, args, self);
}
static VALUE argss_rpg_cache_tile(VALUE self, VALUE filename, VALUE tile_id, VALUE hue) {
	VALUE key = rb_ary_new3(3, filename, tile_id, hue);
	VALUE cache = rb_iv_get(ARGSS::ARPG::ACache::id, "@cache");
	VALUE cache_key;
	if ((rb_funcall(cache, rb_intern("include?"), 1, key) == Qfalse) ||
		(rb_funcall(rb_hash_aref(cache, key), rb_intern("disposed?"), 0) == Qtrue)) {
		VALUE args[2] = {INT2NUM(32), INT2NUM(32)};
		cache_key = rb_hash_aset(cache, key, rb_class_new_instance(2, args, ARGSS::ABitmap::id));
		double x = (NUM2INT(tile_id) - 384) % 8 * 32;
		double y = (NUM2INT(tile_id) - 384) / 8 * 32;
		VALUE rect = ARGSS::ARect::New(x, y, 32, 32);
		rb_funcall(cache_key, rb_intern("blt"), 4, INT2NUM(0), INT2NUM(0), argss_rpg_cache_tileset(self, filename), rect);
		rb_funcall(cache_key, rb_intern("hue_change"), 1, hue);
	}
	else {
		cache_key = rb_hash_aref(cache, key);
	}
	return cache_key;
}
static VALUE argss_rpg_cache_clear(VALUE self) {
	VALUE cache = rb_iv_get(ARGSS::ARPG::ACache::id, "@cache");
	VALUE values = rb_funcall(cache, rb_intern("values"), 0);
	for (int i = 0; i < RARRAY(values)->len; i++) {
		if (rb_funcall(rb_ary_entry(values, i), rb_intern("disposed?"), 0) == Qfalse) {
			rb_funcall(rb_ary_entry(values, i), rb_intern("dispose"), 0);
		}
	}
	rb_iv_set(ARGSS::ARPG::ACache::id, "@cache", rb_hash_new());
	return rb_funcall(rb_const_get(rb_cObject, rb_intern("GC")), rb_intern("start"), 0);
}

////////////////////////////////////////////////////////////
/// ARGSS RPG::Cache initialize
////////////////////////////////////////////////////////////
void ARGSS::ARPG::ACache::Init() {
    typedef VALUE (*rubyfunc)(...);
	id = rb_define_module_under(ARGSS::ARPG::id, "Cache");
	rb_define_singleton_method(id, "load_bitmap", (rubyfunc)argss_rpg_cache_load_bitmap, -1);
	rb_define_singleton_method(id, "animation", (rubyfunc)argss_rpg_cache_animation, 2);
	rb_define_singleton_method(id, "autotile", (rubyfunc)argss_rpg_cache_autotile, 1);
	rb_define_singleton_method(id, "battleback", (rubyfunc)argss_rpg_cache_battleback, 1);
	rb_define_singleton_method(id, "battler", (rubyfunc)argss_rpg_cache_battler, 2);
	rb_define_singleton_method(id, "character", (rubyfunc)argss_rpg_cache_character, 2);
	rb_define_singleton_method(id, "fog", (rubyfunc)argss_rpg_cache_fog, 2);
	rb_define_singleton_method(id, "gameover", (rubyfunc)argss_rpg_cache_gameover, 1);
	rb_define_singleton_method(id, "icon", (rubyfunc)argss_rpg_cache_icon, 1);
	rb_define_singleton_method(id, "panorama", (rubyfunc)argss_rpg_cache_panorama, 2);
	rb_define_singleton_method(id, "picture", (rubyfunc)argss_rpg_cache_picture, 1);
	rb_define_singleton_method(id, "tileset", (rubyfunc)argss_rpg_cache_tileset, 1);
	rb_define_singleton_method(id, "title", (rubyfunc)argss_rpg_cache_title, 1);
	rb_define_singleton_method(id, "windowskin", (rubyfunc)argss_rpg_cache_windowskin, 1);
	rb_define_singleton_method(id, "tile", (rubyfunc)argss_rpg_cache_tile, 3);
	rb_define_singleton_method(id, "clear", (rubyfunc)argss_rpg_cache_clear, 0);
	rb_iv_set(id, "@cache", rb_hash_new());
}
