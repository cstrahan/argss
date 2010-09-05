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
#include "argss_rpg.h"
#include "argss_table.h"
#include "argss_color.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ARPG::id;
VALUE ARGSS::ARPG::Map_id;
VALUE ARGSS::ARPG::MapInfo_id;
VALUE ARGSS::ARPG::Event_id;
VALUE ARGSS::ARPG::EventPage_id;
VALUE ARGSS::ARPG::EventPageCondition_id;
VALUE ARGSS::ARPG::EventPageGraphic_id;
VALUE ARGSS::ARPG::EventCommand_id;
VALUE ARGSS::ARPG::MoveRoute_id;
VALUE ARGSS::ARPG::MoveCommand_id;
VALUE ARGSS::ARPG::Actor_id;
VALUE ARGSS::ARPG::Class_id;
VALUE ARGSS::ARPG::ClassLearning_id;
VALUE ARGSS::ARPG::Skill_id;
VALUE ARGSS::ARPG::Item_id;
VALUE ARGSS::ARPG::Weapon_id;
VALUE ARGSS::ARPG::Armor_id;
VALUE ARGSS::ARPG::Enemy_id;
VALUE ARGSS::ARPG::EnemyAction_id;
VALUE ARGSS::ARPG::Troop_id;
VALUE ARGSS::ARPG::TroopMember_id;
VALUE ARGSS::ARPG::TroopPage_id;
VALUE ARGSS::ARPG::TroopPageCondition_id;
VALUE ARGSS::ARPG::State_id;
VALUE ARGSS::ARPG::Animation_id;
VALUE ARGSS::ARPG::AnimationFrame_id;
VALUE ARGSS::ARPG::AnimationTiming_id;
VALUE ARGSS::ARPG::Tileset_id;
VALUE ARGSS::ARPG::CommonEvent_id;
VALUE ARGSS::ARPG::System_id;
VALUE ARGSS::ARPG::SystemWords_id;
VALUE ARGSS::ARPG::SystemTestBattler_id;
VALUE ARGSS::ARPG::AudioFile_id;

////////////////////////////////////////////////////////////
/// ARGSS RPG ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::ARPG::rmap_initialize(VALUE self, VALUE width, VALUE height) {
	rb_iv_set(self, "@tileset_id", INT2NUM(1));
	rb_iv_set(self, "@width", width);
	rb_iv_set(self, "@height", height);
	rb_iv_set(self, "@autoplay_bgm", Qfalse);
	rb_iv_set(self, "@bgm", rb_class_new_instance(0, 0, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@autoplay_bgs", Qfalse);
	VALUE args[3] = {rb_str_new2(""), INT2NUM(80)};
	rb_iv_set(self, "@bgs", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@encounter_list", rb_ary_new());
	rb_iv_set(self, "@encounter_step", INT2NUM(30));
	rb_iv_set(self, "@data", ARGSS::ATable::New(width, height, INT2NUM(3)));
	rb_iv_set(self, "@events", rb_hash_new());
	return self;
}
VALUE ARGSS::ARPG::rmapinfo_initialize(VALUE self) {
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@parent_id", INT2NUM(0));
	rb_iv_set(self, "@order", INT2NUM(0));
	rb_iv_set(self, "@expanded", Qfalse);
	rb_iv_set(self, "@scroll_x", INT2NUM(0));
	rb_iv_set(self, "@scroll_y", INT2NUM(0));
	return self;
}
VALUE ARGSS::ARPG::revent_initialize(VALUE self, VALUE x, VALUE y) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@x", x);
	rb_iv_set(self, "@y", y);
	rb_iv_set(self, "@pages", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::EventPage_id)));
	return self;
}
VALUE ARGSS::ARPG::reventpage_initialize(VALUE self) {
	rb_iv_set(self, "@condition", rb_class_new_instance(0, 0, ARGSS::ARPG::EventPageCondition_id));
	rb_iv_set(self, "@graphic", rb_class_new_instance(0, 0, ARGSS::ARPG::EventPageGraphic_id));
	rb_iv_set(self, "@move_type", INT2NUM(0));
	rb_iv_set(self, "@move_speed", INT2NUM(3));
	rb_iv_set(self, "@move_frequency", INT2NUM(3));
	rb_iv_set(self, "@move_route", rb_class_new_instance(0, 0, ARGSS::ARPG::MoveRoute_id));
	rb_iv_set(self, "@walk_anime", Qtrue);
	rb_iv_set(self, "@step_anime", Qfalse);
	rb_iv_set(self, "@direction_fix", Qfalse);
	rb_iv_set(self, "@through", Qfalse);
	rb_iv_set(self, "@always_on_top", Qfalse);
	rb_iv_set(self, "@trigger", INT2NUM(0));
	rb_iv_set(self, "@list", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::EventCommand_id)));
	return self;
}
VALUE ARGSS::ARPG::reventpagecondition_initialize(VALUE self) {
	rb_iv_set(self, "@switch1_valid", Qfalse);
	rb_iv_set(self, "@switch2_valid", Qfalse);
	rb_iv_set(self, "@variable_valid", Qfalse);
	rb_iv_set(self, "@self_switch_valid", Qfalse);
	rb_iv_set(self, "@switch1_id", INT2NUM(1));
	rb_iv_set(self, "@switch2_id", INT2NUM(1));
	rb_iv_set(self, "@variable_id", INT2NUM(1));
	rb_iv_set(self, "@variable_value", INT2NUM(0));
	rb_iv_set(self, "@self_switch_ch", rb_str_new("A", 1));
	return self;
}
VALUE ARGSS::ARPG::reventpagegraphic_initialize(VALUE self) {
	rb_iv_set(self, "@tile_id", INT2NUM(0));
	rb_iv_set(self, "@character_name", rb_str_new2(""));
	rb_iv_set(self, "@character_hue", INT2NUM(0));
	rb_iv_set(self, "@direction", INT2NUM(2));
	rb_iv_set(self, "@pattern", INT2NUM(0));
	rb_iv_set(self, "@opacity", INT2NUM(255));
	rb_iv_set(self, "@blend_type", INT2NUM(0));
	return self;
}
VALUE ARGSS::ARPG::reventcommand_initialize(int argc, VALUE* argv, VALUE self) {
	if (argc > 3) raise_argn(argc, 3);
	rb_iv_set(self, "@code", argc < 1 ? INT2NUM(0) : argv[0]);
	rb_iv_set(self, "@indent", argc < 2 ? INT2NUM(0) : argv[1]);
	rb_iv_set(self, "@parameters", argc < 3 ? rb_ary_new() : argv[2]);
	return self;
}
VALUE ARGSS::ARPG::rmoveroute_initialize(VALUE self) {
	rb_iv_set(self, "@repeat", Qtrue);
	rb_iv_set(self, "@skippable", Qfalse);
	rb_iv_set(self, "@list", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::MoveCommand_id)));
	return self;
}
VALUE ARGSS::ARPG::rmovecommand_initialize(int argc, VALUE* argv, VALUE self) {
	if (argc > 2) raise_argn(argc, 2);
	rb_iv_set(self, "@code", argc < 1 ? INT2NUM(0) : argv[0]);
	rb_iv_set(self, "@parameters", argc < 2 ? rb_ary_new() : argv[1]);
	return self;
}
VALUE ARGSS::ARPG::ractor_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@class_id", INT2NUM(1));
	rb_iv_set(self, "@initial_level", INT2NUM(1));
	rb_iv_set(self, "@final_level", INT2NUM(99));
	rb_iv_set(self, "@exp_basis", INT2NUM(30));
	rb_iv_set(self, "@exp_inflation", INT2NUM(30));
	rb_iv_set(self, "@character_name", rb_str_new2(""));
	rb_iv_set(self, "@character_hue", INT2NUM(0));
	rb_iv_set(self, "@battler_name", rb_str_new2(""));
	rb_iv_set(self, "@battler_hue", INT2NUM(0));
	VALUE table = ARGSS::ATable::New(INT2NUM(6), INT2NUM(100));
	VALUE table_data = rb_ary_new();
	for (int i = 1; i < 100; i++) {
		rb_ary_push(table_data, INT2NUM(500 + i * 50));
		rb_ary_push(table_data, INT2NUM(500 + i * 50));
		rb_ary_push(table_data, INT2NUM(50 + i * 5));
		rb_ary_push(table_data, INT2NUM(50 + i * 5));
		rb_ary_push(table_data, INT2NUM(50 + i * 5));
		rb_ary_push(table_data, INT2NUM(50 + i * 5));
	}
	rb_iv_set(table, "@data", table_data);
	rb_iv_set(self, "@parameters", table);
	rb_iv_set(self, "@weapon_id", INT2NUM(0));
	rb_iv_set(self, "@armor1_id", INT2NUM(0));
	rb_iv_set(self, "@armor2_id", INT2NUM(0));
	rb_iv_set(self, "@armor3_id", INT2NUM(0));
	rb_iv_set(self, "@armor4_id", INT2NUM(0));
	rb_iv_set(self, "@weapon_fix", Qfalse);
	rb_iv_set(self, "@armor1_fix", Qfalse);
	rb_iv_set(self, "@armor2_fix", Qfalse);
	rb_iv_set(self, "@armor3_fix", Qfalse);
	rb_iv_set(self, "@armor4_fix", Qfalse);
	return self;
}
VALUE ARGSS::ARPG::rclass_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@position", INT2NUM(0));
	rb_iv_set(self, "@weapon_set", rb_ary_new());
	rb_iv_set(self, "@armor_set", rb_ary_new());
	rb_iv_set(self, "@element_ranks", ARGSS::ATable::New(1));
	rb_iv_set(self, "@state_ranks", ARGSS::ATable::New(1));
	rb_iv_set(self, "@learnings", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::rclasslearning_initialize(VALUE self) {
	rb_iv_set(self, "@level", INT2NUM(1));
	rb_iv_set(self, "@skill_id", INT2NUM(1));
	return self;
}
VALUE ARGSS::ARPG::rskill_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@icon_name", rb_str_new2(""));
	rb_iv_set(self, "@description", rb_str_new2(""));
	rb_iv_set(self, "@scope", INT2NUM(0));
	rb_iv_set(self, "@occasion", INT2NUM(1));
	rb_iv_set(self, "@animation1_id", INT2NUM(0));
	rb_iv_set(self, "@animation2_id", INT2NUM(0));
	VALUE args[2] = {rb_str_new2(""), INT2NUM(80)};
	rb_iv_set(self, "@menu_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@common_event_id", INT2NUM(0));
	rb_iv_set(self, "@sp_cost", INT2NUM(0));
	rb_iv_set(self, "@power", INT2NUM(0));
	rb_iv_set(self, "@atk_f", INT2NUM(0));
	rb_iv_set(self, "@eva_f", INT2NUM(0));
	rb_iv_set(self, "@str_f", INT2NUM(0));
	rb_iv_set(self, "@dex_f", INT2NUM(0));
	rb_iv_set(self, "@agi_f", INT2NUM(0));
	rb_iv_set(self, "@int_f", INT2NUM(100));
	rb_iv_set(self, "@hit", INT2NUM(100));
	rb_iv_set(self, "@pdef_f", INT2NUM(0));
	rb_iv_set(self, "@mdef_f", INT2NUM(100));
	rb_iv_set(self, "@variance", INT2NUM(15));
	rb_iv_set(self, "@element_set", rb_ary_new());
	rb_iv_set(self, "@plus_state_set", rb_ary_new());
	rb_iv_set(self, "@minus_state_set", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::ritem_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@icon_name", rb_str_new2(""));
	rb_iv_set(self, "@description", rb_str_new2(""));
	rb_iv_set(self, "@scope", INT2NUM(0));
	rb_iv_set(self, "@occasion", INT2NUM(0));
	rb_iv_set(self, "@animation1_id", INT2NUM(0));
	rb_iv_set(self, "@animation2_id", INT2NUM(0));
	VALUE args[2] = {rb_str_new2(""), INT2NUM(80)};
	rb_iv_set(self, "@menu_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@common_event_id", INT2NUM(0));
	rb_iv_set(self, "@price", INT2NUM(0));
	rb_iv_set(self, "@consumable", Qtrue);
	rb_iv_set(self, "@parameter_type", INT2NUM(0));
	rb_iv_set(self, "@parameter_points", INT2NUM(0));
	rb_iv_set(self, "@recover_hp_rate", INT2NUM(0));
	rb_iv_set(self, "@recover_hp", INT2NUM(0));
	rb_iv_set(self, "@recover_sp_rate", INT2NUM(0));
	rb_iv_set(self, "@recover_sp", INT2NUM(0));
	rb_iv_set(self, "@hit", INT2NUM(100));
	rb_iv_set(self, "@pdef_f", INT2NUM(0));
	rb_iv_set(self, "@mdef_f", INT2NUM(0));
	rb_iv_set(self, "@variance", INT2NUM(0));
	rb_iv_set(self, "@element_set", rb_ary_new());
	rb_iv_set(self, "@plus_state_set", rb_ary_new());
	rb_iv_set(self, "@minus_state_set", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::rweapon_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@icon_name", rb_str_new2(""));
	rb_iv_set(self, "@description", rb_str_new2(""));
	rb_iv_set(self, "@animation1_id", INT2NUM(0));
	rb_iv_set(self, "@animation2_id", INT2NUM(0));
	rb_iv_set(self, "@price", INT2NUM(0));
	rb_iv_set(self, "@atk", INT2NUM(0));
	rb_iv_set(self, "@pdef", INT2NUM(0));
	rb_iv_set(self, "@mdef", INT2NUM(0));
	rb_iv_set(self, "@str_plus", INT2NUM(0));
	rb_iv_set(self, "@dex_plus", INT2NUM(0));
	rb_iv_set(self, "@agi_plus", INT2NUM(0));
	rb_iv_set(self, "@int_plus", INT2NUM(0));
	rb_iv_set(self, "@element_set", rb_ary_new());
	rb_iv_set(self, "@plus_state_set", rb_ary_new());
	rb_iv_set(self, "@minus_state_set", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::rarmor_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@icon_name", rb_str_new2(""));
	rb_iv_set(self, "@description", rb_str_new2(""));
	rb_iv_set(self, "@kind", INT2NUM(0));
	rb_iv_set(self, "@auto_state_id", INT2NUM(0));
	rb_iv_set(self, "@price", INT2NUM(0));
	rb_iv_set(self, "@pdef", INT2NUM(0));
	rb_iv_set(self, "@mdef", INT2NUM(0));
	rb_iv_set(self, "@eva", INT2NUM(0));
	rb_iv_set(self, "@str_plus", INT2NUM(0));
	rb_iv_set(self, "@dex_plus", INT2NUM(0));
	rb_iv_set(self, "@agi_plus", INT2NUM(0));
	rb_iv_set(self, "@int_plus", INT2NUM(0));
	rb_iv_set(self, "@guard_element_set", rb_ary_new());
	rb_iv_set(self, "@guard_state_set", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::renemy_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@battler_name", rb_str_new2(""));
	rb_iv_set(self, "@battler_hue", INT2NUM(0));
	rb_iv_set(self, "@maxhp", INT2NUM(500));
	rb_iv_set(self, "@maxsp", INT2NUM(500));
	rb_iv_set(self, "@str", INT2NUM(50));
	rb_iv_set(self, "@dex", INT2NUM(50));
	rb_iv_set(self, "@agi", INT2NUM(50));
	rb_iv_set(self, "@int", INT2NUM(50));
	rb_iv_set(self, "@atk", INT2NUM(100));
	rb_iv_set(self, "@pdef", INT2NUM(100));
	rb_iv_set(self, "@mdef", INT2NUM(100));
	rb_iv_set(self, "@eva", INT2NUM(0));
	rb_iv_set(self, "@animation1_id", INT2NUM(0));
	rb_iv_set(self, "@animation2_id", INT2NUM(0));
	rb_iv_set(self, "@element_ranks", ARGSS::ATable::New(1));
	rb_iv_set(self, "@state_ranks", ARGSS::ATable::New(1));
	rb_iv_set(self, "@actions", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::EnemyAction_id)));
	rb_iv_set(self, "@exp", INT2NUM(0));
	rb_iv_set(self, "@gold", INT2NUM(0));
	rb_iv_set(self, "@item_id", INT2NUM(0));
	rb_iv_set(self, "@weapon_id", INT2NUM(0));
	rb_iv_set(self, "@armor_id", INT2NUM(0));
	rb_iv_set(self, "@treasure_prob", INT2NUM(100));
	return self;
}
VALUE ARGSS::ARPG::renemyaction_initialize(VALUE self) {
	rb_iv_set(self, "@kind", INT2NUM(0));
	rb_iv_set(self, "@basic", INT2NUM(0));
	rb_iv_set(self, "@skill_id", INT2NUM(1));
	rb_iv_set(self, "@condition_turn_a", INT2NUM(0));
	rb_iv_set(self, "@condition_turn_b", INT2NUM(1));
	rb_iv_set(self, "@condition_hp", INT2NUM(100));
	rb_iv_set(self, "@condition_level", INT2NUM(1));
	rb_iv_set(self, "@condition_switch_id", INT2NUM(0));
	rb_iv_set(self, "@rating", INT2NUM(5));
	return self;
}
VALUE ARGSS::ARPG::rtroop_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@members", rb_ary_new());
	rb_iv_set(self, "@pages", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::TroopPage_id)));
	return self;
}
VALUE ARGSS::ARPG::rtroopmember_initialize(VALUE self) {
	rb_iv_set(self, "@enemy_id", INT2NUM(1));
	rb_iv_set(self, "@x", INT2NUM(0));
	rb_iv_set(self, "@y", INT2NUM(0));
	rb_iv_set(self, "@hidden", Qfalse);
	rb_iv_set(self, "@immortal", Qfalse);
	return self;
}
VALUE ARGSS::ARPG::rtrooppage_initialize(VALUE self) {
	rb_iv_set(self, "@condition", rb_class_new_instance(0, 0, ARGSS::ARPG::TroopPageCondition_id));
	rb_iv_set(self, "@span", INT2NUM(0));
	rb_iv_set(self, "@list", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::EventCommand_id)));
	return self;
}
VALUE ARGSS::ARPG::rtrooppagecondition_initialize(VALUE self) {
	rb_iv_set(self, "@turn_valid", Qfalse);
	rb_iv_set(self, "@enemy_valid", Qfalse);
	rb_iv_set(self, "@actor_valid", Qfalse);
	rb_iv_set(self, "@switch_valid", Qfalse);
	rb_iv_set(self, "@turn_a", INT2NUM(0));
	rb_iv_set(self, "@turn_b", INT2NUM(0));
	rb_iv_set(self, "@enemy_index", INT2NUM(0));
	rb_iv_set(self, "@enemy_hp", INT2NUM(50));
	rb_iv_set(self, "@actor_id", INT2NUM(1));
	rb_iv_set(self, "@actor_hp", INT2NUM(50));
	rb_iv_set(self, "@switch_id", INT2NUM(1));
	return self;
}
VALUE ARGSS::ARPG::rstate_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@animation_id", INT2NUM(0));
	rb_iv_set(self, "@restriction", INT2NUM(0));
	rb_iv_set(self, "@nonresistance", Qfalse);
	rb_iv_set(self, "@zero_hp", Qfalse);
	rb_iv_set(self, "@cant_get_exp", Qfalse);
	rb_iv_set(self, "@cant_evade", Qfalse);
	rb_iv_set(self, "@slip_damage", Qfalse);
	rb_iv_set(self, "@rating", INT2NUM(5));
	rb_iv_set(self, "@hit_rate", INT2NUM(100));
	rb_iv_set(self, "@maxhp_rate", INT2NUM(100));
	rb_iv_set(self, "@maxsp_rate", INT2NUM(100));
	rb_iv_set(self, "@str_rate", INT2NUM(100));
	rb_iv_set(self, "@dex_rate", INT2NUM(100));
	rb_iv_set(self, "@agi_rate", INT2NUM(100));
	rb_iv_set(self, "@int_rate", INT2NUM(100));
	rb_iv_set(self, "@atk_rate", INT2NUM(100));
	rb_iv_set(self, "@pdef_rate", INT2NUM(100));
	rb_iv_set(self, "@mdef_rate", INT2NUM(100));
	rb_iv_set(self, "@eva", INT2NUM(0));
	rb_iv_set(self, "@battle_only", Qtrue);
	rb_iv_set(self, "@hold_turn", INT2NUM(0));
	rb_iv_set(self, "@auto_release_prob", INT2NUM(0));
	rb_iv_set(self, "@shock_release_prob", INT2NUM(0));
	rb_iv_set(self, "@guard_element_set", rb_ary_new());
	rb_iv_set(self, "@plus_state_set", rb_ary_new());
	rb_iv_set(self, "@minus_state_set", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::ranimation_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@animation_name", rb_str_new2(""));
	rb_iv_set(self, "@animation_hue", INT2NUM(0));
	rb_iv_set(self, "@position", INT2NUM(1));
	rb_iv_set(self, "@frame_max", INT2NUM(1));
	rb_iv_set(self, "@frames", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::AnimationFrame_id)));
	rb_iv_set(self, "@timings", rb_ary_new());
	return self;
}
VALUE ARGSS::ARPG::ranimationframe_initialize(VALUE self) {
	rb_iv_set(self, "@cell_max", INT2NUM(0));
	rb_iv_set(self, "@cell_data", ARGSS::ATable::New(INT2NUM(0), INT2NUM(0)));
	return self;
}
VALUE ARGSS::ARPG::ranimationtiming_initialize(VALUE self) {
	rb_iv_set(self, "@frame", INT2NUM(0));
	VALUE args[2] = {rb_str_new2(""), INT2NUM(80)};
	rb_iv_set(self, "@se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@flash_scope", INT2NUM(0));
	rb_iv_set(self, "@flash_color", ARGSS::AColor::New(255, 255, 255, 255));
	rb_iv_set(self, "@flash_duration", INT2NUM(5));
	rb_iv_set(self, "@condition", INT2NUM(0));
	return self;
}
VALUE ARGSS::ARPG::rtileset_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@tileset_name", rb_str_new2(""));
	VALUE arr = rb_ary_new();
	for (int i = 0; i < 7; i++) {
		rb_ary_push(arr, rb_ary_new3(1, rb_str_new2("")));
	}
	rb_iv_set(self, "@autotile_names", arr);
	rb_iv_set(self, "@panorama_name", rb_str_new2(""));
	rb_iv_set(self, "@panorama_hue", INT2NUM(0));
	rb_iv_set(self, "@fog_name", rb_str_new2(""));
	rb_iv_set(self, "@fog_hue", INT2NUM(0));
	rb_iv_set(self, "@fog_opacity", INT2NUM(64));
	rb_iv_set(self, "@fog_blend_type", INT2NUM(0));
	rb_iv_set(self, "@fog_zoom", INT2NUM(200));
	rb_iv_set(self, "@fog_sx", INT2NUM(0));
	rb_iv_set(self, "@fog_sy", INT2NUM(0));
	rb_iv_set(self, "@battleback_name", rb_str_new2(""));
	rb_iv_set(self, "@passages", ARGSS::ATable::New(384));
	VALUE table = ARGSS::ATable::New(384);
	rb_ary_store(rb_iv_get(table, "@data"), 0, INT2NUM(5));
	rb_iv_set(self, "@priorities", table);
	rb_iv_set(self, "@terrain_tags", ARGSS::ATable::New(384));
	return self;
}
VALUE ARGSS::ARPG::rcommonevent_initialize(VALUE self) {
	rb_iv_set(self, "@id", INT2NUM(0));
	rb_iv_set(self, "@name", rb_str_new2(""));
	rb_iv_set(self, "@trigger", INT2NUM(0));
	rb_iv_set(self, "@switch_id", INT2NUM(1));
	rb_iv_set(self, "@list", rb_ary_new3(1, rb_class_new_instance(0, 0, ARGSS::ARPG::EventCommand_id)));
	return self;
}
VALUE ARGSS::ARPG::rsystem_initialize(VALUE self) {
	rb_iv_set(self, "@magic_number", INT2NUM(0));
	rb_iv_set(self, "@party_members", rb_ary_new3(1, INT2NUM(1)));
	rb_iv_set(self, "@elements", rb_ary_new3(2, Qnil, rb_str_new2("")));
	rb_iv_set(self, "@switches", rb_ary_new3(2, Qnil, rb_str_new2("")));
	rb_iv_set(self, "@variables", rb_ary_new3(2, Qnil, rb_str_new2("")));
	rb_iv_set(self, "@windowskin_name", rb_str_new2(""));
	rb_iv_set(self, "@title_name", rb_str_new2(""));
	rb_iv_set(self, "@gameover_name", rb_str_new2(""));
	rb_iv_set(self, "@battle_transition", rb_str_new2(""));
	rb_iv_set(self, "@title_bgm", rb_class_new_instance(0, 0, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@battle_bgm", rb_class_new_instance(0, 0, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@battle_end_me", rb_class_new_instance(0, 0, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@gameover_me", rb_class_new_instance(0, 0, ARGSS::ARPG::AudioFile_id));
	VALUE args[2] = {rb_str_new2(""), INT2NUM(80)};
	rb_iv_set(self, "@cursor_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@decision_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@cancel_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@buzzer_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@equip_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@shop_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@save_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@load_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@battle_start_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@escape_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@actor_collapse_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@enemy_collapse_se", rb_class_new_instance(2, args, ARGSS::ARPG::AudioFile_id));
	rb_iv_set(self, "@words", rb_class_new_instance(0, 0, ARGSS::ARPG::SystemWords_id));
	rb_iv_set(self, "@test_battlers", rb_ary_new());
	rb_iv_set(self, "@test_troop_id", INT2NUM(1));
	rb_iv_set(self, "@start_map_id", INT2NUM(1));
	rb_iv_set(self, "@start_x", INT2NUM(0));
	rb_iv_set(self, "@start_y", INT2NUM(0));
	rb_iv_set(self, "@battleback_name", rb_str_new2(""));
	rb_iv_set(self, "@battler_name", rb_str_new2(""));
	rb_iv_set(self, "@battler_hue", INT2NUM(0));
	rb_iv_set(self, "@edit_map_id", INT2NUM(1));
	return self;
}
VALUE ARGSS::ARPG::rsystemwords_initialize(VALUE self) {
	rb_iv_set(self, "@gold", rb_str_new2(""));
	rb_iv_set(self, "@hp", rb_str_new2(""));
	rb_iv_set(self, "@sp", rb_str_new2(""));
	rb_iv_set(self, "@str", rb_str_new2(""));
	rb_iv_set(self, "@dex", rb_str_new2(""));
	rb_iv_set(self, "@agi", rb_str_new2(""));
	rb_iv_set(self, "@int", rb_str_new2(""));
	rb_iv_set(self, "@atk", rb_str_new2(""));
	rb_iv_set(self, "@pdef", rb_str_new2(""));
	rb_iv_set(self, "@mdef", rb_str_new2(""));
	rb_iv_set(self, "@weapon", rb_str_new2(""));
	rb_iv_set(self, "@armor1", rb_str_new2(""));
	rb_iv_set(self, "@armor2", rb_str_new2(""));
	rb_iv_set(self, "@armor3", rb_str_new2(""));
	rb_iv_set(self, "@armor4", rb_str_new2(""));
	rb_iv_set(self, "@attack", rb_str_new2(""));
	rb_iv_set(self, "@skill", rb_str_new2(""));
	rb_iv_set(self, "@guard", rb_str_new2(""));
	rb_iv_set(self, "@item", rb_str_new2(""));
	rb_iv_set(self, "@equip", rb_str_new2(""));
	return self;
}
VALUE ARGSS::ARPG::rsystemtestbattler_initialize(VALUE self) {
	rb_iv_set(self, "@actor_id", INT2NUM(1));
	rb_iv_set(self, "@level", INT2NUM(1));
	rb_iv_set(self, "@weapon_id", INT2NUM(0));
	rb_iv_set(self, "@armor1_id", INT2NUM(0));
	rb_iv_set(self, "@armor2_id", INT2NUM(0));
	rb_iv_set(self, "@armor3_id", INT2NUM(0));
	rb_iv_set(self, "@armor4_id", INT2NUM(0));
	return self;
}
VALUE ARGSS::ARPG::raudiofile_initialize(int argc, VALUE* argv, VALUE self) {
	if (argc > 3) raise_argn(argc, 3);
	rb_iv_set(self, "@name", argc < 1 ? rb_str_new2("") : argv[0]);
	rb_iv_set(self, "@volume", argc < 2 ? INT2NUM(100) : argv[1]);
	rb_iv_set(self, "@pitch", argc < 3 ? INT2NUM(100) : argv[2]);
	return self;
}

////////////////////////////////////////////////////////////
/// ARGSS RPG initialize
////////////////////////////////////////////////////////////
void ARGSS::ARPG::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_module("RPG");
	Map_id = rb_define_class_under(id, "Map", rb_cObject);
	MapInfo_id = rb_define_class_under(id, "MapInfo", rb_cObject);
	Event_id = rb_define_class_under(id, "Event", rb_cObject);
	EventPage_id = rb_define_class_under(Event_id, "Page", rb_cObject);
	EventPageCondition_id = rb_define_class_under(EventPage_id, "Condition", rb_cObject);
	EventPageGraphic_id = rb_define_class_under(EventPage_id, "Graphic", rb_cObject);
	EventCommand_id = rb_define_class_under(id, "EventCommand", rb_cObject);
	MoveRoute_id = rb_define_class_under(id, "MoveRoute", rb_cObject);
	MoveCommand_id = rb_define_class_under(id, "MoveCommand", rb_cObject);
	Actor_id = rb_define_class_under(id, "Actor", rb_cObject);
	Class_id = rb_define_class_under(id, "Class", rb_cObject);
	ClassLearning_id = rb_define_class_under(Class_id, "Learning", rb_cObject);
	Skill_id = rb_define_class_under(id, "Skill", rb_cObject);
	Item_id = rb_define_class_under(id, "Item", rb_cObject);
	Weapon_id = rb_define_class_under(id, "Weapon", rb_cObject);
	Armor_id = rb_define_class_under(id, "Armor", rb_cObject);
	Enemy_id = rb_define_class_under(id, "Enemy", rb_cObject);
	EnemyAction_id = rb_define_class_under(Enemy_id, "Action", rb_cObject);
	Troop_id = rb_define_class_under(id, "Troop", rb_cObject);
	TroopMember_id = rb_define_class_under(Troop_id, "Member", rb_cObject);
	TroopPage_id = rb_define_class_under(Troop_id, "Page", rb_cObject);
	TroopPageCondition_id = rb_define_class_under(TroopPage_id, "Condition", rb_cObject);
	State_id = rb_define_class_under(id, "State", rb_cObject);
	Animation_id = rb_define_class_under(id, "Animation", rb_cObject);
	AnimationFrame_id = rb_define_class_under(Animation_id, "Frame", rb_cObject);
	AnimationTiming_id = rb_define_class_under(Animation_id, "Timing", rb_cObject);
	Tileset_id = rb_define_class_under(id, "Tileset", rb_cObject);
	CommonEvent_id = rb_define_class_under(id, "CommonEvent", rb_cObject);
	System_id = rb_define_class_under(id, "System", rb_cObject);
	SystemWords_id = rb_define_class_under(System_id, "Words", rb_cObject);
	SystemTestBattler_id = rb_define_class_under(System_id, "TestBattler", rb_cObject);
	AudioFile_id = rb_define_class_under(id, "AudioFile", rb_cObject);

	rb_define_method(Map_id, "initialize", (rubyfunc)rmap_initialize, 2);
	rb_define_method(MapInfo_id, "initialize", (rubyfunc)rmapinfo_initialize, 0);
	rb_define_method(Event_id, "initialize", (rubyfunc)revent_initialize, 2);
	rb_define_method(EventPage_id, "initialize", (rubyfunc)reventpage_initialize, 0);
	rb_define_method(EventPageCondition_id, "initialize", (rubyfunc)reventpagecondition_initialize, 0);
	rb_define_method(EventPageGraphic_id, "initialize", (rubyfunc)reventpagegraphic_initialize, 0);
	rb_define_method(EventCommand_id, "initialize", (rubyfunc)reventcommand_initialize, -1);
	rb_define_method(MoveRoute_id, "initialize", (rubyfunc)rmoveroute_initialize, 0);
	rb_define_method(MoveCommand_id, "initialize", (rubyfunc)rmovecommand_initialize, -1);
	rb_define_method(Actor_id, "initialize", (rubyfunc)ractor_initialize, 0);
	rb_define_method(Class_id, "initialize", (rubyfunc)rclass_initialize, 0);
	rb_define_method(ClassLearning_id, "initialize", (rubyfunc)rclasslearning_initialize, 0);
	rb_define_method(Skill_id, "initialize", (rubyfunc)rskill_initialize, 0);
	rb_define_method(Item_id, "initialize", (rubyfunc)ritem_initialize, 0);
	rb_define_method(Weapon_id, "initialize", (rubyfunc)rweapon_initialize, 0);
	rb_define_method(Armor_id, "initialize", (rubyfunc)rarmor_initialize, 0);
	rb_define_method(Enemy_id, "initialize", (rubyfunc)renemy_initialize, 0);
	rb_define_method(EnemyAction_id, "initialize", (rubyfunc)renemyaction_initialize, 0);
	rb_define_method(Troop_id, "initialize", (rubyfunc)rtroop_initialize, 0);
	rb_define_method(TroopMember_id, "initialize", (rubyfunc)rtroopmember_initialize, 0);
	rb_define_method(TroopPage_id, "initialize", (rubyfunc)rtrooppage_initialize, 0);
	rb_define_method(TroopPageCondition_id, "initialize", (rubyfunc)rtrooppagecondition_initialize, 0);
	rb_define_method(State_id, "initialize", (rubyfunc)rstate_initialize, 0);
	rb_define_method(Animation_id, "initialize", (rubyfunc)ranimation_initialize, 0);
	rb_define_method(AnimationFrame_id, "initialize", (rubyfunc)ranimationframe_initialize, 0);
	rb_define_method(AnimationTiming_id, "initialize", (rubyfunc)ranimationtiming_initialize, 0);
	rb_define_method(Tileset_id, "initialize", (rubyfunc)rtileset_initialize, 0);
	rb_define_method(CommonEvent_id, "initialize", (rubyfunc)rcommonevent_initialize, 0);
	rb_define_method(System_id, "initialize", (rubyfunc)rsystem_initialize, 0);
	rb_define_method(SystemWords_id, "initialize", (rubyfunc)rsystemwords_initialize, 0);
	rb_define_method(SystemTestBattler_id, "initialize", (rubyfunc)rsystemtestbattler_initialize, 0);
	rb_define_method(AudioFile_id, "initialize", (rubyfunc)raudiofile_initialize, -1);

	rb_define_attr(Map_id, "tileset_id", 1, 1);
	rb_define_attr(Map_id, "width", 1, 1);
	rb_define_attr(Map_id, "height", 1, 1);
	rb_define_attr(Map_id, "autoplay_bgm", 1, 1);
	rb_define_attr(Map_id, "bgm", 1, 1);
	rb_define_attr(Map_id, "autoplay_bgs", 1, 1);
	rb_define_attr(Map_id, "bgs", 1, 1);
	rb_define_attr(Map_id, "encounter_list", 1, 1);
	rb_define_attr(Map_id, "encounter_step", 1, 1);
	rb_define_attr(Map_id, "data", 1, 1);
	rb_define_attr(Map_id, "events", 1, 1);
	rb_define_attr(MapInfo_id, "name", 1, 1);
	rb_define_attr(MapInfo_id, "parent_id", 1, 1);
	rb_define_attr(MapInfo_id, "order", 1, 1);
	rb_define_attr(MapInfo_id, "expanded", 1, 1);
	rb_define_attr(MapInfo_id, "scroll_x", 1, 1);
	rb_define_attr(MapInfo_id, "scroll_y", 1, 1);
	rb_define_attr(Event_id, "id", 1, 1);
	rb_define_attr(Event_id, "name", 1, 1);
	rb_define_attr(Event_id, "x", 1, 1);
	rb_define_attr(Event_id, "y", 1, 1);
	rb_define_attr(Event_id, "pages", 1, 1);
	rb_define_attr(EventPage_id, "condition", 1, 1);
	rb_define_attr(EventPage_id, "graphic", 1, 1);
	rb_define_attr(EventPage_id, "move_type", 1, 1);
	rb_define_attr(EventPage_id, "move_speed", 1, 1);
	rb_define_attr(EventPage_id, "move_frequency", 1, 1);
	rb_define_attr(EventPage_id, "move_route", 1, 1);
	rb_define_attr(EventPage_id, "walk_anime", 1, 1);
	rb_define_attr(EventPage_id, "step_anime", 1, 1);
	rb_define_attr(EventPage_id, "direction_fix", 1, 1);
	rb_define_attr(EventPage_id, "through", 1, 1);
	rb_define_attr(EventPage_id, "always_on_top", 1, 1);
	rb_define_attr(EventPage_id, "trigger", 1, 1);
	rb_define_attr(EventPage_id, "list", 1, 1);
	rb_define_attr(EventPageCondition_id, "switch1_valid", 1, 1);
	rb_define_attr(EventPageCondition_id, "switch2_valid", 1, 1);
	rb_define_attr(EventPageCondition_id, "variable_valid", 1, 1);
	rb_define_attr(EventPageCondition_id, "self_switch_valid", 1, 1);
	rb_define_attr(EventPageCondition_id, "switch1_id", 1, 1);
	rb_define_attr(EventPageCondition_id, "switch2_id", 1, 1);
	rb_define_attr(EventPageCondition_id, "variable_id", 1, 1);
	rb_define_attr(EventPageCondition_id, "variable_value", 1, 1);
	rb_define_attr(EventPageCondition_id, "self_switch_ch", 1, 1);
	rb_define_attr(EventPageGraphic_id, "tile_id", 1, 1);
	rb_define_attr(EventPageGraphic_id, "character_name", 1, 1);
	rb_define_attr(EventPageGraphic_id, "character_hue", 1, 1);
	rb_define_attr(EventPageGraphic_id, "direction", 1, 1);
	rb_define_attr(EventPageGraphic_id, "pattern", 1, 1);
	rb_define_attr(EventPageGraphic_id, "opacity", 1, 1);
	rb_define_attr(EventPageGraphic_id, "blend_type", 1, 1);
	rb_define_attr(EventCommand_id, "code", 1, 1);
	rb_define_attr(EventCommand_id, "indent", 1, 1);
	rb_define_attr(EventCommand_id, "parameters", 1, 1);
	rb_define_attr(MoveRoute_id, "repeat", 1, 1);
	rb_define_attr(MoveRoute_id, "skippable", 1, 1);
	rb_define_attr(MoveRoute_id, "list", 1, 1);
	rb_define_attr(MoveCommand_id, "code", 1, 1);
	rb_define_attr(MoveCommand_id, "parameters", 1, 1);
	rb_define_attr(Actor_id, "id", 1, 1);
	rb_define_attr(Actor_id, "name", 1, 1);
	rb_define_attr(Actor_id, "class_id", 1, 1);
	rb_define_attr(Actor_id, "initial_level", 1, 1);
	rb_define_attr(Actor_id, "final_level", 1, 1);
	rb_define_attr(Actor_id, "exp_basis", 1, 1);
	rb_define_attr(Actor_id, "exp_inflation", 1, 1);
	rb_define_attr(Actor_id, "character_name", 1, 1);
	rb_define_attr(Actor_id, "character_hue", 1, 1);
	rb_define_attr(Actor_id, "battler_name", 1, 1);
	rb_define_attr(Actor_id, "battler_hue", 1, 1);
	rb_define_attr(Actor_id, "parameters", 1, 1);
	rb_define_attr(Actor_id, "weapon_id", 1, 1);
	rb_define_attr(Actor_id, "armor1_id", 1, 1);
	rb_define_attr(Actor_id, "armor2_id", 1, 1);
	rb_define_attr(Actor_id, "armor3_id", 1, 1);
	rb_define_attr(Actor_id, "armor4_id", 1, 1);
	rb_define_attr(Actor_id, "weapon_fix", 1, 1);
	rb_define_attr(Actor_id, "armor1_fix", 1, 1);
	rb_define_attr(Actor_id, "armor2_fix", 1, 1);
	rb_define_attr(Actor_id, "armor3_fix", 1, 1);
	rb_define_attr(Actor_id, "armor4_fix", 1, 1);
	rb_define_attr(Class_id, "id", 1, 1);
	rb_define_attr(Class_id, "name", 1, 1);
	rb_define_attr(Class_id, "position", 1, 1);
	rb_define_attr(Class_id, "weapon_set", 1, 1);
	rb_define_attr(Class_id, "armor_set", 1, 1);
	rb_define_attr(Class_id, "element_ranks", 1, 1);
	rb_define_attr(Class_id, "state_ranks", 1, 1);
	rb_define_attr(Class_id, "learnings", 1, 1);
	rb_define_attr(ClassLearning_id, "level", 1, 1);
	rb_define_attr(ClassLearning_id, "skill_id", 1, 1);
	rb_define_attr(Skill_id, "id", 1, 1);
	rb_define_attr(Skill_id, "name", 1, 1);
	rb_define_attr(Skill_id, "icon_name", 1, 1);
	rb_define_attr(Skill_id, "description", 1, 1);
	rb_define_attr(Skill_id, "scope", 1, 1);
	rb_define_attr(Skill_id, "occasion", 1, 1);
	rb_define_attr(Skill_id, "animation1_id", 1, 1);
	rb_define_attr(Skill_id, "animation2_id", 1, 1);
	rb_define_attr(Skill_id, "menu_se", 1, 1);
	rb_define_attr(Skill_id, "common_event_id", 1, 1);
	rb_define_attr(Skill_id, "sp_cost", 1, 1);
	rb_define_attr(Skill_id, "power", 1, 1);
	rb_define_attr(Skill_id, "atk_f", 1, 1);
	rb_define_attr(Skill_id, "eva_f", 1, 1);
	rb_define_attr(Skill_id, "str_f", 1, 1);
	rb_define_attr(Skill_id, "dex_f", 1, 1);
	rb_define_attr(Skill_id, "agi_f", 1, 1);
	rb_define_attr(Skill_id, "int_f", 1, 1);
	rb_define_attr(Skill_id, "hit", 1, 1);
	rb_define_attr(Skill_id, "pdef_f", 1, 1);
	rb_define_attr(Skill_id, "mdef_f", 1, 1);
	rb_define_attr(Skill_id, "variance", 1, 1);
	rb_define_attr(Skill_id, "element_set", 1, 1);
	rb_define_attr(Skill_id, "plus_state_set", 1, 1);
	rb_define_attr(Skill_id, "minus_state_set", 1, 1);
	rb_define_attr(Item_id, "id", 1, 1);
	rb_define_attr(Item_id, "name", 1, 1);
	rb_define_attr(Item_id, "icon_name", 1, 1);
	rb_define_attr(Item_id, "description", 1, 1);
	rb_define_attr(Item_id, "scope", 1, 1);
	rb_define_attr(Item_id, "occasion", 1, 1);
	rb_define_attr(Item_id, "animation1_id", 1, 1);
	rb_define_attr(Item_id, "animation2_id", 1, 1);
	rb_define_attr(Item_id, "menu_se", 1, 1);
	rb_define_attr(Item_id, "common_event_id", 1, 1);
	rb_define_attr(Item_id, "price", 1, 1);
	rb_define_attr(Item_id, "consumable", 1, 1);
	rb_define_attr(Item_id, "parameter_type", 1, 1);
	rb_define_attr(Item_id, "parameter_points", 1, 1);
	rb_define_attr(Item_id, "recover_hp_rate", 1, 1);
	rb_define_attr(Item_id, "recover_hp", 1, 1);
	rb_define_attr(Item_id, "recover_sp_rate", 1, 1);
	rb_define_attr(Item_id, "recover_sp", 1, 1);
	rb_define_attr(Item_id, "hit", 1, 1);
	rb_define_attr(Item_id, "pdef_f", 1, 1);
	rb_define_attr(Item_id, "mdef_f", 1, 1);
	rb_define_attr(Item_id, "variance", 1, 1);
	rb_define_attr(Item_id, "element_set", 1, 1);
	rb_define_attr(Item_id, "plus_state_set", 1, 1);
	rb_define_attr(Item_id, "minus_state_set", 1, 1);
	rb_define_attr(Weapon_id, "id", 1, 1);
	rb_define_attr(Weapon_id, "name", 1, 1);
	rb_define_attr(Weapon_id, "icon_name", 1, 1);
	rb_define_attr(Weapon_id, "description", 1, 1);
	rb_define_attr(Weapon_id, "animation1_id", 1, 1);
	rb_define_attr(Weapon_id, "animation2_id", 1, 1);
	rb_define_attr(Weapon_id, "price", 1, 1);
	rb_define_attr(Weapon_id, "atk", 1, 1);
	rb_define_attr(Weapon_id, "pdef", 1, 1);
	rb_define_attr(Weapon_id, "mdef", 1, 1);
	rb_define_attr(Weapon_id, "str_plus", 1, 1);
	rb_define_attr(Weapon_id, "dex_plus", 1, 1);
	rb_define_attr(Weapon_id, "agi_plus", 1, 1);
	rb_define_attr(Weapon_id, "int_plus", 1, 1);
	rb_define_attr(Weapon_id, "element_set", 1, 1);
	rb_define_attr(Weapon_id, "plus_state_set", 1, 1);
	rb_define_attr(Weapon_id, "minus_state_set", 1, 1);
	rb_define_attr(Armor_id, "id", 1, 1);
	rb_define_attr(Armor_id, "name", 1, 1);
	rb_define_attr(Armor_id, "icon_name", 1, 1);
	rb_define_attr(Armor_id, "description", 1, 1);
	rb_define_attr(Armor_id, "kind", 1, 1);
	rb_define_attr(Armor_id, "auto_state_id", 1, 1);
	rb_define_attr(Armor_id, "price", 1, 1);
	rb_define_attr(Armor_id, "pdef", 1, 1);
	rb_define_attr(Armor_id, "mdef", 1, 1);
	rb_define_attr(Armor_id, "eva", 1, 1);
	rb_define_attr(Armor_id, "str_plus", 1, 1);
	rb_define_attr(Armor_id, "dex_plus", 1, 1);
	rb_define_attr(Armor_id, "agi_plus", 1, 1);
	rb_define_attr(Armor_id, "int_plus", 1, 1);
	rb_define_attr(Armor_id, "guard_element_set", 1, 1);
	rb_define_attr(Armor_id, "guard_state_set", 1, 1);
	rb_define_attr(Enemy_id, "id", 1, 1);
	rb_define_attr(Enemy_id, "name", 1, 1);
	rb_define_attr(Enemy_id, "battler_name", 1, 1);
	rb_define_attr(Enemy_id, "battler_hue", 1, 1);
	rb_define_attr(Enemy_id, "maxhp", 1, 1);
	rb_define_attr(Enemy_id, "maxsp", 1, 1);
	rb_define_attr(Enemy_id, "str", 1, 1);
	rb_define_attr(Enemy_id, "dex", 1, 1);
	rb_define_attr(Enemy_id, "agi", 1, 1);
	rb_define_attr(Enemy_id, "int", 1, 1);
	rb_define_attr(Enemy_id, "atk", 1, 1);
	rb_define_attr(Enemy_id, "pdef", 1, 1);
	rb_define_attr(Enemy_id, "mdef", 1, 1);
	rb_define_attr(Enemy_id, "eva", 1, 1);
	rb_define_attr(Enemy_id, "animation1_id", 1, 1);
	rb_define_attr(Enemy_id, "animation2_id", 1, 1);
	rb_define_attr(Enemy_id, "element_ranks", 1, 1);
	rb_define_attr(Enemy_id, "state_ranks", 1, 1);
	rb_define_attr(Enemy_id, "actions", 1, 1);
	rb_define_attr(Enemy_id, "exp", 1, 1);
	rb_define_attr(Enemy_id, "gold", 1, 1);
	rb_define_attr(Enemy_id, "item_id", 1, 1);
	rb_define_attr(Enemy_id, "weapon_id", 1, 1);
	rb_define_attr(Enemy_id, "armor_id", 1, 1);
	rb_define_attr(Enemy_id, "treasure_prob", 1, 1);
	rb_define_attr(EnemyAction_id, "kind", 1, 1);
	rb_define_attr(EnemyAction_id, "basic", 1, 1);
	rb_define_attr(EnemyAction_id, "skill_id", 1, 1);
	rb_define_attr(EnemyAction_id, "condition_turn_a", 1, 1);
	rb_define_attr(EnemyAction_id, "condition_turn_b", 1, 1);
	rb_define_attr(EnemyAction_id, "condition_hp", 1, 1);
	rb_define_attr(EnemyAction_id, "condition_level", 1, 1);
	rb_define_attr(EnemyAction_id, "condition_switch_id", 1, 1);
	rb_define_attr(EnemyAction_id, "rating", 1, 1);
	rb_define_attr(Troop_id, "id", 1, 1);
	rb_define_attr(Troop_id, "name", 1, 1);
	rb_define_attr(Troop_id, "members", 1, 1);
	rb_define_attr(Troop_id, "pages", 1, 1);
	rb_define_attr(TroopMember_id, "enemy_id", 1, 1);
	rb_define_attr(TroopMember_id, "x", 1, 1);
	rb_define_attr(TroopMember_id, "y", 1, 1);
	rb_define_attr(TroopMember_id, "hidden", 1, 1);
	rb_define_attr(TroopMember_id, "immortal", 1, 1);
	rb_define_attr(TroopPage_id, "condition", 1, 1);
	rb_define_attr(TroopPage_id, "span", 1, 1);
	rb_define_attr(TroopPage_id, "list", 1, 1);
	rb_define_attr(TroopPageCondition_id, "turn_valid", 1, 1);
	rb_define_attr(TroopPageCondition_id, "enemy_valid", 1, 1);
	rb_define_attr(TroopPageCondition_id, "actor_valid", 1, 1);
	rb_define_attr(TroopPageCondition_id, "switch_valid", 1, 1);
	rb_define_attr(TroopPageCondition_id, "turn_a", 1, 1);
	rb_define_attr(TroopPageCondition_id, "turn_b", 1, 1);
	rb_define_attr(TroopPageCondition_id, "enemy_index", 1, 1);
	rb_define_attr(TroopPageCondition_id, "enemy_hp", 1, 1);
	rb_define_attr(TroopPageCondition_id, "actor_id", 1, 1);
	rb_define_attr(TroopPageCondition_id, "actor_hp", 1, 1);
	rb_define_attr(TroopPageCondition_id, "switch_id", 1, 1);
	rb_define_attr(State_id, "id", 1, 1);
	rb_define_attr(State_id, "name", 1, 1);
	rb_define_attr(State_id, "animation_id", 1, 1);
	rb_define_attr(State_id, "restriction", 1, 1);
	rb_define_attr(State_id, "nonresistance", 1, 1);
	rb_define_attr(State_id, "zero_hp", 1, 1);
	rb_define_attr(State_id, "cant_get_exp", 1, 1);
	rb_define_attr(State_id, "cant_evade", 1, 1);
	rb_define_attr(State_id, "slip_damage", 1, 1);
	rb_define_attr(State_id, "rating", 1, 1);
	rb_define_attr(State_id, "hit_rate", 1, 1);
	rb_define_attr(State_id, "maxhp_rate", 1, 1);
	rb_define_attr(State_id, "maxsp_rate", 1, 1);
	rb_define_attr(State_id, "str_rate", 1, 1);
	rb_define_attr(State_id, "dex_rate", 1, 1);
	rb_define_attr(State_id, "agi_rate", 1, 1);
	rb_define_attr(State_id, "int_rate", 1, 1);
	rb_define_attr(State_id, "atk_rate", 1, 1);
	rb_define_attr(State_id, "pdef_rate", 1, 1);
	rb_define_attr(State_id, "mdef_rate", 1, 1);
	rb_define_attr(State_id, "eva", 1, 1);
	rb_define_attr(State_id, "battle_only", 1, 1);
	rb_define_attr(State_id, "hold_turn", 1, 1);
	rb_define_attr(State_id, "auto_release_prob", 1, 1);
	rb_define_attr(State_id, "shock_release_prob", 1, 1);
	rb_define_attr(State_id, "guard_element_set", 1, 1);
	rb_define_attr(State_id, "plus_state_set", 1, 1);
	rb_define_attr(State_id, "minus_state_set", 1, 1);
	rb_define_attr(Animation_id, "id", 1, 1);
	rb_define_attr(Animation_id, "name", 1, 1);
	rb_define_attr(Animation_id, "animation_name", 1, 1);
	rb_define_attr(Animation_id, "animation_hue", 1, 1);
	rb_define_attr(Animation_id, "position", 1, 1);
	rb_define_attr(Animation_id, "frame_max", 1, 1);
	rb_define_attr(Animation_id, "frames", 1, 1);
	rb_define_attr(Animation_id, "timings", 1, 1);
	rb_define_attr(AnimationFrame_id, "cell_max", 1, 1);
	rb_define_attr(AnimationFrame_id, "cell_data", 1, 1);
	rb_define_attr(AnimationTiming_id, "frame", 1, 1);
	rb_define_attr(AnimationTiming_id, "se", 1, 1);
	rb_define_attr(AnimationTiming_id, "flash_scope", 1, 1);
	rb_define_attr(AnimationTiming_id, "flash_color", 1, 1);
	rb_define_attr(AnimationTiming_id, "flash_duration", 1, 1);
	rb_define_attr(AnimationTiming_id, "condition", 1, 1);
	rb_define_attr(Tileset_id, "id", 1, 1);
	rb_define_attr(Tileset_id, "name", 1, 1);
	rb_define_attr(Tileset_id, "tileset_name", 1, 1);
	rb_define_attr(Tileset_id, "autotile_names", 1, 1);
	rb_define_attr(Tileset_id, "panorama_name", 1, 1);
	rb_define_attr(Tileset_id, "panorama_hue", 1, 1);
	rb_define_attr(Tileset_id, "fog_name", 1, 1);
	rb_define_attr(Tileset_id, "fog_hue", 1, 1);
	rb_define_attr(Tileset_id, "fog_opacity", 1, 1);
	rb_define_attr(Tileset_id, "fog_blend_type", 1, 1);
	rb_define_attr(Tileset_id, "fog_zoom", 1, 1);
	rb_define_attr(Tileset_id, "fog_sx", 1, 1);
	rb_define_attr(Tileset_id, "fog_sy", 1, 1);
	rb_define_attr(Tileset_id, "battleback_name", 1, 1);
	rb_define_attr(Tileset_id, "passages", 1, 1);
	rb_define_attr(Tileset_id, "priorities", 1, 1);
	rb_define_attr(Tileset_id, "terrain_tags", 1, 1);
	rb_define_attr(CommonEvent_id, "id", 1, 1);
	rb_define_attr(CommonEvent_id, "name", 1, 1);
	rb_define_attr(CommonEvent_id, "trigger", 1, 1);
	rb_define_attr(CommonEvent_id, "switch_id", 1, 1);
	rb_define_attr(CommonEvent_id, "list", 1, 1);
	rb_define_attr(System_id, "magic_number", 1, 1);
	rb_define_attr(System_id, "party_members", 1, 1);
	rb_define_attr(System_id, "elements", 1, 1);
	rb_define_attr(System_id, "switches", 1, 1);
	rb_define_attr(System_id, "variables", 1, 1);
	rb_define_attr(System_id, "windowskin_name", 1, 1);
	rb_define_attr(System_id, "title_name", 1, 1);
	rb_define_attr(System_id, "gameover_name", 1, 1);
	rb_define_attr(System_id, "battle_transition", 1, 1);
	rb_define_attr(System_id, "title_bgm", 1, 1);
	rb_define_attr(System_id, "battle_bgm", 1, 1);
	rb_define_attr(System_id, "battle_end_me", 1, 1);
	rb_define_attr(System_id, "gameover_me", 1, 1);
	rb_define_attr(System_id, "cursor_se", 1, 1);
	rb_define_attr(System_id, "decision_se", 1, 1);
	rb_define_attr(System_id, "cancel_se", 1, 1);
	rb_define_attr(System_id, "buzzer_se", 1, 1);
	rb_define_attr(System_id, "equip_se", 1, 1);
	rb_define_attr(System_id, "shop_se", 1, 1);
	rb_define_attr(System_id, "save_se", 1, 1);
	rb_define_attr(System_id, "load_se", 1, 1);
	rb_define_attr(System_id, "battle_start_se", 1, 1);
	rb_define_attr(System_id, "escape_se", 1, 1);
	rb_define_attr(System_id, "actor_collapse_se", 1, 1);
	rb_define_attr(System_id, "enemy_collapse_se", 1, 1);
	rb_define_attr(System_id, "words", 1, 1);
	rb_define_attr(System_id, "test_battlers", 1, 1);
	rb_define_attr(System_id, "test_troop_id", 1, 1);
	rb_define_attr(System_id, "start_map_id", 1, 1);
	rb_define_attr(System_id, "start_x", 1, 1);
	rb_define_attr(System_id, "start_y", 1, 1);
	rb_define_attr(System_id, "battleback_name", 1, 1);
	rb_define_attr(System_id, "battler_name", 1, 1);
	rb_define_attr(System_id, "battler_hue", 1, 1);
	rb_define_attr(System_id, "edit_map_id", 1, 1);
	rb_define_attr(SystemWords_id, "gold", 1, 1);
	rb_define_attr(SystemWords_id, "hp", 1, 1);
	rb_define_attr(SystemWords_id, "sp", 1, 1);
	rb_define_attr(SystemWords_id, "str", 1, 1);
	rb_define_attr(SystemWords_id, "dex", 1, 1);
	rb_define_attr(SystemWords_id, "agi", 1, 1);
	rb_define_attr(SystemWords_id, "int", 1, 1);
	rb_define_attr(SystemWords_id, "atk", 1, 1);
	rb_define_attr(SystemWords_id, "pdef", 1, 1);
	rb_define_attr(SystemWords_id, "mdef", 1, 1);
	rb_define_attr(SystemWords_id, "weapon", 1, 1);
	rb_define_attr(SystemWords_id, "armor1", 1, 1);
	rb_define_attr(SystemWords_id, "armor2", 1, 1);
	rb_define_attr(SystemWords_id, "armor3", 1, 1);
	rb_define_attr(SystemWords_id, "armor4", 1, 1);
	rb_define_attr(SystemWords_id, "attack", 1, 1);
	rb_define_attr(SystemWords_id, "skill", 1, 1);
	rb_define_attr(SystemWords_id, "guard", 1, 1);
	rb_define_attr(SystemWords_id, "item", 1, 1);
	rb_define_attr(SystemWords_id, "equip", 1, 1);
	rb_define_attr(SystemTestBattler_id, "actor_id", 1, 1);
	rb_define_attr(SystemTestBattler_id, "level", 1, 1);
	rb_define_attr(SystemTestBattler_id, "weapon_id", 1, 1);
	rb_define_attr(SystemTestBattler_id, "armor1_id", 1, 1);
	rb_define_attr(SystemTestBattler_id, "armor2_id", 1, 1);
	rb_define_attr(SystemTestBattler_id, "armor3_id", 1, 1);
	rb_define_attr(SystemTestBattler_id, "armor4_id", 1, 1);
	rb_define_attr(AudioFile_id, "name", 1, 1);
	rb_define_attr(AudioFile_id, "volume", 1, 1);
	rb_define_attr(AudioFile_id, "pitch", 1, 1);
}
