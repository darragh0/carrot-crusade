#include "canvas.h"


GameSprite::GameSprite(QWidget *parent, const char *name)
    : QLabel(parent),
      name(name),
      pixmap(std::make_shared<QPixmap>("../images/sprites/carrot.png")) {

    this->setFixedSize(this->pixmap->size());
    this->setPixmap(*this->pixmap);
}


GameCanvas::GameCanvas(QWidget* parent)
    : QLabel(parent),
      carrot(std::make_shared<GameSprite>(parent, "Carrot")) {

    this->setFocus();
}


void GameCanvas::setRegion(const std::shared_ptr<Map::Region>& map_region) {

    QPixmap pixmap(map_region->file_path);

    this->parentWidget()->setFixedSize(pixmap.size());
    this->setFixedSize(pixmap.size());
    this->setPixmap(pixmap);

    this->region = map_region;

    // Center carrot vertically
    this->carrot->move(0, 36*8 - this->carrot->height());
}


void GameCanvas::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {

        case Qt::Key_W:
            this->carrot->move(this->carrot->x(), this->carrot->y() - 8);
            break;

        case Qt::Key_A:
            this->carrot->move(this->carrot->x() - 8, this->carrot->y());
            break;

        case Qt::Key_S:
            this->carrot->move(this->carrot->x(), this->carrot->y() + 8);
            break;

        case Qt::Key_D:
            this->carrot->move(this->carrot->x() + 8, this->carrot->y());
            break;
    }
}
