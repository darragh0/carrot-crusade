#include "../h/map.h"
#include <iostream>


game::Region::Region(const std::string& name, const std::string& img_src, const std::string& outlined_img_src)
    : name(name),
      pixmap(QPixmap(img_src.c_str())),
      outline((QPixmap(outlined_img_src.c_str())).toImage()) {
}


void game::Region::setExit(Direction dir, Region* region) {
    this->exits.insert({dir, region});
}


game::Region* game::Region::getExit(Direction dir) {
    return this->exits.at(dir);
}
