#ifndef __INC_WHAD_PHY_TIMESTAMP_HPP
#define __INC_WHAD_PHY_TIMESTAMP_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"

namespace whad::phy {

    class Timestamp
    {
        public:
            Timestamp();
            Timestamp(uint32_t sec, uint32_t usec);

            void set(uint32_t sec, uint32_t usec);
            uint32_t getSeconds();
            void setSeconds(uint32_t seconds);
            uint32_t getMicroseconds();
            void setMicroseconds(uint32_t microseconds);

        private:
            uint32_t m_sec;
            uint32_t m_usec;
    };

}

#endif /* __INC_WHAD_PHY_TIMESTAMP_HPP */