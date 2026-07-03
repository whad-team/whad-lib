#ifndef __INC_WHAD_BLE_RAWPDU_HPP
#define __INC_WHAD_BLE_RAWPDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class RawPdu : public BleMsg
    {
        public:
            RawPdu(BleMsg &message);
            RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                    PDU pdu, uint32_t crc, bool crc_validity, uint32_t timestamp,
                    uint32_t relative_timestamp, Direction direction, bool processed,
                    bool decrypted, Phy phy);
            RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                    PDU pdu, uint32_t crc, bool crc_validity, Direction direction,
                    bool processed, bool decrypted, Phy phy);

            uint32_t getChannel();
            int32_t getRssi();
            uint32_t getConnHandle();
            uint32_t getAccessAddress();
            PDU& getPdu();
            uint32_t getCrc();
            bool isCrcValid();
            uint32_t getTimestamp();
            uint32_t getRelativeTimestamp();
            Direction getDirection();
            bool isProcessed();
            bool isDecrypted();
            bool hasTimestamp();
            Phy getPhy();

        private:
            void pack();

            uint32_t m_channel;
            int32_t m_rssi;
            uint32_t m_connHandle;
            uint32_t m_accessAddress;
            PDU m_pdu;
            uint32_t m_crc;
            bool m_crcValidity;
            uint32_t m_timestamp;
            uint32_t m_relative_timestamp;
            Direction m_direction;
            bool m_processed;
            bool m_decrypted;
            bool m_hasTimestamp;
            Phy m_phy;

    };

}

#endif /* __INC_WHAD_BLE_RAWPDU_HPP */
