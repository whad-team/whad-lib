#ifndef __INC_WHAD_BLE_JAM_REACTIVE_HPP
#define __INC_WHAD_BLE_JAM_REACTIVE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ReactiveJam : public BleMsg
    {
        public:
            ReactiveJam(uint32_t channel, uint8_t *pPattern, int length, uint32_t position);
    };

}

#endif /* __INC_WHAD_BLE_JAM_REACTIVE_HPP */