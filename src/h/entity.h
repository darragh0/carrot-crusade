#pragma once

#include <QLabel>
#include <QPixmap>
#include <QWidget>


namespace game {

    class Entity : public QLabel {

        Q_OBJECT

        public:

            [[maybe_unused]] const std::string name;
            QPixmap* pixmap;
            const uint8_t canvas_pos_x;
            const uint8_t canvas_pos_y;
            const int origin_x;
            const int origin_y;

            Entity(
                QWidget* parent,
                // NOLINTNEXTLINE
                const std::string name,
                const std::string& img_src,
                int origin_x,
                int origin_y,
                uint8_t canvas_pos_x,
                uint8_t canvas_pos_y
            );

            ~Entity() override;

            int getX();
            int getY();
            void setCoords(int x, int y);

    };


    class Sprite : public Entity {

        public:

            Sprite(
                QWidget* parent,
                // NOLINTNEXTLINE
                const std::string name,
                const std::string& img_src,
                int origin_x,
                int origin_y,
                uint8_t canvas_pos_x,
                uint8_t canvas_pos_y
            );

    };

}