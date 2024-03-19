#ifndef __INC_WHAD_UNIFYING_RAWPDU_HPP
#define __INC_WHAD_UNIFYING_RAWPDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>
#include <unifying/packet.hpp>

namespace whad::unifying {

    class RawPduReceived : public UnifyingMsg
    {
        public:
            RawPduReceived(UnifyingMsg &message);
            RawPduReceived(UnifyingPacket &packet);

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

#endif /* __INC_WHAD_UNIFYING_RAWPDU_HPP */