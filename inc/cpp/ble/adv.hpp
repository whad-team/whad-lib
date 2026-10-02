#ifndef __INC_WHAD_BLE_ADV_HPP
#define __INC_WHAD_BLE_ADV_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>
#include <ble/channelmap.hpp>
#include <ble/adv_ext.hpp>

namespace whad::ble {

    class AdvMode : public BleMsg
    {
        public:
            AdvMode(BleMsg &message);
            AdvMode(uint8_t *pAdvData, size_t advDataLength, uint8_t *pScanRsp, size_t scanRspLength);
            AdvMode(AdvType advType, uint16_t interMin, uint16_t interMax, uint8_t *pAdvData, size_t advDataLength, 
                    uint8_t *pScanRsp, size_t scanRspLength, ChannelMap channelMap, Csa csa);
            AdvMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength,
        AdvType type, ChannelMap channelMap, uint16_t interMin, uint16_t interMax);

            unsigned int getAdvDataLength();
            unsigned int getScanRspLength();
            uint8_t *getAdvData();
            uint8_t *getScanRsp();
            AdvType getAdvType();
            uint16_t getIntervalMin();
            uint16_t getIntervalMax();
            Csa getCsa();
            ChannelMap& getChannelMap();

            /* Extended Advertising PDUs. */
            bool addExtPdu(ExtAdvPdu &pdu);
            size_t getNumberOfExtPdus();
            ExtAdvPdu* getExtPdu(unsigned int index);

        private:
            void pack();
            void unpack();

            uint8_t m_advData[31];
            size_t m_advDataLength;
            uint8_t m_scanRsp[31];
            size_t m_scanRspLength;

            AdvType m_type;
            uint16_t m_interMin;
            uint16_t m_interMax;
            Csa m_csa;
            ChannelMap m_channelMap;
        
            std::vector<ExtAdvPdu> m_pdus;
    };

}

#endif /* __INC_WHAD_BLE_ADV_HPP */
