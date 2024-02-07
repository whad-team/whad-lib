#ifndef __INC_WHAD_PHY_SETFREQ_HPP
#define __INC_WHAD_PHY_SETFREQ_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class SetFreq : public PhyMsg
    {
        public:
            SetFreq(NanoPbMsg &message);
            SetFreq(uint32_t frequency);

            uint32_t getFrequency();

        private:
            void pack();
            void unpack();
            
            uint32_t m_freq;
    };

}

#endif /* __INC_WHAD_PHY_SETFREQ_HPP */