#ifndef __INC_WHAD_DOT15D4_SENDINSLOT_HPP
#define __INC_WHAD_DOT15D4_SENDINSLOT_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SendInSlot : public Dot15d4Msg
    {
        public:
            SendInSlot(Dot15d4Msg &message);
            SendInSlot(uint64_t slot, uint8_t *pPdu, int length);

            /* Getters. */
            uint64_t getSlot();
            PDU& getPdu();

        private:
            void pack();
            void unpack();

            uint64_t m_slot;
            PDU m_pdu; 
    };

}

#endif /* __INC_WHAD_DOT15D4_SENDINSLOT_HPP */