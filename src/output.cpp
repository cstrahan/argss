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
#include "output.h"
#include "options.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include "system.h"
#include "player.h"
#include "console.h"
#include "msgbox.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
int Output::output_type;
std::string Output::filename;

////////////////////////////////////////////////////////////
/// Output Initialize
////////////////////////////////////////////////////////////
void Output::Init(){
	output_type = OUTPUT_TYPE;
	filename = OUTPUT_FILE;
}

////////////////////////////////////////////////////////////
/// Output Error
////////////////////////////////////////////////////////////
void Output::Error(std::string err){
	Post(err);
	Player::Exit();
}

////////////////////////////////////////////////////////////
/// Output Warning
////////////////////////////////////////////////////////////
void Output::Warning(std::string warn) {
	Post(warn);
}

////////////////////////////////////////////////////////////
/// Output Post message
////////////////////////////////////////////////////////////
void Output::Post(std::string msg) {	
	switch(output_type) {
	case 1:
		if (Console::Active()) Console::Write(msg);
		break;
	case 2:
		if (!Console::Active()) Console::Init();
		Console::Write(msg);
		break;
	case 3:
		MsgBox::OK(msg, System::Title);
		break;
	case 4:
		PostFile(msg);
		break;
	case 5:
		if (Console::Active()) Console::Write(msg);
		else PostFile(msg);
		break;
	case 6:
		if (Console::Active()) Console::Write(msg);
		else MsgBox::OK(msg, System::Title);
	}
}

////////////////////////////////////////////////////////////
/// Output File
////////////////////////////////////////////////////////////
void Output::PostFile(std::string msg) {
	std::ofstream file;
	file.open(filename.c_str(), std::ios::out | std::ios::app);
	file << msg;
	file.close();
}

////////////////////////////////////////////////////////////
/// Output Console
////////////////////////////////////////////////////////////
void Output::Console() {
	if (!Console::Active()) Console::Init();
	output_type = 2;
}

////////////////////////////////////////////////////////////
/// Output Console
////////////////////////////////////////////////////////////
void Output::MsgBox() {
	if (Console::Active()) Console::Free();
	output_type = 3;
}

////////////////////////////////////////////////////////////
/// Output Console
////////////////////////////////////////////////////////////
void Output::File(std::string name) {
	if (Console::Active()) Console::Free();
	output_type = 4;
	filename = name;
}

////////////////////////////////////////////////////////////
/// Output Console
////////////////////////////////////////////////////////////
void Output::None() {
	if (Console::Active()) Console::Free();
	output_type = 0;
}