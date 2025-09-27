#ifndef __INC_WHAD_BLE_ADV_HPP
#define __INC_WHAD_BLE_ADV_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class AdvMode : public BleMsg
    {
        public:
            AdvMode(BleMsg &message);
            AdvMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength);
            AdvMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength,
                    AdvType type, ChannelMap chanMap, uint16_t interMin, uint16_t interMax);

            unsigned int getAdvDataLength();
            unsigned int getScanRspLength();
            uint8_t *getAdvData();
            uint8_t *getScanRsp();
            AdvType getAdvType();
            ChannelMap &getChannelMap();
            uint16_t getIntervalMin();
            uint16_t getIntervalMax();

        private:
            void pack();
            void unpack();

            uint8_t m_advData[31];
            int m_advDataLength;
            uint8_t m_scanRsp[31];
            int m_scanRspLength;
            AdvType m_type;
            ChannelMap m_channelMap;
            uint16_t m_interMin;
            uint16_t m_interMax;
    };

}

#endif /* __INC_WHAD_BLE_ADV_HPP */
