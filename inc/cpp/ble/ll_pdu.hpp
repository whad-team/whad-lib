#ifndef __INC_WHAD_BLE_LLPDU_HPP
#define __INC_WHAD_BLE_LLPDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class LinkLayerPdu : public BleMsg
    {
        public:
            LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted);
    };

}

#endif /* __INC_WHAD_BLE_LLPDU_HPP */