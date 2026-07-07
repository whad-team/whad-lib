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
            SendPdu(BleMsg &message);
            SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt, Phy phy);

            Direction getDirection();
            uint32_t getConnHandle();
            PDU& getPdu();
            bool isEncrypted();
            Phy getPhy();

        private:
            void pack();
            void unpack();

            Direction m_direction;
            uint32_t m_connHandle;
            PDU m_pdu;
            bool m_encrypt;
            Phy m_phy;
    };

}

#endif /* __INC_WHAD_BLE_SEND_PDU_HPP */
