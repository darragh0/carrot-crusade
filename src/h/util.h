#pragma once

#include <unordered_set>


namespace game {

    const int PIXEL_SCALE_FACTOR = 10;
    const int HORIZONTAL_TILES = 128;
    const int VERTICAL_TILES = 72;
    const int CARROT_CENTER_X = 3;
    const int CARROT_CENTER_Y = 9;

    enum Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST,
    };

}
