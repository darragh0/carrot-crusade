#include "../h/map.h"


template<>
size_t game::Map::intPairHash<uint8_t>::operator()(const std::pair<uint8_t, uint8_t>& coords) const {
    return coords.first + (*(&coords.second) << 8);
}


template<>
size_t game::Map::intPairHash<uint16_t>::operator()(const std::pair<uint16_t, uint16_t>& coords) const {
    return coords.first + (*(&coords.second) << 16);
}


game::Map::Region::Region(
        std::string name,
        const std::string& img_src,
        const std::string& outlined_img_src,
        const uint8_t map_pos_x,
        const uint8_t map_pos_y
    )
    : name(std::move(name)),
      pixmap(new QPixmap(img_src.c_str())),
      outline(QPixmap(outlined_img_src.c_str()).toImage()),
      map_coords(std::make_pair(map_pos_x, map_pos_y)) {
}


game::Map::Region::~Region() {
    delete this->pixmap;
}


game::Map::Map() {
     parseRegionAttrs(this);
}


game::Map* game::Map::getInstance() {
    static Map* instance = new Map();
    return instance;
}


game::Map::Region* game::Map::getRegion(uint8_t x, uint8_t y) {
    return Map::regions.at(std::make_pair(x, y));
}


void game::Map::addRegion(game::Map::Region* region) {
    this->regions[region->map_coords] = region;  // Overriding
}


game::Map::~Map() {
    for (const auto& region : Map::regions)
        delete region.second;
}
