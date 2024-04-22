#include <QApplication>
#include <QSplashScreen>
#include <QThread>

#include "../h/mainwindow.h"
#include "../h/canvas.h"


int main(int argc, char **argv) {

    QApplication app(argc, argv);
    QSplashScreen splash(QPixmap("../images/home-screen.png"));
    splash.show();

    QThread::sleep(1);

    MainWindow mainWindow;
    game::Canvas canvas(&mainWindow);

    game::Region rocky_road(
        "Rocky Road",
        "../images/map-regions/rocky-road-outline.png",
        "../images/map-regions/rocky-road-outline.png"
    );

    game::Region snowy_summit(
            "Snowy Summit",
        "../images/map-regions/snowy-summit-outline.png",
        "../images/map-regions/snowy-summit.png"
    );

    rocky_road.setExit(game::EAST, &snowy_summit);
    snowy_summit.setExit(game::WEST, &rocky_road);
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
