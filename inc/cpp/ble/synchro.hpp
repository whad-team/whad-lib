#ifndef __INC_WHAD_BLE_SYNC_HPP
#define __INC_WHAD_BLE_SYNC_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Synchronized : public BleMsg
    {
        public:
            Synchronized(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval,
                            uint32_t hopIncrement, ChannelMap channelMap);
    };

    class Desynchronized : public BleMsg
    {
        public:
            Desynchronized(uint32_t accessAddress);
    };

}

#endif /* __INC_WHAD_BLE_SYNC_HPP */