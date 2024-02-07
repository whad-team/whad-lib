#ifndef __INC_WHAD_PHY_STOP_HPP
#define __INC_WHAD_PHY_STOP_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class Stop : public PhyMsg
    {
        public:
            Stop(PhyMsg &message);
            Stop();

        private:
            void pack();
    };

}

#endif /* __INC_WHAD_PHY_STOP_HPP */