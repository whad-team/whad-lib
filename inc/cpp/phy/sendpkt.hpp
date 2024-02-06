#ifndef __INC_WHAD_PHY_SENDPACKET_HPP
#define __INC_WHAD_PHY_SENDPACKET_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SendPacket : public PhyMsg
    {
        public:
            SendPacket(NanoPbMsg &message);
            SendPacket(Packet &packet);

            Packet getPacket();
        
        private:
            whad_phy_packet_t m_packet;
    };

}

#endif /* __INC_WHAD_PHY_SENDPACKET_HPP */