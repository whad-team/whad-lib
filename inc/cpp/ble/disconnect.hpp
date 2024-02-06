#ifndef __INC_WHAD_BLE_DISCONNECT_TO_HPP
#define __INC_WHAD_BLE_DISCONNECT_TO_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Disconnect : public BleMsg
    {
        public:
            Disconnect(uint32_t connHandle);
    };

}

#endif /* __INC_WHAD_BLE_DISCONNECT_TO_HPP */