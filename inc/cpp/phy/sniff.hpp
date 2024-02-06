#ifndef __INC_WHAD_PHY_SNIFF_HPP
#define __INC_WHAD_PHY_SNIFF_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SniffMode : public PhyMsg
    {
        public:

            SniffMode(NanoPbMsg &message);
            SniffMode(bool iqMode);

            bool isIqModeEnabled();
    };

}

#endif /* __INC_WHAD_PHY_SNIFF_HPP */