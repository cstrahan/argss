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
#include "inputkeys.h"
#include "argss_ruby.h"

////////////////////////////////////////////////////////////
/// VALUE to key
////////////////////////////////////////////////////////////
Input::Keys::InputKey Input::NUM2KEY(VALUE num) {
    switch (NUM2INT(num))
	{
		case 1001 : return Keys::BACKSPACE;
		case 1002 : return Keys::TAB;
		case 1003 : return Keys::CLEAR;
		case 1004 : return Keys::RETURN;
		case 1005 : return Keys::PAUSE;
		case 1006 : return Keys::ESCAPE;
		case 1007 : return Keys::SPACE;
		case 1008 : return Keys::PGUP;
		case 1009 : return Keys::PGDN;
		case 1010 : return Keys::ENDS;
		case 1011 : return Keys::HOME;
		case 1012 : return Keys::LEFT;
		case 1013 : return Keys::UP;
		case 1014 : return Keys::RIGHT;
		case 1015 : return Keys::DOWN;
		case 1016 : return Keys::SNAPSHOT;
		case 1017 : return Keys::INSERT;
		case 1018 : return Keys::DEL;
		case 1019 : return Keys::SHIFT;
		case 1020 : return Keys::LSHIFT;
		case 1021 : return Keys::RSHIFT;
		case 1022 : return Keys::CTRL;
		case 1023 : return Keys::LCTRL;
		case 1024 : return Keys::RCTRL;
		case 1025 : return Keys::ALT;
		case 1026 : return Keys::LALT;
		case 1027 : return Keys::RALT;
		case 1028 : return Keys::N0;
		case 1029 : return Keys::N1;
		case 1030 : return Keys::N2;
		case 1031 : return Keys::N3;
		case 1032 : return Keys::N4;
		case 1033 : return Keys::N5;
		case 1034 : return Keys::N6;
		case 1035 : return Keys::N7;
		case 1036 : return Keys::N8;
		case 1037 : return Keys::N9;
		case 1038 : return Keys::A;
		case 1039 : return Keys::B;
		case 1040 : return Keys::C;
		case 1041 : return Keys::D;
		case 1042 : return Keys::E;
		case 1043 : return Keys::F;
		case 1044 : return Keys::G;
		case 1045 : return Keys::H;
		case 1046 : return Keys::I;
		case 1047 : return Keys::J;
		case 1048 : return Keys::K;
		case 1049 : return Keys::L;
		case 1050 : return Keys::M;
		case 1051 : return Keys::N;
		case 1052 : return Keys::O;
		case 1053 : return Keys::P;
		case 1054 : return Keys::Q;
		case 1055 : return Keys::R;
		case 1056 : return Keys::S;
		case 1057 : return Keys::T;
		case 1058 : return Keys::U;
		case 1059 : return Keys::V;
		case 1060 : return Keys::W;
		case 1061 : return Keys::X;
		case 1062 : return Keys::Y;
		case 1063 : return Keys::Z;
		case 1064 : return Keys::LOS;
		case 1065 : return Keys::ROS;
		case 1066 : return Keys::APPS;
		case 1067 : return Keys::KP0;
		case 1068 : return Keys::KP1;
		case 1069 : return Keys::KP2;
		case 1070 : return Keys::KP3;
		case 1071 : return Keys::KP4;
		case 1072 : return Keys::KP5;
		case 1073 : return Keys::KP6;
		case 1074 : return Keys::KP7;
		case 1075 : return Keys::KP8;
		case 1076 : return Keys::KP9;
		case 1077 : return Keys::MULTIPLY;
		case 1078 : return Keys::ADD;
		case 1079 : return Keys::SEPARATOR;
		case 1080 : return Keys::SUBTRACT;
		case 1081 : return Keys::DECIMAL;
		case 1082 : return Keys::DIVIDE;
		case 1083 : return Keys::F1;
		case 1084 : return Keys::F2;
		case 1085 : return Keys::F3;
		case 1086 : return Keys::F4;
		case 1087 : return Keys::F5;
		case 1088 : return Keys::F6;
		case 1089 : return Keys::F7;
		case 1090 : return Keys::F8;
		case 1091 : return Keys::F9;
		case 1092 : return Keys::F10;
		case 1093 : return Keys::F11;
		case 1094 : return Keys::F12;
		case 1095 : return Keys::CAPS_LOCK;
		case 1096 : return Keys::NUM_LOCK;
		case 1097 : return Keys::SCROLL_LOCK;

		case 2001:	return Keys::MOUSE_LEFT;
		case 2002:	return Keys::MOUSE_RIGHT;
		case 2003:	return Keys::MOUSE_MIDDLE;
		case 2004:	return Keys::MOUSE_XBUTTON1;
		case 2005:	return Keys::MOUSE_XBUTTON2;

		case 3001:	return Keys::JOY_1;
		case 3002:	return Keys::JOY_2;
		case 3003:	return Keys::JOY_3;
		case 3004:	return Keys::JOY_4;
		case 3005:	return Keys::JOY_5;
		case 3006:	return Keys::JOY_6;
		case 3007:	return Keys::JOY_7;
		case 3008:	return Keys::JOY_8;
		case 3009:	return Keys::JOY_9;
		case 3010:	return Keys::JOY_10;
		case 3011:	return Keys::JOY_11;
		case 3012:	return Keys::JOY_12;
		case 3013:	return Keys::JOY_13;
		case 3014:	return Keys::JOY_14;
		case 3015:	return Keys::JOY_15;
		case 3016:	return Keys::JOY_16;
		case 3017:	return Keys::JOY_17;
		case 3018:	return Keys::JOY_18;
		case 3019:	return Keys::JOY_19;
		case 3020:	return Keys::JOY_20;
		case 3021:	return Keys::JOY_21;
		case 3022:	return Keys::JOY_22;
		case 3023:	return Keys::JOY_23;
		case 3024:	return Keys::JOY_24;
		case 3025:	return Keys::JOY_25;
		case 3026:	return Keys::JOY_26;
		case 3027:	return Keys::JOY_27;
		case 3028:	return Keys::JOY_28;
		case 3029:	return Keys::JOY_29;
		case 3030:	return Keys::JOY_30;
		case 3031:	return Keys::JOY_31;
		case 3032:	return Keys::JOY_32;
    }
	return Keys::InputKey(0);
}

////////////////////////////////////////////////////////////
/// Key to VALUE
////////////////////////////////////////////////////////////
VALUE Input::KEY2NUM(int key) {
	return INT2NUM(key + 1000);
}
