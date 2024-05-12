#pragma once

#include <QLabel>
#include <QKeyEvent>

#include "entity.h"
#include "map.h"


namespace game {

    class Canvas : public QLabel {

        Q_OBJECT

        public:

            Sprite* carrot = nullptr;
            Map::Region* region = nullptr;
            QLabel* textbox = nullptr;

            explicit Canvas(QWidget* parent);
            ~Canvas() override;

            void setRegion(Map::Region* map_region, int x = -1, int y = -1);
            void moveCarrot(int dx, int dy);

        protected:

            void keyPressEvent(QKeyEvent* event) override;

    };

}
