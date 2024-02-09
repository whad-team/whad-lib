#ifndef __INC_WHAD_BLE_HIJACK_SLAVE_HPP
#define __INC_WHAD_BLE_HIJACK_SLAVE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>
#include <ble/hijack_base.hpp>

namespace whad::ble {

    class HijackSlave : public BleMsg, public HijackBase
    {
        public:
            HijackSlave(BleMsg &message);
            HijackSlave(uint32_t accessAddress);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_BLE_HIJACK_SLAVE_HPP */