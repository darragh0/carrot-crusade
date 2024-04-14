#pragma once

#include <memory>
#include <string>
#include <QLabel>
#include <QKeyEvent>

#include "map.h"


namespace game {

    class Sprite : public QLabel {

        Q_OBJECT

        public:

            const std::string& name;
            const std::shared_ptr<QPixmap> pixmap;

            explicit Sprite(QWidget* parent, const std::string& name);

            int getX();
            int getY();
    };


    class Canvas : public QLabel {

        Q_OBJECT

        public:

            std::shared_ptr<Sprite> carrot;
            Region* region = nullptr;

            explicit Canvas(QWidget* parent);

            void setRegion(Region* map_region);
            void moveCarrot(int dx, int dy);

        protected:

            void keyPressEvent(QKeyEvent* event) override;

    };

}
