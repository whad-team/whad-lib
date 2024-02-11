#ifndef __INC_WHAD_BLE_SNIFF_AA_HPP
#define __INC_WHAD_BLE_SNIFF_AA_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SniffAccessAddress : public BleMsg
    {
        public:
            SniffAccessAddress(BleMsg &message);
            SniffAccessAddress(ChannelMap channelMap);

            ChannelMap& getChannelMap();

        private:
            void pack();
            void unpack();

            ChannelMap m_channelMap;
    };

    class AccessAddressDiscovered : public BleMsg
    {
        public:
            AccessAddressDiscovered(BleMsg &message);
            AccessAddressDiscovered(uint32_t accessAddress);
            AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp);
            AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi);
            AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp, int32_t rssi);

            uint32_t getAccessAddress();
            bool hasTimestamp();
            uint32_t getTimestamp();
            bool hasRssi();
            int32_t getRssi();

        private:
            void pack();
            void unpack();

            uint32_t m_accessAddr;
            bool m_hasRssi;
            int32_t m_rssi;
            bool m_hasTimestamp;
            uint32_t m_timestamp;

    };

}

#endif /* __INC_WHAD_BLE_SNIFF_AA_HPP */