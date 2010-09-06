/*
 *  inputbuttons_osx.h
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-15.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

#ifndef _INPUTBUTTONS_OSX_H_
#define _INPUTBUTTONS_OSX_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <vector>

////////////////////////////////////////////////////////////
/// Keys namespace
////////////////////////////////////////////////////////////
namespace Input {
	void InitButtons();
	extern std::map< int, std::vector<int> > buttons;
};

#endif