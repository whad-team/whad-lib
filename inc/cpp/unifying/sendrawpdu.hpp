#ifndef __INC_WHAD_UNIFYING_SENDRAWPDU_HPP
#define __INC_WHAD_UNIFYING_SENDRAWPDU_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include <unifying/base.hpp>

namespace whad::unifying {

    class SendRawPdu : public UnifyingMsg
    {
        public:
            SendRawPdu(UnifyingMsg &message);
            SendRawPdu(uint32_t channel, int retrCount, uint8_t *pPdu, int length);

            /* Getters. */
            uint32_t getChannel();
            int getRetrCounter();
            PDU& getPdu();

        private:
            void pack();
            void unpack();

            uint32_t m_channel;
            PDU m_pdu;
            int m_retrCount;
    };

}

#endif /* __INC_WHAD_UNIFYING_SENDRAWPDU_HPP */