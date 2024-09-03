#ifndef __INC_WHAD_UNIFYING_BASE_HPP
#define __INC_WHAD_UNIFYING_BASE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "../domains/unifying.h"

namespace whad::unifying {

    /*! Logitech Unifying PDU class. */
    typedef whad::Packet<255> PDU;

    /*! Logitech Unifying device address. */
    typedef DeviceAddress<1,5> UnifyingAddress;

    /*! Unifying message types. */
    enum MessageType {
        UnknownMsg = WHAD_UNIFYING_UNKNOWN,                     /*!< Unknown message. */
        SetNodeAddressMsg = WHAD_UNIFYING_SET_NODE_ADDR,        /*!< Set node address. */
        SniffModeMsg = WHAD_UNIFYING_SNIFF_MODE,                /*!< Set interface in sniffing mode. */
        JamModeMsg = WHAD_UNIFYING_JAM_MODE,                    /*!< Set interface in jamming mode. */
        SendMsg = WHAD_UNIFYING_SEND,                           /*!< Send PDU. */
        SendRawMsg = WHAD_UNIFYING_SEND_RAW,                    /*!< Send raw PDU. */
        DongleModeMsg = WHAD_UNIFYING_DONGLE_MODE,              /*!< Set interface in dongle mode. */
        KeyboardModeMsg = WHAD_UNIFYING_KEYBOARD_MODE,          /*!< Set interface in keyboard mode. */
        MouseModeMsg = WHAD_UNIFYING_MOUSE_MODE,                /*!< Set interface in mouse mode. */
        StartMsg = WHAD_UNIFYING_START,                         /*!< Start current mode. */
        StopMsg = WHAD_UNIFYING_STOP,                           /*!< Stop current mode. */
        SniffPairingMsg = WHAD_UNIFYING_SNIFF_PAIRING,          /*!< Set interface in pairing sniffing mode. */
        JammedMsg = WHAD_UNIFYING_JAMMED,                       /*!< Jamming result notification. */
        RawPduReceivedMsg = WHAD_UNIFYING_RAW_PDU_RECEIVED,     /*!< Raw PDU received notification. */
        PduReceivedMsg = WHAD_UNIFYING_PDU_RECEIVED             /*!< PDU received notification. */
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