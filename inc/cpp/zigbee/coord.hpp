#ifndef __INC_WHAD_ZIGBEE_COORD_HPP
#define __INC_WHAD_ZIGBEE_COORD_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>

namespace whad::zigbee {

    class CoordMode : public ZigbeeMsg
    {
        public:
            CoordMode(ZigbeeMsg &message);
            CoordMode(uint32_t channel);

            /* Getters. */
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;               
    };

}

#endif /* __INC_WHAD_ZIGBEE_COORD_HPP */