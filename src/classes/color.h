#ifndef _ARGSS_COLORH_
#define _ARGSS_COLORH_

#include "SFML\Graphics\Color.hpp"

sf::Color argss_color_getsf(unsigned long self);
unsigned long argss_color_new(unsigned long r, unsigned long g, unsigned long b, unsigned long a);
unsigned long argss_color_new2(float r, float g, float b, float a);
unsigned long argss_color_new3(sf::Color color);

void Init_Color();

#endif
