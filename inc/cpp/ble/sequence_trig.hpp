#ifndef __INC_WHAD_BLE_SEQUENCE_TRIGGERED_HPP
#define __INC_WHAD_BLE_SEQUENCE_TRIGGERED_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class SequenceTriggered : public BleMsg
    {
        public:
            SequenceTriggered(BleMsg &message);
            SequenceTriggered(uint32_t id);

            uint32_t getId();

        private:
            void pack();
            void unpack();

            uint32_t m_id;
    };

}

#endif /* __INC_WHAD_BLE_SEQUENCE_TRIGGERED_HPP */