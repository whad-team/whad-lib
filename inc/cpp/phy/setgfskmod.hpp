#ifndef __INC_WHAD_PHY_SETGFSKMOD_HPP
#define __INC_WHAD_PHY_SETGFSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>
#include <phy/fskmod.hpp>

namespace whad::phy {

    class SetGfskMod : public PhyMsg, public FskMod
    {
        public:
            SetGfskMod(PhyMsg &message);
            SetGfskMod(uint32_t deviation);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_PHY_SETGFSKMOD_HPP */