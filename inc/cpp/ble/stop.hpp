#ifndef __INC_WHAD_BLE_STOP_HPP
#define __INC_WHAD_BLE_STOP_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Stop : public BleMsg
    {
        public:
            Stop(void);
    };

}

#endif /* __INC_WHAD_BLE_STOP_HPP */