#ifndef __INC_WHAD_PHY_SETQPSKMOD_HPP
#define __INC_WHAD_PHY_SETQPSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetQpskMod : public PhyMsg
    {
        public:
            SetQpskMod(NanoPbMsg &message);
            SetQpskMod(bool offset);

            bool getOffset();
    };

}

#endif /* __INC_WHAD_PHY_SETQPSKMOD_HPP */