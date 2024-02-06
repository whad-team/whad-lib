#ifndef __INC_WHAD_PHY_SETPACKETSIZE_HPP
#define __INC_WHAD_PHY_SETPACKETSIZE_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetPacketSize : public PhyMsg
    {
        public:
            SetPacketSize(NanoPbMsg &message);
            SetPacketSize(uint32_t size);

            uint32_t getSize();
    };

}

#endif /* __INC_WHAD_PHY_SETPACKETSIZE_HPP */