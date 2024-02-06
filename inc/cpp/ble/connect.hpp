#ifndef __INC_WHAD_BLE_CONNECT_TO_HPP
#define __INC_WHAD_BLE_CONNECT_TO_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ConnectTo : public BleMsg
    {
        public:
            ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                        uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit);
    };

}

#endif /* __INC_WHAD_BLE_CONNECT_TO_HPP */