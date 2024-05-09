#pragma once

#include <QLabel>
#include <QKeyEvent>

#include "map.h"


namespace game {


    class Sprite : public QLabel {

        Q_OBJECT

        public:

            [[maybe_unused]] const std::string& name;
            QPixmap* pixmap;
            int origin_x;
            int origin_y;

            explicit Sprite(QWidget* parent, const std::string& name, int origin_x, int origin_y);
            ~Sprite() override;

            int getX();
            int getY();

            void setCoords(int& x, int& y);
    };



    class Canvas : public QLabel {

        Q_OBJECT

        public:

            Sprite* carrot;
            Map::Region* region = nullptr;
            QLabel* textbox = nullptr;

            explicit Canvas(QWidget* parent);
            ~Canvas() override;

            void setRegion(Map::Region* map_region, int x, int y);
            void moveCarrot(int dx, int dy);

        protected:

            void keyPressEvent(QKeyEvent* event) override;

    };

}
