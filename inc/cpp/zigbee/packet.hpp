#ifndef __INC_WHAD_ZIGBEE_PACKET_HPP
#define __INC_WHAD_ZIGBEE_PACKET_HPP

#include "zigbee/base.hpp"

namespace whad::zigbee {
    class ZigbeePacket {
        public:

            ZigbeePacket();
            ZigbeePacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs);
            ZigbeePacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi);
            ZigbeePacket(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi, uint32_t timestamp);

            /* Setters. */
            void setChannel(uint32_t channel);
            void setPdu(PDU &pdu);
            void setFcs(uint32_t fcs);
            void addRssi(int32_t rssi);
            void addTimestamp(uint32_t timestamp);
            void addFcsValidity(bool valid);
            void addLqi(uint32_t lqi);

            /* Getters. */
            uint32_t getChannel();
            PDU& getPdu();
            uint32_t getFcs();
            bool hasRssi();
            int32_t getRssi();
            bool hasFcsValidity();
            bool isFcsValid();
            bool hasLqi();
            uint32_t getLqi();
            bool hasTimestamp();
            uint32_t getTimestamp();

        private:

            uint32_t m_channel;
            PDU m_pdu;
            bool m_hasTimestamp;
            uint32_t m_timestamp;
            uint32_t m_fcs;
            bool m_hasRssi;
            int32_t m_rssi;
            bool m_hasFcsValidity;
            bool m_fcsValidity;
            bool m_hasLqi;
            uint32_t m_lqi;
    };
}

#endif /* __INC_WHAD_ZIGBEE_PACKET_HPP */