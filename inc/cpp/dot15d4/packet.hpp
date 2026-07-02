#ifndef __INC_WHAD_DOT15D4_PACKET_HPP
#define __INC_WHAD_DOT15D4_PACKET_HPP

#include "dot15d4/base.hpp"

namespace whad::dot15d4 {
    class Dot15d4Packet {
        public:

            Dot15d4Packet();
            Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs);
            Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi);
            Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi, uint32_t timestamp);

            Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi, uint32_t timestamp, uint64_t asn, uint32_t start_of_slot_timestamp, 
                uint64_t time_slot);
            
            Dot15d4Packet(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs,
                int32_t rssi, uint32_t timestamp, uint64_t asn, uint32_t start_of_slot_timestamp, 
                uint64_t time_slot, uint32_t base_channel_frequency, uint32_t number_of_channels, 
                uint32_t channel_spacing);

            /* Setters. */
            void setChannel(uint32_t channel);
            void setPdu(PDU &pdu);
            void setFcs(uint32_t fcs);
            void addRssi(int32_t rssi);
            void addTimestamp(uint32_t timestamp);
            void addFcsValidity(bool valid);
            void addLqi(uint32_t lqi);
            void addAsn(uint64_t asn);
            void addStartOfSlotTimestamp(uint32_t start_of_slot_timestamp);
            void addTimeSlot(uint64_t time_slot);
            void addBaseChannelFrequency(uint32_t base_channel_frequency);
            void addNumberOfChannels(uint32_t number_of_channels);
            void addChannelSpacing(uint32_t channel_spacing);


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

            uint64_t getAsn();
            uint32_t getStartOfSlotTimestamp();
            uint64_t getTimeSlot();
            uint32_t getBaseChannelFrequency();
            uint32_t getNumberOfChannels();
            uint32_t getChannelSpacing();


            bool hasAsn();
            bool hasStartOfSlotTimestamp();
            bool hasTimeSlot();
            bool hasBaseChannelFrequency();
            bool hasNumberOfChannels();
            bool hasChannelSpacing();
            

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


            bool m_hasAsn;
            bool m_hasStartOfSlotTimestamp;
            bool m_hasTimeSlot;
            bool m_hasBaseChannelFrequency;
            bool m_hasNumberOfChannels;
            bool m_hasChannelSpacing;


            uint64_t m_asn;
            uint32_t m_startOfSlotTimestamp;
            uint64_t m_timeSlot;
            uint32_t m_baseChannelFrequency;
            uint32_t m_numberOfChannels;
            uint32_t m_channelSpacing;
    };
}

#endif /* __INC_WHAD_DOT15D4_PACKET_HPP */