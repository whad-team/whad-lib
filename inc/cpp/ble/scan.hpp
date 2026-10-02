#ifndef __INC_WHAD_BLE_SCAN_HPP
#define __INC_WHAD_BLE_SCAN_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

#define SCAN_INTERVAL_DEFAULT   200

namespace whad::ble {

    class ScanMode : public BleMsg
    {
        public:
            ScanMode(BleMsg &message);
            ScanMode(bool active);
            ScanMode(bool active, uint32_t interval);
            ScanMode(bool active, uint32_t interval, bool use_ext_adv);

            bool isActiveModeEnabled();
            uint32_t getInterval();
            bool useExtAdv();


        private:
            void pack();
            void unpack();

            bool m_active;
            uint32_t m_interval;
            bool m_useExtAdv;
    };

    class AdvPdu : public BleMsg
    {
        public:
            AdvPdu(BleMsg &message);
            AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, unsigned int advDataLength, uint32_t channel, Phy phy);

            AdvType getAdvType();
            int32_t getRssi();
            BDAddress& getAddress();
            uint8_t *getAdvData();
            unsigned int getAdvDataLength();
            uint32_t getChannel();
            Phy getPhy();

        private:
            void pack();
            void unpack();

            AdvType m_advType;
            int32_t m_rssi;
            BDAddress m_address;
            uint8_t *m_advData;
            unsigned int m_advDataLength;
            uint32_t m_channel;
            Phy m_phy;
    };

}

#endif /* __INC_WHAD_BLE_SCAN_HPP */
