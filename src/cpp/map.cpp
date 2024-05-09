#include "../h/map.h"
#include <iostream>
#include <filesystem>
#include <fstream>


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


void game::Map::init() {

    for (const auto& region_folder : std::filesystem::directory_iterator("../assets/images/map-regions")) {
        const std::string attrs_toml_path = region_folder.path().generic_string() + "/attrs.toml";
        const std::string src_png = region_folder.path().generic_string() + "/src.png";
        const std::string outline_png = region_folder.path().generic_string() + "/outline.png";

        std::string name;
        std::string map_pos_x_str;
        std::string map_pos_y_str;

        std::ifstream file(attrs_toml_path);

        std::getline(file, name);
        std::getline(file, map_pos_x_str);
        std::getline(file, map_pos_y_str);
        file.close();

        name = name.substr(8, name.length() - 9);

        map_pos_x_str = map_pos_x_str.substr(12, map_pos_x_str.length() - 12);
        const uint8_t map_pos_x = std::stoi(map_pos_x_str);

        map_pos_y_str = map_pos_y_str.substr(12, map_pos_y_str.length() - 12);
        const uint8_t map_pos_y = std::stoi(map_pos_y_str);

        new game::Map::Region(
                name,
                src_png,
                outline_png,
                map_pos_x,
                map_pos_y
        );

    }
}


void game::Map::deleteRegions() {
    for (const auto& region : Map::regions)
        delete region.second;
}
