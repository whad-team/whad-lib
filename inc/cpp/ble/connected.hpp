#ifndef __INC_WHAD_BLE_CONNECTED_HPP
#define __INC_WHAD_BLE_CONNECTED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Connected : public BleMsg
    {
        public:
            Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr);
    };

}

#endif /* __INC_WHAD_BLE_CONNECTED_HPP */