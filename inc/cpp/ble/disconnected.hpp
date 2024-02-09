#ifndef __INC_WHAD_BLE_DISCONNECTED_HPP
#define __INC_WHAD_BLE_DISCONNECTED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Disconnected : public BleMsg
    {
        public:
            Disconnected(BleMsg &message);
            Disconnected(uint32_t conn_handle, uint32_t reason);

            uint32_t getConnHandle();
            uint32_t getReasonCode();

        private:
            void pack();
            void unpack();

            uint32_t m_connHandle;
            uint32_t m_reasonCode;
    };

}

#endif /* __INC_WHAD_BLE_DISCONNECTED_HPP */