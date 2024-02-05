#ifndef __INC_WHAD_ESB_HPP
#define __INC_WHAD_ESB_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/esb.h"
#include <esb/address.hpp>

namespace whad
{
    namespace esb
    {   
        typedef whad::Packet<255> Packet;

        enum MessageType {
            UnknownMsg = WHAD_ESB_UNKNOWN,
            SetNodeAddrMsg = WHAD_ESB_SET_NODE_ADDRESS,
            SniffMsg = WHAD_ESB_SNIFF,
            JamMsg = WHAD_ESB_JAM,
            SendMsg = WHAD_ESB_SEND,
            SendRawMsg = WHAD_ESB_SEND_RAW,
            PrxMsg = WHAD_ESB_PRX,
            PtxMsg = WHAD_ESB_PTX,
            StartMsg = WHAD_ESB_START,
            StopMsg = WHAD_ESB_STOP,
            JammedMsg = WHAD_ESB_JAMMED,
            RawPduReceivedMsg = WHAD_ESB_RAW_PDU_RECEIVED,
            PduReceivedMsg = WHAD_ESB_PDU_RECEIVED
        };


        /* Default ESB message class. */
        class EsbMsg : public NanoPbMsg
        {
            public:

                /* Constructor and destructor. */
                EsbMsg();
                EsbMsg(NanoPbMsg &pMessage);
                ~EsbMsg();

                /* Override getType() message. */
                MessageType getType(void);
        };
    }
}

#endif /* __INC_WHAD_ESB_HPP */