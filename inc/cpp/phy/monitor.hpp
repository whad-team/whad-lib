#ifndef __INC_WHAD_PHY_MONITOR_HPP
#define __INC_WHAD_PHY_MONITOR_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class MonitorMode : public PhyMsg
    {
        public:
            MonitorMode(NanoPbMsg &message);
            MonitorMode();
    };

}

#endif /* __INC_WHAD_PHY_MONITOR_HPP */