#include "input.h"
#include "SDL.h"
#include "argss.h"
#include "aerror.h"

unsigned int KeysPressTime[SDLK_LAST];
bool KeysTriggered[SDLK_LAST];
bool KeysRepeat[SDLK_LAST];
bool KeysReleased[SDLK_LAST];
unsigned int Dir4;
unsigned int Dir8;

SDLKey argss_input_num2key(int key) {
    switch (key) {
		case 301 : return SDLK_BACKSPACE;
		case 302 : return SDLK_TAB;
		case 303 : return SDLK_CLEAR;
		case 304 : return SDLK_RETURN;
		case 305 : return SDLK_PAUSE;
		case 306 : return SDLK_ESCAPE;
		case 307 : return SDLK_SPACE;
		case 308 : return SDLK_EXCLAIM;
		case 309 : return SDLK_QUOTEDBL;
		case 310 : return SDLK_HASH;
		case 311 : return SDLK_DOLLAR;
		case 312 : return SDLK_AMPERSAND;
		case 313 : return SDLK_QUOTE;
		case 314 : return SDLK_LEFTPAREN;
		case 315 : return SDLK_RIGHTPAREN;
		case 316 : return SDLK_ASTERISK;
		case 317 : return SDLK_PLUS;
		case 318 : return SDLK_COMMA;
		case 319 : return SDLK_MINUS;
		case 320 : return SDLK_PERIOD;
		case 321 : return SDLK_SLASH;
		case 322 : return SDLK_0;
		case 323 : return SDLK_1;
		case 324 : return SDLK_2;
		case 325 : return SDLK_3;
		case 326 : return SDLK_4;
		case 327 : return SDLK_5;
		case 328 : return SDLK_6;
		case 329 : return SDLK_7;
		case 330 : return SDLK_8;
		case 331 : return SDLK_9;
		case 332 : return SDLK_COLON;
		case 333 : return SDLK_SEMICOLON;
		case 334 : return SDLK_LESS;
		case 335 : return SDLK_EQUALS;
		case 336 : return SDLK_GREATER;
		case 337 : return SDLK_QUESTION;
		case 338 : return SDLK_AT;
		case 339 : return SDLK_LEFTBRACKET;
		case 340 : return SDLK_BACKSLASH;
		case 341 : return SDLK_RIGHTBRACKET;
		case 342 : return SDLK_CARET;
		case 343 : return SDLK_UNDERSCORE;
		case 344 : return SDLK_BACKQUOTE;
		case 345 : return SDLK_a;
		case 346 : return SDLK_b;
		case 347 : return SDLK_c;
		case 348 : return SDLK_d;
		case 349 : return SDLK_e;
		case 350 : return SDLK_f;
		case 351 : return SDLK_g;
		case 352 : return SDLK_h;
		case 353 : return SDLK_i;
		case 354 : return SDLK_j;
		case 355 : return SDLK_k;
		case 356 : return SDLK_l;
		case 357 : return SDLK_m;
		case 358 : return SDLK_n;
		case 359 : return SDLK_o;
		case 360 : return SDLK_p;
		case 361 : return SDLK_q;
		case 362 : return SDLK_r;
		case 363 : return SDLK_s;
		case 364 : return SDLK_t;
		case 365 : return SDLK_u;
		case 366 : return SDLK_v;
		case 367 : return SDLK_w;
		case 368 : return SDLK_x;
		case 369 : return SDLK_y;
		case 370 : return SDLK_z;
		case 371 : return SDLK_DELETE;
		case 372 : return SDLK_WORLD_0;
		case 373 : return SDLK_WORLD_1;
		case 374 : return SDLK_WORLD_2;
		case 375 : return SDLK_WORLD_3;
		case 376 : return SDLK_WORLD_4;
		case 377 : return SDLK_WORLD_5;
		case 378 : return SDLK_WORLD_6;
		case 379 : return SDLK_WORLD_7;
		case 380 : return SDLK_WORLD_8;
		case 381 : return SDLK_WORLD_9;
		case 382 : return SDLK_WORLD_10;
		case 383 : return SDLK_WORLD_11;
		case 384 : return SDLK_WORLD_12;
		case 385 : return SDLK_WORLD_13;
		case 386 : return SDLK_WORLD_14;
		case 387 : return SDLK_WORLD_15;
		case 388 : return SDLK_WORLD_16;
		case 389 : return SDLK_WORLD_17;
		case 390 : return SDLK_WORLD_18;
		case 391 : return SDLK_WORLD_19;
		case 392 : return SDLK_WORLD_20;
		case 393 : return SDLK_WORLD_21;
		case 394 : return SDLK_WORLD_22;
		case 395 : return SDLK_WORLD_23;
		case 396 : return SDLK_WORLD_24;
		case 397 : return SDLK_WORLD_25;
		case 398 : return SDLK_WORLD_26;
		case 399 : return SDLK_WORLD_27;
		case 400 : return SDLK_WORLD_28;
		case 401 : return SDLK_WORLD_29;
		case 402 : return SDLK_WORLD_30;
		case 403 : return SDLK_WORLD_31;
		case 404 : return SDLK_WORLD_32;
		case 405 : return SDLK_WORLD_33;
		case 406 : return SDLK_WORLD_34;
		case 407 : return SDLK_WORLD_35;
		case 408 : return SDLK_WORLD_36;
		case 409 : return SDLK_WORLD_37;
		case 410 : return SDLK_WORLD_38;
		case 411 : return SDLK_WORLD_39;
		case 412 : return SDLK_WORLD_40;
		case 413 : return SDLK_WORLD_41;
		case 414 : return SDLK_WORLD_42;
		case 415 : return SDLK_WORLD_43;
		case 416 : return SDLK_WORLD_44;
		case 417 : return SDLK_WORLD_45;
		case 418 : return SDLK_WORLD_46;
		case 419 : return SDLK_WORLD_47;
		case 420 : return SDLK_WORLD_48;
		case 421 : return SDLK_WORLD_49;
		case 422 : return SDLK_WORLD_50;
		case 423 : return SDLK_WORLD_51;
		case 424 : return SDLK_WORLD_52;
		case 425 : return SDLK_WORLD_53;
		case 426 : return SDLK_WORLD_54;
		case 427 : return SDLK_WORLD_55;
		case 428 : return SDLK_WORLD_56;
		case 429 : return SDLK_WORLD_57;
		case 430 : return SDLK_WORLD_58;
		case 431 : return SDLK_WORLD_59;
		case 432 : return SDLK_WORLD_60;
		case 433 : return SDLK_WORLD_61;
		case 434 : return SDLK_WORLD_62;
		case 435 : return SDLK_WORLD_63;
		case 436 : return SDLK_WORLD_64;
		case 437 : return SDLK_WORLD_65;
		case 438 : return SDLK_WORLD_66;
		case 439 : return SDLK_WORLD_67;
		case 440 : return SDLK_WORLD_68;
		case 441 : return SDLK_WORLD_69;
		case 442 : return SDLK_WORLD_70;
		case 443 : return SDLK_WORLD_71;
		case 444 : return SDLK_WORLD_72;
		case 445 : return SDLK_WORLD_73;
		case 446 : return SDLK_WORLD_74;
		case 447 : return SDLK_WORLD_75;
		case 448 : return SDLK_WORLD_76;
		case 449 : return SDLK_WORLD_77;
		case 450 : return SDLK_WORLD_78;
		case 451 : return SDLK_WORLD_79;
		case 452 : return SDLK_WORLD_80;
		case 453 : return SDLK_WORLD_81;
		case 454 : return SDLK_WORLD_82;
		case 455 : return SDLK_WORLD_83;
		case 456 : return SDLK_WORLD_84;
		case 457 : return SDLK_WORLD_85;
		case 458 : return SDLK_WORLD_86;
		case 459 : return SDLK_WORLD_87;
		case 460 : return SDLK_WORLD_88;
		case 461 : return SDLK_WORLD_89;
		case 462 : return SDLK_WORLD_90;
		case 463 : return SDLK_WORLD_91;
		case 464 : return SDLK_WORLD_92;
		case 465 : return SDLK_WORLD_93;
		case 466 : return SDLK_WORLD_94;
		case 467 : return SDLK_WORLD_95;
		case 468 : return SDLK_KP0;
		case 469 : return SDLK_KP1;
		case 470 : return SDLK_KP2;
		case 471 : return SDLK_KP3;
		case 472 : return SDLK_KP4;
		case 473 : return SDLK_KP5;
		case 474 : return SDLK_KP6;
		case 475 : return SDLK_KP7;
		case 476 : return SDLK_KP8;
		case 477 : return SDLK_KP9;
		case 478 : return SDLK_KP_PERIOD;
		case 479 : return SDLK_KP_DIVIDE;
		case 480 : return SDLK_KP_MULTIPLY;
		case 481 : return SDLK_KP_MINUS;
		case 482 : return SDLK_KP_PLUS;
		case 483 : return SDLK_KP_ENTER;
		case 484 : return SDLK_KP_EQUALS;
		case 485 : return SDLK_UP;
		case 486 : return SDLK_DOWN;
		case 487 : return SDLK_RIGHT;
		case 488 : return SDLK_LEFT;
		case 489 : return SDLK_INSERT;
		case 490 : return SDLK_HOME;
		case 491 : return SDLK_END;
		case 492 : return SDLK_PAGEUP;
		case 493 : return SDLK_PAGEDOWN;
		case 494 : return SDLK_F1;
		case 495 : return SDLK_F2;
		case 496 : return SDLK_F3;
		case 497 : return SDLK_F4;
		case 498 : return SDLK_F5;
		case 499 : return SDLK_F6;
		case 500 : return SDLK_F7;
		case 501 : return SDLK_F8;
		case 502 : return SDLK_F9;
		case 503 : return SDLK_F10;
		case 504 : return SDLK_F11;
		case 505 : return SDLK_F12;
		case 506 : return SDLK_F13;
		case 507 : return SDLK_F14;
		case 508 : return SDLK_F15;
		case 509 : return SDLK_NUMLOCK;
		case 510 : return SDLK_CAPSLOCK;
		case 511 : return SDLK_SCROLLOCK;
		case 512 : return SDLK_RSHIFT;
		case 513 : return SDLK_LSHIFT;
		case 514 : return SDLK_RCTRL;
		case 515 : return SDLK_LCTRL;
		case 516 : return SDLK_RALT;
		case 517 : return SDLK_LALT;
		case 518 : return SDLK_RMETA;
		case 519 : return SDLK_LMETA;
		case 520 : return SDLK_LSUPER;
		case 521 : return SDLK_RSUPER;
		case 522 : return SDLK_MODE;
		case 523 : return SDLK_COMPOSE;
		case 524 : return SDLK_HELP;
		case 525 : return SDLK_PRINT;
		case 526 : return SDLK_SYSREQ;
		case 527 : return SDLK_BREAK;
		case 528 : return SDLK_MENU;
		case 529 : return SDLK_POWER;
		case 530 : return SDLK_EURO;
		case 531 : return SDLK_UNDO;
    }
    return SDLKey(0);
}

static VALUE argss_input_update(VALUE self) {
	Uint8 *keystates = SDL_GetKeyState(NULL); 
    int i, e;
    //argss_update();
	//SDL_PumpEvents();
    for (i = 0; i < SDLK_LAST; ++i) {
        if(keystates[(SDLKey)i]) {
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
    char keysvar[11];
    unsigned int dirpress[10];
    for(i = 1; i < 10; i++) {
		dirpress[i] = 0;
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
				if(e == 0 || dirpress[(i + 1) * 2] < e) {
					Dir4 = (i + 1) * 2;
					e = dirpress[(i + 1) * 2];
				}
			}
		}
		Dir8 = Dir4;
		if (dirpress[9] > 0) {
			Dir8 = 9;
        }
		else if (dirpress[7] > 0) {
			Dir8 = 7;
        }
		else if (dirpress[3] > 0) {
			Dir8 = 3;
        }
		else if (dirpress[1] > 0) {
			Dir8 = 1;
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
    for(int i = 0; i < SDLK_LAST; i++) {
        if(KeysPressTime[i] > 0) {
            rb_ary_push(array, INT2NUM(i));
        }
    }
    return array;
}

void Input_RestartKeys() {
    for (int i = 0; i < SDLK_LAST; i++) {
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

    rb_cv_set(ARGSS_Input, "@@dirkeys1", rb_ary_new3(1, INT2NUM(469)));
    rb_cv_set(ARGSS_Input, "@@dirkeys2", rb_ary_new3(2, INT2NUM(470), INT2NUM(486)));
    rb_cv_set(ARGSS_Input, "@@dirkeys3", rb_ary_new3(1, INT2NUM(471)));
    rb_cv_set(ARGSS_Input, "@@dirkeys4", rb_ary_new3(2, INT2NUM(472), INT2NUM(488)));
    rb_cv_set(ARGSS_Input, "@@dirkeys6", rb_ary_new3(2, INT2NUM(474), INT2NUM(487)));
    rb_cv_set(ARGSS_Input, "@@dirkeys7", rb_ary_new3(1, INT2NUM(475)));
    rb_cv_set(ARGSS_Input, "@@dirkeys8", rb_ary_new3(2, INT2NUM(476), INT2NUM(485)));
    rb_cv_set(ARGSS_Input, "@@dirkeys9", rb_ary_new3(1, INT2NUM(477)));
}
