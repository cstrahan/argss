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

#ifndef _ARUBY_H_
#define _ARUBY_H_

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
extern "C" {
	#include "ruby.h"
}

///////////////////////////////////////////////////////////
/// ARuby namespace.
/// It manages the ruby embedding.
///////////////////////////////////////////////////////////
namespace ARuby {
	///////////////////////////////////////////////////////
	/// Initializes ruby.
	///////////////////////////////////////////////////////
	void Init();

	///////////////////////////////////////////////////////
	/// Starts ruby.
	///////////////////////////////////////////////////////
	void Run();

	///////////////////////////////////////////////////////
	/// Stops ruby excecution.
	///////////////////////////////////////////////////////
	void Exit();

	///////////////////////////////////////////////////////
	/// Adds an object to the protected objects list.
	///////////////////////////////////////////////////////
	void AddObject(VALUE id);

	///////////////////////////////////////////////////////
	/// Removes an object from the protected objects list.
	///////////////////////////////////////////////////////
	void RemoveObject(VALUE id);

	///////////////////////////////////////////////////////
	/// Global ruby load_data function.
	/// Loads from filename a marshaled object.
	///////////////////////////////////////////////////////
	VALUE rload_data(VALUE self, VALUE filename);

	///////////////////////////////////////////////////////
	/// Global ruby save_data function.
	/// Saves to filename the given object marshaled.
	///////////////////////////////////////////////////////
	VALUE rsave_data(VALUE self, VALUE obj, VALUE filename);

	/// List of protected objects.
	/// Protected objects are not destroyed by ruby GC.
	/// Useful for classes like Bitmap that needs to be
	/// disposed before they can be totally destroyed.
	extern VALUE protected_objects;
}

///////////////////////////////////////////////////////////
// Useful ruby related functions and macros
///////////////////////////////////////////////////////////

/// C++ bool to Ruby boolean
#define BOOL2NUM(x) (x ? Qtrue : Qfalse)

/// Ruby boolean to C++ bool
#define NUM2BOOL(x) (x == Qtrue)

/// Quick form for raising wrong number of argument error
#define raise_argn(a, n) (rb_raise(rb_eArgError, "wrong number of arguments(%i for %i)", a, n))

/// Checks if a object is kind of
void Check_Kind(VALUE obj, VALUE kind);

/// Checks if a object is type1 or type2
void Check_Types2(VALUE obj, VALUE type1, VALUE type2);

/// Checks if a object is a boolean
void Check_Bool(VALUE obj);

/// Checks if a object is instance of class
void Check_Class(VALUE obj, VALUE _class);

/// Checks if a object is instance of class or nils
void Check_Classes_N(VALUE obj, VALUE _class);

/// Typedef for creating ruby methods
typedef VALUE (*rubyfunc)(...);

#endif
