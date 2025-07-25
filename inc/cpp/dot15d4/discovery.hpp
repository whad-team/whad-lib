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
            DiscoveredCommunication(uint16_t src, uint16_t dst, uint16_t slot, uint16_t offset);

            /* Getters. */
            uint16_t getSrc();
            uint16_t getDst();
            uint16_t getSlot();
            uint16_t getOffset();

        private:
            void pack();

            uint16_t m_src;
            uint16_t m_dst;
            uint16_t m_slot;
            uint16_t m_offset;               
    };
}

#endif /* __INC_WHAD_DOT15D4_DISCOVERY_HPP */