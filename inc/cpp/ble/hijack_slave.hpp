#ifndef __INC_WHAD_BLE_HIJACK_SLAVE_HPP
#define __INC_WHAD_BLE_HIJACK_SLAVE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class HijackSlave : public BleMsg
    {
        public:
            HijackSlave(uint32_t accessAddress);
    };

}

#endif /* __INC_WHAD_BLE_HIJACK_SLAVE_HPP */