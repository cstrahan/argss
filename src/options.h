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

#define RPGXP 1
#define RPGVX 2

////////////////////////////////////////////////////////////
/// RPGMAKER
///   Defines RPG Maker compability, RPGXP for RPG Maker XP and RPGVX for
///   RPG Maker VX.
////////////////////////////////////////////////////////////
#define RPGMAKER RPGXP

////////////////////////////////////////////////////////////
/// GAME_TITLE
///   Window title to show.
///
/// SCRIPTS_PATH
///   Ruby scripts file path to load.
///
/// SCRIPTS_ZLIB
///   Flag for loading a zlib compressed ruby scripts file. (Like RMXP/VX)
///
/// RTP#
///   RTP 1, 2 and 3 names.
///
/// SCREEN_WIDTH SCREEN_HEIGHT
///   Screen default width and height.
///
/// ALLOW_FULLSCREEN_TOGGLE
///   Allows user to change fullscreen state.
///
/// RUN_FULLSCREEN
///   Run game in fullscreen mode.
///
/// PAUSE_GAME_WHEN_FOCUS_LOST PAUSE_AUDIO_WHEN_FOCUS_LOST
///   Pause the game process and/or audio when the argss window
///   looses its focus.
////////////////////////////////////////////////////////////
#define GAME_TITLE "ARGSS Player"
#define SCRIPTS_PATH "scripts.rb"
#define SCRIPTS_ZLIB false
#define RTP1 ""
#define RTP2 ""
#define RTP3 ""
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define ALLOW_FULLSCREEN_TOGGLE true
#define RUN_FULLSCREEN false
#define PAUSE_GAME_WHEN_FOCUS_LOST true
#define PAUSE_AUDIO_WHEN_FOCUS_LOST false

////////////////////////////////////////////////////////////
/// INI_NAME
///   INI configuration filename.
///
/// READ_INI_GAME_TITLE
///   Read game title from ini file.
///
/// READ_INI_SCRIPTS_PATH
///   Read scripts path file from ini file.
///
/// READ_INI_RTPS
///   Read rtps name from ini file.
///
/// READ_INI_SCREEN_SIZE
///   Read screen size from ini file.
////////////////////////////////////////////////////////////
#ifdef WIN32
#define INI_NAME ".\\ARGSS.ini"
#else
#define INI_NAME "ARGSS.ini"
#endif
#define READ_INI_GAME_TITLE true
#define READ_INI_SCRIPTS_PATH true
#define READ_INI_RTPS true
#define READ_INI_SCREEN_SIZE true

////////////////////////////////////////////////////////////
/// DEFAULT_FPS
///   Default fps rate.
///
/// DEFAULT_BACKCOLOR
///   Default back color for the player window.
///
/// UPDATE_ALL_KEYS
///   Update all keys or just the Input default buttons.
////////////////////////////////////////////////////////////
#define DEFAULT_FPS 60
#define DEFAULT_BACKCOLOR 0x00000000
#define UPDATE_ALL_KEYS true
#define JOYSTICK_SUPPORT true

////////////////////////////////////////////////////////////
/// DEBUG
///   Activate/deactivate debug.
///
/// DEBUG_VARIABLE
///   Ruby debug flag variable.
///
/// DEBUG_ONLY_FPS
///   Restrict FPS on title bar only for DEBUG.
////////////////////////////////////////////////////////////
#define RUBY_DEBUG true
#define DEBUG_VARIABLE "$DEBUG"
#define DEBUG_ONLY_FPS false

////////////////////////////////////////////////////////////
/// OUTPUT_TYPE
///   0 - None
///   1 - Console, if closed none
///   2 - Console, if closed open it
///   3 - Message Box
///   4 - File
///   5 - Try console, if closed file
///   6 - Try console, if closed message box
///
/// OUTPUT_FILE
///   Name of the file for output.
////////////////////////////////////////////////////////////
#define OUTPUT_TYPE 6
#define OUTPUT_FILE "out.txt"

////////////////////////////////////////////////////////////
/// Windows options
///
/// READ_BUTTON_ASSIGMENT
///   If true, tries to read from registry the button
///   assigment options.
///
/// READ_BUTTON_ASSIGMENT_KEY
///   Registry key.
///
/// READ_BUTTON_ASSIGMENT_VALUE
///   Registry entry value.
////////////////////////////////////////////////////////////
#define READ_BUTTON_ASSIGMENT true
#define READ_BUTTON_ASSIGMENT_KEY "SOFTWARE\\Enterbrain\\RGSS"
#define READ_BUTTON_ASSIGMENT_VALUE "ButtonAssign"

////////////////////////////////////////////////////////////
/// OSX options
///
/// OSX_CONFIG_FILE
/// Path to the OSX configuration file; you can use the
/// tilde (~) so that it looks it up from the current user's
/// home directory. It has to be a ini file too.
/// 
////////////////////////////////////////////////////////////
#define OSX_CONFIG_FILE "/Users/npepinpe/argss/config.ini"
#define OSX_DEF_RPGXP_RTP "rpgxp/rtp"
#define OSX_DEF_RPGVX_RTP "rpgvx/rtp"
#define OSX_CONFIG_RPGXP_SECTION_NAME "RPGXP"
#define OSX_CONFIG_RPGVX_SECTION_NAME "RPGVX"
#define OSX_CONFIG_RTPPATH_KEY_NAME "RTP_PATH"
#define OSX_CONFIG_RGSS_SECTION_NAME "RGSS"
