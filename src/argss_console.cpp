//////////////////////////////////////////////////////////////////////////////////
/// ARGSS - Copyright (c) 2009, Alejandro Marzini (vgvgf) - All rights reserved.
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
#include <string>
#include "argss_console.h"
#include "console.h"
#include "log.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::AConsole::id;

////////////////////////////////////////////////////////////
/// ARGSS Console ruby functions
////////////////////////////////////////////////////////////
static VALUE argss_console_initialize(VALUE self) {
	Console::Init();
	// Console redirect for ruby don't work
	// since ARGSS refactoring in commit 19
	// Temp solution:
	rb_eval_string("$stdout.reopen('CONOUT$')");
	rb_eval_string("$stdin.reopen('CONIN$')");
	return Qnil;
}
static VALUE argss_console_set_max_lines(VALUE self, VALUE lines) {
	Console::SetLines(NUM2INT(lines));
	return Qnil;
}
static VALUE argss_console_set_title(VALUE self, VALUE title) {
	Console::SetTitle(StringValuePtr(title));
    return Qnil;
}
static VALUE argss_console_dispose(VALUE self) {
	Console::Free();
	return Qnil;
}

////////////////////////////////////////////////////////////
/// ARGSS Console initialize
////////////////////////////////////////////////////////////
void ARGSS::AConsole::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_module("Console");
    rb_define_singleton_method(id, "initialize", (rubyfunc)argss_console_initialize, 0);
    rb_define_singleton_method(id, "set_max_lines", (rubyfunc)argss_console_set_max_lines, 1);
    rb_define_singleton_method(id, "set_title", (rubyfunc)argss_console_set_title, 1);
    rb_define_singleton_method(id, "dispose", (rubyfunc)argss_console_dispose, 0);
}
