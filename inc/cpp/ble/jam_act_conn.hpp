#ifndef __INC_WHAD_BLE_JAM_ACT_CONN_HPP
#define __INC_WHAD_BLE_JAM_ACT_CONN_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>
#include <ble/hijack_base.hpp>

namespace whad::ble {

    class JamActiveConn : public BleMsg, public HijackBase
    {
        public:
            JamActiveConn(BleMsg &message);
            JamActiveConn(uint32_t accessAddress);

        private:
            void pack();
            void unpack();
    };

}

#endif /* __INC_WHAD_BLE_JAM_ACT_CONN_HPP */