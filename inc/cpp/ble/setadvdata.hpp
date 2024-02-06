#ifndef __INC_WHAD_BLE_SETADVDATA_HPP
#define __INC_WHAD_BLE_SETADVDATA_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SetAdvData : public BleMsg
    {
        public:
            SetAdvData(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLengthv);
    };

}

#endif /* __INC_WHAD_BLE_SETADVDATA_HPP */