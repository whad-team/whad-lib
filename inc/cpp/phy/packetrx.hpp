#ifndef __INC_WHAD_PHY_PACKETRX_HPP
#define __INC_WHAD_PHY_PACKETRX_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class PacketReceived : public PhyMsg
    {
        public:
            PacketReceived(NanoPbMsg &message);
            PacketReceived(uint32_t frequency, int32_t rssi, Timestamp &ts, Packet &packet);

            uint32_t getFrequency();
            int32_t getRssi();
            Timestamp getTimestamp();
            Packet getPacket();

        private:
            bool parse();
            whad_phy_received_packet_t m_packet;
    };

}

#endif /* __INC_WHAD_PHY_PACKETRX_HPP */