#include <QApplication>
#include <QSplashScreen>
#include <QThread>

#include "../h/mainwindow.h"
#include "../h/canvas.h"


int main(int argc, char **argv) {

    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap("../images/misc/splash.png"));
    splash.show();

    QThread::sleep(1);

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

    // Setting up connections
    rocky_road.setExit(game::EAST, &snowy_summit);
    snowy_summit.setExit(game::WEST, &rocky_road);
    snowy_summit.setExit(game::NORTH, &grassy_grove);
    grassy_grove.setExit(game::SOUTH, &snowy_summit);
    grassy_grove.setExit(game::NORTH, &luminous_lake);
    luminous_lake.setExit(game::SOUTH, &grassy_grove);
    canvas.setRegion(&rocky_road, 5, 35);

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
