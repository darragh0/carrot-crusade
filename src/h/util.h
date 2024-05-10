#pragma once

#include <cstdint>

#include <QString>


namespace game {

    const uint8_t PIXEL_SCALE_FACTOR = 10;
    const uint8_t HORIZONTAL_TILES = 128;
    const uint8_t VERTICAL_TILES = 72;
    const uint8_t CARROT_ORIGIN_X = 3;
    const uint8_t CARROT_ORIGIN_Y = 14;

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
