#ifndef __INC_WHAD_BLE_PERIPHERAL_HPP
#define __INC_WHAD_BLE_PERIPHERAL_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class PeripheralMode : public BleMsg
    {
        public:
            PeripheralMode(BleMsg &message);
            PeripheralMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength);
            PeripheralMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength,
                    AdvType type, ChannelMap channelMap, uint16_t interMin, uint16_t interMax);

            uint8_t *getAdvData();
            unsigned int getAdvDataLength();
            uint8_t *getScanRsp();
            unsigned int getScanRspLength();
            AdvType getAdvType();
            ChannelMap &getChannelMap();
            uint16_t getIntervalMin();
            uint16_t getIntervalMax();


        private:
            void pack();
            void unpack();

            uint8_t m_advData[31];
            unsigned int m_advDataLength;
            uint8_t m_scanRsp[31];
            unsigned int m_scanRspLength;
            AdvType m_type;
            ChannelMap m_channelMap;
            uint16_t m_interMin;
            uint16_t m_interMax;
    };

}

#endif /* __INC_WHAD_BLE_PERIPHERAL_HPP */
