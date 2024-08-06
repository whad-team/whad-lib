#ifndef __INC_WHAD_PHY_PACKETRX_HPP
#define __INC_WHAD_PHY_PACKETRX_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/base.hpp>

namespace whad::phy {

    class PacketReceived : public PhyMsg
    {
        public:
            PacketReceived(NanoPbMsg &message);
            PacketReceived(uint32_t frequency, int32_t rssi, Timestamp &ts, Packet &packet, SyncWord &syncword, Endianness endian, uint32_t datarate, uint32_t deviation, ModulationType modulation);

            uint32_t getFrequency();
            int32_t getRssi();
            Timestamp& getTimestamp();
            Packet& getPacket();
            SyncWord& getSyncWord();
            Endianness getEndianness();
            uint32_t getDatarate();
            uint32_t getDeviation();
            ModulationType getModulation();

        private:
            void pack();
            void unpack();

            uint32_t m_frequency;
            int32_t m_rssi;
            Timestamp m_timestamp;
            Packet m_packet;
            SyncWord m_syncword;
            Endianness m_endian;
            uint32_t m_datarate;
            uint32_t m_deviation;
            ModulationType m_modulation;
    };

}

#endif /* __INC_WHAD_PHY_PACKETRX_HPP */
