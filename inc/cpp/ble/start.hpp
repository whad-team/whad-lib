#ifndef __INC_WHAD_BLE_START_HPP
#define __INC_WHAD_BLE_START_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Start : public BleMsg
    {
        public:
            Start(BleMsg &message);
            Start(void);

        private:
            void pack();
    };

}

#endif /* __INC_WHAD_BLE_START_HPP */