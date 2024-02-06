#ifndef __INC_WHAD_BLE_HIJACK_BOTH_HPP
#define __INC_WHAD_BLE_HIJACK_BOTH_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class HijackBoth : public BleMsg
    {
        public:
            HijackBoth(uint32_t accessAddress);
    };

}

#endif /* __INC_WHAD_BLE_HIJACK_BOTH_HPP */