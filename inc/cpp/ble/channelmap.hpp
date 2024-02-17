#ifndef __INC_WHAD_BLE_CHANNEL_MAP_HPP
#define __INC_WHAD_BLE_CHANNEL_MAP_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ChannelMap
    {
        private:

            /* Channel map buffer. */
            uint8_t m_map[5];

        public:
            ChannelMap();
            ChannelMap(uint8_t channelMap[5]);

            /* Basic channel map operations. */
            void enableChannel(int channel);
            void disableChannel(int channel);
            bool isChannelEnabled(int channel);

            bool isNull();

            /* Channel map accessor. */
            uint8_t *getChannelMapBuf(void);
    };

}

#endif /* __INC_WHAD_BLE_CHANNEL_MAP_HPP */