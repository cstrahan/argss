#include "bitmap.h"
#include "../argss.h"
#include "../sfmlargss.h"
#include "aerror.h"
#include "rect.h"
#include "color.h"
#include "../sfml.h"
#include "../tools/HSLRGB.h"

void argss_bitmap_check(VALUE bmp) {
    if (ARGSS_mapBitmaps.count(bmp) == 0) {
        rb_raise(ARGSS_Error, "disposed bitmap <%i>", bmp);
    }
}

static VALUE argss_bitmap_initialize(int argc, VALUE *argv, VALUE self) {
    if (argc == 1) {
        Check_Type(argv[0], T_STRING);
		if (!ARGSS_mapBitmaps[self].LoadFromFile(StringValuePtr(argv[0]))) {
		    //Error
		}
		ARGSS_mapBitmaps[self].SetSmooth(false);
    }
    else if (argc == 2) {
        Check_Kind(argv[0], rb_cNumeric);
        Check_Kind(argv[1], rb_cNumeric);
        ARGSS_mapBitmaps[self].Create(NUM2INT(argv[0]), NUM2INT(argv[1]),
            sf::Color(0, 0, 0, 0));
        ARGSS_mapBitmaps[self].SetSmooth(false);
    }
    else if (argc == 0) {raise_argn(argc, 1);}
    else {raise_argn(argc, 2);}
    return self;
}
static VALUE argss_bitmap_dispose(VALUE self) {
    argss_bitmap_check(self);
    ARGSS_mapBitmaps.erase(self);
    return self;
}
static VALUE argss_bitmap_disposedQ(VALUE self) {
    return INT2BOOL(ARGSS_mapBitmaps.count(self) == 0);
}
static VALUE argss_bitmap_width(VALUE self) {
    argss_bitmap_check(self);
    return INT2NUM(ARGSS_mapBitmaps[self].GetWidth());
}
static VALUE argss_bitmap_height(VALUE self) {
    argss_bitmap_check(self);
    return INT2NUM(ARGSS_mapBitmaps[self].GetHeight());
}
static VALUE argss_bitmap_rect(VALUE self) {
    argss_bitmap_check(self);
    return argss_rect_new2(0, 0, ARGSS_mapBitmaps[self].GetWidth(),
                                ARGSS_mapBitmaps[self].GetHeight());
}
static VALUE argss_bitmap_blt(int argc, VALUE *argv, VALUE self) {
    argss_bitmap_check(self);
    if (argc < 4) {raise_argn(argc, 4);}
    else if (argc > 5) {raise_argn(argc, 5);}
    Check_Kind(argv[0], rb_cNumeric);
    Check_Kind(argv[1], rb_cNumeric);
    Check_Class(argv[2], ARGSS_Bitmap);
    argss_bitmap_check(argv[2]);
    Check_Class(argv[3], ARGSS_Rect);
    sf::IntRect rect = argss_rect_intrect(argv[3]);
    int alpha = 255;
    if (argc == 5) {
        Check_Kind(argv[4], rb_cNumeric);
        alpha = NUM2INT(argv[4]);
    }
    ARGSS_mapBitmaps[self].CopyA(ARGSS_mapBitmaps[argv[2]], NUM2INT(argv[0]), NUM2INT(argv[1]), rect, true, alpha);
    return self;
}
static VALUE argss_bitmap_stretch_blt(int argc, VALUE *argv, VALUE self) {
    argss_bitmap_check(self);
    if (argc < 3) {raise_argn(argc, 3);}
    else if (argc > 4) {raise_argn(argc, 4);}
    Check_Class(argv[0], ARGSS_Rect);
    sf::IntRect drect = argss_rect_intrect(argv[0]);
    Check_Class(argv[1], ARGSS_Bitmap);
    argss_bitmap_check(argv[1]);
    Check_Class(argv[2], ARGSS_Rect);
    sf::IntRect srect = argss_rect_intrect(argv[2]);
    int alpha = 255;
    if (argc == 5) {
        Check_Kind(argv[3], rb_cNumeric);
        alpha = NUM2INT(argv[3]);
    }
    if (srect.GetWidth() == drect.GetWidth() && srect.GetHeight() == drect.GetHeight()) {
        ARGSS_mapBitmaps[self].CopyA(ARGSS_mapBitmaps[argv[1]], drect.Left, drect.Top, srect, true, alpha);
    }
    else {
         sf::Image img = ARGSS_mapBitmaps[argv[1]].Resample(drect.GetWidth(), drect.GetHeight(), srect);
         ARGSS_mapBitmaps[self];
         sf::IntRect rect(0, 0, 0, 0);
         ARGSS_mapBitmaps[self].CopyA(img, drect.Left, drect.Top, rect, true, alpha);
    }
    return self;
}
static VALUE argss_bitmap_fill_rect(int argc, VALUE *argv, VALUE self) {
    argss_bitmap_check(self);
    sf::IntRect rect;
    sf::Color color;
    if (argc < 2) {raise_argn(argc, 2);}
    else if (argc == 2) {
        Check_Class(argv[0], ARGSS_Rect);
        rect = argss_rect_intrect(argv[0]);
        Check_Class(argv[1], ARGSS_Color);
        color = argss_color_getsf(argv[1]);
    }
    else if (argc == 5) {
        Check_Kind(argv[0], rb_cNumeric);
        Check_Kind(argv[1], rb_cNumeric);
        Check_Kind(argv[2], rb_cNumeric);
        Check_Kind(argv[3], rb_cNumeric);
        rect = sf::IntRect(NUM2INT(argv[0]),
                            NUM2INT(argv[1]),
                            NUM2INT(argv[0]) + NUM2INT(argv[2]),
                            NUM2INT(argv[1]) + NUM2INT(argv[3]));
        Check_Class(argv[4], ARGSS_Color);
        color = argss_color_getsf(argv[4]);
    }
    else {raise_argn(argc, 5);}
    ARGSS_mapBitmaps[self].FillRect(rect, color);
    return self;
}
static VALUE argss_bitmap_clear(int argc, VALUE *argv, VALUE self) {
    argss_bitmap_check(self);
    if (argc > 1) {raise_argn(argc, 1);}
    sf::Color color(0, 0, 0, 0);
    if (argc == 1) {
        Check_Class(argv[0], ARGSS_Color);
        color = argss_color_getsf(argv[0]);
    }
    ARGSS_mapBitmaps[self].Create(ARGSS_mapBitmaps[self].GetWidth(), ARGSS_mapBitmaps[self].GetHeight(), color);
    return self;
}
static VALUE argss_bitmap_get_pixel(VALUE self, VALUE x, VALUE y) {
    argss_bitmap_check(self);
    Check_Kind(x, rb_cNumeric);
    Check_Kind(y, rb_cNumeric);
    return argss_color_new3(ARGSS_mapBitmaps[self].GetPixel(NUM2INT(x), NUM2INT(y)));
}
static VALUE argss_bitmap_set_pixel(VALUE self, VALUE x, VALUE y, VALUE color) {
    argss_bitmap_check(self);
    Check_Kind(x, rb_cNumeric);
    Check_Kind(y, rb_cNumeric);
    Check_Class(color, ARGSS_Color);
    ARGSS_mapBitmaps[self].SetPixel(NUM2INT(x), NUM2INT(y), argss_color_getsf(color));
    return self;
}
static VALUE argss_bitmap_hue_change(VALUE self, VALUE hue) {
    argss_bitmap_check(self);
    Check_Kind(hue, rb_cNumeric);
    sf::Color col;
    int h = NUM2INT(hue);
    //ARGSS_mapBitmaps[self].HSL_Adjust(h, 0, 1, sf::IntRect(0, 0, 0, 0));
    for(unsigned int y = 0; y < ARGSS_mapBitmaps[self].GetHeight(); y++) {
        for(unsigned int x = 0; x < ARGSS_mapBitmaps[self].GetWidth(); x++) {
            col = ARGSS_mapBitmaps[self].GetPixel(x, y);
            ARGSS_mapBitmaps[self].SetPixel(x, y, RGBAdjustHSL(col, h, 0, 1));
        }
    }
    return self;
}
static VALUE argss_bitmap_saturation_change(VALUE self, VALUE sat) {
    argss_bitmap_check(self);
    Check_Kind(sat, rb_cNumeric);
    sf::Color col;
    float s = (float)NUM2DBL(sat);
    //ARGSS_mapBitmaps[self].HSL_Adjust(0, s, 1, sf::IntRect(0, 0, 0, 0));
    for(unsigned int y = 0; y < ARGSS_mapBitmaps[self].GetHeight(); y++) {
        for(unsigned int x = 0; x < ARGSS_mapBitmaps[self].GetWidth(); x++) {
            col = ARGSS_mapBitmaps[self].GetPixel(x, y);
            ARGSS_mapBitmaps[self].SetPixel(x, y, RGBAdjustHSL(col, 0, s, 1));
        }
    }
    return self;
}
static VALUE argss_bitmap_luminance_change(VALUE self, VALUE lum) {
    argss_bitmap_check(self);
    Check_Kind(lum, rb_cNumeric);
    sf::Color col;
    float l = (float)NUM2DBL(lum);
    //ARGSS_mapBitmaps[self].HSL_Adjust(0, 0, l, sf::IntRect(0, 0, 0, 0));
    for(unsigned int y = 0; y < ARGSS_mapBitmaps[self].GetHeight(); y++) {
        for(unsigned int x = 0; x < ARGSS_mapBitmaps[self].GetWidth(); x++) {
            col = ARGSS_mapBitmaps[self].GetPixel(x, y);
            ARGSS_mapBitmaps[self].SetPixel(x, y, RGBAdjustHSL(col, 0, 0, l));
        }
    }
    return self;
}
static VALUE argss_bitmap_hsl_change(int argc, VALUE *argv, VALUE self) {
    argss_bitmap_check(self);
    if (argc < 3) {raise_argn(argc, 3);}
    else if (argc > 4) {raise_argn(argc, 4);}
    Check_Kind(argv[0], rb_cNumeric);
    Check_Kind(argv[1], rb_cNumeric);
    Check_Kind(argv[2], rb_cNumeric);
    int h = NUM2INT(argv[0]);
    float s = (float)NUM2DBL(argv[1]);
    float l = (float)NUM2DBL(argv[2]);
    sf::IntRect Rect;
    if (argc == 4) {
        Rect = argss_rect_intrect(argv[3]);
    }
    else {
        Rect = sf::IntRect(0, 0, 0, 0);
    }
    //ARGSS_mapBitmaps[self].HSL_Adjust(h, s, l, rect);

    if ((ARGSS_mapBitmaps[self].GetWidth() == 0) || (ARGSS_mapBitmaps[self].GetHeight() == 0)) {
        return self;
    }

    if ((Rect.GetWidth() == 0) || (Rect.GetHeight() == 0)) {
        Rect.Right  = ARGSS_mapBitmaps[self].GetWidth();
        Rect.Bottom = ARGSS_mapBitmaps[self].GetHeight();
    }
    else {
        if (Rect.Right  > static_cast<int>(ARGSS_mapBitmaps[self].GetWidth()))  Rect.Right  = ARGSS_mapBitmaps[self].GetWidth();
        if (Rect.Bottom > static_cast<int>(ARGSS_mapBitmaps[self].GetHeight())) Rect.Bottom = ARGSS_mapBitmaps[self].GetHeight();
    }
    if (Rect.Left   < 0) Rect.Left = 0;
    if (Rect.Top    < 0) Rect.Top  = 0;

    sf::Color col;

    for(int y = Rect.Top; y < Rect.Bottom; y++) {
        for(int x = Rect.Left; x < Rect.Right; x++) {
            col = ARGSS_mapBitmaps[self].GetPixel(x, y);
            ARGSS_mapBitmaps[self].SetPixel(x, y, RGBAdjustHSL(col, h, s, l));
        }
    }
    return self;
}
static VALUE argss_bitmap_draw_text(int argc, VALUE *argv, VALUE self) {

    // ): Hate Freetype and OpenGL :(
    // To Finish

    argss_bitmap_check(self);

    sf::Color col(255, 0, 0, 255);
    ARGSS_mapBitmaps[self].DDrawText(0, 0, 100, 100, "Hola", col);

    return self;
}
static VALUE argss_bitmap_text_size(VALUE self, VALUE str) {
    argss_bitmap_check(self);
    Check_Type(str, T_STRING);
    //ToDo
    return self;
}

void Init_Bitmap() {
    typedef VALUE (*rubyfunc)(...);
    ARGSS_Bitmap = rb_define_class("Bitmap", rb_cObject);
    rb_define_method(ARGSS_Bitmap, "initialize", (rubyfunc)argss_bitmap_initialize, -1);
    rb_define_method(ARGSS_Bitmap, "dispose", (rubyfunc)argss_bitmap_dispose, 0);
    rb_define_method(ARGSS_Bitmap, "disposed?", (rubyfunc)argss_bitmap_disposedQ, 0);
    rb_define_method(ARGSS_Bitmap, "width", (rubyfunc)argss_bitmap_width, 0);
    rb_define_method(ARGSS_Bitmap, "height", (rubyfunc)argss_bitmap_height, 0);
    rb_define_method(ARGSS_Bitmap, "rect", (rubyfunc)argss_bitmap_rect, 0);
    rb_define_method(ARGSS_Bitmap, "blt", (rubyfunc)argss_bitmap_blt, -1);
    rb_define_method(ARGSS_Bitmap, "stretch_blt", (rubyfunc)argss_bitmap_stretch_blt, -1);
    rb_define_method(ARGSS_Bitmap, "fill_rect", (rubyfunc)argss_bitmap_fill_rect, -1);
    rb_define_method(ARGSS_Bitmap, "clear", (rubyfunc)argss_bitmap_clear, -1);
    rb_define_method(ARGSS_Bitmap, "get_pixel", (rubyfunc)argss_bitmap_get_pixel, 2);
    rb_define_method(ARGSS_Bitmap, "set_pixel", (rubyfunc)argss_bitmap_set_pixel, 3);
    rb_define_method(ARGSS_Bitmap, "hue_change", (rubyfunc)argss_bitmap_hue_change, 1);
    rb_define_method(ARGSS_Bitmap, "saturation_change", (rubyfunc)argss_bitmap_saturation_change, 1);
    rb_define_method(ARGSS_Bitmap, "luminance_change", (rubyfunc)argss_bitmap_luminance_change, 1);
    rb_define_method(ARGSS_Bitmap, "hsl_change", (rubyfunc)argss_bitmap_hsl_change, -1);
    rb_define_method(ARGSS_Bitmap, "draw_text", (rubyfunc)argss_bitmap_draw_text, -1);
    rb_define_method(ARGSS_Bitmap, "text_size", (rubyfunc)argss_bitmap_text_size, 1);
}

