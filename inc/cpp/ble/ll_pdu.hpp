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
            LinkLayerPdu(BleMsg &message);
            LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted);

            uint32_t getConnHandle();
            PDU& getPdu();
            Direction getDirection();
            bool isProcessed();
            bool isDecrypted();

        private:
            void pack();
            void unpack();

            uint32_t m_connHandle;
            PDU m_pdu;
            Direction m_direction;
            bool m_processed;
            bool m_decrypted;
    };

}

#endif /* __INC_WHAD_BLE_LLPDU_HPP */