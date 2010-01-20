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
#include "hslrgb.h"

////////////////////////////////////////////////////////////
/// Defines
////////////////////////////////////////////////////////////
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

struct ColorHSL {
    double h;
    double s;
    double l;
};

////////////////////////////////////////////////////////////
/// RGB to HSL
////////////////////////////////////////////////////////////
ColorHSL RGB2HSL(Color col) {
    ColorHSL ncol;
    double vmin, vmax, delta;
    double dr, dg, db;
    double r, g, b;
    r = col.red / 255.0;
    g = col.green / 255.0;
    b = col.blue / 255.0;
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

////////////////////////////////////////////////////////////
/// Hue to RGB
////////////////////////////////////////////////////////////
double Hue_2_RGB(double v1, double v2, double vH) {
   if (vH < 0) vH += 1;
   if (vH > 1) vH -= 1;
   if ((6 * vH) < 1) return (v1 + (v2 - v1) * 6 * vH);
   if ((2 * vH) < 1) return (v2);
   if ((3 * vH) < 2) return (v1 + (v2 - v1) * ((2.0 / 3) - vH ) * 6);
   return v1;
}

////////////////////////////////////////////////////////////
/// HSL to RGB
////////////////////////////////////////////////////////////
Color HSL2RGB(ColorHSL col) {
    Color ncol(0, 0, 0, 0);
    double v1, v2;
    if(col.s == 0) {
        ncol.red = (Uint8)(col.l * 255);
        ncol.green = (Uint8)(col.l * 255);
        ncol.blue = (Uint8)(col.l * 255);
    }
    else {
        if(col.l < 0.5) {
            v2 = col.l * (1 + col.s);
        }
        else {
            v2 = (col.l + col.s) - (col.s * col.l);
        }
        v1 = 2 * col.l - v2;
        ncol.red = (Uint8)(255 * Hue_2_RGB(v1, v2, col.h + (1.0 / 3)));
        ncol.green = (Uint8)(255 * Hue_2_RGB(v1, v2, col.h));
        ncol.blue = (Uint8)(255 * Hue_2_RGB(v1, v2, col.h - (1.0 / 3)));
    }
    return ncol;
}

////////////////////////////////////////////////////////////
/// Ajust RGB with HSL
////////////////////////////////////////////////////////////
Color RGBAdjustHSL(Color col, double h, double s, double l) {
    ColorHSL hsl;
    Color rgb = col;
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
    rgb.alpha = col.alpha;
    return rgb;
}
