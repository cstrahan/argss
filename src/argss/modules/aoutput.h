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

#ifndef _ARGSS_OUTPUT_H_
#define _ARGSS_OUTPUT_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	///////////////////////////////////////////////////////
	/// ARGSS::Output namespace
	///////////////////////////////////////////////////////
	namespace AOutput {
		///////////////////////////////////////////////////
		/// Initialize Output module.
		///////////////////////////////////////////////////
		void Init();

		/// Output module id.
		extern VALUE id;

		/// Ruby stdout id.
		extern VALUE stdout_id;

		/// Ruby stderr id.
		extern VALUE stderr_id;

		/// Ruby stdin id.
		extern VALUE stdin_id;

		///////////////////////////////////////////////////
		/// Output module methods.
		///////////////////////////////////////////////////
		//@{

		VALUE rconsole(VALUE self);
		VALUE rmsgbox(VALUE self);
		VALUE rfile(VALUE self, VALUE file);
		VALUE rnone(VALUE self);
		VALUE rstdout_write(VALUE self, VALUE str);
		VALUE rstderr_write(VALUE self, VALUE str);
		VALUE stdin_gets(int argc, VALUE* argv, VALUE self);
		VALUE stdin_getc(int argc, VALUE* argv, VALUE self);

		//@}
	};
};

#endif
