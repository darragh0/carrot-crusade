#pragma once

#include <fstream>
#include <filesystem>

#include "../h/map.h"
#include "../h/entity.h"


namespace game {

    void parseRegionAttrs(Map* map);
    Sprite* parseSpriteAttrs(const std::string& dir);
    Sprite* parseCarrotAttrs();

}
