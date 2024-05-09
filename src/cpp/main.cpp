#include <QApplication>
#include <QSplashScreen>
#include <windows.h>
#include "../h/mainwindow.h"
#include "../h/canvas.h"

using Map = game::Map;


int main(int argc, char **argv) {

    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap("../assets/images/misc/splash.png"));
    splash.show();

    MainWindow mainWindow;
    Map::init();
    auto* canvas = new game::Canvas(&mainWindow);
    auto* spawn = game::Map::regions.at(std::make_pair(0, 0));

    canvas->setRegion(spawn, 5, 35);

    splash.finish(&mainWindow);
    mainWindow.showMaximized();

    // PlaySound(
    //     TEXT("..\\assets\\audio\\songs\\themesong.wav"),
    //     nullptr,
    //     SND_ASYNC | SND_LOOP
    // );
    //

    int ret = QApplication::exec();

    Map::deleteRegions();

    return ret;
}
