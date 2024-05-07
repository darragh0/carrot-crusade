#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <iostream>
#include "../h/mainwindow.h"
#include "../h/canvas.h"
#include <filesystem>
#include <fstream>
#include <vector>


void parseMapRegionAttrs() {

    for (const auto& region_folder : std::filesystem::directory_iterator("../images/map-regions")) {
        const std::string attrs_toml_path = region_folder.path().string() + "\\attrs.toml";
        const std::string src_png = region_folder.path().string() + "\\src.png";
        const std::string outline_png = region_folder.path().string() + "\\outline.png";

        std::string name;
        std::string map_pos_x_str;
        std::string map_pos_y_str;

        std::ifstream file(attrs_toml_path);

        std::getline(file, name);
        std::getline(file, map_pos_x_str);
        std::getline(file, map_pos_y_str);
        file.close();

        const uint8_t first_quote_idx = name.find('"');
        name = name.substr(
            first_quote_idx + 1,
            name.length() - 2 - first_quote_idx
        );

        const uint8_t equal_symbol_idx_x = map_pos_x_str.find('=');
        map_pos_x_str = map_pos_x_str.substr(
            equal_symbol_idx_x + 1,
            map_pos_x_str.length() - 1 - equal_symbol_idx_x
        );

        const uint8_t map_pos_x = std::stoi(map_pos_x_str);

        const uint8_t equal_symbol_idx_y = map_pos_y_str.find('=');
        map_pos_y_str = map_pos_y_str.substr(
                equal_symbol_idx_y + 1,
                map_pos_y_str.length() - 1 - equal_symbol_idx_y
        );

        const uint8_t map_pos_y = std::stoi(map_pos_y_str);

        new game::Map::Region(
            name,
            src_png,
            outline_png,
            map_pos_x,
            map_pos_y
        );
    }

}


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap("../images/misc/splash.png"));
    splash.show();

    QThread::sleep(1);

    parseMapRegionAttrs();

    MainWindow mainWindow;
    game::Canvas canvas(&mainWindow);

    game::Region rocky_road(
        "Rocky Road",
        "../images/map-regions/rocky-road/src.png",
        "../images/map-regions/rocky-road/outline.png"
    );

    game::Region snowy_summit(
        "Snowy Summit",
        "../images/map-regions/snowy-summit/src.png",
        "../images/map-regions/snowy-summit/outline.png"
    );

    game::Region grassy_grove(
        "Grassy Grove",
        "../images/map-regions/grassy-grove/src.png",
        "../images/map-regions/grassy-grove/outline.png"
    );

    game::Region luminous_lake(
        "Luminous Lake",
        "../images/map-regions/luminous-lake/src.png",
        "../images/map-regions/luminous-lake/outline.png"
    );

    game::Region candy_crescent(
        "Candy Crescent",
        "../images/map-regions/candy-crescent/src.png",
        "../images/map-regions/candy-crescent/outline.png"
    );

    // Setting up connections
    rocky_road.setExit(game::EAST, &snowy_summit);
    snowy_summit.setExit(game::WEST, &rocky_road);
    snowy_summit.setExit(game::NORTH, &grassy_grove);
    grassy_grove.setExit(game::SOUTH, &snowy_summit);
    grassy_grove.setExit(game::NORTH, &luminous_lake);
    grassy_grove.setExit(game::EAST, &candy_crescent);
    candy_crescent.setExit(game::WEST, &grassy_grove);
    luminous_lake.setExit(game::SOUTH, &grassy_grove);
    canvas.setRegion(&rocky_road, 5, 35);

    std::cout << "Map regions @ (1, 0): " <<  game::Map::regions.at(std::make_pair(1, 0))->name << std::endl;

    mainWindow.show();
    splash.finish(&mainWindow);

    //    QPalette palette;
    //    palette.setColor(QPalette::Window, Qt::darkGray);
    //    palette.setColor(QPalette::WindowText, Qt::white);
    //
    //    auto* textbox = new QLabel(&mainWindow);
    //    textbox->setStyleSheet("font-size: 2rem; border: 1em solid #dddddd; padding: 1em; margin: 0;");
    //    textbox->setAutoFillBackground(true);
    //    textbox->setPalette(palette);
    //    textbox->setFixedSize(1024, 150);
    //    textbox->move(0, 576);
    //
    //    auto *top_text = new QLabel(&mainWindow);
    //    top_text->setFixedSize(1024, 50);
    //    top_text->setStyleSheet("font-size: 5rem;");
    //
    //    auto *bottom_text = new QLabel(&mainWindow);
    //    bottom_text->setFixedSize(1024, 100);
    //    bottom_text->move(0, 50);
    //
    //    canvas.top_textbox = top_text;
    //    canvas.bottom_textbox = bottom_text;

    return QApplication::exec();
}
