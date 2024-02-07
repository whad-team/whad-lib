#ifndef __INC_WHAD_PHY_SETFSKMOD_HPP
#define __INC_WHAD_PHY_SETFSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>
#include <phy/fskmod.hpp>

namespace whad::phy {

    class SetFskMod : public PhyMsg, public FskMod
    {
        public:
            SetFskMod(PhyMsg &message);
            SetFskMod(uint32_t deviation);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_PHY_SETFSKMOD_HPP */