#ifndef __INC_WHAD_BLE_PERIPHERAL_HPP
#define __INC_WHAD_BLE_PERIPHERAL_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class PeripheralMode : public BleMsg
    {
        public:
            PeripheralMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength);
    };

}

#endif /* __INC_WHAD_BLE_PERIPHERAL_HPP */