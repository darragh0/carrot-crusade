#ifndef CONSTS_INCLUDED_
#define CONSTS_INCLUDED_

#include <string>
#include <cstdint>

#include <QString>


namespace game {

    const std::string MAP_REGIONS_DIR = "../assets/images/map-regions";
    const std::string CARROT_DIR = "../assets/images/carrot";
    const uint8_t PIXEL_SCALE_FACTOR = 10;
    const uint8_t HORIZONTAL_TILES = 128;
    const uint8_t VERTICAL_TILES = 72;

    namespace stylesheets {

        const QString CANVAS =
                "QLabel#game-canvas {"
                "}";

        const QString TEXTBOX =
                "QLabel#game-textbox { "
                "    font-size: 25px;"
                "    background-color: #bfa483;"
                "    padding: 0.1em;"
                "    color: black;"
                "    font-size: 1rem;"
                "    text-align: center;"
                "}";
    }
}

#endif
