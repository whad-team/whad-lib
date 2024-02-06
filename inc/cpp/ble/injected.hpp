#ifndef __INC_WHAD_BLE_INJECTED_HPP
#define __INC_WHAD_BLE_INJECTED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Injected : public BleMsg
    {
        public:
            Injected(uint32_t accessAddress, uint32_t attempts, bool success);
    };

}

#endif /* __INC_WHAD_BLE_INJECTED_HPP */