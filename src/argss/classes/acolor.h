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

#ifndef _ARGSS_COLOR_H_
#define _ARGSS_COLOR_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Color namespace
	///////////////////////////////////////////////////////
	namespace AColor {
		///////////////////////////////////////////////////
		/// Initialize Color class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Create Color instance.
		///////////////////////////////////////////////////
		//@{

		VALUE New();
		VALUE New(VALUE color);
		VALUE New(double r, double g, double b, double a);

		//@}

		/// Color class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Color instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rset(int argc, VALUE* argv, VALUE self);
		VALUE rred(VALUE self);
		VALUE rredE(VALUE self, VALUE red);
		VALUE rgreen(VALUE self);
		VALUE rgreenE(VALUE self, VALUE green);
		VALUE rblue(VALUE self);
		VALUE rblueE(VALUE self, VALUE blue);
		VALUE ralpha(VALUE self);
		VALUE ralphaE(VALUE self, VALUE alpha);
		VALUE rinspect(VALUE self);
		VALUE rdump(int argc, VALUE* argv, VALUE self);

		//@}

		///////////////////////////////////////////////////
		/// Color class methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rload(VALUE self, VALUE str);

		//@}
	};
};

#endif
