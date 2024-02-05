#ifndef __INC_WHAD_ESB_PKTRECVD_HPP
#define __INC_WHAD_ESB_PKTRECVD_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "esb/base.hpp"

namespace whad::esb {
    class RawPacketReceived : public EsbMsg
    {
        public:
            RawPacketReceived(EsbMsg &message);
            RawPacketReceived(uint32_t channel, Packet &packet);

            /* Setters. */
            void setChannel(uint32_t channel);
            void setPacket(Packet& packet);
            void setRssi(int32_t rssi);
            void setTimestamp(uint32_t timestamp);
            void setAddress(EsbAddress &address);
            void setCrcValidity(bool validity);
            

            /* Getters. */
            uint32_t getChannel();
            bool hasRssi();
            int32_t getRssi();
            bool hasTimestamp();
            uint32_t getTimestamp();
            bool hasCrcValidity();
            bool isCrcValid();
            bool hasAddress();
            EsbAddress& getAddress();
            Packet& getPacket();


        protected:
            void parse();
            void update();

            uint32_t m_channel;
            
            int32_t m_rssi;
            bool m_hasRssi;
            uint32_t m_timestamp;
            bool m_hasTimestamp;
            bool m_crcValidity;
            bool m_hasCrcValidity;
            EsbAddress m_address;
            bool m_hasAddress;
            Packet m_packet;
    };

    class PacketReceived : public RawPacketReceived
    {
        public:
            /* Constructors. */
            PacketReceived(EsbMsg &message);
            PacketReceived(uint32_t channel, Packet &packet);

        private:
            void parse();
            void update();
    };
}

#endif /* __INC_WHAD_ESB_PKTRECVD_HPP */