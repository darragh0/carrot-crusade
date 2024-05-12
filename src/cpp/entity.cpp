#include "../h/entity.h"

#include "../h/constants.h"


game::Entity::Entity(
        QWidget* parent,
        // NOLINTNEXTLINE
        const std::string name,
        const std::string& img_src,
        const int origin_x,
        const int origin_y,
        const uint8_t canvas_pos_x,
        const uint8_t canvas_pos_y
        )
        : QLabel(parent),
          name(name),
          pixmap(new QPixmap(img_src.c_str())),
          origin_x(origin_x),
          origin_y(origin_y),
          canvas_pos_x(canvas_pos_x),
          canvas_pos_y(canvas_pos_y) {

    int width = this->pixmap->width() * game::PIXEL_SCALE_FACTOR;
    int height = this->pixmap->height() * game::PIXEL_SCALE_FACTOR;

    this->setFixedSize(width, height);
    this->setPixmap(this->pixmap->scaled(width, height, Qt::KeepAspectRatio));
}


game::Entity::~Entity() {
    delete this->pixmap;
}


int game::Entity::getX() {
    return (this->x() / game::PIXEL_SCALE_FACTOR) + this->origin_x;
}


int game::Entity::getY() {
    return (this->y() / game::PIXEL_SCALE_FACTOR) + this->origin_y;
}


void game::Entity::setCoords(const int x, const int y) {
    this->move((x - this->origin_x) * game::PIXEL_SCALE_FACTOR, (y - this->origin_y) * game::PIXEL_SCALE_FACTOR);
}


game::Sprite::Sprite(
        QWidget *parent,
        // NOLINTNEXTLINE
        const std::string name,
        const std::string& img_src,
        const int origin_x,
        const int origin_y,
        const uint8_t canvas_pos_x,
        const uint8_t canvas_pos_y
        )
        : Entity(parent, name, img_src, origin_x, origin_y, canvas_pos_x, canvas_pos_y) {
}
