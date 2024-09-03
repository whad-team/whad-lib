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

        /*! ESB Message type */
        enum MessageType {
            UnknownMsg = WHAD_ESB_UNKNOWN,                      /*!< Unknown message. */
            SetNodeAddrMsg = WHAD_ESB_SET_NODE_ADDRESS,         /*!< Set node address message. */
            SniffMsg = WHAD_ESB_SNIFF,                          /*!< Set interface in sniffing mode. */
            JamMsg = WHAD_ESB_JAM,                              /*!< Set interface in jamming mode. */
            SendMsg = WHAD_ESB_SEND,                            /*!< Send PDU. */
            SendRawMsg = WHAD_ESB_SEND_RAW,                     /*!< Send raw PDU. */
            PrxMsg = WHAD_ESB_PRX,                              /*!< Set interface in Primary Receiver mode. */
            PtxMsg = WHAD_ESB_PTX,                              /*!< Set interface in Primary Transmitter mode. */
            StartMsg = WHAD_ESB_START,                          /*!< Start current mode. */
            StopMsg = WHAD_ESB_STOP,                            /*!< Stop current mode. */
            JammedMsg = WHAD_ESB_JAMMED,                        /*!< Jamming result notification. */
            RawPduReceivedMsg = WHAD_ESB_RAW_PDU_RECEIVED,      /*!< Raw PDU received notification. */
            PduReceivedMsg = WHAD_ESB_PDU_RECEIVED              /*!< PDU received notification. */
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