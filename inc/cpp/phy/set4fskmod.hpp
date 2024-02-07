#ifndef __INC_WHAD_PHY_SET4FSKMOD_HPP
#define __INC_WHAD_PHY_SET4FSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>
#include <phy/fskmod.hpp>

namespace whad::phy {

    class Set4FskMod : public PhyMsg, public FskMod
    {
        public:
            Set4FskMod(PhyMsg &message);
            Set4FskMod(uint32_t deviation);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_PHY_SET4FSKMOD_HPP */