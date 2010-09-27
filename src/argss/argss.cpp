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
#include <string>

extern "C" {
	#include "ruby.h"
}

#include "argss/argss.h"
#include "argss/classes/abitmap.h"
#include "argss/classes/acolor.h"
#include "argss/classes/afont.h"
#include "argss/classes/aerror.h"
#include "argss/classes/aplane.h"
#include "argss/classes/arect.h"
#include "argss/classes/asprite.h"
#include "argss/classes/atable.h"
#include "argss/classes/atilemap.h"
#include "argss/classes/atone.h"
#include "argss/classes/aviewport.h"
#include "argss/classes/awindow.h"
#include "argss/modules/aaudio.h"
#include "argss/modules/agraphics.h"
#include "argss/modules/ainput.h"
#include "argss/modules/akeys.h"
#include "argss/modules/aoutput.h"
#include "argss/rpg/rpg.h"
#include "argss/rpg/rpg_cache.h"
#include "argss/rpg/rpg_weather.h"
#include "argss/rpg/rpg_sprite.h"

///////////////////////////////////////////////////////////
// Initialize
///////////////////////////////////////////////////////////
void ARGSS::Init() {
	ARGSS::ABitmap::Init();
	ARGSS::AColor::Init();
	ARGSS::AError::Init();
	ARGSS::AFont::Init();
	ARGSS::APlane::Init();
	ARGSS::ARect::Init();
	ARGSS::ASprite::Init();
	ARGSS::ATable::Init();
	ARGSS::ATilemap::Init();
	ARGSS::ATone::Init();
	ARGSS::AViewport::Init();
	ARGSS::AWindow::Init();

	ARGSS::AAudio::Init();
	ARGSS::AGraphics::Init();
	ARGSS::AInput::Init();
	ARGSS::AKeys::Init();
	ARGSS::AOutput::Init();

	ARGSS::ARPG::Init();
	/*ARGSS::ARPG::ACache::Init();
	ARGSS::ARPG::ASprite::Init();
	ARGSS::ARPG::AWeather::Init();*/
}
