#ifndef __INC_WHAD_BLE_CONN_EVT_TRIGGER_HPP
#define __INC_WHAD_BLE_CONN_EVT_TRIGGER_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ConnEventTrigger
    {
        private:
            uint32_t m_connEvent;

        public:
            ConnEventTrigger(uint32_t connEvent);
            uint32_t getConnEvent(void);
    };

}

#endif /* __INC_WHAD_BLE_CONN_EVT_TRIGGER_HPP */