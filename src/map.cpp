#include <iostream>

#include "map.h"


Map::Region::Region(const char *name, const char *file_path, int x, int y)
    : name(name),
      file_path(file_path),
      x(x),
      y(y) {}


void Map::Region::showConnections() {

    std::cout << "Regions connected to: " << this->name << std::endl;

    if (this->north)
        std::cout << "North: " << this->north->name << std::endl;

    if (this->east)
        std::cout << "East:  " << this->east->name << std::endl;

    if (this->south)
        std::cout << "South: " << this->south->name << std::endl;

    if (this->west)
        std::cout << "West:  " << this->west->name << std::endl;
}


void Map::addRegion(const char* name, const char* file_path, int x, int y) {
    std::shared_ptr<Region> region = std::make_shared<Region>(name, file_path, x, y);

    this->applyConnections(region);
    this->regions[name] = region;
}


std::shared_ptr<Map::Region> Map::getRegion(const char* name) {
    return this->regions.at(name);
}


void Map::applyConnections(std::shared_ptr<Region>& new_region) {

    for (auto &pair: this->regions) {

        std::shared_ptr<Region> region = pair.second;

        if (region->y == new_region->y) {

            if (region->x == new_region->x + 1) {
                new_region->east = region;
                region->west = new_region;
            } else if (region->x == new_region->x - 1) {
                new_region->west = region;
                region->east = new_region;
            }

        } else if (region->x == new_region->x) {

            if (region->y == new_region->y + 1) {
                new_region->north = region;
                region->south = new_region;
            } else if (region->y == new_region->y - 1) {
                new_region->south = region;
                region->north = new_region;
            }
        }
    }
}
