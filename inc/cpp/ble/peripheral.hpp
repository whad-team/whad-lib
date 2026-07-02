#ifndef __INC_WHAD_BLE_PERIPHERAL_HPP
#define __INC_WHAD_BLE_PERIPHERAL_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>
#include <ble/adv_ext.hpp>

namespace whad::ble {

    class PeripheralMode : public BleMsg
    {
        public:
            PeripheralMode(BleMsg &message);
            PeripheralMode(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLength, Csa csa);

            uint8_t *getAdvData();
            unsigned int getAdvDataLength();
            uint8_t *getScanRsp();
            unsigned int getScanRspLength();
            Csa getCsa();

            bool addExtPdu(ExtAdvPdu &pdu);
            size_t getNumberOfExtPdus();
            std::vector<ExtAdvPdu>::iterator getExtPdusIterator();
            ExtAdvPdu* getExtPdu(unsigned int index);

        private:
            void pack();
            void unpack();

            uint8_t m_advData[31];
            unsigned int m_advDataLength;
            uint8_t m_scanRsp[31];
            unsigned int m_scanRspLength;
            Csa m_csa;
            std::vector<ExtAdvPdu> m_pdus;
    };

}

#endif /* __INC_WHAD_BLE_PERIPHERAL_HPP */
