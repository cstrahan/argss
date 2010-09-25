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

#ifndef _ARGSS_RECT_H_
#define _ARGSS_RECT_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Rect namespace
	///////////////////////////////////////////////////////
	namespace ARect {
		///////////////////////////////////////////////////
		/// Initialize Rect class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Create Rect instance.
		///////////////////////////////////////////////////
		//@{

		VALUE New(double x, double y, double width, double height);

		//@}

		/// Rect class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Rect instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h);
		VALUE rset(VALUE self, VALUE x, VALUE y, VALUE w, VALUE h);
		VALUE rx(VALUE self);
		VALUE rxE(VALUE self, VALUE x);
		VALUE ry(VALUE self);
		VALUE ryE(VALUE self, VALUE y);
		VALUE rwidth(VALUE self);
		VALUE rwidthE(VALUE self, VALUE w);
		VALUE rheight(VALUE self);
		VALUE rheightE(VALUE self, VALUE h);
		VALUE rempty(VALUE self);
		VALUE rinspect(VALUE self);
		VALUE rdump(int argc, VALUE* argv, VALUE self);

		//@}

		///////////////////////////////////////////////////
		/// Rect class methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rload(VALUE self, VALUE str);

		//@}
	};
};

#endif
