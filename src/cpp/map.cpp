#include "../h/map.h"
#include <iostream>


//size_t game::Map::CoordsHasher::operator()(const Coords &coords) const {
size_t game::Map::CoordsHasher::operator()(const std::pair<uint8_t, uint8_t>& coords) const {
    return coords.first + (*(&coords.second) << 8);
}


std::unordered_map<std::pair<uint8_t, uint8_t>, game::Map::Region*, game::Map::CoordsHasher> game::Map::regions = {};


game::Map::Region::Region(
        const std::string name,
        const std::string& img_src,
        const std::string& outlined_img_src,
        const uint8_t map_pos_x,
        const uint8_t map_pos_y
    ) : name(name),
        pixmap(new QPixmap(img_src.c_str())),
        outline((new QPixmap(outlined_img_src.c_str()))->toImage()),
        coords(std::make_pair(map_pos_x, map_pos_y)) {
//        coords(Coords(map_pos_x, map_pos_y)) {

    Map::regions[this->coords] = this;
} // TODO: Cleanup


game::Region::Region(const std::string& name, const std::string& img_src, const std::string& outlined_img_src)
    : name(name),
      pixmap(new QPixmap(img_src.c_str())),
      outline((new QPixmap(outlined_img_src.c_str()))->toImage()) {  // TODO: Cleanup
}


void game::Region::setExit(Direction dir, Region* region) {
    this->exits.insert({dir, region});
}


game::Region* game::Region::getExit(Direction dir) {
    return this->exits[dir];
}
