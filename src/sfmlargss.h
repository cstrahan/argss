#ifndef _SFMLARGSS_H_
#define _SFMLARGSS_H_

#include <map>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

extern std::map<VALUE, sf::Image> ARGSS_mapBitmaps;
extern std::map<VALUE, sf::Sprite> ARGSS_mapSprites;

extern sf::Color ARGSS_Graphics_BackColor;

#endif
