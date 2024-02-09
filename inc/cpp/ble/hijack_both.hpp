#ifndef __INC_WHAD_BLE_HIJACK_BOTH_HPP
#define __INC_WHAD_BLE_HIJACK_BOTH_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>
#include <ble/hijack_base.hpp>

namespace whad::ble {

    class HijackBoth : public BleMsg, public HijackBase
    {
        public:
            HijackBoth(BleMsg &message);
            HijackBoth(uint32_t accessAddress);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_BLE_HIJACK_BOTH_HPP */