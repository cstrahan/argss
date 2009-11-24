#include "HSLRGB.h"

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

struct ColorHSL {
    float h;
    float s;
    float l;
};

ColorHSL RGB2HSL(SDL_Color col) {
    ColorHSL ncol;
    float vmin, vmax, delta;
    float dr, dg, db;
    float r, g, b;
    r = col.r / 255.0;
    g = col.g / 255.0;
    b = col.b / 255.0;
    vmin = min(min(r, g), b);
    vmax = max(max(r, g), b);
    delta = vmax - vmin;
    ncol.l = (vmax + vmin) / 2;
    if (delta == 0) {
        ncol.h = 0;
        ncol.s = 0;
    }
    else {
        if(ncol.l < 0.5) {
            ncol.s = delta / (vmax + vmin);
        }
        else {
            ncol.s = delta / (2 - vmax - vmin);
        }
        dr = (((vmax - r) / 6) + (delta / 2)) / delta;
        dg = (((vmax - g) / 6) + (delta / 2)) / delta;
        db = (((vmax - b) / 6) + (delta / 2)) / delta;
        if(r == vmax) {
            ncol.h = db - dg;
        }
        else if(g == vmax) {
            ncol.h = (1.0 / 3) + dr - db;
        }
        else if(b == vmax) {
            ncol.h = (2.0 / 3) + dg - dr;
        }
    }
    return ncol;
}

float Hue_2_RGB(float v1, float v2, float vH) {
   if (vH < 0) vH += 1;
   if (vH > 1) vH -= 1;
   if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
   if ((2 * vH) < 1) return (v2);
   if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.0 / 3) - vH ) * 6);
   return v1;
}

SDL_Color HSL2RGB(ColorHSL col) {
    SDL_Color ncol;
    float v1, v2;
    if(col.s == 0) {
        ncol.r = (Uint8)(col.l * 255);
        ncol.g = (Uint8)(col.l * 255);
        ncol.b = (Uint8)(col.l * 255);
    }
    else {
        if(col.l < 0.5) {
            v2 = col.l * (1 + col.s);
        }
        else {
            v2 = (col.l + col.s) - (col.s * col.l);
        }
        v1 = 2 * col.l - v2;
        ncol.r = (Uint8)(255 * Hue_2_RGB(v1, v2, col.h + (1.0 / 3)));
        ncol.g = (Uint8)(255 * Hue_2_RGB(v1, v2, col.h));
        ncol.b = (Uint8)(255 * Hue_2_RGB(v1, v2, col.h - (1.0 / 3)));
    }
    return ncol;
}

SDL_Color RGBAdjustHSL(SDL_Color col, int h, float s, float l) {
    ColorHSL hsl;
    SDL_Color rgb = col;
    hsl = RGB2HSL(rgb);
    hsl.h = hsl.h + h / 360.0;
    while(hsl.h > 1) {hsl.h -= 1;}
    while(hsl.h < 0) {hsl.h += 1;}
    hsl.s = hsl.s + s;
    if (hsl.s > 1) {hsl.s = 1;}
    if (hsl.s < 0) {hsl.s = 0;}
    hsl.l = hsl.l * l;
    if (hsl.l > 1) {hsl.l = 1;}
    if (hsl.l < 0) {hsl.l = 0;}
    rgb = HSL2RGB(hsl);
    rgb.unused = col.unused;
    return rgb;
}
