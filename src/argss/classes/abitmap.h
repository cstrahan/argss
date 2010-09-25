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

#ifndef _ARGSS_BITMAP_H_
#define _ARGSS_BITMAP_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Bitmap namespace
	///////////////////////////////////////////////////////
	namespace ABitmap {
		///////////////////////////////////////////////////
		/// Initialize Bitmap class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Check if Bitmap is disposed.
		/// An error will be raised if it is disposed.
		///////////////////////////////////////////////////
		void CheckDisposed(VALUE id);

		/// Bitmap class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Bitmap instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rdispose(VALUE self);
		VALUE rdisposedQ(VALUE self);
		VALUE rwidth(VALUE self);
		VALUE rheight(VALUE self);
		VALUE rrect(VALUE self);
		VALUE rblt(int argc, VALUE* argv, VALUE self);
		VALUE rstretch_blt(int argc, VALUE* argv, VALUE self);
		VALUE rfill_rect(int argc, VALUE* argv, VALUE self);
		VALUE rclear(int argc, VALUE* argv, VALUE self);
		VALUE rget_pixel(VALUE self, VALUE x, VALUE y);
		VALUE rset_pixel(VALUE self, VALUE x, VALUE y, VALUE color);
		VALUE rhue_change(VALUE self, VALUE hue);
		VALUE rsaturation_change(VALUE self, VALUE saturation);
		VALUE rluminance_change(VALUE self, VALUE luminance);
		VALUE rhsl_change(int argc, VALUE* argv, VALUE self);
		VALUE rdraw_text(int argc, VALUE* argv, VALUE self);
		VALUE rtext_size(VALUE self, VALUE text);
		VALUE rgradient_fill_rect(int argc, VALUE* argv, VALUE self);
		VALUE rclear_rect(int argc, VALUE* argv, VALUE self);
		VALUE rblur(VALUE self);
		VALUE rradial_blur(VALUE self, VALUE angle, VALUE division);
		VALUE rfont(VALUE self);
		VALUE rfontE(VALUE self, VALUE font);
		VALUE rdup(VALUE self);

		//@}
	};
};

#endif
