#ifndef __INC_WHAD_BLE_SEND_RAW_PDU_HPP
#define __INC_WHAD_BLE_SEND_RAW_PDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SendRawPdu : public BleMsg
    {
        public:
            SendRawPdu(Direction direction, uint32_t connHandle, uint32_t accessAddress, uint8_t *pPdu, int length, uint32_t crc, bool encrypt);
    };

}

#endif /* __INC_WHAD_BLE_SEND_RAW_PDU_HPP */