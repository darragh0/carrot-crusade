#include "../h/constants.h"
#include "../h/map.h"
#include "../h/excepts.h"


game::Sprite* game::parseSpriteAttrs(const std::string& dir, const bool carrot, const bool vehicle) {

    auto* sprite = new game::Sprite();
    const std::string attrs_toml_path = dir + "/attrs.toml";
    const std::string src_png = dir + "/src.png";

    std::string name, origin_x_str, origin_y_str, canvas_pos_x_str, canvas_pos_y_str, description_str, hint_n;
    std::ifstream file(attrs_toml_path);

    std::getline(file, name);
    std::getline(file, origin_x_str);
    std::getline(file, origin_y_str);
    std::getline(file, canvas_pos_x_str);
    std::getline(file, canvas_pos_y_str);

    if ((!carrot) && (!vehicle)) {
        std::getline(file, description_str);
        std::getline(file, hint_n);
    }

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

    if (carrot) {
        auto* c = new Carrot(nullptr, name, src_png, origin_x, origin_y, map_pos_x, map_pos_y);
        sprite->carrot = c;
    } else if (vehicle) {
        auto* v = new Vehicle(nullptr, name, src_png, origin_x, origin_y, map_pos_x, map_pos_y);
        sprite->vehicle = v;
    } else {
        description_str = description_str.substr(8, description_str.length() - 9);
        hint_n = hint_n.substr(4, hint_n.length() - 4);
        const int n = std::stoi(hint_n);
        auto* i = new HintNote(nullptr, name, src_png, origin_x, origin_y, map_pos_x, map_pos_y, description_str, n);
        sprite->item = i;
    }

    return sprite;
}


void game::parseRegionAttrs(Map* map) {

    for (const auto& region_folder : std::filesystem::directory_iterator(MAP_REGIONS_DIR)) {
        const std::string path = region_folder.path().generic_string();
        const std::string attrs_toml_path = path + "/attrs.toml";
        const std::string src_png = path + "/src.png";
        const std::string outline_png = path + "/outline.png";

        if (!std::filesystem::is_regular_file(attrs_toml_path))
            throw incomplete_map_region(
                "Map region is missing an attributes (`attrs.toml`) file:" +
                region_folder.path().filename().generic_string()
            );

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

        auto* region = new game::Map::Region(
                name,
                src_png,
                outline_png,
                map_pos_x,
                map_pos_y
        );

        std::string vehicles_path = path + "/sprites/vehicles";
        if (std::filesystem::is_directory(vehicles_path)) {
            for (const auto& sprite_folder : std::filesystem::directory_iterator(vehicles_path)) {
                game::Sprite* sprite = parseSpriteAttrs(sprite_folder.path().generic_string(), false, true);
                region->vehicles[std::make_pair(sprite->vehicle->canvas_pos_x, sprite->vehicle->canvas_pos_y)] = sprite;
            }
        }

        std::string items_path = path + "/sprites/items";
        if (std::filesystem::is_directory(items_path)) {
            for (const auto& sprite_folder : std::filesystem::directory_iterator(items_path)) {
                game::Sprite* sprite = parseSpriteAttrs(sprite_folder.path().generic_string(), false, false);
                region->items[std::make_pair(sprite->item->canvas_pos_x, sprite->item->canvas_pos_y)] = sprite;
            }
        }

        map->addRegion(region);

    }

}
