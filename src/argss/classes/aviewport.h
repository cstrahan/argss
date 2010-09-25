//////////////////////////////////////////////////////////////////////////////
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

#ifndef _ARGSS_VIEWPORT_H_
#define _ARGSS_VIEWPORT_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Viewport namespace
	///////////////////////////////////////////////////////
	namespace AViewport {
		///////////////////////////////////////////////////
		/// Initialize Viewport class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Check if Viewport is disposed.
		/// An error will be raised if it is disposed.
		///////////////////////////////////////////////////
		void CheckDisposed(VALUE id);

		/// Viewport class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Viewport instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rdispose(VALUE self);
		VALUE rdisposedQ(VALUE self);
		VALUE rflash(VALUE self, VALUE color, VALUE duration);
		VALUE rupdate(VALUE self);
		VALUE rrect(VALUE self);
		VALUE rrectE(VALUE self, VALUE rect);
		VALUE rvisible(VALUE self);
		VALUE rvisibleE(VALUE self, VALUE visible);
		VALUE rz(VALUE self);
		VALUE rzE(VALUE self, VALUE z);
		VALUE rox(VALUE self);
		VALUE roxE(VALUE self, VALUE ox);
		VALUE roy(VALUE self);
		VALUE royE(VALUE self, VALUE oy);
		VALUE rcolor(VALUE self);
		VALUE rcolorE(VALUE self, VALUE color);
		VALUE rtone(VALUE self);
		VALUE rtoneE(VALUE self, VALUE tone);

		//@}
	};
};

#endif
