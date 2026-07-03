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
            AdvMode(AdvType advType, uint32_t interMin, uint32_t interMax, uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength);

            unsigned int getAdvDataLength();
            unsigned int getScanRspLength();
            uint8_t *getAdvData();
            uint8_t *getScanRsp();
            AdvType getAdvType();
            uint32_t getIntervalMin();
            uint32_t getIntervalMax();
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
            int m_advDataLength;
            uint8_t m_scanRsp[31];
            int m_scanRspLength;

            AdvType m_type;
            uint32_t m_interMin;
            uint32_t m_interMax;
            Csa m_csa;
            ChannelMap m_channelMap;
        
            std::vector<ExtAdvPdu> m_pdus;
    };

}

#endif /* __INC_WHAD_BLE_ADV_HPP */
