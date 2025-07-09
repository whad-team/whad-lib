#ifndef __INC_WHAD_ANT_SENDPKT_HPP
#define __INC_WHAD_ANT_SENDPKT_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {
    
    class SendPacket : public AntMsg
    {
        protected:
            void pack();
            void unpack();

            uint32_t m_rf_channel;
            uint32_t m_channel_number;
            Packet m_packet;

        public:
            SendPacket(AntMsg &message);
            SendPacket(uint32_t rf_channel, uint32_t channel_number, Packet &packet);

            /* Getters. */
            uint32_t getRFChannel();
            uint32_t getChannelNumber();
            Packet &getPacket();
    };

    class SendPacketRaw : public AntMsg
    {
        protected:
            void pack();
            void unpack();

            uint32_t m_rf_channel;
            uint32_t m_channel_number;
            Packet m_packet;

        public:
            SendPacketRaw(AntMsg &message);
            SendPacketRaw(uint32_t rf_channel, uint32_t channel_number, Packet &packet);

            /* Getters. */
            uint32_t getRFChannel();
            uint32_t getChannelNumber();
            Packet &getPacket();
    };
}

#endif /* __INC_WHAD_ANT_SENDPKT_HPP */