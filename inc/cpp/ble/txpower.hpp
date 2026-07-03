#ifndef __INC_WHAD_BLE_TX_POWER_HPP
#define __INC_WHAD_BLE_TX_POWER_HPP

#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SetTxPowerLevel : public BleMsg
    {
        public:
            SetTxPowerLevel(BleMsg &message);
            SetTxPowerLevel(int32_t level);

            int32_t getLevel();

        private:
            void pack();
            void unpack();

            int32_t m_level;
    };

}

#endif /* __INC_WHAD_BLE_TX_POWER_HPP */
