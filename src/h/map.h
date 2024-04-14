#pragma once

#include <string>
#include <vector>


namespace game {


    /**
     * Region: A class representing a region (sector) of the map.
     */
    class Region {

    public:

        const std::string &name;
        const std::string &file_path;
        std::vector<std::pair<int, int>> forbidden_coordinates;
        Region* north = nullptr;
        Region* east = nullptr;
        Region* south = nullptr;
        Region* west = nullptr;

        /**
         * Region constructor.
         *
         * @param name  Name of the region.
         */
        Region(const std::string &name, const std::string &file_path);

    };

}
