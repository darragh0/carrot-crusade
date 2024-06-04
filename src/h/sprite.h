#ifndef GSPRITE_INCLUDED_
#define GSPRITE_INCLUDED_

#include <QLabel>
#include <QPixmap>
#include <QWidget>


namespace game {

    class Carrot;


    class SpriteEntity : public QLabel {

        Q_OBJECT

        public:

            [[maybe_unused]] const std::string name;
            QPixmap* pixmap;
            const uint16_t canvas_pos_x;
            const uint16_t canvas_pos_y;
            const int origin_x;
            const int origin_y;

        protected:

            SpriteEntity(
                QWidget* parent,
                // NOLINTNEXTLINE
                const std::string name,
                const std::string& img_src,
                int origin_x,
                int origin_y,
                uint16_t canvas_pos_x,
                uint16_t canvas_pos_y
            );

        public:

            [[nodiscard]] uint16_t getX() const;
            [[nodiscard]] uint16_t getY() const;
            virtual void setCoords(int x, int y);
            virtual void doAction(Carrot* carrot) = 0;
            ~SpriteEntity() override;
    };


    class Vehicle : public virtual SpriteEntity {

        public:

            Vehicle(
                QWidget* parent,
                // NOLINTNEXTLINE
                const std::string name,
                const std::string& img_src,
                int origin_x,
                int origin_y,
                uint16_t canvas_pos_x,
                uint16_t canvas_pos_y
            );

            void doAction(Carrot* carrot) override;
    };


    class Item : public virtual SpriteEntity {

        private:

            const std::string description;

        public:

            Item(
                    QWidget* parent,
                    // NOLINTNEXTLINE
                    const std::string name,
                    const std::string& img_src,
                    int origin_x,
                    int origin_y,
                    uint16_t canvas_pos_x,
                    uint16_t canvas_pos_y,
                    std::string description
            );

            [[nodiscard]] const std::string& getDescription() const;
            void doAction(Carrot* carrot) override;
    };

    class Character {

        protected:
            Character() = default;

        public:
            virtual void operator << (Item* item) = 0;
            virtual void operator << (Vehicle* vehicle) = 0;
    };

    class Carrot : public virtual SpriteEntity, public virtual Character {

        private:

            Vehicle* ride = nullptr;

        public:

            Carrot(
                QWidget* parent,
                std::string name,
                const std::string& img_src,
                int origin_x,
                int origin_y,
                uint16_t canvas_pos_x,
                uint16_t canvas_pos_y
            );

            [[nodiscard]] bool inVehicle() const;
            void setRide(Vehicle* vehicle);
            bool rideIs(Vehicle* vehicle);
            void endRide();
            void operator << (Item* item) override;
            void operator << (Vehicle* vehicle) override;
            void doAction(Carrot* carrot) override;
            void setCoords(int x, int y) override;
    };

}

#endif
