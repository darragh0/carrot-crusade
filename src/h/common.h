#ifndef COMMON_H_INCLUDED_
#define COMMON_H_INCLUDED_

#include <fstream>
#include <filesystem>

#include "../h/sprite.h"

namespace game {

    class Map;

    union Sprite {
        Carrot* carrot;
        Vehicle* vehicle;
        HintNote* item;
    };

    void parseRegionAttrs(Map* map);
    Sprite* parseSpriteAttrs(const std::string& dir, bool carrot = false, bool vehicle = false);

}

#endif
