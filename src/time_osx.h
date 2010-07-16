/*
 *  time_osx.h
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-16.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

#ifndef _TIME_OSX_H_
#define _TIME_OSX_H_

////////////////////////////////////////////////////////////
/// Time namespace
////////////////////////////////////////////////////////////
namespace Time {
	long GetTime();
	void SleepMs(long ms);
};

#endif