#pragma once

#include <cstdint>
#include <QString>

namespace game {

    const uint8_t PIXEL_SCALE_FACTOR = 10;
    const uint8_t HORIZONTAL_TILES = 128;
    const uint8_t VERTICAL_TILES = 72;
    const uint8_t CARROT_ORIGIN_X = 3;
    const uint8_t CARROT_ORIGIN_Y = 14;

    const QString CANVAS_CSS =
        "QLabel#game-canvas {"
        "    border: 10px solid #98684a;"
        "    outline: 2px solid #98684a;"
        "    border-bottom: none;"
        "    border-radius: 10px;"
        "    border-bottom-left-radius: 0;"
        "    border-bottom-right-radius: 0;"
        "}";

    const QString TEXTBOX_CSS =
        "QLabel#game-textbox { "
        "    font-size: 25px;"
        "    background-color: #bfa483;"
        "    border: 10px solid #98684a;"
        "    outline: 2px solid #98684a;"
        "    border-top: none;"
        "    border-radius: 10px;"
        "    border-top-left-radius: 0;"
        "    border-top-right-radius: 0;"
        "    padding: 0.1em;"
        "    color: black;"
        "    font-size: 1rem;"
        "}";
}
