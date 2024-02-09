#ifndef __INC_WHAD_BLE_CENTRAL_HPP
#define __INC_WHAD_BLE_CENTRAL_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class CentralMode : public BleMsg
    {
        public:
            CentralMode(BleMsg &message);
            CentralMode(void);

        private:
            void pack();
    };

}

#endif /* __INC_WHAD_BLE_CENTRAL_HPP */