#pragma once

#include <string>
#include <unordered_map>
#include "util.h"
#include <QPixmap>

#include <cstdint>


namespace game {

    class Map {

        private:

            Map() = default;

        public:

            struct CoordsHasher {
    //                size_t operator () (const Map::Coords& coords) const;
                size_t operator () (const std::pair<uint8_t, uint8_t>& coords) const;
            };

            class Region {
            public:
                const std::string name;
                QPixmap* pixmap;
                QImage outline;
//                Coords coords;  // Map coordinates
                std::pair<uint8_t, uint8_t> coords;

                Region(
                    std::string  name,
                    const std::string& img_src,
                    const std::string& outlined_img_src,
                    uint8_t map_pos_x,
                    uint8_t map_pos_y
                );

                ~Region() = default;
            };

            // Could use singleton instead ig
            static std::unordered_map<std::pair<uint8_t, uint8_t>, Region*, CoordsHasher> regions;
    };

}
