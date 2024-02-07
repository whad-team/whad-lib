#ifndef __INC_WHAD_PHY_SCHEDPACKET_HPP
#define __INC_WHAD_PHY_SCHEDPACKET_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SchedulePacket : public PhyMsg
    {
        public:
            SchedulePacket(PhyMsg &message);
            SchedulePacket(Packet &packet, Timestamp &timestamp);

            Packet& getPacket();
            Timestamp& getTimestamp();

        private:
            void pack();
            void unpack();

            Packet m_packet;
            Timestamp m_timestamp;
    };

    class PacketScheduled : public PhyMsg
    {
        public:
            PacketScheduled(PhyMsg &message);
            PacketScheduled(uint8_t packetId, bool full);

            uint8_t getPacketId();
            bool isFull();

        private:
            void pack();
            void unpack();

            uint8_t m_pktId;
            bool m_full;
    };

    class ScheduledPacketSent : public PhyMsg
    {
        public:
            ScheduledPacketSent(PhyMsg &message);
            ScheduledPacketSent(uint32_t packetId);

            uint32_t getPacketId();

        private:
            void pack();
            void unpack();

            uint32_t m_pktId;
    };

}

#endif /* __INC_WHAD_PHY_SCHEDPACKET_HPP */