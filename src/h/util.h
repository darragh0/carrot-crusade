#pragma once

#include <cstdint>
#include <QString>

namespace game {

    const uint8_t PIXEL_SCALE_FACTOR = 10;
    const uint8_t HORIZONTAL_TILES = 128;
    const uint8_t VERTICAL_TILES = 72;
    const uint8_t CARROT_ORIGIN_X = 3;
    const uint8_t CARROT_ORIGIN_Y = 14;
    const QString TEXTBOX_CSS =
        "QLabel { "
        "    font-size: 25px;"
        "    background-color: #bfa483;"
        "    border: 0.25em solid #98684a;"
        "    border-bottom-left-radius: 0.5em;"
        "    border-bottom-right-radius: 0.5em;"
        "    padding: 0.1em;"
        "    color: black;"
        "    font-size: 1rem;"
        "    "
        "}";
}
