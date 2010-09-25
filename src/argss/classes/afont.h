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

#ifndef _ARGSS_FONT_H_
#define _ARGSS_FONT_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Font namespace
	///////////////////////////////////////////////////////
	namespace AFont {
		///////////////////////////////////////////////////
		/// Initialize Font class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Create Font instance.
		///////////////////////////////////////////////////
		//@{

		VALUE New();

		//@}

		/// Font class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Font instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rexistQ(VALUE self);
		VALUE rname(VALUE self);
		VALUE rnameE(VALUE self, VALUE name);
		VALUE rsize(VALUE self);
		VALUE rsizeE(VALUE self, VALUE size);
		VALUE rbold(VALUE self);
		VALUE rboldE(VALUE self, VALUE bold);
		VALUE ritalic(VALUE self);
		VALUE ritalicE(VALUE self, VALUE italic);
		VALUE rcolor(VALUE self);
		VALUE rcolorE(VALUE self, VALUE color);
		VALUE rshadow(VALUE self);
		VALUE rshadowE(VALUE self, VALUE shadow);

		//@}

		///////////////////////////////////////////////////
		/// Font class methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rdefault_name(VALUE self);
		VALUE rdefault_nameE(VALUE self, VALUE default_name);
		VALUE rdefault_size(VALUE self);
		VALUE rdefault_sizeE(VALUE self, VALUE default_size);
		VALUE rdefault_bold(VALUE self);
		VALUE rdefault_boldE(VALUE self, VALUE default_bold);
		VALUE rdefault_italic(VALUE self);
		VALUE rdefault_italicE(VALUE self, VALUE default_italic);
		VALUE rdefault_color(VALUE self);
		VALUE rdefault_colorE(VALUE self, VALUE default_color);
		VALUE rdefault_shadow(VALUE self);
		VALUE rdefault_shadowE(VALUE self, VALUE default_shadow);

		//@}
	};
};

#endif
