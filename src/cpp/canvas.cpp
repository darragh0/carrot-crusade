#include "../h/canvas.h"

#include <iostream>

#include <QApplication>
#include <QRect>
#include <QScreen>

#include "../h/util.h"
#include "../h/constants.h"


game::Canvas::Canvas(QWidget* parent)
    : QLabel(parent) {

    this->carrot = parseCarrotAttrs();
    this->carrot->setParent(this);
    this->carrot->show();
    this->setObjectName("game-canvas");  // Before setting stylesheet !important
    this->setStyleSheet(game::stylesheets::CANVAS);this->setAlignment(Qt::AlignTop);
    this->textbox = new QLabel(this);
    this->textbox->setObjectName("game-textbox");
    this->textbox->setStyleSheet(game::stylesheets::TEXTBOX);
    this->textbox->setAlignment(Qt::AlignCenter);
    this->setFocus();
}


game::Canvas::~Canvas() {
    delete this->textbox;
    delete this->carrot;
}


void game::Canvas::setRegion(Map::Region* map_region, int x, int y) {

    static int count = 0;  // TODO: Document use of static local var
    count++;

    if (x == -1 && y == -1) {
        x = this->carrot->canvas_pos_x;
        y = this->carrot->canvas_pos_y;
    }

    int width = map_region->pixmap->width() * game::PIXEL_SCALE_FACTOR;
    int height = map_region->pixmap->height() * game::PIXEL_SCALE_FACTOR + 100;
    const std::string txt = "<span style=\"color: blue; font-weight: bold;\">Current Region:</span> " + map_region->name;

    if (count == 1) {
        this->textbox->setFixedSize(width, 100);
        this->setFixedSize(width, height);

        QScreen* screen = QApplication::primaryScreen();
        QRect geom = screen->availableGeometry();  // Excludes Taskbar (otherwise height includes it)

        int horizontal_padding = (geom.width() - width) / 2;
        int vertical_padding = (geom.height() - height) / 2;

        this->move(horizontal_padding,vertical_padding);
        this->textbox->move(0, height - 100);
    } else {
        for (auto& pair : this->region->sprites) {
            Sprite* sprite = pair.second;
            sprite->hide();
        }
    }

    this->textbox->setText(QString::fromStdString(txt));
    this->setPixmap(map_region->pixmap->scaled(width, height, Qt::KeepAspectRatio));
    this->region = map_region;
    this->carrot->setCoords(x, y);

    for (auto& pair : this->region->sprites) {
        Sprite* sprite = pair.second;
        sprite->setParent(this);  // !!!!!!!!!!!!!!!!!!!! FIXME
        sprite->show();
        sprite->setCoords(sprite->canvas_pos_x, sprite->canvas_pos_y);
    }
}


void game::Canvas::moveCarrot(int dx, int dy) {

    const int current_x = this->carrot->getX();
    const int current_y = this->carrot->getY();

    int next_x = current_x + dx;
    int next_y = current_y + dy;

    bool at_edge =
        (next_y == -1)
        || (next_y == game::VERTICAL_TILES)
        || (next_x == -1)
        || (next_x == game::HORIZONTAL_TILES);

    if (at_edge) {

        QRgb current_pixel = this->region->outline.pixel(current_x, current_y);

        if (qGreen(current_pixel) != 255)
            return;

        // Configuring spawn point
        next_x = (HORIZONTAL_TILES + next_x) % game::HORIZONTAL_TILES;
        next_y = (VERTICAL_TILES + next_y) % game::VERTICAL_TILES;

        uint8_t next_region_x = this->region->map_coords.first + dx;
        uint8_t next_region_y = this->region->map_coords.second - dy;  // '-', since QT does Y coordinate from top to bottom

        Map* map = Map::getInstance();
        Map::Region* next_region = map->getRegion(next_region_x, next_region_y);
        this->setRegion(next_region, next_x, next_y);
        return;
    }

    QRgb next_pixel = this->region->outline.pixel(next_x, next_y);

    if (qRed(next_pixel) == 255 && qGreen(next_pixel) == 0 && qBlue(next_pixel) == 0) {
        return;
    }

    this->carrot->setCoords(next_x, next_y);
    std::cout << "x: " << next_x << "\ty: " << next_y << std::endl;

}


void game::Canvas::keyPressEvent(QKeyEvent *event) {

    int dx = 0;
    int dy = 0;

    switch (event->key()) {
        case Qt::Key_W: dy--; break;
        case Qt::Key_A: dx--; break;
        case Qt::Key_S: dy++; break;
        case Qt::Key_D: dx++; break;
        default: return;
    }

    this->moveCarrot(dx, dy);
}
