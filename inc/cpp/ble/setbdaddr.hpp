#ifndef __INC_WHAD_BLE_SETBDADDR_HPP
#define __INC_WHAD_BLE_SETBDADDR_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SetBdAddress : public BleMsg
    {
        public:
            SetBdAddress(NanoPbMsg message);
            SetBdAddress(BDAddress address);

            BDAddress *getAddress();
    };

}

#endif /* __INC_WHAD_BLE_SETBDADDR_HPP */