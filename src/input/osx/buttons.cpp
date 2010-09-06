/*
 *  inputbuttons_osx.cpp
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-15.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "inputbuttons_osx.h"
#include "inputkeys.h"
#include "registry_osx.h"
#include "options.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
std::map< int, std::vector<int> > Input::buttons;

////////////////////////////////////////////////////////////
/// Initialize
////////////////////////////////////////////////////////////
void Input::InitButtons() {
	bool standard = true;
	
	if (READ_BUTTON_ASSIGMENT) {
		std::string data = Registry::ReadStrValue(OSX_CONFIG_RGSS_SECTION_NAME, READ_BUTTON_ASSIGMENT_KEY, "");
		if (data.size() > 0) {
			for (int i = 11; i < 19; i++) {
				for (int j = 0; j < 15; j++) {
					if (JOYSTICK_SUPPORT && j < 10) {
						if (i == data[j]) {
							if (j == 0) buttons[i].push_back(Keys::JOY_1);
							if (j == 1) buttons[i].push_back(Keys::JOY_2);
							if (j == 2) buttons[i].push_back(Keys::JOY_3);
							if (j == 3) buttons[i].push_back(Keys::JOY_4);
							if (j == 4) buttons[i].push_back(Keys::JOY_5);
							if (j == 5) buttons[i].push_back(Keys::JOY_6);
							if (j == 6) buttons[i].push_back(Keys::JOY_7);
							if (j == 7) buttons[i].push_back(Keys::JOY_8);
							if (j == 8) buttons[i].push_back(Keys::JOY_9);
							if (j == 9) buttons[i].push_back(Keys::JOY_10);
						}
					}
					if (i == data[10 + j]) {
						if (j == 0) buttons[i].push_back(Keys::SPACE);
						if (j == 1) buttons[i].push_back(Keys::RETURN);
						if (j == 2) buttons[i].push_back(Keys::ESCAPE);
						if (j == 3) buttons[i].push_back(Keys::KP0);
						if (j == 4) buttons[i].push_back(Keys::SHIFT);
						if (j == 5) buttons[i].push_back(Keys::Z);
						if (j == 6) buttons[i].push_back(Keys::X);
						if (j == 7) buttons[i].push_back(Keys::C);
						if (j == 8) buttons[i].push_back(Keys::V);
						if (j == 9) buttons[i].push_back(Keys::B);
						if (j == 10) buttons[i].push_back(Keys::A);
						if (j == 11) buttons[i].push_back(Keys::S);
						if (j == 12) buttons[i].push_back(Keys::D);
						if (j == 13) buttons[i].push_back(Keys::Q);
						if (j == 14) buttons[i].push_back(Keys::W);
					}
				}
			}
			standard = false;
		}
	}
	if (standard) {
		buttons[11].push_back(Keys::Z);
		buttons[11].push_back(Keys::SHIFT);
		buttons[12].push_back(Keys::X);
		buttons[12].push_back(Keys::KP0);
		buttons[12].push_back(Keys::ESCAPE);
		buttons[13].push_back(Keys::SPACE);
		buttons[13].push_back(Keys::RETURN);
		buttons[13].push_back(Keys::C);
		buttons[14].push_back(Keys::A);
		buttons[15].push_back(Keys::S);
		buttons[16].push_back(Keys::D);
		buttons[17].push_back(Keys::Q);
		buttons[18].push_back(Keys::W);
		if (JOYSTICK_SUPPORT) {
			buttons[11].push_back(Keys::JOY_1);
			buttons[12].push_back(Keys::JOY_2);
			buttons[13].push_back(Keys::JOY_3);
			buttons[14].push_back(Keys::JOY_4);
			buttons[15].push_back(Keys::JOY_5);
			buttons[16].push_back(Keys::JOY_6);
			buttons[17].push_back(Keys::JOY_7);
			buttons[18].push_back(Keys::JOY_8);
		}
	}
	buttons[2].push_back(Keys::DOWN);
	buttons[4].push_back(Keys::LEFT);
	buttons[6].push_back(Keys::RIGHT);
	buttons[8].push_back(Keys::UP);
	buttons[21].push_back(Keys::SHIFT);
	buttons[22].push_back(Keys::CTRL);
	buttons[23].push_back(Keys::ALT);
	buttons[25].push_back(Keys::F5);
	buttons[26].push_back(Keys::F6);
	buttons[27].push_back(Keys::F7);
	buttons[28].push_back(Keys::F8);
	buttons[29].push_back(Keys::F9);
}