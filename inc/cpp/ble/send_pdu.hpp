#ifndef __INC_WHAD_BLE_SEND_PDU_HPP
#define __INC_WHAD_BLE_SEND_PDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SendPdu : public BleMsg
    {
        public:
            SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt);
    };

}

#endif /* __INC_WHAD_BLE_SEND_PDU_HPP */