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

#ifndef _ARGSS_SPRITE_H_
#define _ARGSS_SPRITE_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Sprite namespace
	///////////////////////////////////////////////////////
	namespace ASprite {
		///////////////////////////////////////////////////
		/// Initialize Sprite class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Check if Sprite is disposed.
		/// An error will be raised if it is disposed.
		///////////////////////////////////////////////////
		void CheckDisposed(VALUE id);

		/// Sprite class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Sprite instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rdispose(VALUE self);
		VALUE rdisposedQ(VALUE self);
		VALUE rflash(VALUE self, VALUE color, VALUE duration);
		VALUE rupdate(VALUE self);
		VALUE rwidth(VALUE self);
		VALUE rheight(VALUE self);
		VALUE rviewport(VALUE self);
		VALUE rviewportE(VALUE self, VALUE viewport);
		VALUE rbitmap(VALUE self);
		VALUE rbitmapE(VALUE self, VALUE bitmap);
		VALUE rsrc_rect(VALUE self);
		VALUE rsrc_rectE(VALUE self, VALUE src_rect);
		VALUE rvisible(VALUE self);
		VALUE rvisibleE(VALUE self, VALUE visible);
		VALUE rx(VALUE self);
		VALUE rfx(VALUE self);
		VALUE rxE(VALUE self, VALUE x);
		VALUE ry(VALUE self);
		VALUE rfy(VALUE self);
		VALUE ryE(VALUE self, VALUE y);
		VALUE rz(VALUE self);
		VALUE rzE(VALUE self, VALUE z);
		VALUE rox(VALUE self);
		VALUE roxE(VALUE self, VALUE ox);
		VALUE roy(VALUE self);
		VALUE royE(VALUE self, VALUE oy);
		VALUE rzoom_x(VALUE self);
		VALUE rzoom_xE(VALUE self, VALUE zoom_x);
		VALUE rzoom_y(VALUE self);
		VALUE rzoom_yE(VALUE self, VALUE zoom_y);
		VALUE rangle(VALUE self);
		VALUE rangleE(VALUE self, VALUE angle);
		VALUE rmirror(VALUE self);
		VALUE rmirrorE(VALUE self, VALUE mirror);
		VALUE rflipx(VALUE self);
		VALUE rflipxE(VALUE self, VALUE flipx);
		VALUE rflipy(VALUE self);
		VALUE rflipyE(VALUE self, VALUE flipy);
		VALUE rbush_depth(VALUE self);
		VALUE rbush_depthE(VALUE self, VALUE bush_depth);
		VALUE ropacity(VALUE self);
		VALUE ropacityE(VALUE self, VALUE opacity);
		VALUE rblend_type(VALUE self);
		VALUE rblend_typeE(VALUE self, VALUE blend_type);
		VALUE rcolor(VALUE self);
		VALUE rcolorE(VALUE self, VALUE color);
		VALUE rtone(VALUE self);
		VALUE rtoneE(VALUE self, VALUE tone);

		//@}
	};
};

#endif
