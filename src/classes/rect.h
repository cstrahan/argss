#ifndef _ARGSS_RECTH_
#define _ARGSS_RECTH_

#include "SFML/Graphics/Rect.hpp"

unsigned long argss_rect_new(unsigned long x, unsigned long y, unsigned long w, unsigned long h);
unsigned long argss_rect_new2(int x, int y, int w, int h);
sf::IntRect argss_rect_intrect(unsigned long rect);
sf::FloatRect argss_rect_floatrect(unsigned long rect);

void Init_Rect();

#endif
