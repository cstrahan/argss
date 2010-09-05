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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "argss_tilemapautotiles_xp.h"
#include "argss_bitmap.h"

////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::ATilemapAutotiles::id;

////////////////////////////////////////////////////////////
/// ARGSS TilemapAutotiles ruby functions
////////////////////////////////////////////////////////////
VALUE ARGSS::ATilemapAutotiles::rinitialize(VALUE self) {
	rb_iv_set(self, "@autotiles", rb_ary_new2(8));
	return self;
}
VALUE ARGSS::ATilemapAutotiles::raref(VALUE self, VALUE index) {
	return rb_ary_entry(rb_iv_get(self, "@autotiles"), NUM2INT(index));
}
VALUE ARGSS::ATilemapAutotiles::raset(VALUE self, VALUE index, VALUE bitmap) {
	Check_Classes_N(bitmap, ARGSS::ABitmap::id);
	rb_ary_store(rb_iv_get(self, "@autotiles"), NUM2INT(index), bitmap);
	return bitmap;
}

////////////////////////////////////////////////////////////
/// ARGSS TilemapAutotiles initialize
////////////////////////////////////////////////////////////
void ARGSS::ATilemapAutotiles::Init() {
	typedef VALUE (*rubyfunc)(...);
	id = rb_define_class("TilemapAutotiles", rb_cObject);
	rb_define_method(id, "initialize", (rubyfunc)rinitialize, 0);
	rb_define_method(id, "[]", (rubyfunc)raref, 1);
	rb_define_method(id, "[]=", (rubyfunc)raset, 2);
}

////////////////////////////////////////////////////////////
/// ARGSS TilemapAutotiles new ruby instance
////////////////////////////////////////////////////////////
VALUE ARGSS::ATilemapAutotiles::New() {
	return rb_class_new_instance(0, 0, id);
}
