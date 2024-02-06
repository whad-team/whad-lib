#ifndef __INC_WHAD_PHY_SETFSKMOD_HPP
#define __INC_WHAD_PHY_SETFSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetFskMod : public PhyMsg
    {
        public:
            SetFskMod(NanoPbMsg &message);
            SetFskMod(uint32_t deviation);

            uint32_t getDeviation();
    };

}

#endif /* __INC_WHAD_PHY_SETFSKMOD_HPP */