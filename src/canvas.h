#pragma once

#include <memory>
#include <QLabel>
#include <QKeyEvent>

#include "map.h"


class GameSprite : public QLabel {

    Q_OBJECT

    public:

        const char* name;
        const std::shared_ptr<QPixmap> pixmap;

        explicit GameSprite(QWidget* parent, const char* name);

};


class GameCanvas : public QLabel {

    Q_OBJECT

    public:

        std::shared_ptr<GameSprite> carrot;
        std::shared_ptr<Map::Region> region;

        explicit GameCanvas(QWidget* parent);

        void setRegion(const std::shared_ptr<Map::Region>& map_region);

    protected:

        void keyPressEvent(QKeyEvent* event) override;

};
