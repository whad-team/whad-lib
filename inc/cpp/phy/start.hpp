#ifndef __INC_WHAD_PHY_START_HPP
#define __INC_WHAD_PHY_START_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class Start : public PhyMsg
    {
        public:
            Start(PhyMsg &message);
            Start();

        private:
            void pack();
    };

}

#endif /* __INC_WHAD_PHY_START_HPP */