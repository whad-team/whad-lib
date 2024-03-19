#ifndef __INC_WHAD_ZIGBEE_RAWPDU_HPP
#define __INC_WHAD_ZIGBEE_RAWPDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>
#include <zigbee/packet.hpp>

namespace whad::zigbee {

    class RawPduReceived : public ZigbeeMsg
    {
        public:
            RawPduReceived(ZigbeeMsg &message);
            RawPduReceived(ZigbeePacket &pdu);

            /* Getter. */
            ZigbeePacket& getPacket();

        private:
            void pack();
            void unpack();

            ZigbeePacket m_packet;               
    };
}

#endif /* __INC_WHAD_ZIGBEE_RAWPDU_HPP */