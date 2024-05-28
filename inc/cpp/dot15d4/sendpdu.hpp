#ifndef __INC_WHAD_DOT15D4_SEND_HPP
#define __INC_WHAD_DOT15D4_SEND_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SendPdu : public Dot15d4Msg
    {
        public:
            SendPdu(Dot15d4Msg &message);
            SendPdu(uint32_t channel, uint8_t *pPdu, int length);

            /* Getters. */
            uint32_t getChannel();
            PDU& getPdu();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            PDU m_pdu;               
    };

}

#endif /* __INC_WHAD_DOT15D4_SEND_HPP */