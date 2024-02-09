#ifndef __INC_WHAD_BLE_HIJACK_BASE_HPP
#define __INC_WHAD_BLE_HIJACK_BASE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class HijackBase
    {
        public:
            HijackBase();
            HijackBase(uint32_t accessAddress);

            uint32_t    getAccessAddress();

        protected:
            uint32_t m_accessAddr;
    };

}

#endif /* __INC_WHAD_BLE_HIJACK_BASE_HPP */