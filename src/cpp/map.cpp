#include "../h/map.h"
#include <iostream>

//size_t game::Map::CoordsHasher::operator()(const Coords &coords) const {
size_t game::Map::CoordsHasher::operator()(const std::pair<uint8_t, uint8_t>& coords) const {
    return coords.first + (*(&coords.second) << 8);
}


std::unordered_map<std::pair<uint8_t, uint8_t>, game::Map::Region*, game::Map::CoordsHasher> game::Map::regions = {};


game::Map::Region::Region(
        std::string name,
        const std::string& img_src,
        const std::string& outlined_img_src,
        const uint8_t map_pos_x,
        const uint8_t map_pos_y
    )

    :   name(std::move(name)),
        pixmap(new QPixmap(img_src.c_str())),
        outline(QPixmap(outlined_img_src.c_str()).toImage()),
        coords(std::make_pair(map_pos_x, map_pos_y)) {

    Map::regions[this->coords] = this;

}


game::Map::Region::~Region() {
    delete this->pixmap;
}


void game::Map::deleteRegions() {
    for (const auto& region : Map::regions)
        delete region.second;
}
