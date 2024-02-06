#ifndef __INC_WHAD_BLE_SNIFF_CONNREQ_HPP
#define __INC_WHAD_BLE_SNIFF_CONNREQ_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SniffConnReq : public BleMsg
    {
        public:
            SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty);
    };

}

#endif /* __INC_WHAD_BLE_SNIFF_CONNREQ_HPP */