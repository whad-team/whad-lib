#ifndef __INC_WHAD_PHY_JAM_HPP
#define __INC_WHAD_PHY_JAM_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    enum JammingMode {
        PhyContinuousJamming = PHY_JAM_MODE_CONTINUOUS,
        PhyReactiveJamming = PHY_JAM_MODE_REACTIVE
    };

    class JamMode : public PhyMsg
    {
        public:
            JamMode(PhyMsg &message);
            JamMode(JammingMode);

            JammingMode getMode();

        private:
            void pack();
            void unpack();

            JammingMode m_mode;
    };

    class Jammed : public PhyMsg
    {
        public:
            Jammed(PhyMsg &message);
            Jammed(Timestamp &timestamp);

            Timestamp getTimestamp();

        private:
            void pack();
            void unpack();

            Timestamp m_timestamp;
    };

}

#endif /* __INC_WHAD_PHY_JAM_HPP */