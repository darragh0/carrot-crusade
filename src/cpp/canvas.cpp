#include "../h/canvas.h"
#include <iostream>


game::Sprite::Sprite(QWidget *parent, const std::string& name, int x, int y)
    : QLabel(parent),
      name(name),
      center_x(x),
      center_y(y),
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
    return (this->x() / game::PIXEL_SCALE_FACTOR) + this->center_x;
}


int game::Sprite::getY() {
    return (this->y() / game::PIXEL_SCALE_FACTOR) + this->center_y;
}


void game::Sprite::setCoords(int& x, int& y) {
    this->move((x - this->center_x) * game::PIXEL_SCALE_FACTOR, (y - this->center_y) * game::PIXEL_SCALE_FACTOR);
}


game::Canvas::Canvas(QWidget* parent)
    : QLabel(parent),
      carrot(new Sprite(parent, "Carrot", game::CARROT_CENTER_X, game::CARROT_CENTER_Y)) {

    this->setFocus();  // To notify on keyPressEvent
}


game::Canvas::~Canvas() {
    delete this->region;
    delete this->carrot;
}


void game::Canvas::setRegion(Region* map_region, int x, int y) {

//    this->top_textbox->setText(map_region->name.c_str());

    int width = map_region->pixmap.width() * game::PIXEL_SCALE_FACTOR;
    int height = map_region->pixmap.height() * game::PIXEL_SCALE_FACTOR;

    this->parentWidget()->setFixedSize(width, height);
    this->setFixedSize(width, height);
    this->setPixmap(map_region->pixmap.scaled(width, height, Qt::KeepAspectRatio));

    this->region = map_region;
    this->carrot->setCoords(x, y);
}


void game::Canvas::moveCarrot(game::Direction dir) {

    const int current_x = this->carrot->getX();
    const int current_y = this->carrot->getY();

    int next_x = current_x;
    int next_y = current_y;

    bool at_edge;

    switch (dir) {
        case NORTH: at_edge = (--next_y == -1); break;
        case EAST: at_edge = (++next_x == game::HORIZONTAL_TILES); break;
        case SOUTH: at_edge = (++next_y == game::VERTICAL_TILES); break;
        case WEST: at_edge = (--next_x == -1); break;
    }

    if (at_edge) {
        QRgb current_pixel = this->region->outline.pixel(current_x, current_y);

        if (qGreen(current_pixel) != 255)
            return;

        next_x = (HORIZONTAL_TILES + next_x) % game::HORIZONTAL_TILES;
        next_y = (VERTICAL_TILES + next_y) % game::VERTICAL_TILES;

        Region* next_region = this->region->getExit(dir);
        std::cout << next_region << std::endl;
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

    Direction dir;

    switch (event->key()) {
        case Qt::Key_W: dir = Direction::NORTH; break;
        case Qt::Key_A: dir = Direction::WEST; break;
        case Qt::Key_S: dir = Direction::SOUTH; break;
        case Qt::Key_D: dir = Direction::EAST; break;
        default: return;
    }

    this->moveCarrot(dir);
}
