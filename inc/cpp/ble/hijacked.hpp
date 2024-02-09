#ifndef __INC_WHAD_BLE_HIJACKED_HPP
#define __INC_WHAD_BLE_HIJACKED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>
#include <ble/hijack_base.hpp>

namespace whad::ble {

    class Hijacked : public BleMsg, public HijackBase
    {
        public:
            Hijacked(BleMsg &message);
            Hijacked(uint32_t accessAddress, bool success);

            bool isSuccessful();

        private:
            void pack();
            void unpack();

            bool m_success;
    };

}

#endif /* __INC_WHAD_BLE_HIJACKED_HPP */