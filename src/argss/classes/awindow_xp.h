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

#ifndef _ARGSS_WINDOW_XP_H_
#define _ARGSS_WINDOW_XP_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Window namespace
	///////////////////////////////////////////////////////
	namespace AWindow {
		///////////////////////////////////////////////////
		/// Initialize Window class.
		///////////////////////////////////////////////////
		void Init();

		///////////////////////////////////////////////////
		/// Check if Window is disposed.
		/// An error will be raised if it is disposed.
		///////////////////////////////////////////////////
		void CheckDisposed(VALUE id);

		/// Window class id.
		extern VALUE id;

		///////////////////////////////////////////////////
		/// Window instance methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rinitialize(int argc, VALUE* argv, VALUE self);
		VALUE rdispose(VALUE self);
		VALUE rdisposedQ(VALUE self);
		VALUE rupdate(VALUE self);
		VALUE rviewport(VALUE self);
		VALUE rviewportE(VALUE self, VALUE viewport);
		VALUE rwindowskin(VALUE self);
		VALUE rwindowskinE(VALUE self, VALUE windowskin);
		VALUE rcontents(VALUE self);
		VALUE rcontentsE(VALUE self, VALUE contents);
		VALUE rstretch(VALUE self);
		VALUE rstretchE(VALUE self, VALUE stretch);
		VALUE rcursor_rect(VALUE self);
		VALUE rcursor_rectE(VALUE self, VALUE cursor_rect);
		VALUE ractive(VALUE self);
		VALUE ractiveE(VALUE self, VALUE active);
		VALUE rvisible(VALUE self);
		VALUE rvisibleE(VALUE self, VALUE visible);
		VALUE rpause(VALUE self);
		VALUE rpauseE(VALUE self, VALUE pause);
		VALUE rx(VALUE self);
		VALUE rfx(VALUE self);
		VALUE rxE(VALUE self, VALUE x);
		VALUE ry(VALUE self);
		VALUE rfy(VALUE self);
		VALUE ryE(VALUE self, VALUE y);
		VALUE rwidth(VALUE self);
		VALUE rwidthE(VALUE self, VALUE width);
		VALUE rheight(VALUE self);
		VALUE rheightE(VALUE self, VALUE height);
		VALUE rz(VALUE self);
		VALUE rzE(VALUE self, VALUE z);
		VALUE rox(VALUE self);
		VALUE roxE(VALUE self, VALUE ox);
		VALUE roy(VALUE self);
		VALUE royE(VALUE self, VALUE oy);
		VALUE ropacity(VALUE self);
		VALUE ropacityE(VALUE self, VALUE opacity);
		VALUE rback_opacity(VALUE self);
		VALUE rback_opacityE(VALUE self, VALUE back_opacity);
		VALUE rcontents_opacity(VALUE self);
		VALUE rcontents_opacityE(VALUE self, VALUE contents_opacity);

		//@}
	};
};

#endif
