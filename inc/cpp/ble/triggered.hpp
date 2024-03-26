#ifndef __INC_WHAD_BLE_TRIGGERED_HPP
#define __INC_WHAD_BLE_TRIGGERED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Triggered : public BleMsg
    {
        public:
            Triggered(BleMsg &message);
            Triggered(uint8_t id);

            /* Getters. */
            uint8_t getId();

        private:
            void pack();

            uint8_t m_id;
    };

}

#endif /* __INC_WHAD_BLE_TRIGGERED_HPP */