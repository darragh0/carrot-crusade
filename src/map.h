#pragma once

#include <memory>
#include <unordered_map>


/**
 * Map: A map comprised of regions that are connected to each
 * other vertically (north and south) and horizontally (east and west).
 */
class Map {

    private:

        /**
         * Region: A class representing a region (sector) of the map.
         */
        class Region {

            public:

                const char* name;
                int x;
                int y;
                std::shared_ptr<Region> north = nullptr;
                std::shared_ptr<Region> east = nullptr;
                std::shared_ptr<Region> south = nullptr;
                std::shared_ptr<Region> west = nullptr;

                /**
                 * Region constructor.
                 *
                 * @param name  Name of the region.
                 * @param x     x-coordinate.
                 * @param y     y-coordinate.
                 */
                Region(const char* name, int x, int y) :
                    name(name),
                    x(x),
                    y(y) {}

                /**
                 * Displays the name of each connected map region.
                 */
                void showConnections();
            };

        /**
         * Links a new map region to existing regions by setting applicable
         * directional attributes, contingent on the coordinates of the new region.
         *
         * @param new_region    Shared pointer to the new region.
         */
        void applyConnections(std::shared_ptr<Region> new_region);

    public:

        /**
         * Map linking region names to region instances.
         */
        std::unordered_map<const char*, std::shared_ptr<Region>> regions;

        /**
         * Retrieves and returns the map region with the given name.
         *
         * @param name  Name of the region.
         * @return      Shared pointer to a region instance.
         */
        std::shared_ptr<Region> getRegion(const char* name);

        /**
         * Creates and adds a new region to the map at the location
         * specified by the given coordinates.
         *
         * @param name  Name of the region.
         * @param x     x-coordinate.
         * @param y     y-coordinate.
         */
        void addRegion(const char* name, int x, int y);

};
