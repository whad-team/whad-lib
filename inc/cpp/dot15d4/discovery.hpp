#ifndef __INC_WHAD_DOT15D4_DISCOVERY_HPP
#define __INC_WHAD_DOT15D4_DISCOVERY_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class DiscoveredCommunication : public Dot15d4Msg
    {
        public:
            DiscoveredCommunication(uint8_t* pkt, size_t size, uint16_t slot, uint16_t offset);

            /* Getters. */
            uint8_t* getPkt();
            size_t getSize();
            uint16_t getSlot();
            uint16_t getOffset();

        private:
            void pack();

            uint8_t* m_pkt;
            size_t m_size;
            uint16_t m_slot;
            uint16_t m_offset;               
    };
}

#endif /* __INC_WHAD_DOT15D4_DISCOVERY_HPP */