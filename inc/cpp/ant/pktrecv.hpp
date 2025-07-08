#ifndef __INC_WHAD_ANT_PKTRECVD_HPP
#define __INC_WHAD_ANT_PKTRECVD_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "ant/base.hpp"

namespace whad::ant {
    class RawPacketReceived : public AntMsg
    {
        public:
            RawPacketReceived(AntMsg &message);
            RawPacketReceived(uint32_t rf_channel, uint32_t channel_number, Packet &packet);

            /* Setters. */
            void setRFChannel(uint32_t rf_channel);
            void setChannelNumber(uint32_t channelNumber);
            void setPacket(Packet& packet);
            void setRssi(int32_t rssi);
            void setTimestamp(uint32_t timestamp);
            void setCrcValidity(bool validity);
            

            /* Getters. */
            uint32_t getRFChannel();
            uint32_t getChannelNumber();
            bool hasRssi();
            int32_t getRssi();
            bool hasTimestamp();
            uint32_t getTimestamp();
            bool hasCrcValidity();
            bool isCrcValid();
            Packet& getPacket();


        protected:
            void unpack();
            void pack();

            uint32_t m_channel;
            
            int32_t m_rssi;
            bool m_hasRssi;
            uint32_t m_timestamp;
            bool m_hasTimestamp;
            bool m_crcValidity;
            bool m_hasCrcValidity;
            Packet m_packet;
    };

    class PacketReceived : public RawPacketReceived
    {
        public:
            /* Constructors. */
            PacketReceived(AntMsg &message);
            PacketReceived(uint32_t rf_channel, uint32_t channel_number, Packet &packet);

        private:
            void pack();
            void unpack();
    };
}

#endif /* __INC_WHAD_ANT_PKTRECVD_HPP */