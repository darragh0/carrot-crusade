#include <utility>
#include <iostream>

#include "../h/sprite.h"
#include "../h/constants.h"


game::SpriteEntity::SpriteEntity(
        QWidget* parent,
        // NOLINTNEXTLINE
        const std::string name,
        const std::string& img_src,
        const int origin_x,
        const int origin_y,
        const uint16_t canvas_pos_x,
        const uint16_t canvas_pos_y
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


void game::SpriteEntity::doAction(game::Carrot *carrot) {
}


game::SpriteEntity::~SpriteEntity() {
    delete this->pixmap;
}


uint16_t game::SpriteEntity::getX() const {
    return (this->x() / game::PIXEL_SCALE_FACTOR) + this->origin_x;
}


uint16_t game::SpriteEntity::getY() const {
    return (this->y() / game::PIXEL_SCALE_FACTOR) + this->origin_y;
}


void game::SpriteEntity::setCoords(const int x, const int y) {
    this->move((x - this->origin_x) * game::PIXEL_SCALE_FACTOR, (y - this->origin_y) * game::PIXEL_SCALE_FACTOR);
}


game::Carrot::Carrot(
    QWidget *parent,
    const std::string name,
    const std::string& img_src,
    int origin_x,
    int origin_y,
    uint16_t canvas_pos_x,
    uint16_t canvas_pos_y
    )
    : SpriteEntity(parent, name, img_src, origin_x, origin_y, canvas_pos_x, canvas_pos_y) {
}


void game::Carrot::operator << (game::Item* item) {

}


void game::Carrot::operator << (game::Vehicle* vehicle) {
    // TODO: This.
    vehicle->doAction(this);
}


bool game::Carrot::inVehicle() const {
    return this->ride;
}


void game::Carrot::setRide(game::Vehicle *vehicle) {

    this->move(
        (vehicle->getX() - this->origin_x) * game::PIXEL_SCALE_FACTOR,
        (vehicle->getY() - this->origin_y) * game::PIXEL_SCALE_FACTOR
    );

    std::cout << "Ride started" << std::endl;
    this->ride = vehicle;
}


void game::Carrot::endRide() {
    std::cout << "Ride ended" << std::endl;
    this->ride = nullptr;
}


bool game::Carrot::rideIs(game::Vehicle *vehicle) {
    return vehicle == this->ride;
}

void game::Carrot::doAction(game::Carrot *carrot) {
}


void game::Carrot::setCoords(int x, int y) {
    if (this->ride)
        this->ride->setCoords(x, y);

    this->move((x - this->origin_x) * game::PIXEL_SCALE_FACTOR, (y - this->origin_y) * game::PIXEL_SCALE_FACTOR);
}

game::Vehicle::Vehicle(
    QWidget* parent,
    // NOLINTNEXTLINE
    const std::string name,
    const std::string& img_src,
    const int origin_x,
    const int origin_y,
    const uint16_t canvas_pos_x,
    const uint16_t canvas_pos_y
    )
    : SpriteEntity(parent, name, img_src, origin_x, origin_y, canvas_pos_x, canvas_pos_y) {
}


void game::Vehicle::doAction(game::Carrot *carrot) {
    if (carrot->inVehicle())
        carrot->endRide();
    else
        carrot->setRide(this);
}


game::Item::Item(
        QWidget *parent,
        // NOLINTNEXTLINE
        const std::string name,
        const std::string& img_src,
        const int origin_x,
        const int origin_y,
        const uint16_t canvas_pos_x,
        const uint16_t canvas_pos_y,
        std::string description
        )
        : SpriteEntity(parent, name, img_src, origin_x, origin_y, canvas_pos_x, canvas_pos_y),
          description(std::move(description)) {
}


const std::string& game::Item::getDescription() const {
    return this->description;
}


void game::Item::doAction(game::Carrot *carrot) {
    // TODO: This.
}
