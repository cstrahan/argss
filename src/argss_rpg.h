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

#ifndef _ARGSS_RPG_H_
#define _ARGSS_RPG_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "argss_ruby.h"

////////////////////////////////////////////////////////////
/// ARGSS RPG namespace
////////////////////////////////////////////////////////////
namespace ARGSS {
	namespace ARPG {
		extern VALUE id;
		extern VALUE Map_id;
		extern VALUE MapInfo_id;
		extern VALUE Event_id;
		extern VALUE EventPage_id;
		extern VALUE EventPageCondition_id;
		extern VALUE EventPageGraphic_id;
		extern VALUE EventCommand_id;
		extern VALUE MoveRoute_id;
		extern VALUE MoveCommand_id;
		extern VALUE Actor_id;
		extern VALUE Class_id;
		extern VALUE ClassLearning_id;
		extern VALUE Skill_id;
		extern VALUE Item_id;
		extern VALUE Weapon_id;
		extern VALUE Armor_id;
		extern VALUE Enemy_id;
		extern VALUE EnemyAction_id;
		extern VALUE Troop_id;
		extern VALUE TroopMember_id;
		extern VALUE TroopPage_id;
		extern VALUE TroopPageCondition_id;
		extern VALUE State_id;
		extern VALUE Animation_id;
		extern VALUE AnimationFrame_id;
		extern VALUE AnimationTiming_id;
		extern VALUE Tileset_id;
		extern VALUE CommonEvent_id;
		extern VALUE System_id;
		extern VALUE SystemWords_id;
		extern VALUE SystemTestBattler_id;
		extern VALUE AudioFile_id;
		void Init();
	};
};

#endif
