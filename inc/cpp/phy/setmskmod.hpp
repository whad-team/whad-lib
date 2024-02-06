#ifndef __INC_WHAD_PHY_SETMSKMOD_HPP
#define __INC_WHAD_PHY_SETMSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetMskMod : public PhyMsg
    {
        public:
            SetMskMod(NanoPbMsg &message);
            SetMskMod(uint32_t deviation);

            uint32_t getDeviation();
    };

}

#endif /* __INC_WHAD_PHY_SETMSKMOD_HPP */