#include <iostream>

#include "../h/map.h"


game::Region::Region(const std::string& name, const std::string& file_path)
    : name(name),
      file_path(file_path) {}
