#ifndef __INC_WHAD_PHY_SET4FSKMOD_HPP
#define __INC_WHAD_PHY_SET4FSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class Set4FskMod : public PhyMsg
    {
        public:
            Set4FskMod(NanoPbMsg &message);
            Set4FskMod(uint32_t deviation);

            uint32_t getDeviation();
    };

}

#endif /* __INC_WHAD_PHY_SET4FSKMOD_HPP */