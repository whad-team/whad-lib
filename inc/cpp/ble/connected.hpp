#ifndef __INC_WHAD_BLE_CONNECTED_HPP
#define __INC_WHAD_BLE_CONNECTED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class Connected : public BleMsg
    {
        public:
            Connected(BleMsg &message);
            Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr);

            /* Getters. */
            uint32_t getConnHandle();
            BDAddress& getAdvertiserAddr();
            BDAddress& getInitiatorAddr();

        private:
            void pack();

            uint32_t m_connHandle;
            BDAddress m_advAddr;
            BDAddress m_initAddr;
    };

}

#endif /* __INC_WHAD_BLE_CONNECTED_HPP */