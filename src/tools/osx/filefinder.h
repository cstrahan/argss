/*
 *  filefinder_osx.h
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-15.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

#ifndef _FILEFINDER_OSX_H_
#define _FILEFINDER_OSX_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////
/// Defines
////////////////////////////////////////////////////////////
#define USER_FONTS_PATH "~/Library/Fonts"
#define LOCAL_FONTS_PATH "/Library/Fonts"

////////////////////////////////////////////////////////////
/// FileFinder namespace
////////////////////////////////////////////////////////////
namespace FileFinder {
	void Init();
	std::string FindImage(std::string name);
	std::string FindMusic(std::string name);
	std::string FindFont(std::string name);
	
	extern std::string rtp_paths[3];
};

#endif