#ifndef CUSTOM_EXC_INCLUDED_
#define CUSTOM_EXC_INCLUDED_

#include <string>
#include <exception>


namespace game {

    class incomplete_map_region : public std::exception {

        private:
            const std::string message;

        public:

            explicit incomplete_map_region(std::string msg);
            [[nodiscard]] const char* what() const noexcept override;
    };
}

#endif
