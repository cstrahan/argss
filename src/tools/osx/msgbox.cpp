/*
 *  msgbox_osx.cpp
 *  xcode
 *
 *  Created by Nicolas Pépin Perreault on 10-07-15.
 *  Copyright 2010 McGill University. All rights reserved.
 *
 */

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>
#include "CoreFoundation/CFUserNotification.h"
#include "msgbox_osx.h"

////////////////////////////////////////////////////////////
/// Static helper function
////////////////////////////////////////////////////////////
static bool displayMsgBox(std::string boxTitle, std::string message, unsigned int level) {
    CFStringRef cfsBoxTitle = CFStringCreateWithCString(NULL, boxTitle.c_str(), boxTitle.size());
    CFStringRef cfsMessage = CFStringCreateWithCString(NULL, message.c_str(), message.size());
    CFOptionFlags result;
	int alertLevel = kCFUserNotificationNoteAlertLevel;
	
	// Get the proper alert level
	switch(level) {
		case MSGBOX_LEVEL_ERROR: alertLevel = kCFUserNotificationStopAlertLevel; break;
		case MSGBOX_LEVEL_WARNING: alertLevel = kCFUserNotificationCautionAlertLevel; break;
		default: break;
	}
	
    // Show the message box
    CFUserNotificationDisplayAlert(
		0, // timeout in ms
		kCFUserNotificationNoteAlertLevel, // Notification level
		NULL, // Icon URL TODO
		NULL,
		NULL, // String localization
		cfsBoxTitle, 
		cfsMessage,
		NULL, // OK button text
		NULL, // Cancel (NO) button text
		NULL, // Third button text (when would we need it?)
		&result
	);
	
    // Clean up
    CFRelease(cfsBoxTitle);
    CFRelease(cfsMessage);
	
    // Return result
	return true; // TODO
}

////////////////////////////////////////////////////////////
/// Default Message Box with OK button
////////////////////////////////////////////////////////////
void MsgBox::OK(std::string msg, std::string title) {
	if (msg.length() == 0) return;
	if (msg.length() == 1 && (msg[0] == '\n' || msg[0] == '\r')) return;

	displayMsgBox(title, msg, MSGBOX_LEVEL_INFO);
}

////////////////////////////////////////////////////////////
/// Error Message Box
////////////////////////////////////////////////////////////
void MsgBox::Error(std::string msg, std::string title) {
	if (msg.length() == 0) return;
	if (msg.length() == 1 && (msg[0] == '\n' || msg[0] == '\r')) return;
	
	displayMsgBox(title, msg, MSGBOX_LEVEL_ERROR);
}

////////////////////////////////////////////////////////////
/// Warning Message Box
////////////////////////////////////////////////////////////
void MsgBox::Warning(std::string msg, std::string title) {
	if (msg.length() == 0) return;
	if (msg.length() == 1 && (msg[0] == '\n' || msg[0] == '\r')) return;
	
	displayMsgBox(title, msg, MSGBOX_LEVEL_WARNING);
}
