#pragma once

#include <QLabel>
#include <QKeyEvent>

#include "map.h"


namespace game {


    class Sprite : public QLabel {

        Q_OBJECT

        public:

            const std::string& name;
            QPixmap* pixmap;
            int center_x;
            int center_y;

            explicit Sprite(QWidget* parent, const std::string& name, int center_x, int center_y);
            ~Sprite() override;

            int getX();
            int getY();

            void setCoords(int& x, int& y);
    };


    class Canvas : public QLabel {

        Q_OBJECT

        public:

            Sprite* carrot;
            Region* region = nullptr;
            QLabel* top_textbox = nullptr;
            QLabel* bottom_textbox = nullptr;

            explicit Canvas(QWidget* parent);
            ~Canvas() override;

            void setRegion(Region* map_region, int x, int y);
            void moveCarrot(Direction dir);

        protected:

            void keyPressEvent(QKeyEvent* event) override;

    };

}
