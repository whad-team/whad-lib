#ifndef __INC_WHAD_PHY_SETTXPOWER_HPP
#define __INC_WHAD_PHY_SETTXPOWER_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    enum TxPower {
        PhyTxPowerLow = PHY_TXPOWER_LOW,
        PhyTxPowerMedium = PHY_TXPOWER_MEDIUM,
        PhyTxPowerHigh = PHY_TXPOWER_HIGH
    };

    class SetTxPower : public PhyMsg
    {
        public:
            SetTxPower(PhyMsg &message);
            SetTxPower(TxPower power);

            TxPower getPower();

        private:
            void pack();
            void unpack();

            TxPower m_power;
    };

}

#endif /* __INC_WHAD_PHY_SETTXPOWER_HPP */