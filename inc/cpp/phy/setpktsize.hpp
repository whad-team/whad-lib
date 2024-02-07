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
            SetPacketSize(PhyMsg &message);
            SetPacketSize(uint32_t size);

            uint32_t getSize();

        private:
            void pack();
            void unpack();

            uint32_t m_size;
    };

}

#endif /* __INC_WHAD_PHY_SETPACKETSIZE_HPP */