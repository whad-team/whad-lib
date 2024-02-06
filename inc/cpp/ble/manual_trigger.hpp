#ifndef __INC_WHAD_BLE_MANUAL_TRIGGER_HPP
#define __INC_WHAD_BLE_MANUAL_TRIGGER_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ManualTrigger : public BleMsg
    {
        public:
            ManualTrigger(uint32_t id);
    };

}

#endif /* __INC_WHAD_BLE_MANUAL_TRIGGER_HPP */