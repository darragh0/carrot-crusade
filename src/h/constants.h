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
                "    border: 3px solid white;"
                "    border-radius: 5px;"
                "}";

        const QString TEXTBOX =
                "QLabel#game-textbox { "
                "    font-size: 25px;"
                "    background-color: #bfa483;"
                "    padding: 0.1em;"
                "    color: black;"
                "    font-size: 1rem;"
                "    text-align: center;"
                "    border-left: 3px solid white;"
                "    border-right: 3px solid white;"
                "    border-bottom: 3px solid white;"
                "    border-bottom-left-radius: 5px;"
                "    border-bottom-right-radius: 5px;"
                "}";

        const QString NOTE_TEXTBOX =
                "QLabel#game-note {"
                "    font-size: 18px;"
                "    background-color: #ecc351;"
                "    border: 2px solid #bfa483;"
                "    padding: 0.1em;"
                "    color: black;"
                "    text-align: center;"
                "    border-radius: 3px;"
                "}";
    }
}

#endif
