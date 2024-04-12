#include "mainwindow.h"
#include "canvas.h"

#include <QApplication>


int main(int argc, char **argv) {

    QApplication app(argc, argv);
    MainWindow mainWindow;
    GameCanvas canvas(&mainWindow);
    Map map;

    map.addRegion("Rocky Road", "../images/map-regions/rocky-road.png", 0, 0);
    map.addRegion("Snowy Summit", "../images/map-regions/snowy-summit.png", 1, 0);
    map.addRegion("Grassy Grove", "../images/map-regions/grassy-grove.png", 1, 1);

    canvas.setRegion(map.getRegion("Rocky Road"));

    mainWindow.show();

    return QApplication::exec();

}
