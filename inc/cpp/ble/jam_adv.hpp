#ifndef __INC_WHAD_BLE_JAMADV_HPP
#define __INC_WHAD_BLE_JAMADV_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class JamAdv : public BleMsg
    {
        public:
            JamAdv(void);
            JamAdv(uint32_t channel);
    };

}

#endif /* __INC_WHAD_BLE_JAMADV_HPP */