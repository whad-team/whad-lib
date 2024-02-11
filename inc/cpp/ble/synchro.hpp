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
            Synchronized(BleMsg &message);
            Synchronized(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval,
                            uint32_t hopIncrement, ChannelMap channelMap);

            uint32_t getAccessAddress();
            uint32_t getCrcInit();
            uint32_t getHopInterval();
            uint32_t getHopIncrement();
            ChannelMap& getChannelMap();

        private:
            void pack();
            void unpack();

            uint32_t m_accessAddr;
            uint32_t m_crcInit;
            uint32_t m_hopInterval;
            uint32_t m_hopIncrement;
            ChannelMap m_channelMap;
    };

    class Desynchronized : public BleMsg
    {
        public:
            Desynchronized(BleMsg &message);
            Desynchronized(uint32_t accessAddress);

            uint32_t getAccessAddress();

        private:
            void pack();
            void unpack();

            uint32_t m_accessAddr;
    };

}

#endif /* __INC_WHAD_BLE_SYNC_HPP */