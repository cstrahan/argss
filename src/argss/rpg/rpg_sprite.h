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

#ifndef _ARGSS_RPG_SPRITE_H_
#define _ARGSS_RPG_SPRITE_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	namespace ARPG {
		///////////////////////////////////////////////////
		/// ARGSS::RPG::Sprite namespace
		///////////////////////////////////////////////////
		namespace ASprite {
			///////////////////////////////////////////////
			/// Initialize Sprite class.
			///////////////////////////////////////////////
			void Init();

			/// Sprite class id.
			extern VALUE id;

			///////////////////////////////////////////////
			/// Sprite instance methods.
			///////////////////////////////////////////////
			//@{

			VALUE rinitialize(int argc, VALUE* argv, VALUE self);
			VALUE rdispose(VALUE self);
			VALUE rwhiten(VALUE self);
			VALUE rappear(VALUE self);
			VALUE rescape(VALUE self);
			VALUE rcollapse(VALUE self);
			VALUE rdamage(VALUE self, VALUE value, VALUE critical);
			VALUE ranimation(VALUE self, VALUE animation, VALUE hit);
			VALUE rloop_animation(VALUE self, VALUE animation);
			VALUE rdispose_damage(VALUE self);
			VALUE rdispose_animation(VALUE self);
			VALUE rdispose_loop_animation(VALUE self);
			VALUE rblink_on(VALUE self);
			VALUE rblink_off(VALUE self);
			VALUE rblinkQ(VALUE self);
			VALUE reffectQ(VALUE self);
			VALUE rupdate(VALUE self);
			VALUE rupdate_animation(VALUE self);
			VALUE rupdate_loop_animation(VALUE self);
			VALUE ranimation_set_sprites(VALUE self, VALUE sprites, VALUE cell_data, VALUE position);
			VALUE ranimation_process_timing(VALUE self, VALUE timing, VALUE hit);
			VALUE rxE(VALUE self, VALUE x);
			VALUE ryE(VALUE self, VALUE y);

			//@}
		};
	};
};

#endif
