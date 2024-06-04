#include "../h/canvas.h"

#include <iostream>
#include <cmath>

#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QPoint>

#include "../h/constants.h"


game::Canvas::Canvas(QWidget* parent)
    : QLabel(parent) {

    this->carrot = game::parseSpriteAttrs(CARROT_DIR, true)->carrot;  // FIXME DELETE *
    this->carrot->setParent(this);
    this->carrot->show();
    this->setObjectName("game-canvas");  // Before setting stylesheet !important
    this->setStyleSheet(game::stylesheets::CANVAS);this->setAlignment(Qt::AlignTop);
    this->textbox = new QLabel(this);
    this->note = new QLabel(this);
    this->note->setObjectName("game-note");
    this->note->setAlignment(Qt::AlignCenter);
    this->note->setStyleSheet(game::stylesheets::NOTE_TEXTBOX);
    this->note->hide();
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
        this->note->setFixedSize(width / 2, 100);
        this->setFixedSize(width, height);

        QScreen* screen = QApplication::primaryScreen();
        QRect geom = screen->availableGeometry();  // Excludes Taskbar (otherwise height includes it)

        int horizontal_padding = (geom.width() - width) / 2;
        int vertical_padding = (geom.height() - height) / 2;

        this->move(horizontal_padding,vertical_padding);
        this->textbox->move(0, height - 100);
        this->note->move((width / 2) / 2, height / 2 - 100);
    } else {
        for (auto& pair : this->region->vehicles) {
            Sprite* sprite = pair.second;
            sprite->vehicle->hide();
        }

        for (auto& pair : this->region->items) {
            Sprite* sprite = pair.second;
            sprite->item->hide();
        }
    }

    this->textbox->setText(QString::fromStdString(txt));
    this->setPixmap(map_region->pixmap->scaled(width, height, Qt::KeepAspectRatio));
    this->region = map_region;
    this->carrot->setCoords(x, y);

    for (auto& pair : this->region->vehicles) {
        Sprite* sprite = pair.second;

        if (Vehicle* v = sprite->vehicle) {
            v->setParent(this);
            v->show();
            this->carrot->raise();

            if (this->carrot->rideIs(v))
                continue;

            v->setCoords(v->canvas_pos_x, v->canvas_pos_y);
        }
    }

    for (auto& pair : this->region->items) {
        Sprite* sprite = pair.second;

        if (HintNote* i = sprite->item) {
            i->setParent(this);

            int carrot_hint_n = 0;

            if (this->carrot->current_note)
                carrot_hint_n = this->carrot->current_note->hintNumber();

            const int n = i->hintNumber();
            std::cout << i->name << std::endl;
            std::cout << i->hintNumber() << std::endl;

            if (n == carrot_hint_n + 1) {
                const std::string text = "<b>" + i->name + ": </b>" + i->getDescription();
                i->show();
                i->setCoords(i->canvas_pos_x, i->canvas_pos_y);
                this->note->setText(QString::fromStdString(text));
            }
        }
    }

}


void game::Canvas::toggleNoteDisplay() const {
    if (this->carrot->current_note) {
        if (this->note->isVisible())
            this->note->hide();
        else
            this->note->show();
    }
}


void game::Canvas::interactWithSprite() {
    if (this->carrot->inVehicle()) {
        const int x = this->carrot->getX();
        const int y = this->carrot->getY();

        for (int _x = x; _x < game::HORIZONTAL_TILES; _x++) {
            for (int _y = y; _y < game::VERTICAL_TILES; _y++) {
                QRgb pixel = this->region->outline.pixel(_x, _y);

                const double dist = std::sqrt(
                        std::pow(x - _x, 2)
                        + std::pow(y - _y, 2)
                );

                if (dist < 10 && qRed(pixel) == 255 && qGreen(pixel) == 0 && qBlue(pixel) == 0) {
                   this->carrot->endRide();
                   this->carrot->setCoords(_x + 2, _y + 2);
                   return;
                }
            }
        }

        return;
    }

    QPoint p = this->mapFromGlobal(QCursor::pos());
    const int x = p.x() / game::PIXEL_SCALE_FACTOR;
    const int y = p.y() / game::PIXEL_SCALE_FACTOR;

    // Sort by min dist.
    for (const auto& sprite_pair : this->region->vehicles) {
        Sprite* sprite = sprite_pair.second;
        const int sprite_x = sprite->vehicle->getX();
        const int sprite_y = sprite->vehicle->getY();

        const double dist = std::sqrt(
            std::pow(x - sprite_x, 2)
             + std::pow(y - sprite_y, 2)
        );

        if (dist < 10) {
            *(this->carrot) << (sprite->vehicle);
        }
    }

    for (const auto& item_pair : this->region->items) {
        Sprite* sprite = item_pair.second;
        const int item_x = sprite->item->getX();
        const int item_y = sprite->item->getY();

        const double dist = std::sqrt(
            std::pow(x - item_x, 2)
            + std::pow(y - item_y, 2)
        );

        if (dist < 5) {
            sprite->item->doAction(this->carrot);
        }
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
        case Qt::Key_Space: this->interactWithSprite(); break;
        case Qt::Key_N: this->toggleNoteDisplay(); break;
        default: return;
    }

    this->moveCarrot(dx, dy);
}
