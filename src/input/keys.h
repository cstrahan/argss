/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

#ifndef _INPUT_KEYS_H_
#define _INPUT_KEYS_H_

///////////////////////////////////////////////////////////
/// Keys namespace
///////////////////////////////////////////////////////////
namespace Input {
	namespace Keys {
		enum InputKey {
			BACKSPACE,
			TAB,
			CLEAR,
			RETURN,
			PAUSE,
			ESCAPE,
			SPACE,
			PGUP,
			PGDN,
			ENDS,
			HOME,
			LEFT,
			UP,
			RIGHT,
			DOWN,
			SNAPSHOT,
			INSERT,
			DEL,
			SHIFT,
			LSHIFT,
			RSHIFT,
			CTRL,
			LCTRL,
			RCTRL,
			ALT,
			LALT,
			RALT,
			N0,
			N1,
			N2,
			N3,
			N4,
			N5,
			N6,
			N7,
			N8,
			N9,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			LOS,
			ROS,
			APPS,
			KP0,
			KP1,
			KP2,
			KP3,
			KP4,
			KP5,
			KP6,
			KP7,
			KP8,
			KP9,
			MULTIPLY,
			ADD,
			SEPARATOR,
			SUBTRACT,
			DECIMAL,
			DIVIDE,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			CAPS_LOCK,
			NUM_LOCK,
			SCROLL_LOCK,

			MOUSE_LEFT,
			MOUSE_RIGHT,
			MOUSE_MIDDLE,
			MOUSE_XBUTTON1,
			MOUSE_XBUTTON2,

			JOY_1,
			JOY_2,
			JOY_3,
			JOY_4,
			JOY_5,
			JOY_6,
			JOY_7,
			JOY_8,
			JOY_9,
			JOY_10,
			JOY_11,
			JOY_12,
			JOY_13,
			JOY_14,
			JOY_15,
			JOY_16,
			JOY_17,
			JOY_18,
			JOY_19,
			JOY_20,
			JOY_21,
			JOY_22,
			JOY_23,
			JOY_24,
			JOY_25,
			JOY_26,
			JOY_27,
			JOY_28,
			JOY_29,
			JOY_30,
			JOY_31,
			JOY_32,

			KEYS_COUNT
		};
	};

	Keys::InputKey NUM2KEY(unsigned long num);
	unsigned long KEY2NUM(int key);
};

#endif
