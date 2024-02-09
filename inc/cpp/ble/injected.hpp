#ifndef __INC_WHAD_BLE_INJECTED_HPP
#define __INC_WHAD_BLE_INJECTED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Injected : public BleMsg
    {
        public:
            Injected(BleMsg &message);
            Injected(uint32_t accessAddress, uint32_t attempts, bool success);

            uint32_t getAccessAddress();
            uint32_t getAttempts();
            bool isSuccessful();

        private:
            void pack();
            void unpack();

            uint32_t m_accessAddr;
            uint32_t m_attempts;
            bool m_success;
    };

}

#endif /* __INC_WHAD_BLE_INJECTED_HPP */