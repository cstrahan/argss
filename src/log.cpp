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
#include "log.h"
#include "options.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "msgbox.h"
#include "system.h"
#include "console.h"

////////////////////////////////////////////////////////////
/// Log Fatal Error
////////////////////////////////////////////////////////////
void Log::Fatal(std::string err){
	Post(err);
	exit(1);
}

////////////////////////////////////////////////////////////
/// Log Warning
////////////////////////////////////////////////////////////
void Log::Warning(std::string warn) {
	Post(warn);
}

////////////////////////////////////////////////////////////
/// Log Post message
////////////////////////////////////////////////////////////
void Log::Post(std::string msg) {
	std::ofstream file;
	switch(ERROR_REPORT) {
	case 1:
		std::cout << msg;
		break;
	case 2:
		file.open(ERROR_FILE, std::ios::out | std::ios::app);
		file << msg;
		file.close();
		break;
	case 3:
		MsgBox::OK(msg, System::Title);
		break;
	case 4:
		if(Console::Active()) {
			std::cout << msg;
		}
		else {
			file.open(ERROR_FILE, std::ios::out | std::ios::app);
			file << msg;
			file.close();
		}
		break;
	case 5:
		if(Console::Active()) {
			std::cout << msg;
		}
		else {
			MsgBox::OK(msg, System::Title);
		}
		break;
	case 6:
		if(!Console::Active()) {
			Console::Init();
		}
		std::cout << msg;
	}
}
