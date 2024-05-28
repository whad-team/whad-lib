#ifndef __INC_WHAD_DOT15D4_PDU_HPP
#define __INC_WHAD_DOT15D4_PDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>
#include <dot15d4/packet.hpp>

namespace whad::dot15d4 {

    class PduReceived : public Dot15d4Msg
    {
        public:
            PduReceived(Dot15d4Msg &message);
            PduReceived(Dot15d4Packet &pdu);

            /* Getter. */
            Dot15d4Packet& getPacket();

        private:
            void pack();
            void unpack();

            Dot15d4Packet m_packet;               
    };
}

#endif /* __INC_WHAD_DOT15D4_PDU_HPP */