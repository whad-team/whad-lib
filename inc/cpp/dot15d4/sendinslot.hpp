#ifndef __INC_WHAD_DOT15D4_SEND_IN_SLOT_HPP
#define __INC_WHAD_DOT15D4_SEND_IN_SLOT_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SendInSlotPdu : public Dot15d4Msg
    {
        public:
            SendInSlotPdu(Dot15d4Msg &message);
            SendInSlotPdu(uint64_t slot, uint32_t wait_offset, uint8_t *pPdu, int length);

            /* Getters. */
            uint64_t getSlot();
            uint32_t getWaitOffset();
            PDU& getPdu();

        private:
            void pack();
            void unpack();

            uint64_t m_slot;
            uint32_t m_wait_offset;
            PDU m_pdu;               
    };

}

#endif /* __INC_WHAD_DOT15D4_SEND_IN_SLOT_HPP */