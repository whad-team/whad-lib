#ifndef __INC_WHAD_BLE_HIJACKED_HPP
#define __INC_WHAD_BLE_HIJACKED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Hijacked : public BleMsg
    {
        public:
            Hijacked(uint32_t accessAddress, bool success);
    };

}

#endif /* __INC_WHAD_BLE_HIJACKED_HPP */