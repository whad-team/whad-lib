#ifndef __INC_WHAD_BLE_SNIFF_CONNREQ_HPP
#define __INC_WHAD_BLE_SNIFF_CONNREQ_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SniffConnReq : public BleMsg
    {
        public:
            SniffConnReq(BleMsg &message);
            SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty);

            uint32_t getChannel();
            BDAddress& getTargetAddress();
            bool mustReportAdv();
            bool mustReportEmpty();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            BDAddress m_targetAddr;
            bool m_showAdv;
            bool m_showEmpty;
    };

}

#endif /* __INC_WHAD_BLE_SNIFF_CONNREQ_HPP */