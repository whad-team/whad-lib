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
            ConnectTo(BleMsg &message);
            ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                        uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit);

            /* Getters. */
            BDAddress& getTargetAddr();
            uint32_t getAccessAddr();
            ChannelMap& getChannelMap();
            uint32_t getHopInterval();
            uint32_t getHopIncrement();
            uint32_t getCrcInit();

        private:
            void pack();
            void unpack();

            BDAddress m_targetAddr;
            uint32_t m_accessAddr;
            ChannelMap m_channelMap;
            uint32_t m_hopInterval;
            uint32_t m_hopIncrement;
            uint32_t m_crcInit;
                    
    };

}

#endif /* __INC_WHAD_BLE_CONNECT_TO_HPP */