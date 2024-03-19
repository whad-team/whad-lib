#ifndef __INC_WHAD_ZIGBEE_PDU_HPP
#define __INC_WHAD_ZIGBEE_PDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>
#include <zigbee/packet.hpp>

namespace whad::zigbee {

    class PduReceived : public ZigbeeMsg
    {
        public:
            PduReceived(ZigbeeMsg &message);
            PduReceived(ZigbeePacket &pdu);

            /* Getter. */
            ZigbeePacket& getPacket();

        private:
            void pack();
            void unpack();

            ZigbeePacket m_packet;               
    };
}

#endif /* __INC_WHAD_ZIGBEE_PDU_HPP */