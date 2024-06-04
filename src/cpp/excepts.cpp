#include <utility>

#include "../h/excepts.h"


game::incomplete_map_region::incomplete_map_region(std::string msg)
    : message(std::move(msg)) {}


const char *game::incomplete_map_region::what() const noexcept {
    return this->message.c_str();
}
