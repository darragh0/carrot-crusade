#pragma once

#include <string>
#include <unordered_map>
#include "util.h"
#include <QPixmap>

#include <cstdint>


namespace game {

    class Map {

        private:

//            struct Coords {
//                const uint8_t x;
//                const uint8_t y;
//            };


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
                    const std::string name,
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


































    /**
     * Region: A class representing a region (sector) of the map.
     */
    class Region {

    public:

        const std::string& name;
        QPixmap* pixmap;
        QImage outline;
        std::unordered_map<Direction, Region*> exits;

        /**
         * Region constructor.
         *
         * @param name  Name of the region.
         */
        Region(const std::string& name, const std::string& img_src, const std::string& outlined_img_src);

        /**
         * Region destructor.
         */
         ~Region() = default;

         void setExit(Direction dir, Region* region);
         Region* getExit(Direction dir);
    };

}
