#ifndef __INC_WHAD_BLE_ADV_HPP
#define __INC_WHAD_BLE_ADV_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class AdvMode : public BleMsg
    {
        public:
            AdvMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength);
    };

}

#endif /* __INC_WHAD_BLE_ADV_HPP */