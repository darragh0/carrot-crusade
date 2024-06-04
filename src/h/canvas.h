#ifndef CANVAS_INCLUDED_
#define CANVAS_INCLUDED_

#include <QLabel>
#include <QKeyEvent>

#include "../h/map.h"


namespace game {

    class Canvas : public QLabel {

        Q_OBJECT

        public:

            Carrot* carrot = nullptr;
            Map::Region* region = nullptr;
            QLabel* textbox = nullptr;
            QLabel* note = nullptr;

            explicit Canvas(QWidget* parent);
            ~Canvas() override;

            void setRegion(Map::Region* map_region, int x = -1, int y = -1);
            void moveCarrot(int dx, int dy);
            void interactWithSprite();
            void toggleNoteDisplay() const;

        protected:

            void keyPressEvent(QKeyEvent* event) override;

    };

}

#endif