/*
 *  console_osx.h
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-15.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

#ifndef _CONSOLE_OSX_H_
#define _CONSOLE_OSX_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////
/// Console Namespace
////////////////////////////////////////////////////////////
namespace Console {
	void Init();
	void SetTitle(char* title);
	void SetLines(int lines);
	void Free();
	bool Active();
	void Write(std::string msg);
};

#endif