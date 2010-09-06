/*
 *  filefinder_osx.cpp
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-15.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "filefinder_osx.h"
#include "system.h"
#include "options.h"
#include "registry_osx.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
std::string FileFinder::rtp_paths[3];

////////////////////////////////////////////////////////////
/// FileFinder initialization
////////////////////////////////////////////////////////////
void FileFinder::Init() {
	for (int i = 0; i < 3; i++) {
		if (System::RTPS[i] == "") continue;
		if (RPGMAKER == RPGXP) {
			rtp_paths[i] = Registry::ReadStrValue(OSX_CONFIG_RPGXP_SECTION_NAME, OSX_CONFIG_RTPPATH_KEY_NAME, System::RTPS[i]);
		}
		else if (RPGMAKER == RPGVX) {
			rtp_paths[i] = Registry::ReadStrValue(OSX_CONFIG_RPGVX_SECTION_NAME, OSX_CONFIG_RTPPATH_KEY_NAME, System::RTPS[i]);
		}
	}
}

////////////////////////////////////////////////////////////
/// Check if file exists
////////////////////////////////////////////////////////////
bool fexists(std::string filename) {
	std::ifstream file(filename.c_str());
	return file.is_open();
}

////////////////////////////////////////////////////////////
/// Make path
////////////////////////////////////////////////////////////
std::string slasher(std::string str) {
	for(unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == '\\') {
			str[i] = '/';
		}
	}
	return str;
}

////////////////////////////////////////////////////////////
/// Find image
////////////////////////////////////////////////////////////
std::string FileFinder::FindImage(std::string name) {
	name = slasher(name);
	std::string path;
	path = name;
	if (fexists(path)) return path;
	path = name; path += ".bmp";
	if (fexists(path)) return path;
	path = name; path += ".gif";
	if (fexists(path)) return path;
	path = name; path += ".jpg";
	if (fexists(path)) return path;
	path = name; path += ".jpeg";
	if (fexists(path)) return path;
	path = name; path += ".png";
	if (fexists(path)) return path;
	for (int i = 0; i < 3; i++) {
		if (rtp_paths[i] != "") {
			std::string rtp_path = slasher(rtp_paths[i]);
			rtp_path += name;
			path = rtp_path;
			if (fexists(path)) return path;
			path = rtp_path; path += ".bmp";
			if (fexists(path)) return path;
			path = rtp_path; path += ".gif";
			if (fexists(path)) return path;
			path = rtp_path; path += ".jpg";
			if (fexists(path)) return path;
			path = rtp_path; path += ".jpeg";
			if (fexists(path)) return path;
			path = rtp_path; path += ".png";
			if (fexists(path)) return path;
		}
	}
	return "";
}

////////////////////////////////////////////////////////////
/// Find music
////////////////////////////////////////////////////////////
std::string FileFinder::FindMusic(std::string name) {
	name = slasher(name);
	std::string path;
	path = name;
	if (fexists(path)) return path;
	path = name; path += ".wav";
	if (fexists(path)) return path;
	path = name; path += ".mid";
	if (fexists(path)) return path;
	path = name; path += ".midi";
	if (fexists(path)) return path;
	path = name; path += ".ogg";
	if (fexists(path)) return path;
	path = name; path += ".mp3";
	if (fexists(path)) return path;
	for (int i = 0; i < 3; i++) {
		if (rtp_paths[i] != "") {
			std::string rtp_path = slasher(rtp_paths[i]);
			rtp_path += name;
			path = rtp_path;
			if (fexists(path)) return path;
			path = rtp_path; path += ".wav";
			if (fexists(path)) return path;
			path = rtp_path; path += ".mid";
			if (fexists(path)) return path;
			path = rtp_path; path += ".midi";
			if (fexists(path)) return path;
			path = rtp_path; path += ".ogg";
			if (fexists(path)) return path;
			path = rtp_path; path += ".mp3";
			if (fexists(path)) return path;
		}
	}
	return "";
}

////////////////////////////////////////////////////////////
/// Find font
////////////////////////////////////////////////////////////
std::string FileFinder::FindFont(std::string name) {
	name = slasher(name);
	std::string path;
	path = name;
	if (fexists(path)) return path;
	path = name; path += ".ttf";
	if (fexists(path)) return path;
	
	path = USER_FONTS_PATH; path += name;
	if (fexists(path)) return path;
	path = LOCAL_FONTS_PATH; path += name; path += ".ttf";
	if (fexists(path)) return path;
	
	return "";
}