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
            SniffAccessAddress(ChannelMap channelMap);
    };

    class AccessAddressDiscovered : public BleMsg
    {
        public:
            AccessAddressDiscovered(uint32_t accessAddress);
            AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp);
            AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi);
            AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp, int32_t rssi);

    };

}

#endif /* __INC_WHAD_BLE_SNIFF_AA_HPP */