#include "../h/mainwindow.h"
#include "../h/canvas.h"

#include <QApplication>
#include <QSplashScreen>
#include <QThread>

int main(int argc, char **argv) {

    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap("../images/home-screen.png"));
    splash.show();

    QThread::sleep(3);

    MainWindow mainWindow;
    game::Canvas canvas(&mainWindow);

    auto* rocky_road = new game::Region("Rocky Road", "../images/map-regions/rocky-road.png");
    // auto* snowy_summit = new game::Region("Snowy Summit", "../images/map-regions/snowy-summit.png");
    // auto* grassy_grove = new game::Region("Grassy Grove", "../images/map-regions/grassy-grove.png");

    canvas.setRegion(rocky_road);

    mainWindow.show();
    splash.finish(&mainWindow);

    return QApplication::exec();
}
