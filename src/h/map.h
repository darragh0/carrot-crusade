#pragma once

#include <string>
#include <unordered_map>
#include "util.h"
#include <QPixmap>


namespace game {

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
