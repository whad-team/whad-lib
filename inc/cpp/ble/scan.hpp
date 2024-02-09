#ifndef __INC_WHAD_BLE_SCAN_HPP
#define __INC_WHAD_BLE_SCAN_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ScanMode : public BleMsg
    {
        public:
            ScanMode(BleMsg &message);
            ScanMode(bool active);

            bool isActiveModeEnabled();

        private:
            void pack();
            void unpack();

            bool m_active;
    };

    class AdvPdu : public BleMsg
    {
        public:
            AdvPdu(BleMsg &message);
            AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, unsigned int advDataLength);

            AdvType getAdvType();
            int32_t getRssi();
            BDAddress& getAddress();
            uint8_t *getAdvData();
            unsigned int getAdvDataLength();

        private:
            void pack();
            void unpack();

            AdvType m_advType;
            int32_t m_rssi;
            BDAddress m_address;
            uint8_t *m_advData;
            unsigned int m_advDataLength;
    };

}

#endif /* __INC_WHAD_BLE_SCAN_HPP */