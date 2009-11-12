#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#ifdef WIN32
	#include "console_win32.h"
#endif
#ifdef OSX
	#include "console_osx.h"
#endif
#ifdef LINUX
	#include "console_linux.h"
#endif

void Init_Console();

#endif
