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

#ifndef _ARGSS_RPG_CACHE_H_
#define _ARGSS_RPG_CACHE_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	namespace ARPG {
		///////////////////////////////////////////////////
		/// ARGSS::RPG::Cache namespace
		///////////////////////////////////////////////////
		namespace ACache {
			///////////////////////////////////////////////
			/// Initialize Cache module.
			///////////////////////////////////////////////
			void Init();

			/// Cache module id.
			extern VALUE id;

			///////////////////////////////////////////////
			/// Cache module methods.
			///////////////////////////////////////////////
			//@{

			VALUE rload_bitmap(int argc, VALUE* argv, VALUE self);
			VALUE ranimation(VALUE self, VALUE filename, VALUE hue);
			VALUE rautotile(VALUE self, VALUE filename);
			VALUE rbattleback(VALUE self, VALUE filename);
			VALUE rbattler(VALUE self, VALUE filename, VALUE hue);
			VALUE rcharacter(VALUE self, VALUE filename, VALUE hue);
			VALUE rfog(VALUE self, VALUE filename, VALUE hue);
			VALUE rgameover(VALUE self, VALUE filename);
			VALUE ricon(VALUE self, VALUE filename);
			VALUE rpanorama(VALUE self, VALUE filename, VALUE hue);
			VALUE rpicture(VALUE self, VALUE filename);
			VALUE rtileset(VALUE self, VALUE filename);
			VALUE rtitle(VALUE self, VALUE filename);
			VALUE rwindowskin(VALUE self, VALUE filename);
			VALUE rtile(VALUE self, VALUE filename, VALUE tile_id, VALUE hue);
			VALUE rclear(VALUE self);

			//@}
		};
	};
};

#endif
