#ifndef __INC_WHAD_BLE_HIJACK_MASTER_HPP
#define __INC_WHAD_BLE_HIJACK_MASTER_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class HijackMaster : public BleMsg
    {
        public:
            HijackMaster(uint32_t accessAddress);
    };

}

#endif /* __INC_WHAD_BLE_HIJACK_MASTER_HPP */