#include "input.h"
#include "../argss.h"
#include "../sfml.h"
#include "../classes/aerror.h"

const sf::Input& SFML_Input = SFML_Window.GetInput();
unsigned int KeysPressTime[sf::Key::Count];
bool KeysTriggered[sf::Key::Count];
bool KeysRepeat[sf::Key::Count];
bool KeysReleased[sf::Key::Count];
unsigned int Dir4;
unsigned int Dir8;

sf::Key::Code argss_input_num2key(int key) {
    switch (key) {
        case 301 :    return sf::Key::A;
        case 302 :    return sf::Key::B;
        case 303 :    return sf::Key::C;
        case 304 :    return sf::Key::D;
        case 305 :    return sf::Key::E;
        case 306 :    return sf::Key::F;
        case 307 :    return sf::Key::G;
        case 308 :    return sf::Key::H;
        case 309 :    return sf::Key::I;
        case 310 :    return sf::Key::J;
        case 311 :    return sf::Key::K;
        case 312 :    return sf::Key::L;
        case 313 :    return sf::Key::M;
        case 314 :    return sf::Key::N;
        case 315 :    return sf::Key::O;
        case 316 :    return sf::Key::P;
        case 317 :    return sf::Key::Q;
        case 318 :    return sf::Key::R;
        case 319 :    return sf::Key::S;
        case 320 :    return sf::Key::T;
        case 321 :    return sf::Key::U;
        case 322 :    return sf::Key::V;
        case 323 :    return sf::Key::W;
        case 324 :    return sf::Key::X;
        case 325 :    return sf::Key::Y;
        case 326 :    return sf::Key::Z;
        case 327 :    return sf::Key::Num0;
        case 328 :    return sf::Key::Num1;
        case 329 :    return sf::Key::Num2;
        case 330 :    return sf::Key::Num3;
        case 331 :    return sf::Key::Num4;
        case 332 :    return sf::Key::Num5;
        case 333 :    return sf::Key::Num6;
        case 334 :    return sf::Key::Num7;
        case 335 :    return sf::Key::Num8;
        case 336 :    return sf::Key::Num9;
        case 337 :    return sf::Key::Escape;
        case 338 :    return sf::Key::LControl;
        case 339 :    return sf::Key::LShift;
        case 340 :    return sf::Key::LAlt;
        case 341 :    return sf::Key::LSystem;
        case 342 :    return sf::Key::RControl;
        case 343 :    return sf::Key::RShift;
        case 344 :    return sf::Key::RAlt;
        case 345 :    return sf::Key::RSystem;
        case 346 :    return sf::Key::Menu;
        case 347 :    return sf::Key::Space;
        case 348 :    return sf::Key::Return;
        case 349 :    return sf::Key::Back;
        case 350 :    return sf::Key::Tab;
        case 351 :    return sf::Key::PageUp;
        case 352 :    return sf::Key::PageDown;
        case 353 :    return sf::Key::End;
        case 354 :    return sf::Key::Home;
        case 355 :    return sf::Key::Insert;
        case 356 :    return sf::Key::Delete;
        case 357 :    return sf::Key::Add;
        case 358 :    return sf::Key::Subtract;
        case 359 :    return sf::Key::Multiply;
        case 360 :    return sf::Key::Divide;
        case 361 :    return sf::Key::Left;
        case 362 :    return sf::Key::Right;
        case 363 :    return sf::Key::Up;
        case 364 :    return sf::Key::Down;
        case 365 :    return sf::Key::Numpad0;
        case 366 :    return sf::Key::Numpad1;
        case 367 :    return sf::Key::Numpad2;
        case 368 :    return sf::Key::Numpad3;
        case 369 :    return sf::Key::Numpad4;
        case 370 :    return sf::Key::Numpad5;
        case 371 :    return sf::Key::Numpad6;
        case 372 :    return sf::Key::Numpad7;
        case 373 :    return sf::Key::Numpad8;
        case 374 :    return sf::Key::Numpad9;
        case 375 :    return sf::Key::F1;
        case 376 :    return sf::Key::F2;
        case 377 :    return sf::Key::F3;
        case 378 :    return sf::Key::F4;
        case 379 :    return sf::Key::F5;
        case 380 :    return sf::Key::F6;
        case 381 :    return sf::Key::F7;
        case 382 :    return sf::Key::F8;
        case 383 :    return sf::Key::F9;
        case 384 :    return sf::Key::F10;
        case 385 :    return sf::Key::F11;
        case 386 :    return sf::Key::F12;
        case 387 :    return sf::Key::F13;
        case 388 :    return sf::Key::F14;
        case 389 :    return sf::Key::F15;
        case 390 :    return sf::Key::F16;
        case 391 :    return sf::Key::F17;
        case 392 :    return sf::Key::F18;
        case 393 :    return sf::Key::F19;
        case 394 :    return sf::Key::F20;
        case 395 :    return sf::Key::F21;
        case 396 :    return sf::Key::F22;
        case 397 :    return sf::Key::F23;
        case 398 :    return sf::Key::F24;
        case 399 :    return sf::Key::Pause;
        case 400 :    return sf::Key::Cancel;
        case 401 :    return sf::Key::Clear;
        case 402 :    return sf::Key::Snapshot;
        case 403 :    return sf::Key::Select;
        case 404 :    return sf::Key::Print;
        case 405 :    return sf::Key::Execute;
        case 406 :    return sf::Key::Help;
        case 407 :    return sf::Key::Separator;
        case 408 :    return sf::Key::Decimal;
        case 409 :    return sf::Key::CapsLock;
        case 410 :    return sf::Key::NumLock;
        case 411 :    return sf::Key::ScrollLock;
        case 412 :    return sf::Key::Oem1;
        case 413 :    return sf::Key::Oem2;
        case 414 :    return sf::Key::Oem3;
        case 415 :    return sf::Key::Oem4;
        case 416 :    return sf::Key::Oem5;
        case 417 :    return sf::Key::Oem6;
        case 418 :    return sf::Key::Oem7;
        case 419 :    return sf::Key::Oem8;
        case 420 :    return sf::Key::Oem102;
        case 421 :    return sf::Key::Plus;
        case 422 :    return sf::Key::Comma;
        case 423 :    return sf::Key::Minus;
        case 424 :    return sf::Key::Period;
        case 425 :    return sf::Key::OemClear;
        case 426 :    return sf::Key::Kana;
        case 427 :    return sf::Key::Junja;
        case 428 :    return sf::Key::Final;
        case 429 :    return sf::Key::Kanji;
        case 430 :    return sf::Key::Convert;
        case 431 :    return sf::Key::NonConvert;
        case 432 :    return sf::Key::Accept;
        case 433 :    return sf::Key::ModeChange;
    }
    return sf::Key::Code(0);
}

static VALUE argss_input_update(VALUE self) {
    int i, e;
    argss_update();
    for (i = 0; i < sf::Key::Count; ++i) {
        if(SFML_Input.IsKeyDown(sf::Key::Code(i))) {
            KeysPressTime[i] += 1;
            KeysReleased[i] = false;
        }
        else {
            if(KeysPressTime[i] > 0) {
                KeysReleased[i] = true;
            }
            else {
                KeysReleased[i] = false;
            }
            KeysPressTime[i] = 0;
        }
        if(KeysPressTime[i] > 0) {
            if (KeysPressTime[i] == 1) {
				KeysTriggered[i] = true;
            }
			else {
				KeysTriggered[i] = false;
			}
			if (KeysPressTime[i] == 1 || (KeysPressTime[i] >= ARGSS_Input_StartRepeatTime &&
                                            KeysPressTime[i] % ARGSS_Input_RepeatTime == 0)) {
				KeysRepeat[i] = true;
            }
			else {
				KeysRepeat[i] = false;
			}
        }
        else {
            KeysTriggered[i] = false;
            KeysRepeat[i] = false;
        }
    }
    VALUE dirkeys;
    char keysvar[10];
    unsigned int dirpress[10];
    for(i = 1; i < 10; i++) {
        if(i != 5) {
            sprintf(keysvar, "@@dirkeys%d", i);
            dirkeys = rb_cv_get(ARGSS_Input, keysvar);
            unsigned int presstime;
            for(e = 0; e < RARRAY(dirkeys)->len; e++) {
                presstime = KeysPressTime[argss_input_num2key(NUM2INT(rb_ary_entry(dirkeys, e)))];
                if(presstime > dirpress[i]) {
                    dirpress[i] = presstime;
                }
            }
        }
    }

	dirpress[1]	+= (dirpress[2] > 0 && dirpress[4] > 0) ? dirpress[2] + dirpress[4] : 0;
	dirpress[3]	+= (dirpress[2] > 0 && dirpress[6] > 0) ? dirpress[2] + dirpress[6] : 0;
	dirpress[7]	+= (dirpress[8] > 0 && dirpress[4] > 0) ? dirpress[8] + dirpress[4] : 0;
	dirpress[9]	+= (dirpress[8] > 0 && dirpress[6] > 0) ? dirpress[8] + dirpress[6] : 0;

	Dir4 = 0;
	Dir8 = 0;

	if (!(dirpress[2] > 0 && dirpress[8] > 0) && !(dirpress[4] > 0 && dirpress[6] > 0)) {
		e = 0;
		for(i = 0; i < 4; i++) {
			if (dirpress[(i + 1) * 2] > 0) {
				if (Dir4 == 1 || dirpress[(i + 1) * 2] < e) {
					Dir4 = INT2FIX((i + 1) * 2);
					e = dirpress[(i + 1) * 2];
				}
			}
		}
		Dir8 = Dir4;
		if (dirpress[9] > 0) {
			Dir8 = INT2FIX(9);
        }
		else if (dirpress[7] > 0) {
			Dir8 = INT2FIX(7);
        }
		else if (dirpress[3] > 0) {
			Dir8 = INT2FIX(3);
        }
		else if (dirpress[1] > 0) {
			Dir8 = INT2FIX(1);
        }
	}
    return Qnil;
}

static VALUE argss_input_press(VALUE self, VALUE button) {
    Check_Type(button, T_FIXNUM);
    return INT2BOOL(KeysPressTime[argss_input_num2key(NUM2INT(button))] > 0);
}

static VALUE argss_input_trigger(VALUE self, VALUE button) {
    Check_Type(button, T_FIXNUM);
    return INT2BOOL(KeysTriggered[argss_input_num2key(NUM2INT(button))]);
}

static VALUE argss_input_repeat(VALUE self, VALUE button) {
    Check_Type(button, T_FIXNUM);
    return INT2BOOL(KeysRepeat[argss_input_num2key(NUM2INT(button))]);
}

static VALUE argss_input_release(VALUE self, VALUE button) {
    Check_Type(button, T_FIXNUM);
    return INT2BOOL(KeysReleased[argss_input_num2key(NUM2INT(button))]);
}

static VALUE argss_input_dir4(VALUE self) {
    return INT2NUM(Dir4);
}

static VALUE argss_input_dir8(VALUE self) {
    return INT2NUM(Dir8);
}

static VALUE argss_input_pressed(VALUE self) {
    VALUE array = rb_ary_new();
    for(int i = 0; i < sf::Key::Count; i++) {
        if(KeysPressTime[i] > 0) {
            rb_ary_push(array, INT2NUM(i));
        }
    }
    return array;
}

void Input_RestartKeys() {
    for (int i = 0; i < sf::Key::Count; i++) {
        KeysPressTime[i] = 0;
        KeysTriggered[i] = false;
        KeysRepeat[i] = false;
        KeysReleased[i] = false;
    }
    Dir4 = 0;
    Dir8 = 0;
}

void Init_Input()
{
    ARGSS_Input_StartRepeatTime = 10;
    ARGSS_Input_RepeatTime = 2;

    Input_RestartKeys();

    typedef VALUE (*rubyfunc)(...);
    ARGSS_Input = rb_define_module("Input");
    rb_define_singleton_method(ARGSS_Input, "update", (rubyfunc)argss_input_update, 0);
    rb_define_singleton_method(ARGSS_Input, "press?", (rubyfunc)argss_input_press, 1);
    rb_define_singleton_method(ARGSS_Input, "trigger?", (rubyfunc)argss_input_trigger, 1);
    rb_define_singleton_method(ARGSS_Input, "repeat?", (rubyfunc)argss_input_repeat, 1);
    rb_define_singleton_method(ARGSS_Input, "release?", (rubyfunc)argss_input_release, 1);
    rb_define_singleton_method(ARGSS_Input, "dir4", (rubyfunc)argss_input_dir4, 0);
    rb_define_singleton_method(ARGSS_Input, "dir8", (rubyfunc)argss_input_dir8, 0);
    rb_define_singleton_method(ARGSS_Input, "pressed", (rubyfunc)argss_input_pressed, 0);
    //rb_define_singleton_method(ARGSS_Input, "triggered", (rubyfunc)argss_input_triggered, 0);
    //rb_define_singleton_method(ARGSS_Input, "repeated", (rubyfunc)argss_input_repeated, 0);
    //rb_define_singleton_method(ARGSS_Input, "released", (rubyfunc)argss_input_released, 0);
    rb_define_const(ARGSS_Input, "DOWN", INT2FIX(2));
    rb_define_const(ARGSS_Input, "LEFT", INT2FIX(4));
    rb_define_const(ARGSS_Input, "RIGHT", INT2FIX(6));
    rb_define_const(ARGSS_Input, "UP", INT2FIX(8));
    rb_define_const(ARGSS_Input, "A", INT2FIX(11));
    rb_define_const(ARGSS_Input, "B", INT2FIX(12));
    rb_define_const(ARGSS_Input, "C", INT2FIX(13));
    rb_define_const(ARGSS_Input, "X", INT2FIX(14));
    rb_define_const(ARGSS_Input, "Y", INT2FIX(15));
    rb_define_const(ARGSS_Input, "Z", INT2FIX(16));
    rb_define_const(ARGSS_Input, "L", INT2FIX(17));
    rb_define_const(ARGSS_Input, "R", INT2FIX(18));
    rb_define_const(ARGSS_Input, "SHIFT", INT2FIX(21));
    rb_define_const(ARGSS_Input, "CTRL", INT2FIX(22));
    rb_define_const(ARGSS_Input, "ALT", INT2FIX(23));
    rb_define_const(ARGSS_Input, "F5", INT2FIX(25));
    rb_define_const(ARGSS_Input, "F6", INT2FIX(26));
    rb_define_const(ARGSS_Input, "F7", INT2FIX(27));
    rb_define_const(ARGSS_Input, "F8", INT2FIX(28));
    rb_define_const(ARGSS_Input, "F9", INT2FIX(29));

    rb_cv_set(ARGSS_Input, "@@dirkeys1", rb_ary_new3(1, INT2NUM(366)));
    rb_cv_set(ARGSS_Input, "@@dirkeys2", rb_ary_new3(2, INT2NUM(367), INT2NUM(361)));
    rb_cv_set(ARGSS_Input, "@@dirkeys3", rb_ary_new3(1, INT2NUM(368)));
    rb_cv_set(ARGSS_Input, "@@dirkeys4", rb_ary_new3(2, INT2NUM(369), INT2NUM(362)));
    rb_cv_set(ARGSS_Input, "@@dirkeys6", rb_ary_new3(2, INT2NUM(371), INT2NUM(363)));
    rb_cv_set(ARGSS_Input, "@@dirkeys7", rb_ary_new3(1, INT2NUM(372)));
    rb_cv_set(ARGSS_Input, "@@dirkeys8", rb_ary_new3(2, INT2NUM(373), INT2NUM(364)));
    rb_cv_set(ARGSS_Input, "@@dirkeys9", rb_ary_new3(1, INT2NUM(374)));
}
