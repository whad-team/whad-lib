#ifndef __INC_WHAD_PHY_SETMSKMOD_HPP
#define __INC_WHAD_PHY_SETMSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>
#include <phy/fskmod.hpp>

namespace whad::phy {

    class SetMskMod : public PhyMsg, public FskMod
    {
        public:
            SetMskMod(PhyMsg &message);
            SetMskMod(uint32_t deviation);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_PHY_SETMSKMOD_HPP */