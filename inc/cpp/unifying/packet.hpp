#ifndef __INC_WHAD_ZIGBEE_PACKET_HPP
#define __INC_WHAD_ZIGBEE_PACKET_HPP

#include "unifying/base.hpp"

namespace whad::unifying {
    class UnifyingPacket {
        public:

            UnifyingPacket();
            UnifyingPacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t crc);
            UnifyingPacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t crc,
                int32_t rssi);
            UnifyingPacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t crc,
                int32_t rssi, uint32_t timestamp);

            /* Setters. */
            void setChannel(uint32_t channel);
            void setPdu(PDU &pdu);
            void setCrc(uint32_t crc);
            void addRssi(int32_t rssi);
            void addTimestamp(uint32_t timestamp);
            void addCrcValidity(bool valid);
            void addLqi(uint32_t lqi);

            /* Getters. */
            uint32_t getChannel();
            PDU& getPdu();
            uint32_t getCrc();
            bool hasRssi();
            int32_t getRssi();
            bool hasCrcValidity();
            bool isCrcValid();
            bool hasTimestamp();
            uint32_t getTimestamp();

        private:

            uint32_t m_channel;
            PDU m_pdu;
            bool m_hasTimestamp;
            uint32_t m_timestamp;
            uint32_t m_crc;
            bool m_hasRssi;
            int32_t m_rssi;
            bool m_hasCrcValidity;
            bool m_crcValidity;
    };
}

#endif /* __INC_WHAD_ZIGBEE_PACKET_HPP */