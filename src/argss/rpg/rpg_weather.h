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

#ifndef _ARGSS_RPG_WEATHER_H_
#define _ARGSS_RPG_WEATHER_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "aruby.h"

namespace ARGSS {
	namespace ARPG {
		///////////////////////////////////////////////////
		/// ARGSS::RPG::Weather namespace
		///////////////////////////////////////////////////
		namespace AWeather {
			///////////////////////////////////////////////
			/// Initialize Weather class.
			///////////////////////////////////////////////
			void Init();

			/// Weather class id.
			extern VALUE id;

			///////////////////////////////////////////////
			/// Weather instance methods.
			///////////////////////////////////////////////
			//@{

			VALUE rinitialize(int argc, VALUE* argv, VALUE self);
			VALUE rdispose(VALUE self);
			VALUE rtypeE(VALUE self, VALUE type);
			VALUE roxE(VALUE self, VALUE ox);
			VALUE royE(VALUE self, VALUE oy);
			VALUE rmaxE(VALUE self, VALUE max);
			VALUE rupdate(VALUE self);

			//@}
		};
	};
};

#endif
