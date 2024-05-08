#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <iostream>
#include "../h/mainwindow.h"
#include "../h/canvas.h"
#include <filesystem>
#include <fstream>
#include <QVBoxLayout>


void parseMapRegionAttrs() {

    for (const auto& region_folder : std::filesystem::directory_iterator("../images/map-regions")) {
        const std::string attrs_toml_path = region_folder.path().generic_string() + "/attrs.toml";
        const std::string src_png = region_folder.path().generic_string() + "/src.png";
        const std::string outline_png = region_folder.path().generic_string() + "/outline.png";

        std::string name;
        std::string map_pos_x_str;
        std::string map_pos_y_str;

        std::ifstream file(attrs_toml_path);

        std::getline(file, name);
        std::getline(file, map_pos_x_str);
        std::getline(file, map_pos_y_str);
        file.close();

        name = name.substr(8, name.length() - 9);

        map_pos_x_str = map_pos_x_str.substr(12, map_pos_x_str.length() - 12);
        const uint8_t map_pos_x = std::stoi(map_pos_x_str);

        map_pos_y_str = map_pos_y_str.substr(12, map_pos_y_str.length() - 12);
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
    auto* canvas = new game::Canvas(&mainWindow);

    auto* spawn = game::Map::regions.at(std::make_pair(0, 0));
    auto* textbox = new QLabel(&mainWindow);

    textbox->setStyleSheet(game::TEXTBOX_CSS);
    textbox->setAlignment(Qt::AlignCenter);
    textbox->setFixedSize(spawn->pixmap->width() * game::PIXEL_SCALE_FACTOR, 100);

    canvas->setTextBox(textbox);
    canvas->setRegion(spawn, 5, 35);

    // Create a layout for the central widget of the main window
    auto* centralLayout = new QVBoxLayout(mainWindow.centralWidget());
    centralLayout->addWidget(canvas, 0, Qt::AlignCenter); // Add the canvas to the layout and center it horizontally
    centralLayout->addWidget(textbox, 0, Qt::AlignCenter);

    // Adding centralLayout means it takes focus, hence the following:
    canvas->setFocus();

    splash.finish(&mainWindow);
    mainWindow.showMaximized();

    int ret = QApplication::exec();

    game::Map::deleteRegions();
    delete centralLayout;
    delete canvas;
    delete textbox;

    return ret;
}
