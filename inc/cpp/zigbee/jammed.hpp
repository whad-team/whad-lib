#ifndef __INC_WHAD_ZIGBEE_JAMMED_HPP
#define __INC_WHAD_ZIGBEE_JAMMED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>

namespace whad::zigbee {

    class Jammed : public ZigbeeMsg
    {
        public:
            Jammed(ZigbeeMsg &message);
            Jammed(uint32_t timestamp);

            /* Getters. */
            uint32_t getTimestamp();

        private:
            void pack();
            void unpack();

            uint32_t m_timestamp;               
    };
}

#endif /* __INC_WHAD_ZIGBEE_JAMMED_HPP */