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

#ifndef _INPUT_H_
#define _INPUT_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include "inputkeys.h"

////////////////////////////////////////////////////////////
/// Input namespace
////////////////////////////////////////////////////////////
namespace Input {
	void Init();
	void Update();
	void ClearKeys();
	bool IsPressed(int button);
	bool IsTriggered(int button);
	bool IsRepeated(int button);
	bool IsReleased(int button);
	unsigned long GetPressed();
	unsigned long GetTriggered();
	unsigned long GetRepeated();
	unsigned long GetReleased();

	extern std::vector<int> press_time;
	extern std::vector<bool> triggered;
	extern std::vector<bool> repeated;
	extern std::vector<bool> released;
	extern int dir4;
	extern int dir8;
	extern int start_repeat_time;
	extern int repeat_time;
};

#endif
