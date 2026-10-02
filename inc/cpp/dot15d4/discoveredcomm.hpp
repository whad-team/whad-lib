#ifndef __INC_WHAD_DOT15D4_DISCOVERED_COMM_HPP
#define __INC_WHAD_DOT15D4_DISCOVERED_COMM_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class DiscoveredCommunication : public Dot15d4Msg
    {
        public:
            DiscoveredCommunication(Dot15d4Msg &message);
            DiscoveredCommunication(uint64_t slot, uint32_t offset, uint8_t *pPdu, uint32_t length);

            /* Getters. */
            uint64_t getSlot();
            uint32_t getOffset();
            PDU& getPdu();

        private:
            void pack();
            void unpack();

            uint64_t m_slot;
            uint32_t m_offset;      
            PDU m_pdu;         
    };

}

#endif /* __INC_WHAD_DOT15D4_DISCOVERED_COMM_HPP */