#include <windows.h>

#include <QApplication>
#include <QSplashScreen>
#include <iostream>
#include "../h/mainwindow.h"
#include "../h/canvas.h"


int main(int argc, char **argv) {

    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap("../assets/images/misc/splash.png"));
    splash.show();

    MainWindow mainWindow;
    game::Map* map = game::Map::getInstance();

    auto* canvas = new game::Canvas(&mainWindow);
    auto* spawn = map->getRegion(0, 0);

    canvas->setRegion(spawn);

    splash.finish(&mainWindow);
    mainWindow.showMaximized();

//    PlaySound(
//         TEXT("..\\assets\\audio\\songs\\themesong.wav"),
//         nullptr,
//         SND_ASYNC | SND_LOOP
//    );

    int ret = QApplication::exec();

    delete game::Map::getInstance();

    return ret;
}
