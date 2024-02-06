#ifndef __INC_WHAD_ESB_SENDPKT_HPP
#define __INC_WHAD_ESB_SENDPKT_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class SendPacket : public EsbMsg
    {
        protected:
            bool parse();

            uint32_t m_channel;
            uint32_t m_retries;
            Packet m_packet;

        public:
            SendPacket(EsbMsg &message);
            SendPacket(uint32_t channel, uint32_t retries, Packet &packet);

            /* Getters. */
            uint32_t getChannel();
            uint32_t getRetrCount();
            Packet &getPacket();
    };

    class SendPacketRaw : public SendPacket
    {
        public:
            SendPacketRaw(EsbMsg &message);
            SendPacketRaw(uint32_t channel, uint32_t retries, Packet &packet);

        private:
            bool parse();
    };
}

#endif /* __INC_WHAD_ESB_SENDPKT_HPP */