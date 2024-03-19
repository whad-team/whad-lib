#ifndef __INC_WHAD_ZIGBEE_ENERGYSAMPLE_HPP
#define __INC_WHAD_ZIGBEE_ENERGYSAMPLE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>

namespace whad::zigbee {

    class EnergySample : public ZigbeeMsg
    {
        public:
            EnergySample(ZigbeeMsg &message);
            EnergySample(uint32_t timestamp, uint32_t value);

            /* Getters. */
            uint32_t getTimestamp();
            uint32_t getValue();

        private:
            void pack();
            void unpack();

            uint32_t m_timestamp;
            uint32_t m_value;               
    };

}

#endif /* __INC_WHAD_ZIGBEE_ENERGYSAMPLE_HPP */