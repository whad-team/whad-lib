#ifndef __INC_WHAD_PHY_SYNCWORD_HPP
#define __INC_WHAD_PHY_SYNCWORD_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"

namespace whad::phy {

    class SyncWord 
    {
        public:
            SyncWord();
            SyncWord(uint8_t *syncword, uint8_t size);

            uint8_t *get();
            uint8_t getSize();

        private:
            uint8_t m_syncword[10];
            uint8_t m_size;
    };

}

#endif /* __INC_WHAD_PHY_SYNCWORD_HPP */