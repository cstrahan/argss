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

#ifndef _ARGSS_AUDIO_H_
#define _ARGSS_AUDIO_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Audio namespace
	///////////////////////////////////////////////////////
	namespace AAudio {
		///////////////////////////////////////////////////
		/// Initialize Audio module.
		///////////////////////////////////////////////////
		void Init();

		/// Audio module id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Audio module methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rbgm_play(int argc, VALUE* argv, VALUE self);
		VALUE rbgm_stop(VALUE self);
		VALUE rbgm_fade(VALUE self, VALUE fade);
		VALUE rbgs_play(int argc, VALUE* argv, VALUE self);
		VALUE rbgs_stop(VALUE self);
		VALUE rbgs_fade(VALUE self, VALUE fade);
		VALUE rme_play(int argc, VALUE* argv, VALUE self);
		VALUE rme_stop(VALUE self);
		VALUE rme_fade(VALUE self, VALUE fade);
		VALUE rse_play(int argc, VALUE* argv, VALUE self);
		VALUE rse_stop(VALUE self);

		//@}
	};
};

#endif
