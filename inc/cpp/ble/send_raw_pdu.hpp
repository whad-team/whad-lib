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
            SendRawPdu(BleMsg &message);
            SendRawPdu(Direction direction, uint32_t connHandle, uint32_t accessAddress, uint8_t *pPdu, int length, uint32_t crc, bool encrypt);

            Direction getDirection();
            uint32_t getConnHandle();
            uint32_t getAccessAddress();
            PDU& getPdu();
            uint32_t getCrc();
            bool isEncrypted();

        private:
            void pack();
            void unpack();

            Direction m_direction;
            uint32_t m_connHandle;
            uint32_t m_accessAddr;
            PDU m_pdu;
            uint32_t m_crc;
            bool m_encrypt;
    };

}

#endif /* __INC_WHAD_BLE_SEND_RAW_PDU_HPP */