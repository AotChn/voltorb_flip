#ifndef G_CONSTANTS_H
#define G_CONSTANTS_H

#include <SFML/Graphics.hpp>
#include "color_constants.h"

const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 1000;
const unsigned int BOARD_SIZE = 1000; //nxn board
const unsigned int TILE_SIZE = BOARD_SIZE/5;

enum CUSTOM_SFEV{
    Idle = -1,
    Draw = sf::Event::EventType::Count,
    Close = sf::Event::Closed
};
#endif