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

///////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////
#include "argss/classes/aerror.h"

///////////////////////////////////////////////////////////
// Global Variables
///////////////////////////////////////////////////////////
VALUE ARGSS::AError::id;

///////////////////////////////////////////////////////////
// ARGSS Error initialize
///////////////////////////////////////////////////////////
void ARGSS::AError::Init() {
	id = rb_define_class("ARGSSError", rb_eStandardError);
}

///////////////////////////////////////////////////////////
// FileNotFound
///////////////////////////////////////////////////////////
void ARGSS::AError::FileNotFound(std::string file) {
	VALUE enoent = rb_const_get(rb_mErrno, rb_intern("ENOENT"));
	rb_raise(enoent, "No such file or directory - %s", file.c_str());
}

///////////////////////////////////////////////////////////
// AudioNotLoad
///////////////////////////////////////////////////////////
void ARGSS::AError::AudioNotLoad(std::string type, std::string file) {
	rb_raise(ARGSS::AError::id, "couldn't load %s %s.\n", file.c_str(), type.c_str());
}

void ARGSS::AError::AudioNotLoad(std::string type, std::string file, std::string description) {
	rb_raise(ARGSS::AError::id, "couldn't load %s %s.\n%s\n", file.c_str(), type.c_str(), description.c_str());
}

///////////////////////////////////////////////////////////
// AudioNotPlay
///////////////////////////////////////////////////////////
void ARGSS::AError::AudioNotPlay(std::string type, std::string file) {
	rb_raise(ARGSS::AError::id, "couldn't play %s %s.\n", file.c_str(), type.c_str());
}

void ARGSS::AError::AudioNotPlay(std::string type, std::string file, std::string description) {
	rb_raise(ARGSS::AError::id, "couldn't play %s %s.\n%s\n", file.c_str(), type.c_str(), description.c_str());
}
