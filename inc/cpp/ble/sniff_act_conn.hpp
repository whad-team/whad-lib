#ifndef __INC_WHAD_BLE_SNIFF_ACT_CONN_HPP
#define __INC_WHAD_BLE_SNIFF_ACT_CONN_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SniffActiveConn : public BleMsg
    {
        public:
            SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels);
    };

}

#endif /* __INC_WHAD_BLE_SNIFF_ACT_CONN_HPP */