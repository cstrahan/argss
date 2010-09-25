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
#include "argss/rpg/rpg.h"
#include "argss/rpg/rpg_cache.h"
#include "argss/rpg/rpg_sprite.h"
#include "argss/classes/abitmap.h"
#include "argss/classes/acolor.h"
#include "argss/classes/afont.h"
#include "argss/classes/arect.h"
#include "argss/classes/asprite.h"
#include "argss/modules/aaudio.h"
#include "argss/modules/agraphics.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::ARPG::ASprite::id;

///////////////////////////////////////////////////////////
// ARGSS RPG::Sprite instance methods
///////////////////////////////////////////////////////////
VALUE ARGSS::ARPG::ASprite::rinitialize(int argc, VALUE* argv, VALUE self) {
	if (argc > 1) raise_argn(argc, 1);
	VALUE viewport = Qnil;
	if (argc == 1) viewport = argv[0];
	rb_call_super(1, &viewport);
	rb_iv_set(self, "@_whiten_duration", INT2NUM(0));
	rb_iv_set(self, "@_appear_duration", INT2NUM(0));
	rb_iv_set(self, "@_escape_duration", INT2NUM(0));
	rb_iv_set(self, "@_collapse_duration", INT2NUM(0));
	rb_iv_set(self, "@_damage_duration", INT2NUM(0));
	rb_iv_set(self, "@_animation_duration", INT2NUM(0));
	rb_iv_set(self, "@_blink", Qfalse);
	return self;
}
VALUE ARGSS::ARPG::ASprite::rdispose(VALUE self) {
	rdispose_damage(self);
	rdispose_animation(self);
	rdispose_loop_animation(self);
	return rb_call_super(0, 0);
}
VALUE ARGSS::ARPG::ASprite::rwhiten(VALUE self) {
	ARGSS::ASprite::rblend_typeE(self, INT2NUM(0));
	rb_funcall(rb_iv_get(rb_iv_get(rb_iv_get(self, "@bitmap"), "@font"), "@color"), rb_intern("set"), 4, INT2NUM(255), INT2NUM(255), INT2NUM(255), INT2NUM(128));
	ARGSS::ASprite::ropacityE(self, INT2NUM(255));
	rb_iv_set(self, "@_whiten_duration", INT2NUM(16));
	rb_iv_set(self, "@_appear_duration", INT2NUM(0));
	rb_iv_set(self, "@_escape_duration", INT2NUM(0));
	return rb_iv_set(self, "@_collapse_duration", INT2NUM(0));
}
VALUE ARGSS::ARPG::ASprite::rappear(VALUE self) {
ARGSS::ASprite::rblend_typeE(self, INT2NUM(0));
	rb_funcall(rb_iv_get(rb_iv_get(rb_iv_get(self, "@bitmap"), "@font"), "@color"), rb_intern("set"), 4, INT2NUM(0), INT2NUM(0), INT2NUM(0), INT2NUM(0));
	ARGSS::ASprite::ropacityE(self, INT2NUM(0));
	rb_iv_set(self, "@_appear_duration", INT2NUM(16));
	rb_iv_set(self, "@_whiten_duration", INT2NUM(0));
	rb_iv_set(self, "@_escape_duration", INT2NUM(0));
	return rb_iv_set(self, "@_collapse_duration", INT2NUM(0));
}
VALUE ARGSS::ARPG::ASprite::rescape(VALUE self) {
	ARGSS::ASprite::rblend_typeE(self, INT2NUM(0));
	rb_funcall(rb_iv_get(rb_iv_get(rb_iv_get(self, "@bitmap"), "@font"), "@color"), rb_intern("set"), 4, INT2NUM(0), INT2NUM(0), INT2NUM(0), INT2NUM(0));
	ARGSS::ASprite::ropacityE(self, INT2NUM(255));
	rb_iv_set(self, "@_escape_duration", INT2NUM(32));
	rb_iv_set(self, "@_whiten_duration", INT2NUM(0));
	rb_iv_set(self, "@_appear_duration", INT2NUM(0));
	return rb_iv_set(self, "@_collapse_duration", INT2NUM(0));
}
VALUE ARGSS::ARPG::ASprite::rcollapse(VALUE self) {
	ARGSS::ASprite::rblend_typeE(self, INT2NUM(1));
	rb_funcall(rb_iv_get(rb_iv_get(rb_iv_get(self, "@bitmap"), "@font"), "@color"), rb_intern("set"), 4, INT2NUM(255), INT2NUM(64), INT2NUM(64), INT2NUM(255));
	ARGSS::ASprite::ropacityE(self, INT2NUM(255));
	rb_iv_set(self, "@_collapse_duration", INT2NUM(48));
	rb_iv_set(self, "@_whiten_duration", INT2NUM(0));
	rb_iv_set(self, "@_appear_duration", INT2NUM(0));
	return rb_iv_set(self, "@_escape_duration", INT2NUM(0));
}
VALUE ARGSS::ARPG::ASprite::rdamage(VALUE self, VALUE value, VALUE critical) {
	rdispose_damage(self);
	VALUE damage_string;
	if (rb_obj_is_kind_of(value, rb_cNumeric)) {
		damage_string = rb_obj_as_string(rb_funcall(value, rb_intern("abs"), 0));
	} else {
		damage_string = rb_obj_as_string(value);
	}
	VALUE args[2] = {INT2NUM(160), INT2NUM(48)};
	VALUE bitmap = rb_class_new_instance(2, args, ARGSS::ABitmap::id);
	VALUE bitmap_font = rb_iv_get(bitmap, "@font");
	ARGSS::AFont::rnameE(bitmap_font, rb_str_new2("Arial Black"));
	ARGSS::AFont::rsizeE(bitmap_font, INT2NUM(32));
	rb_funcall(rb_iv_get(bitmap_font, "@color"), rb_intern("set="), 3, INT2NUM(0), INT2NUM(0), INT2NUM(0));
	rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(-1), INT2NUM(13), INT2NUM(160), INT2NUM(36), damage_string, INT2NUM(1));
	rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(1), INT2NUM(13), INT2NUM(160), INT2NUM(36), damage_string, INT2NUM(1));
	rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(-1), INT2NUM(13), INT2NUM(160), INT2NUM(36), damage_string, INT2NUM(1));
	rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(1), INT2NUM(13), INT2NUM(160), INT2NUM(36), damage_string, INT2NUM(1));
	if (rb_obj_is_kind_of(value, rb_cNumeric), NUM2INT(value) < 0) {
		rb_funcall(rb_iv_get(bitmap_font, "@color"), rb_intern("set"), 4, INT2NUM(176), INT2NUM(255), INT2NUM(144), INT2NUM(255));
	} else {
		rb_funcall(rb_iv_get(bitmap_font, "@color"), rb_intern("set"), 4, INT2NUM(255), INT2NUM(255), INT2NUM(255), INT2NUM(255));
	}
	rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(0), INT2NUM(12), INT2NUM(160), INT2NUM(36), damage_string, INT2NUM(1));
	if (critical == Qtrue) {
		rb_iv_set(bitmap_font, "@size", INT2NUM(20));
		rb_funcall(rb_iv_get(bitmap_font, "@color"), rb_intern("set"), 4, INT2NUM(0), INT2NUM(0), INT2NUM(0), INT2NUM(255));
		rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(-1), INT2NUM(-1), INT2NUM(160), INT2NUM(20), rb_str_new2("CRITICAL"), INT2NUM(1));
		rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(1), INT2NUM(-1), INT2NUM(160), INT2NUM(20), rb_str_new2("CRITICAL"), INT2NUM(1));
		rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(-1), INT2NUM(1), INT2NUM(160), INT2NUM(20), rb_str_new2("CRITICAL"), INT2NUM(1));
		rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(1), INT2NUM(1), INT2NUM(160), INT2NUM(20), rb_str_new2("CRITICAL"), INT2NUM(1));
		rb_funcall(rb_iv_get(bitmap_font, "@color"), rb_intern("set"), 4, INT2NUM(255), INT2NUM(255), INT2NUM(255), INT2NUM(255));
		rb_funcall(bitmap, rb_intern("draw_text"), 6, INT2NUM(0), INT2NUM(0), INT2NUM(160), INT2NUM(20), rb_str_new2("CRITICAL"), INT2NUM(1));
	}
	VALUE viewport = rb_iv_get(self, "@viewport");
	VALUE damage_sprite = rb_class_new_instance(1, &viewport, ARGSS::ASprite::id);
	rb_funcall(damage_sprite, rb_intern("bitmap="), 1, bitmap);
	rb_funcall(damage_sprite, rb_intern("ox="), 1, INT2NUM(80));
	rb_funcall(damage_sprite, rb_intern("oy="), 1, INT2NUM(20));
	rb_funcall(damage_sprite, rb_intern("x="), 1, rb_iv_get(self, "@x"));
	rb_funcall(damage_sprite, rb_intern("y="), 1, INT2NUM(NUM2INT(rb_iv_get(self, "@y")) - NUM2INT(rb_iv_get(self, "@oy")) / 2));
	rb_funcall(damage_sprite, rb_intern("z="), 1, INT2NUM(3000));
	rb_iv_set(self, "@_damage_sprite", damage_sprite);
	return rb_iv_set(self, "@_damage_duration", INT2NUM(40));
}
VALUE ARGSS::ARPG::ASprite::ranimation(VALUE self, VALUE animation, VALUE hit) {
	rb_funcall(self, rb_intern("dispose_animation"), 0);
	rb_iv_set(self, "@_animation", animation);
	if (animation == Qnil) return Qnil;
	rb_iv_set(self, "@_animation_hit", hit);
	rb_iv_set(self, "@_animation_duration", rb_iv_get(animation, "@frame_max"));
	VALUE animation_name = rb_iv_get(animation, "@animation_name");
	VALUE animation_hue = rb_iv_get(animation, "@animation_hue");
	VALUE bitmap = rb_funcall(ARGSS::ARPG::ACache::id, rb_intern("animation"), 2, animation_name, animation_hue);
	VALUE reference_count = rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_reference_count"));
	if (rb_funcall(reference_count, rb_intern("include?"), 1, bitmap)) {
		rb_hash_aset(reference_count, bitmap, INT2NUM(NUM2INT(rb_hash_aref(reference_count, bitmap)) + 1));
	} else {
		rb_hash_aset(reference_count, bitmap, INT2NUM(1));
	}
	VALUE animation_sprites = rb_iv_set(self, "@_animation_sprites", rb_ary_new());
	if (rb_iv_get(animation, "@position") != INT2NUM(3) ||
		rb_funcall(rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_animations")), rb_intern("include?"), 1, animation)) {
		VALUE viewport = rb_iv_get(self, "@viewport");
		for (int i = 0; i < 16; i++) {
			VALUE sprite = rb_class_new_instance(1, &viewport, ARGSS::ASprite::id);
			rb_funcall(sprite, rb_intern("bitmap="), 1, bitmap);
			rb_funcall(sprite, rb_intern("visible="), 1, Qfalse);
			rb_ary_push(animation_sprites, sprite);
		}
		if (!rb_funcall(rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_animations")), rb_intern("include?"), 1, animation)) {
			rb_ary_push(rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_animations")), animation);
		}
	}
	return rb_funcall(self, rb_intern("update_animation"), 0);
}
VALUE ARGSS::ARPG::ASprite::rloop_animation(VALUE self, VALUE animation) {
	if (animation == rb_iv_get(self, "@_loop_animation")) return Qnil;
	rb_funcall(self, rb_intern("dispose_loop_animation"), 0);
	rb_iv_set(self, "@_loop_animation", animation);
	if (animation == Qnil) return Qnil;
	rb_iv_set(self, "@_loop_animation_index", INT2NUM(0));
	VALUE animation_name = rb_iv_get(animation, "@animation_name");
	VALUE animation_hue = rb_iv_get(animation, "@animation_hue");
	VALUE bitmap = rb_funcall(ARGSS::ARPG::ACache::id, rb_intern("animation"), 2, animation_name, animation_hue);
	VALUE reference_count = rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_reference_count"));
	if (rb_funcall(reference_count, rb_intern("include?"), 1, bitmap)) {
		rb_hash_aset(reference_count, bitmap, INT2NUM(NUM2INT(rb_hash_aref(reference_count, bitmap)) + 1));
	} else {
		rb_hash_aset(reference_count, bitmap, INT2NUM(1));
	}
	VALUE loop_animation_sprites = rb_iv_set(self, "@_loop_animation_sprites", rb_ary_new());
	VALUE viewport = rb_iv_get(self, "@viewport");
	for (int i = 0; i < 16; i++) {
		VALUE sprite = rb_class_new_instance(1, &viewport, ARGSS::ASprite::id);
		rb_funcall(sprite, rb_intern("bitmap="), 1, bitmap);
		rb_funcall(sprite, rb_intern("visible="), 1, Qfalse);
		rb_ary_push(loop_animation_sprites, sprite);
	}
	return rb_funcall(self, rb_intern("update_loop_animation"), 0);
}
VALUE ARGSS::ARPG::ASprite::rdispose_damage(VALUE self) {
	VALUE damage_sprite = rb_iv_get(self, "@_damage_sprite");
	if (damage_sprite != Qnil) {
		rb_funcall(rb_iv_get(damage_sprite, "@bitmap"), rb_intern("dispose"), 0);
		rb_funcall(damage_sprite, rb_intern("dispose"), 0);
		rb_iv_set(self, "@_damage_sprite", Qnil);
		rb_iv_set(self, "@_damage_duration", INT2NUM(0));
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rdispose_animation(VALUE self) {
	VALUE animation_sprites = rb_iv_get(self, "@_animation_sprites");
	if (animation_sprites != Qnil) {
		VALUE sprite = rb_ary_entry(animation_sprites, 0);
		if (sprite != Qnil) {
			VALUE bitmap = rb_iv_get(sprite, "@bitmap");
			VALUE reference_count = rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_reference_count"));
			rb_hash_aset(reference_count, bitmap, INT2NUM(NUM2INT(rb_hash_aref(reference_count, bitmap)) - 1));
			if (NUM2INT(rb_hash_aref(reference_count, bitmap)) == 0) {
				rb_funcall(bitmap, rb_intern("dispose"), 0);
			}
		}
		for (int i = 0; i < RARRAY(animation_sprites)->len; i++) {
			rb_funcall(rb_ary_entry(animation_sprites, i), rb_intern("dispose"), 0);
		}
		rb_iv_set(self, "@_animation_sprites", Qnil);
		rb_iv_set(self, "@_animation", Qnil);
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rdispose_loop_animation(VALUE self) {
	VALUE loop_animation_sprites = rb_iv_get(self, "@_loop_animation_sprites");
	if (loop_animation_sprites != Qnil) {
		VALUE sprite = rb_ary_entry(loop_animation_sprites, 0);
		if (sprite != Qnil) {
			VALUE bitmap = rb_iv_get(sprite, "@bitmap");
			VALUE reference_count = rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_reference_count"));
			rb_hash_aset(reference_count, bitmap, INT2NUM(NUM2INT(rb_hash_aref(reference_count, bitmap)) - 1));
			if (NUM2INT(rb_hash_aref(reference_count, bitmap)) == 0) {
				rb_funcall(bitmap, rb_intern("dispose"), 0);
			}
		}
		for (int i = 0; i < RARRAY(loop_animation_sprites)->len; i++) {
			rb_funcall(rb_ary_entry(loop_animation_sprites, i), rb_intern("dispose"), 0);
		}
		rb_iv_set(self, "@_loop_animation_sprites", Qnil);
		rb_iv_set(self, "@_loop_animation", Qnil);
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rblink_on(VALUE self) {
	if (rb_iv_get(self, "@_blink") == Qfalse) {
		rb_iv_set(self, "@_blink", Qtrue);
		rb_iv_set(self, "@_blink_count", INT2NUM(0));
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rblink_off(VALUE self) {
	if (rb_iv_get(self, "@_blink") == Qtrue) {
		rb_iv_set(self, "@_blink", Qfalse);
		rb_funcall(rb_iv_get(self, "@color"), rb_intern("set"), 4, INT2NUM(0), INT2NUM(0), INT2NUM(0), INT2NUM(0));
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rblinkQ(VALUE self) {
	return rb_iv_get(self, "@_blink");
}
VALUE ARGSS::ARPG::ASprite::reffectQ(VALUE self) {
	return BOOL2NUM(
		NUM2INT(rb_iv_get(self, "@_whiten_duration")) > 0 ||
		NUM2INT(rb_iv_get(self, "@_appear_duration")) > 0 ||
		NUM2INT(rb_iv_get(self, "@_escape_duration")) > 0 ||
		NUM2INT(rb_iv_get(self, "@_collapse_duration")) > 0 ||
		NUM2INT(rb_iv_get(self, "@_damage_duration")) > 0 ||
		NUM2INT(rb_iv_get(self, "@_animation_duration")) > 0
	);
}
VALUE ARGSS::ARPG::ASprite::rupdate(VALUE self) {
	rb_call_super(0, 0);
	if (NUM2INT(rb_iv_get(self, "@_whiten_duration")) > 0) {
		rb_iv_set(self, "@_whiten_duration", INT2NUM(NUM2INT(rb_iv_get(self, "@_whiten_duration")) - 1));
		rb_iv_set(rb_iv_get(self, "@color"), "@alpha", INT2NUM(128 - (16 - NUM2INT(rb_iv_get(self, "@_whiten_duration"))) * 10));
	}
	if (NUM2INT(rb_iv_get(self, "@_appear_duration")) > 0) {
		rb_iv_set(self, "@_appear_duration", INT2NUM(NUM2INT(rb_iv_get(self, "@_appear_duration")) - 1));
		rb_iv_set(self, "@opacity", INT2NUM(128 - (16 - NUM2INT(rb_iv_get(self, "@_appear_duration"))) * 16));
	}
	if (NUM2INT(rb_iv_get(self, "@_escape_duration")) > 0) {
		rb_iv_set(self, "@_escape_duration", INT2NUM(NUM2INT(rb_iv_get(self, "@_escape_duration")) - 1));
		rb_iv_set(self, "@opacity", INT2NUM(256 - (32 - NUM2INT(rb_iv_get(self, "@_escape_duration"))) * 10));
	}
	if (NUM2INT(rb_iv_get(self, "@_collapse_duration")) > 0) {
		rb_iv_set(self, "@_collapse_duration", INT2NUM(NUM2INT(rb_iv_get(self, "@_collapse_duration")) - 1));
		rb_iv_set(self, "@opacity", INT2NUM(256 - (48 - NUM2INT(rb_iv_get(self, "@_collapse_duration"))) * 6));
	}
	if (NUM2INT(rb_iv_get(self, "@_damage_duration")) > 0) {
		int val_damage_duration = NUM2INT(rb_iv_get(self, "@_damage_duration"));
		rb_iv_set(self, "@_damage_duration", INT2NUM(val_damage_duration - 1));
		VALUE damage_sprite = rb_iv_get(self, "@_damage_sprite");
		switch (val_damage_duration) {
		case 38: case 39:
			rb_funcall(damage_sprite, rb_intern("y="), 1, INT2NUM(NUM2INT(rb_iv_get(damage_sprite, "@y")) - 4));
			break;
		case 36: case 37:
			rb_funcall(damage_sprite, rb_intern("y="), 1, INT2NUM(NUM2INT(rb_iv_get(damage_sprite, "@y")) - 2));
			break;
		case 34: case 35:
			rb_funcall(damage_sprite, rb_intern("y="), 1, INT2NUM(NUM2INT(rb_iv_get(damage_sprite, "@y")) + 2));
			break;
		case 28: case 29: case 30: case 31: case 32: case 33:
			rb_funcall(damage_sprite, rb_intern("y="), 1, INT2NUM(NUM2INT(rb_iv_get(damage_sprite, "@y")) + 4));
		}
		rb_iv_set(self, "@opacity", INT2NUM(256 - (12 - val_damage_duration) * 32));
		if (val_damage_duration == 0) {
			rb_funcall(self, rb_intern("dispose_damage"), 0);
		}
	}
	if (rb_iv_get(self, "@_animation") != Qnil && NUM2INT(rb_funcall(ARGSS::AGraphics::id, rb_intern("frame_count"), 0)) % 2 == 0) {
		rb_iv_set(self, "@_animation_duration", INT2NUM(NUM2INT(rb_iv_get(self, "@_animation_duration")) - 1));
		rb_funcall(self, rb_intern("update_animation"), 0);
	}
	if (rb_iv_get(self, "@_loop_animation") != Qnil && NUM2INT(rb_funcall(ARGSS::AGraphics::id, rb_intern("frame_count"), 0)) % 2 == 0) {
		rb_funcall(self, rb_intern("update_loop_animation"), 0);
		int val_frame_max = NUM2INT(rb_iv_get(rb_iv_get(self, "@_loop_animation"), "@frame_max"));
		rb_iv_set(self, "@_loop_animation_index", INT2NUM((NUM2INT(rb_iv_get(self, "@_loop_animation_index")) + 1) % val_frame_max));
	}
	if (rb_iv_get(self, "@_blink") == Qtrue) {
		int val_blink_count = (NUM2INT(rb_iv_get(self, "@_blink_count")) + 1) % 32;
		rb_iv_set(self, "@_blink_count", INT2NUM(val_blink_count));
		int alpha;
		if (val_blink_count < 16) {
			alpha = (16 - val_blink_count) * 6;
		} else {
			alpha = (val_blink_count- 16) * 6;
		}
		rb_funcall(rb_iv_get(self, "@color"), rb_intern("set"), 4, INT2NUM(255), INT2NUM(255), INT2NUM(255), INT2NUM(alpha));
	}
	return rb_ary_clear(rb_cvar_get(ARGSS::ARPG::ASprite::id, rb_intern("@@_animations")));
}
VALUE ARGSS::ARPG::ASprite::rupdate_animation(VALUE self) {
	int val_animation_duration = NUM2INT(rb_iv_get(self, "@_animation_duration"));
	if (val_animation_duration > 0) {
		VALUE animation = rb_iv_get(self, "@_animation");
		VALUE frame_index = INT2NUM(NUM2INT(rb_iv_get(animation, "@frame_max")) - val_animation_duration);
		VALUE cell_data = rb_iv_get(rb_ary_entry(rb_iv_get(animation, "@frames"), NUM2INT(frame_index)), "@cell_data");
		VALUE position = rb_iv_get(animation, "@position");
		rb_funcall(self, rb_intern("animation_set_sprites"), 3, rb_iv_get(self, "@_animation_sprites"), cell_data, position);
		VALUE timings = rb_iv_get(rb_iv_get(self, "@_animation"), "@timings");
		for (int i = 0; i < RARRAY(timings)->len; i++) {
			VALUE timing = rb_ary_entry(timings, i);
			if (rb_iv_get(timing, "@frame") == frame_index) {
				rb_funcall(self, rb_intern("animation_process_timing"), 2, timing, rb_iv_get(self, "@_animation_hit"));
			}
		}
	} else {
		rb_funcall(self, rb_intern("dispose_animation"), 0);
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rupdate_loop_animation(VALUE self) {
	VALUE loop_animation = rb_iv_get(self, "@_loop_animation");
	VALUE frame_index = rb_iv_get(self, "@_loop_animation_index");
	VALUE cell_data = rb_iv_get(rb_ary_entry(rb_iv_get(loop_animation, "@frames"), NUM2INT(frame_index)), "@cell_data");
	VALUE position = rb_iv_get(loop_animation, "@position");
	rb_funcall(self, rb_intern("animation_set_sprites"), 3, rb_iv_get(self, "@_loop_animation_sprites"), cell_data, position);
	VALUE timings = rb_iv_get(loop_animation, "@timings");
	for (int i = 0; i < RARRAY(timings)->len; i++) {
		VALUE timing = rb_ary_entry(timings, i);
		if (rb_iv_get(timing, "@frame") == frame_index) {
			rb_funcall(self, rb_intern("animation_process_timing"), 2, timing, rb_iv_get(self, "@_animation_hit"));
		}
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::ranimation_set_sprites(VALUE self, VALUE sprites, VALUE cell_data, VALUE position) {
	for (int i = 0; i < 16; i++) {
		VALUE sprite = rb_ary_entry(sprites, i);
		VALUE cell_table_data = rb_iv_get(cell_data, "@data");
		int cell_table_xsize = NUM2INT(rb_iv_get(cell_data, "@xsize"));
		VALUE pattern = rb_ary_entry(cell_table_data, i);
		if (sprite == Qnil || pattern == Qnil || pattern == INT2NUM(-1)) {
			if (sprite != Qnil) {
				rb_iv_set(sprite, "@visible", Qfalse);
			}
			continue;
		}
		rb_iv_set(sprite, "@visible", Qtrue);
		int val_pattern = NUM2INT(pattern);
		rb_funcall(rb_iv_get(sprite, "@src_rect"), rb_intern("set"), 4, INT2NUM((val_pattern % 5) * 192), INT2NUM(val_pattern / 5 * 192), INT2NUM(192), INT2NUM(192));
		if (position == INT2NUM(3)) {
			VALUE viewport = rb_iv_get(self, "@viewport");
			VALUE viewport_rect = rb_funcall(viewport, rb_intern("rect"), 0);
			if (viewport != Qnil) {
				rb_funcall(sprite, rb_intern("x="), 1, INT2NUM(NUM2INT(rb_iv_get(viewport_rect, "@width")) / 2));
				rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(NUM2INT(rb_iv_get(viewport_rect, "@height")) - 160));
			} else {
				rb_funcall(sprite, rb_intern("x="), 1, INT2NUM(320));
				rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(240));
			}
		} else {
			VALUE src_rect = rb_iv_get(self, "@src_rect");
			int val_x = NUM2INT(rb_iv_get(self, "@x"));
			int val_y = NUM2INT(rb_iv_get(self, "@y"));
			int val_ox = NUM2INT(rb_iv_get(self, "@ox"));
			int val_oy = NUM2INT(rb_iv_get(self, "@oy"));
			int val_rect_w = NUM2INT(rb_iv_get(src_rect, "@width"));
			int val_rect_h = NUM2INT(rb_iv_get(src_rect, "@height"));
			rb_funcall(sprite, rb_intern("x="), 1, INT2NUM(val_x - val_ox + val_rect_w / 2));
			val_y = val_y - val_oy + val_rect_h / 2;
			rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(val_y));
			if (position == INT2NUM(0)) {
				rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(val_y - val_rect_h / 4));
			} else if (position == INT2NUM(2)) {
				rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(val_y + val_rect_h / 4));
			}
		}
		int val_x = NUM2INT(rb_iv_get(sprite, "@x"));
		int val_y = NUM2INT(rb_iv_get(sprite, "@y"));
		rb_funcall(sprite, rb_intern("x="), 1, INT2NUM(val_x + rb_ary_entry(cell_table_data, i + 1 * cell_table_xsize)));
		rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(val_y + rb_ary_entry(cell_table_data, i + 2 * cell_table_xsize)));
		rb_funcall(sprite, rb_intern("z="), 1, INT2NUM(2000));
		rb_funcall(sprite, rb_intern("ox="), 1, INT2NUM(96));
		rb_funcall(sprite, rb_intern("oy="), 1, INT2NUM(96));
		rb_funcall(sprite, rb_intern("zoom_x="), 1, rb_float_new(rb_ary_entry(cell_table_data, i + 3 * cell_table_xsize) / 100.0f));
		rb_funcall(sprite, rb_intern("zoom_y="), 1, rb_float_new(rb_ary_entry(cell_table_data, i + 3 * cell_table_xsize) / 100.0f));
		rb_funcall(sprite, rb_intern("angle="), 1, INT2NUM(rb_ary_entry(cell_table_data, i + 4 * cell_table_xsize)));
		rb_funcall(sprite, rb_intern("mirror="), 1, BOOL2NUM(rb_ary_entry(cell_table_data, i + 5 * cell_table_xsize) == 1));
		rb_funcall(sprite, rb_intern("opacity="), 1, rb_float_new(rb_ary_entry(cell_table_data, i + 6 * cell_table_xsize) * rb_iv_get(self, "@opacity") / 255.0f));
		rb_funcall(sprite, rb_intern("blend_type="), 1, INT2NUM(rb_ary_entry(cell_table_data, i + 7 * cell_table_xsize)));
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::ranimation_process_timing(VALUE self, VALUE timing, VALUE hit) {
	int val_condition = NUM2INT(rb_iv_get(timing, "@condition"));
	if ((val_condition == 0) ||
		(val_condition == 1 && hit == Qtrue) ||
		(val_condition == 2 && hit == Qfalse)) {
		VALUE se = rb_iv_get(timing, "@se");
		if (RSTRING(rb_iv_get(se, "@name"))->len > 0) {
			VALUE name = rb_str_new2("Audio/SE/");
			rb_str_concat(name, rb_iv_get(se, "@name"));
			rb_funcall(ARGSS::AAudio::id, rb_intern("se_play"), 3, name, rb_iv_get(se, "@volume"), rb_iv_get(se, "@pitch"));
		}
		VALUE flash_color = rb_iv_get(timing, "@flash_color");
		int val_flash_duration = NUM2INT(rb_iv_get(timing, "@flash_duration"));
		VALUE viewport = rb_iv_get(self, "@viewport");
		switch (NUM2INT(rb_iv_get(timing, "@flash_scope"))) {
		case 1:
			rb_funcall(self, rb_intern("flash"), 2, flash_color, INT2NUM(val_flash_duration * 2));
			break;
		case 2:
			if (viewport != Qnil) {
				rb_funcall(viewport, rb_intern("flash"), 2, flash_color, INT2NUM(val_flash_duration * 2));
			}
			break;
		case 3:
			rb_funcall(self, rb_intern("flash"), 2, Qnil, INT2NUM(val_flash_duration * 2));
		}
	}
	return Qnil;
}
VALUE ARGSS::ARPG::ASprite::rxE(VALUE self, VALUE x) {
	int sx = NUM2INT(x) - NUM2INT(rb_iv_get(self, "@x"));
	if (sx != 0) {
		VALUE animation_sprites = rb_iv_get(self, "@_animation_sprites");
		if (animation_sprites != Qnil) {
			for (int i = 0; i < 16; i++) {
				VALUE sprite = rb_ary_entry(animation_sprites, i);
				int val_x = NUM2INT(rb_iv_get(self, "@x"));
				rb_funcall(sprite, rb_intern("x="), 1, INT2NUM(val_x + sx));
			}
		}
		VALUE loop_animation_sprites = rb_iv_get(self, "@_loop_animation_sprites");
		if (loop_animation_sprites != Qnil) {
			for (int i = 0; i < 16; i++) {
				VALUE sprite = rb_ary_entry(loop_animation_sprites, i);
				int val_x = NUM2INT(rb_iv_get(self, "@x"));
				rb_funcall(sprite, rb_intern("x="), 1, INT2NUM(val_x + sx));
			}
		}
	}
	return rb_call_super(1, &x);
}
VALUE ARGSS::ARPG::ASprite::ryE(VALUE self, VALUE y) {
	int sy = NUM2INT(y) - NUM2INT(rb_iv_get(self, "@y"));
	if (sy != 0) {
		VALUE animation_sprites = rb_iv_get(self, "@_animation_sprites");
		if (animation_sprites != Qnil) {
			for (int i = 0; i < 16; i++) {
				VALUE sprite = rb_ary_entry(animation_sprites, i);
				int val_y = NUM2INT(rb_iv_get(self, "@y"));
				rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(val_y + sy));
			}
		}
		VALUE loop_animation_sprites = rb_iv_get(self, "@_loop_animation_sprites");
		if (loop_animation_sprites != Qnil) {
			for (int i = 0; i < 16; i++) {
				VALUE sprite = rb_ary_entry(loop_animation_sprites, i);
				int val_y = NUM2INT(rb_iv_get(self, "@y"));
				rb_funcall(sprite, rb_intern("y="), 1, INT2NUM(val_y + sy));
			}
		}
	}
	return rb_call_super(1, &y);
}

///////////////////////////////////////////////////////////
// ARGSS RPG::Sprite initialize
///////////////////////////////////////////////////////////
void ARGSS::ARPG::ASprite::Init() {
	id = rb_define_class_under(ARGSS::ARPG::id, "Sprite", ARGSS::ASprite::id);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, -1);
	rb_define_method(id, "dispose", (rubyfunc)rdispose, 0);
	rb_define_method(id, "whiten", (rubyfunc)rwhiten, 0);
	rb_define_method(id, "appear", (rubyfunc)rappear, 0);
	rb_define_method(id, "escape", (rubyfunc)rescape, 0);
	rb_define_method(id, "collapse", (rubyfunc)rcollapse, 0);
	rb_define_method(id, "damage", (rubyfunc)rdamage, 2);
	rb_define_method(id, "animation", (rubyfunc)ranimation, 2);
	rb_define_method(id, "loop_animation", (rubyfunc)rloop_animation, 1);
	rb_define_method(id, "dispose_damage", (rubyfunc)rdispose_damage, 0);
	rb_define_method(id, "dispose_animation", (rubyfunc)rdispose_animation, 0);
	rb_define_method(id, "dispose_loop_animation", (rubyfunc)rdispose_loop_animation, 0);
	rb_define_method(id, "blink_on", (rubyfunc)rblink_on, 0);
	rb_define_method(id, "blink_off", (rubyfunc)rblink_off, 0);
	rb_define_method(id, "blink?", (rubyfunc)rblinkQ, 0);
	rb_define_method(id, "effect?", (rubyfunc)reffectQ, 0);
	rb_define_method(id, "update", (rubyfunc)rupdate, 0);
	rb_define_method(id, "update_animation", (rubyfunc)rupdate_animation, 0);
	rb_define_method(id, "update_loop_animation", (rubyfunc)rupdate_loop_animation, 0);
	rb_define_method(id, "animation_set_sprites", (rubyfunc)ranimation_set_sprites, 3);
	rb_define_method(id, "animation_process_timing", (rubyfunc)ranimation_process_timing, 2);
	rb_define_method(id, "x=", (rubyfunc)rxE, 1);
	rb_define_method(id, "y=", (rubyfunc)ryE, 1);

	rb_define_class_variable(id, "@@_animations", rb_ary_new());
	rb_define_class_variable(id, "@@_reference_count", rb_hash_new());
}
