#ifndef __INC_WHAD_BLE_PATTERN_TRIGGER_HPP
#define __INC_WHAD_BLE_PATTERN_TRIGGER_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <ble/base.hpp>

namespace whad::ble {

    class PatternTrigger
    {
        public:
            PatternTrigger();
            PatternTrigger(uint8_t *pPattern, uint8_t *pMask, int length, uint32_t offset);
            int getLength(void);
            uint8_t *getPattern(void);
            uint8_t *getMask(void);
            uint32_t getOffset(void);

        private:
            uint8_t *m_pattern;
            uint8_t *m_mask;
            uint32_t m_offset;
            int m_length;
    };

}

#endif /* __INC_WHAD_BLE_PATTERN_TRIGGER_HPP */