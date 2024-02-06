#ifndef __INC_WHAD_PHY_SETGFSKMOD_HPP
#define __INC_WHAD_PHY_SETGFSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetGfskMod : public PhyMsg
    {
        public:
            SetGfskMod(NanoPbMsg &message);
            SetGfskMod(uint32_t deviation);

            uint32_t getDeviation();
    };

}

#endif /* __INC_WHAD_PHY_SETGFSKMOD_HPP */