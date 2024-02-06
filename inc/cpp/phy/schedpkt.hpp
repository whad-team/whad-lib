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
            SchedulePacket(NanoPbMsg &message);
            SchedulePacket(Packet &packet, Timestamp &timestamp);

            Packet getPacket();
            Timestamp getTimestamp();
    };

    class PacketScheduled : public PhyMsg
    {
        public:
            PacketScheduled(NanoPbMsg &message);
            PacketScheduled(uint8_t packetId, bool full);

            uint8_t getPacketId();
            bool isFull();

        private:
            bool parse();
            whad_phy_scheduled_packet_t m_packet;
    };

    class ScheduledPacketSent : public PhyMsg
    {
        public:
            ScheduledPacketSent(NanoPbMsg &message);
            ScheduledPacketSent(uint32_t packetId);

            uint32_t getPacketId();
    };

}

#endif /* __INC_WHAD_PHY_SCHEDPACKET_HPP */