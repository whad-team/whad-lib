#ifndef __INC_WHAD_BLE_SETADVDATA_HPP
#define __INC_WHAD_BLE_SETADVDATA_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SetAdvData : public BleMsg
    {
        public:
            SetAdvData(BleMsg &message);
            SetAdvData(uint8_t *pAdvData, unsigned int advDataLength, uint8_t *pScanRsp, unsigned int scanRspLengthv);

            uint8_t *getAdvData();
            unsigned int getAdvDataLength();
            uint8_t *getScanRsp();
            unsigned int getScanRspLength();

        private:
            void pack();
            void unpack();

            uint8_t *m_advData;
            unsigned int m_advDataLength;
            uint8_t *m_scanRsp;
            unsigned int m_scanRspLength;
    };

}

#endif /* __INC_WHAD_BLE_SETADVDATA_HPP */