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

#ifndef _ARGSS_TONE_H_
#define _ARGSS_TONE_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Tone namespace
	///////////////////////////////////////////////////////
	namespace ATone {
		///////////////////////////////////////////////////
		/// Initialize Tone class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Create Tone instance.
		///////////////////////////////////////////////////
		//@{

		VALUE New();
		VALUE New(VALUE tone);
		VALUE New(double r, double g, double b, double gray);

		//@}

		/// Tone class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Tone instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rset(int argc, VALUE* argv, VALUE self);
		VALUE rred(VALUE self);
		VALUE rredE(VALUE self, VALUE r);
		VALUE rgreen(VALUE self);
		VALUE rgreenE(VALUE self, VALUE g);
		VALUE rblue(VALUE self);
		VALUE rblueE(VALUE self, VALUE b);
		VALUE rgray(VALUE self);
		VALUE rgrayE(VALUE self, VALUE g);
		VALUE rinspect(VALUE self);
		VALUE rdump(int argc, VALUE* argv, VALUE self);
		
		//@}

		///////////////////////////////////////////////////
		/// Tone class methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rload(VALUE self, VALUE str);

		//@}
	};
};

#endif
