#ifndef __INC_WHAD_PHY_FSKMOD_HPP
#define __INC_WHAD_PHY_FSKMOD_HPP

#include <stdint.h>

namespace whad::phy {

    class FskMod
    {
        public:
            FskMod();
            FskMod(uint32_t deviation);

            uint32_t getDeviation();

        protected:
            uint32_t m_deviation;
    };

}

#endif /* __INC_WHAD_PHY_FSKMOD_HPP */