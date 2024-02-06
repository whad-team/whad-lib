#ifndef __INC_WHAD_BLE_SCAN_HPP
#define __INC_WHAD_BLE_SCAN_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ScanMode : public BleMsg
    {
        public:
            ScanMode(bool active);
    };

    class AdvPdu : public BleMsg
    {
        public:
            AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, int advDataLength);
    };

}

#endif /* __INC_WHAD_BLE_SCAN_HPP */