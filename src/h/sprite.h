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

            [[maybe_unused]] std::string name;
            QPixmap* pixmap;
            uint16_t canvas_pos_x;
            uint16_t canvas_pos_y;
            int origin_x;
            int origin_y;

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


    class HintNote : public virtual SpriteEntity {

        private:

            std::string description;
            int number : 3;

        public:

            HintNote(
                    QWidget* parent,
                    // NOLINTNEXTLINE
                    const std::string name,
                    const std::string& img_src,
                    int origin_x,
                    int origin_y,
                    uint16_t canvas_pos_x,
                    uint16_t canvas_pos_y,
                    std::string description,
                    int n
            );

            HintNote(HintNote& note);

            [[nodiscard]] const std::string& getDescription() const;
            void doAction(Carrot* carrot) override;
            [[nodiscard]] int hintNumber() const;
    };

    class Character {

        protected:
            Character() = default;

        public:
            HintNote* current_note = nullptr;
            virtual void operator << (HintNote* item) = 0;
            virtual void operator << (Vehicle* vehicle) = 0;
    };

    class Carrot : public virtual SpriteEntity, public virtual Character {

        private:

            Vehicle* ride = nullptr;
            HintNote* note = nullptr;

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
            void operator << (HintNote* item) override;
            void operator << (Vehicle* vehicle) override;
            void doAction(Carrot* carrot) override;
            void setCoords(int x, int y) override;
    };

}

#endif
