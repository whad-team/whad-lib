#ifndef __INC_WHAD_PHY_SETBPSKMOD_HPP
#define __INC_WHAD_PHY_SETBPSKMOD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetBpskMod : public PhyMsg
    {
        public:
            SetBpskMod(PhyMsg &message);
            SetBpskMod();

        private:
            void pack();
    };

}

#endif /* __INC_WHAD_PHY_SETBPSKMOD_HPP */