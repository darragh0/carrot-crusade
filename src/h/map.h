#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

#include <QPixmap>

#include "util.h"


namespace game {

    /**
     * Map Singleton.
     *
     * This class allows interaction with and manipulation of
     * the game's different regions.
     */
    class Map {

        private:

            /**
             * Used to hash a standard pair of x & y coordinates.
             */
            struct CoordsHasher {
                size_t operator()(const std::pair<uint8_t, uint8_t> &coords) const;
            };

            Map();

            /**
             * A region representing an area of the map (analogous to Zork's `rooms).
             *
             * Each region has a unique set of coordinates that establishes
             * its location relative to other regions on the game's map.
             */
            class Region {

                public:

                    const std::string name;
                    std::pair<uint8_t, uint8_t> coords;

                    /**
                     * The region's image, stored as a pixel map, along with
                     * another image with highlighted barriers.
                     *
                     * @note `outline` is stored as a `QImage` for retrieving
                     *        individual pixel data.
                     * @dir carrot-crusade/assets/images/map-regions
                     */
                    QPixmap *pixmap;
                    QImage outline;

                    Region(
                            std::string name,
                            const std::string &img_src,
                            const std::string &outlined_img_src,
                            uint8_t map_pos_x,
                            uint8_t map_pos_y
                    );

                    ~Region();
            };

        private:

            std::unordered_map<std::pair<uint8_t, uint8_t>, Region*, CoordsHasher> regions = {};

        public:


            /**
             * Retrieves the single Map instance.
             */
            static Map* getInstance();

            /**
             * Returns the region at the given coordinates.
             *
             * @param x         Region's x-coordinate.
             * @param y         Region's y-coordinate.
             */
            Region* getRegion(uint8_t x, uint8_t y);

            /**
             * Add a region to the map.
             *
             * @param region    Region to be added.
             */
            void addRegion(Region* region);

            ~Map();

        /// @see Canvas::setRegion(Region*, int, int)
        friend class Canvas;

    };

}
