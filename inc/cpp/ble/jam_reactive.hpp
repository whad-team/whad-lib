#ifndef __INC_WHAD_BLE_JAM_REACTIVE_HPP
#define __INC_WHAD_BLE_JAM_REACTIVE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class ReactiveJam : public BleMsg
    {
        public:
            ReactiveJam(BleMsg &message);
            ReactiveJam(uint32_t channel, uint8_t *pPattern, unsigned int length, uint32_t position);

            uint32_t getChannel();
            uint8_t *getPattern();
            unsigned int getPatternLength();
            uint32_t getPosition();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            uint8_t m_pattern[20];
            unsigned int m_patternLength;
            uint32_t m_position;
            
    };

}

#endif /* __INC_WHAD_BLE_JAM_REACTIVE_HPP */