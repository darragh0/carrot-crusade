#include "../h/util.h"

#include "../h/constants.h"


void game::parseRegionAttrs(Map* map) {

    for (const auto& region_folder : std::filesystem::directory_iterator(MAP_REGIONS_DIR)) {
        const std::string path = region_folder.path().generic_string();
        const std::string attrs_toml_path = path + "/attrs.toml";
        const std::string src_png = path + "/src.png";
        const std::string outline_png = path + "/outline.png";

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

        auto *region = new game::Map::Region(
                name,
                src_png,
                outline_png,
                map_pos_x,
                map_pos_y
        );

        std::string erm = path + "/entities/sprites";
        if (std::filesystem::is_directory(erm)) {
            for (const auto& sprite_folder : std::filesystem::directory_iterator(erm)) {
                Sprite* sprite = parseSpriteAttrs(sprite_folder.path().generic_string());
                region->sprites[std::make_pair(sprite->canvas_pos_x, sprite->canvas_pos_y)] = sprite;
            }
        }

        map->addRegion(region);

    }

}


game::Sprite* game::parseSpriteAttrs(const std::string& dir) {

    const std::string attrs_toml_path = dir + "/attrs.toml";
    const std::string src_png = dir + "/src.png";

    std::string name, origin_x_str, origin_y_str, canvas_pos_x_str, canvas_pos_y_str;
    std::ifstream file(attrs_toml_path);

    std::getline(file, name);
    std::getline(file, origin_x_str);
    std::getline(file, origin_y_str);
    std::getline(file, canvas_pos_x_str);
    std::getline(file, canvas_pos_y_str);

    file.close();

    name = name.substr(8, name.length() - 9);

    origin_x_str = origin_x_str.substr(11, origin_x_str.length() - 11);
    origin_y_str = origin_y_str.substr(11, origin_y_str.length() - 11);
    canvas_pos_x_str = canvas_pos_x_str.substr(15, canvas_pos_x_str.length() - 15);
    canvas_pos_y_str = canvas_pos_y_str.substr(15, canvas_pos_y_str.length() - 15);

    const int origin_x = std::stoi(origin_x_str);
    const int origin_y = std::stoi(origin_y_str);
    const uint8_t map_pos_x = std::stoi(canvas_pos_x_str);
    const uint8_t map_pos_y = std::stoi(canvas_pos_y_str);

    return new Sprite(nullptr, name, src_png, origin_x, origin_y, map_pos_x, map_pos_y);

}


game::Sprite* game::parseCarrotAttrs() {
    return parseSpriteAttrs(CARROT_DIR);
}
