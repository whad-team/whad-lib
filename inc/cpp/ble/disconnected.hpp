#ifndef __INC_WHAD_BLE_DISCONNECTED_HPP
#define __INC_WHAD_BLE_DISCONNECTED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Disconnected : public BleMsg
    {
        public:
            Disconnected(uint32_t conn_handle, uint32_t reason);
    };

}

#endif /* __INC_WHAD_BLE_DISCONNECTED_HPP */