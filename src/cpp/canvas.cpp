#include "../h/canvas.h"
#include <iostream>


game::Sprite::Sprite(QWidget *parent, const std::string& name, int origin_x, int origin_y)
    : QLabel(parent),
      name(name),
      origin_x(origin_x),
      origin_y(origin_y),
      pixmap(new QPixmap("../images/sprites/carrot.png")) {

    int width = this->pixmap->width() * game::PIXEL_SCALE_FACTOR;
    int height = this->pixmap->height() * game::PIXEL_SCALE_FACTOR;

    this->setFixedSize(width, height);
    this->setPixmap(this->pixmap->scaled(width, height, Qt::KeepAspectRatio));
}


game::Sprite::~Sprite() {
    delete this->pixmap;
}


int game::Sprite::getX() {
    return (this->x() / game::PIXEL_SCALE_FACTOR) + this->origin_x;
}


int game::Sprite::getY() {
    return (this->y() / game::PIXEL_SCALE_FACTOR) + this->origin_y;
}


void game::Sprite::setCoords(int& x, int& y) {
    this->move((x - this->origin_x) * game::PIXEL_SCALE_FACTOR, (y - this->origin_y) * game::PIXEL_SCALE_FACTOR);
}


game::Canvas::Canvas(QWidget* parent)
    : QLabel(parent),
      carrot(new Sprite(parent, "Carrot", game::CARROT_ORIGIN_X, game::CARROT_ORIGIN_Y)) {

    this->setFocus();  // To notify on keyPressEvent
}


game::Canvas::~Canvas() {
    delete this->region;
    delete this->carrot;
}


void game::Canvas::setRegion(Map::Region* map_region, int x, int y) {

//    this->top_textbox->setText(map_region->name.c_str());

    int width = map_region->pixmap->width() * game::PIXEL_SCALE_FACTOR;
    int height = map_region->pixmap->height() * game::PIXEL_SCALE_FACTOR;

    this->parentWidget()->setFixedSize(width, height);
    this->setFixedSize(width, height);
    this->setPixmap(map_region->pixmap->scaled(width, height, Qt::KeepAspectRatio));

    this->region = map_region;
    this->carrot->setCoords(x, y);
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

        uint8_t next_region_x = this->region->coords.first + dx;
        uint8_t next_region_y = this->region->coords.second - dy;  // '-', since QT does Y coordinate from top to bottom

        Map::Region* next_region = Map::regions.at(std::make_pair(next_region_x, next_region_y));
        this->setRegion(next_region, next_x, next_y);
        return;
    }

    QRgb next_pixel = this->region->outline.pixel(next_x, next_y);

    if (qRed(next_pixel) == 255)
        return;

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
