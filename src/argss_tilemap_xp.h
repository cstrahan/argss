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

#ifndef _ARGSS_TILEMAP_XP_H_
#define _ARGSS_TILEMAP_XP_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "argss_tilemapautotiles_xp.h"

////////////////////////////////////////////////////////////
/// ARGSS Tilemap namespace
////////////////////////////////////////////////////////////
namespace ARGSS {
	namespace ATilemap {
		extern VALUE id;
		void Init();
		void CheckDisposed(VALUE self);

		VALUE rinitialize(int argc, VALUE *argv, VALUE self);
		VALUE rdispose(VALUE self);
		VALUE rdisposeQ(VALUE self);
		VALUE rupdate(VALUE self);
		VALUE rviewport(VALUE self);
		VALUE rviewportE(VALUE self, VALUE viewport);
		VALUE rtileset(VALUE self);
		VALUE rtilesetE(VALUE self, VALUE tileset);
		VALUE rautotiles(VALUE self);
		VALUE rmap_data(VALUE self);
		VALUE rmap_dataE(VALUE self, VALUE map_data);
		VALUE rflash_data(VALUE self);
		VALUE rflash_dataE(VALUE self, VALUE flash_data);
		VALUE rpriorities(VALUE self);
		VALUE rprioritiesE(VALUE self, VALUE priorities);
		VALUE rvisible(VALUE self);
		VALUE rvisibleE(VALUE self, VALUE visible);
		VALUE rox(VALUE self);
		VALUE roxE(VALUE self, VALUE ox);
		VALUE roy(VALUE self);
		VALUE royE(VALUE self, VALUE oy);
	};
};

#endif
