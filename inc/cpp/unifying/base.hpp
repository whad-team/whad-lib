#ifndef __INC_WHAD_UNIFYING_BASE_HPP
#define __INC_WHAD_UNIFYING_BASE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "../domains/unifying.h"

namespace whad::unifying {

    typedef whad::Packet<255> PDU;

    typedef DeviceAddress<1,5> UnifyingAddress;

    /* Unifying message types. */
    enum MessageType {
        UnknownMsg = WHAD_UNIFYING_UNKNOWN,
        SetNodeAddressMsg = WHAD_UNIFYING_SET_NODE_ADDR,
        SniffModeMsg = WHAD_UNIFYING_SNIFF_MODE,
        JamModeMsg = WHAD_UNIFYING_JAM_MODE,
        SendMsg = WHAD_UNIFYING_SEND,
        SendRawMsg = WHAD_UNIFYING_SEND_RAW,
        DongleModeMsg = WHAD_UNIFYING_DONGLE_MODE,
        KeyboardModeMsg = WHAD_UNIFYING_KEYBOARD_MODE,
        MouseModeMsg = WHAD_UNIFYING_MOUSE_MODE,
        StartMsg = WHAD_UNIFYING_START,
        StopMsg = WHAD_UNIFYING_STOP,
        SniffPairingMsg = WHAD_UNIFYING_SNIFF_PAIRING,
        JammedMsg = WHAD_UNIFYING_JAMMED,
        RawPduReceivedMsg = WHAD_UNIFYING_RAW_PDU_RECEIVED,
        PduReceivedMsg = WHAD_UNIFYING_PDU_RECEIVED
    };


    /* Default BLE message class. */
    class UnifyingMsg : public NanoPbMsg
    {
        public:

            /* Constructor and destructor. */
            UnifyingMsg();
            UnifyingMsg(NanoPbMsg pMessage);
            ~UnifyingMsg();

            /* Override getType() message. */
            MessageType getType(void);
    };           
}

#endif /* __INC_WHAD_UNIFYING_BASE_HPP */