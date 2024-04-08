#include <iostream>

#include "Map.h"


int main() {

    Map map;

    map.addRegion("center", 1, 1);
    map.addRegion("left", 0, 1);
    map.addRegion("right", 2, 1);
    map.addRegion("top", 1, 2);
    map.addRegion("bottom", 1, 0);

    for (auto& reg : map.regions) {
        reg.second->showConnections();
        std::cout << std::endl;
    }

    return 0;
}
