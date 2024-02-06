#ifndef __INC_WHAD_BLE_SNIFFADV_HPP
#define __INC_WHAD_BLE_SNIFFADV_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SniffAdv : public BleMsg
    {
        private:
            uint32_t m_channel;
            BDAddress m_targetAddr;
            bool m_useExtAdv;

        public:
            SniffAdv(NanoPbMsg message);
            SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv);

            /* Getters. */
            uint32_t getChannel();
            BDAddress getAddress();
            bool mustUseExtAdv();
    };

}

#endif /* __INC_WHAD_BLE_SNIFFADV_HPP */