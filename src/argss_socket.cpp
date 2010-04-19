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

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "argss_socket.h"
#include "socket.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ASocket::id;

////////////////////////////////////////////////////////////
/// Socket initialize function
////////////////////////////////////////////////////////////
VALUE ARGSS::ASocket::rinitialize(VALUE self) {
	
    return self;
}

////////////////////////////////////////////////////////////
/// Connect
////////////////////////////////////////////////////////////
VALUE ARGSS::ASocket::rconnect(VALUE self, VALUE host, VALUE port) {
	
	return Qnil;
}

////////////////////////////////////////////////////////////
/// Listen
////////////////////////////////////////////////////////////
VALUE ARGSS::ASocket::rlisten(VALUE self, VALUE port) {

	return Qnil;
}

////////////////////////////////////////////////////////////
/// Shutdown
////////////////////////////////////////////////////////////
VALUE ARGSS::ASocket::rshutdown(VALUE self) {

	return Qnil;
}


////////////////////////////////////////////////////////////
/// ASocket initialize
////////////////////////////////////////////////////////////
void ARGSS::ASocket::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_class("ASocket", rb_cObject);
    rb_define_method(id, "initialize", (rubyfunc)rinitialize, 0);
    rb_define_method(id, "connect", (rubyfunc)rconnect, 2);
	rb_define_method(id, "listen", (rubyfunc)rlisten, 1);
    rb_define_method(id, "shutdown", (rubyfunc)rshutdown, 0);
}