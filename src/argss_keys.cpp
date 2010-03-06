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
#include "argss_keys.h"
#include "input.h"

////////////////////////////////////////////////////////////
/// Global Variables
////////////////////////////////////////////////////////////
VALUE ARGSS::AKeys::id;

////////////////////////////////////////////////////////////
/// ARGSS Keys initialize
////////////////////////////////////////////////////////////
void ARGSS::AKeys::Init() {
    typedef VALUE (*rubyfunc)(...);
    id = rb_define_module("Keys");
	rb_define_const(id, "BACKSPACE", INT2FIX(1001));
	rb_define_const(id, "TAB", INT2FIX(1002));
	rb_define_const(id, "CLEAR", INT2FIX(1003));
	rb_define_const(id, "RETURN", INT2FIX(1004));
	rb_define_const(id, "PAUSE", INT2FIX(1005));
	rb_define_const(id, "ESCAPE", INT2FIX(1006));
	rb_define_const(id, "SPACE", INT2FIX(1007));
	rb_define_const(id, "PGUP", INT2FIX(1008));
	rb_define_const(id, "PGDN", INT2FIX(1009));
	rb_define_const(id, "ENDS", INT2FIX(1010));
	rb_define_const(id, "HOME", INT2FIX(1011));
	rb_define_const(id, "LEFT", INT2FIX(1012));
	rb_define_const(id, "UP", INT2FIX(1013));
	rb_define_const(id, "RIGHT", INT2FIX(1014));
	rb_define_const(id, "DOWN", INT2FIX(1015));
	rb_define_const(id, "SNAPSHOT", INT2FIX(1016));
	rb_define_const(id, "INSERT", INT2FIX(1017));
	rb_define_const(id, "DEL", INT2FIX(1018));
	rb_define_const(id, "LSHIFT", INT2FIX(1019));
	rb_define_const(id, "RSHIFT", INT2FIX(1020));
	rb_define_const(id, "LCTRL", INT2FIX(1021));
	rb_define_const(id, "RCTRL", INT2FIX(1022));
	rb_define_const(id, "LALT", INT2FIX(1023));
	rb_define_const(id, "RALT", INT2FIX(1024));
	rb_define_const(id, "N0", INT2FIX(1025));
	rb_define_const(id, "N1", INT2FIX(1026));
	rb_define_const(id, "N2", INT2FIX(1027));
	rb_define_const(id, "N3", INT2FIX(1028));
	rb_define_const(id, "N4", INT2FIX(1029));
	rb_define_const(id, "N5", INT2FIX(1030));
	rb_define_const(id, "N6", INT2FIX(1031));
	rb_define_const(id, "N7", INT2FIX(1032));
	rb_define_const(id, "N8", INT2FIX(1033));
	rb_define_const(id, "N9", INT2FIX(1034));
	rb_define_const(id, "A", INT2FIX(1035));
	rb_define_const(id, "B", INT2FIX(1036));
	rb_define_const(id, "C", INT2FIX(1037));
	rb_define_const(id, "D", INT2FIX(1038));
	rb_define_const(id, "E", INT2FIX(1039));
	rb_define_const(id, "F", INT2FIX(1040));
	rb_define_const(id, "G", INT2FIX(1041));
	rb_define_const(id, "H", INT2FIX(1042));
	rb_define_const(id, "I", INT2FIX(1043));
	rb_define_const(id, "J", INT2FIX(1044));
	rb_define_const(id, "K", INT2FIX(1045));
	rb_define_const(id, "L", INT2FIX(1046));
	rb_define_const(id, "M", INT2FIX(1047));
	rb_define_const(id, "N", INT2FIX(1048));
	rb_define_const(id, "O", INT2FIX(1049));
	rb_define_const(id, "P", INT2FIX(1050));
	rb_define_const(id, "Q", INT2FIX(1051));
	rb_define_const(id, "R", INT2FIX(1052));
	rb_define_const(id, "S", INT2FIX(1053));
	rb_define_const(id, "T", INT2FIX(1054));
	rb_define_const(id, "U", INT2FIX(1055));
	rb_define_const(id, "V", INT2FIX(1056));
	rb_define_const(id, "W", INT2FIX(1057));
	rb_define_const(id, "X", INT2FIX(1058));
	rb_define_const(id, "Y", INT2FIX(1059));
	rb_define_const(id, "Z", INT2FIX(1060));
	rb_define_const(id, "LOS", INT2FIX(1061));
	rb_define_const(id, "ROS", INT2FIX(1062));
	rb_define_const(id, "APPS", INT2FIX(1063));
	rb_define_const(id, "KP0", INT2FIX(1064));
	rb_define_const(id, "KP1", INT2FIX(1065));
	rb_define_const(id, "KP2", INT2FIX(1066));
	rb_define_const(id, "KP3", INT2FIX(1067));
	rb_define_const(id, "KP4", INT2FIX(1068));
	rb_define_const(id, "KP5", INT2FIX(1069));
	rb_define_const(id, "KP6", INT2FIX(1070));
	rb_define_const(id, "KP7", INT2FIX(1071));
	rb_define_const(id, "KP8", INT2FIX(1072));
	rb_define_const(id, "KP9", INT2FIX(1073));
	rb_define_const(id, "MULTIPLY", INT2FIX(1074));
	rb_define_const(id, "ADD", INT2FIX(1075));
	rb_define_const(id, "SEPARATOR", INT2FIX(1076));
	rb_define_const(id, "SUBTRACT", INT2FIX(1077));
	rb_define_const(id, "DECIMAL", INT2FIX(1078));
	rb_define_const(id, "DIVIDE", INT2FIX(1079));
	rb_define_const(id, "F1", INT2FIX(1080));
	rb_define_const(id, "F2", INT2FIX(1081));
	rb_define_const(id, "F3", INT2FIX(1082));
	rb_define_const(id, "F4", INT2FIX(1083));
	rb_define_const(id, "F5", INT2FIX(1084));
	rb_define_const(id, "F6", INT2FIX(1085));
	rb_define_const(id, "F7", INT2FIX(1086));
	rb_define_const(id, "F8", INT2FIX(1087));
	rb_define_const(id, "F9", INT2FIX(1088));
	rb_define_const(id, "F10", INT2FIX(1089));
	rb_define_const(id, "F11", INT2FIX(1090));
	rb_define_const(id, "F12", INT2FIX(1091));
	rb_define_const(id, "CAPS_LOCK", INT2FIX(1092));
	rb_define_const(id, "NUM_LOCK", INT2FIX(1093));
	rb_define_const(id, "SCROLL_LOCK", INT2FIX(1094));

	rb_define_const(id, "MOUSE_LEFT", INT2FIX(2001));
	rb_define_const(id, "MOUSE_RIGHT", INT2FIX(2002));
	rb_define_const(id, "MOUSE_MIDDLE", INT2FIX(2003));
	rb_define_const(id, "MOUSE_XBUTTON1", INT2FIX(2004));
	rb_define_const(id, "MOUSE_XBUTTON2", INT2FIX(2005));

	rb_define_const(id, "JOY_1", INT2FIX(3001));
	rb_define_const(id, "JOY_2", INT2FIX(3002));
	rb_define_const(id, "JOY_3", INT2FIX(3003));
	rb_define_const(id, "JOY_4", INT2FIX(3004));
	rb_define_const(id, "JOY_5", INT2FIX(3005));
	rb_define_const(id, "JOY_6", INT2FIX(3006));
	rb_define_const(id, "JOY_7", INT2FIX(3007));
	rb_define_const(id, "JOY_8", INT2FIX(3008));
	rb_define_const(id, "JOY_9", INT2FIX(3009));
	rb_define_const(id, "JOY_10", INT2FIX(3010));
	rb_define_const(id, "JOY_11", INT2FIX(3011));
	rb_define_const(id, "JOY_12", INT2FIX(3012));
	rb_define_const(id, "JOY_13", INT2FIX(3013));
	rb_define_const(id, "JOY_14", INT2FIX(3014));
	rb_define_const(id, "JOY_15", INT2FIX(3015));
	rb_define_const(id, "JOY_16", INT2FIX(3016));
	rb_define_const(id, "JOY_17", INT2FIX(3017));
	rb_define_const(id, "JOY_18", INT2FIX(3018));
	rb_define_const(id, "JOY_19", INT2FIX(3019));
	rb_define_const(id, "JOY_20", INT2FIX(3020));
	rb_define_const(id, "JOY_21", INT2FIX(3021));
	rb_define_const(id, "JOY_22", INT2FIX(3022));
	rb_define_const(id, "JOY_23", INT2FIX(3023));
	rb_define_const(id, "JOY_24", INT2FIX(3024));
	rb_define_const(id, "JOY_25", INT2FIX(3025));
	rb_define_const(id, "JOY_26", INT2FIX(3026));
	rb_define_const(id, "JOY_27", INT2FIX(3027));
	rb_define_const(id, "JOY_28", INT2FIX(3028));
	rb_define_const(id, "JOY_29", INT2FIX(3029));
	rb_define_const(id, "JOY_30", INT2FIX(3030));
	rb_define_const(id, "JOY_31", INT2FIX(3031));
	rb_define_const(id, "JOY_32", INT2FIX(3032));
}
