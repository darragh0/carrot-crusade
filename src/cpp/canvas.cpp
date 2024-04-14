#include "../h/canvas.h"
#include <iostream>


game::Sprite::Sprite(QWidget *parent, const std::string& name)
    : QLabel(parent),
      name(name),
      pixmap(std::make_shared<QPixmap>("../images/sprites/carrot.png")) {

    this->setFixedSize(56, 120);
    this->setPixmap(this->pixmap->scaled(56, 120, Qt::KeepAspectRatio));
}


int game::Sprite::getX() {
    return this->x() / 8 + 3;  // TODO: pivot_point attribute on Sprite
}


int game::Sprite::getY() {
    return this->y() / 8 + 9;
}


game::Canvas::Canvas(QWidget* parent)
    : QLabel(parent),
      carrot(std::make_shared<Sprite>(parent, "Carrot")) {

    this->setFocus();  // To notify on keyPressEvent
}


void game::Canvas::setRegion(Region* map_region) {

    QPixmap pixmap(map_region->file_path.c_str());

    this->parentWidget()->setFixedSize(1024, 576);
    this->setFixedSize(1024, 576);
    this->setPixmap(pixmap.scaled(1024, 576, Qt::KeepAspectRatio));

    this->region = map_region;

    // Center carrot vertically
    this->carrot->move(0, 36*8 - this->carrot->height());
}


void game::Canvas::moveCarrot(int dx, int dy) {

    int next_x = this->carrot->getX() + dx;
    int next_y = this->carrot->getY() + dy;

    if (next_x == -1 || next_x == 128)
        return;

    if (next_y == -1 || next_y == 72)
        return;

//    for (std::pair<int, int>& pair : this->region->forbidden_coordinates) {
//        if (pair.first == next_x && pair.second == next_y)
//            return;
//    }

    this->carrot->move(this->carrot->x() + (dx * 8), this->carrot->y() + (dy * 8));
    std::cout << next_x << ", " << next_y << std::endl;
}


void game::Canvas::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {

        case Qt::Key_W:
            this->moveCarrot(0, -1);
            break;

        case Qt::Key_A:
            this->moveCarrot(-1, 0);
            break;

        case Qt::Key_S:
            this->moveCarrot(0, 1);
            break;

        case Qt::Key_D:
            this->moveCarrot(1, 0);
            break;
    }
}
