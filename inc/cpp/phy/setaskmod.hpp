#ifndef __INC_WHAD_PHY_SETASKMOD_HPP
#define __INC_WHAD_PHY_SETASKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetAskMod : public PhyMsg
    {
        public:
            SetAskMod(NanoPbMsg &message);
            SetAskMod(bool ook);

            bool isOok();
    };

}

#endif /* __INC_WHAD_PHY_SETASKMOD_HPP */