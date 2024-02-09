#ifndef __INC_WHAD_BLE_JAMADV_HPP
#define __INC_WHAD_BLE_JAMADV_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class JamAdv : public BleMsg
    {
        public:
            JamAdv(BleMsg &message);
            JamAdv();
            JamAdv(uint32_t channel);

            bool hasChannel();
            uint32_t getChannel();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            bool m_hasChannel;
    };

}

#endif /* __INC_WHAD_BLE_JAMADV_HPP */