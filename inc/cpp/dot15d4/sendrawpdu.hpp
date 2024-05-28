#ifndef __INC_WHAD_DOT15D4_SENDRAW_HPP
#define __INC_WHAD_DOT15D4_SENDRAW_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <dot15d4/base.hpp>

namespace whad::dot15d4 {

    class SendRawPdu : public Dot15d4Msg
    {
        public:
            SendRawPdu(Dot15d4Msg &message);
            SendRawPdu(uint32_t channel, uint8_t *pPdu, int length, uint32_t fcs);

            /* Getters. */
            uint32_t getChannel();
            PDU& getPdu();
            uint32_t getFcs();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            PDU m_pdu; 
            uint32_t m_fcs;              
    };

}

#endif /* __INC_WHAD_DOT15D4_SENDRAW_HPP */