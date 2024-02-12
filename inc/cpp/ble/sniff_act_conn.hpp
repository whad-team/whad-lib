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
            SniffActiveConn(BleMsg &message);
            SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels);

            uint32_t getAccessAddress();
            uint32_t getCrcInit();
            uint32_t getHopInterval();
            uint32_t getHopIncrement();
            ChannelMap& getChannelMap();
            ChannelMap& getChannels();

        private:
            void pack();
            void unpack();

            uint32_t m_accessAddr;
            uint32_t m_crcInit;
            uint32_t m_hopInterval;
            uint32_t m_hopIncrement;
            ChannelMap m_channelMap;
            ChannelMap m_channels;
    };

}

#endif /* __INC_WHAD_BLE_SNIFF_ACT_CONN_HPP */