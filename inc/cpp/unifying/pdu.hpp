#ifndef __INC_WHAD_UNIFYING_PDU_HPP
#define __INC_WHAD_UNIFYING_PDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>
#include <unifying/packet.hpp>

namespace whad::unifying {

    class PduReceived : public UnifyingMsg
    {
        public:
            PduReceived(UnifyingMsg &message);
            PduReceived(UnifyingPacket &packet);

            /* Setter. */
            void addAddress(UnifyingAddress& address);

            /* Getters. */
            UnifyingPacket& getPacket();
            bool hasAddress();
            UnifyingAddress& getAddress();

        private:
            void pack();
            void unpack();

            UnifyingPacket m_packet;
            bool m_hasAddress;
            UnifyingAddress m_address;
    };

}

#endif /* __INC_WHAD_UNIFYING_PDU_HPP */