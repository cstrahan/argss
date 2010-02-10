//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
///         All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///     * Redistributions of source code must retain the above copyright
///       notice, this list of conditions and the following disclaimer.
///     * Redistributions in binary form must reproduce the above copyright
///       notice, this list of conditions and the following disclaimer in the
///       documentation and/or other materials provided with the distribution.
///
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
/// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
/// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
/// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
/// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
/// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
/// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////////

#ifndef _ARGSS_RUBY_H_
#define _ARGSS_RUBY_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <vector>
extern "C" {
    #include "ruby.h"
}

////////////////////////////////////////////////////////////
/// ARGSS::ARuby namespace
////////////////////////////////////////////////////////////
namespace ARGSS {
	namespace ARuby {
		void Init();
		void Run();

		void AddObject(VALUE id);
		void RemoveObject(VALUE id);
		extern VALUE protected_objects;

		VALUE rload_data(VALUE self, VALUE filename);
		VALUE rsave_data(VALUE self, VALUE obj, VALUE filename);
	}
}

////////////////////////////////////////////////////////////
/// Ruby macros
////////////////////////////////////////////////////////////
#define BOOL2NUM(x) (x ? Qtrue : Qfalse)
#define INT2BOOL(x) (x == 0 ? (VALUE)0 : (VALUE)2)
#define NUM2BOOL(x) (x == (VALUE)2)
#define raise_argn(a, n) (rb_raise(rb_eArgError, "wrong number of arguments(%i for %i)", a, n))

////////////////////////////////////////////////////////////
/// Object type checking
////////////////////////////////////////////////////////////
void Check_Kind(VALUE o, VALUE c);
void Check_Types2(VALUE x, VALUE t1, VALUE t2);
void Check_Bool(VALUE x);
void Check_Class(VALUE x, VALUE c);
void Check_Classes_N(VALUE x, VALUE c);

#endif
