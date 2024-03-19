#ifndef __INC_WHAD_ZIGBEE_SEND_HPP
#define __INC_WHAD_ZIGBEE_SEND_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <zigbee/base.hpp>

namespace whad::zigbee {

    class SendPdu : public ZigbeeMsg
    {
        public:
            SendPdu(ZigbeeMsg &message);
            SendPdu(uint32_t channel, uint8_t *pPdu, int length);

            /* Getters. */
            uint32_t getChannel();
            PDU& getPdu();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            PDU m_pdu;               
    };

}

#endif /* __INC_WHAD_ZIGBEE_SEND_HPP */