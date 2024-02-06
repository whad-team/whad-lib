#ifndef __INC_WHAD_PHY_SETDATARATE_HPP
#define __INC_WHAD_PHY_SETDATARATE_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetDatarate : public PhyMsg
    {
        public:
            SetDatarate(NanoPbMsg &message);
            SetDatarate(uint32_t datarate);

            uint32_t getDatarate();
    };

}

#endif /* __INC_WHAD_PHY_SETDATARATE_HPP */