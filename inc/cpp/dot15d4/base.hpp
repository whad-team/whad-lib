#ifndef __INC_WHAD_DOT15D4_BASE_HPP
#define __INC_WHAD_DOT15D4_BASE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "../domains/dot15d4.h"

namespace whad::dot15d4 {

    typedef whad::Packet<255> PDU;

    /* Dot15d4 message types. */
    enum MessageType {
        UnknownMsg = WHAD_DOT15D4_UNKNOWN,
        SetNodeAddressMsg = WHAD_DOT15D4_SET_NODE_ADDRESS,
        SniffModeMsg = WHAD_DOT15D4_SNIFF,
        JamModeMsg = WHAD_DOT15D4_JAM,
        EnergyDetectionMsg = WHAD_DOT15D4_NRG_DETECTION,
        SendMsg = WHAD_DOT15D4_SEND,
        SendRawMsg = WHAD_DOT15D4_SEND_RAW,
        EndDeviceModeMsg = WHAD_DOT15D4_END_DEVICE_MODE,
        RouterModeMsg = WHAD_DOT15D4_ROUTER_MODE,
        CoordModeMsg = WHAD_DOT15D4_COORD_MODE,
        StartMsg = WHAD_DOT15D4_START,
        StopMsg = WHAD_DOT15D4_STOP,
        MitmModeMsg = WHAD_DOT15D4_MITM_MODE,
        JammedMsg = WHAD_DOT15D4_JAMMED,
        EnergyDetectionSampleMsg = WHAD_DOT15D4_NRG_DETECTION_SAMPLE,
        RawPduReceivedMsg = WHAD_DOT15D4_RAW_PDU_RECEIVED,
        PduReceivingMsg = WHAD_DOT15D4_PDU_RECEIVED
    };

    /* Dot15d4 address type. */
    typedef enum {
        AddressShort = WHAD_DOT15D4_ADDR_SHORT,
        AddressExtended = WHAD_DOT15D4_ADDR_EXTENDED
    } AddressType;

    /* MitM role. */
    typedef enum {
        ReactiveRole = WHAD_DOT15D4_MITM_REACTIVE,
        CorrectorRole = WHAD_DOT15D4_MITM_CORRECTOR
    } MitmRole;


    /* Default BLE message class. */
    class Dot15d4Msg : public NanoPbMsg
    {
        public:

            /* Constructor and destructor. */
            Dot15d4Msg();
            Dot15d4Msg(NanoPbMsg pMessage);
            ~Dot15d4Msg();

            /* Override getType() message. */
            MessageType getType(void);
    };           
}

#endif /* __INC_WHAD_DOT15D4_BASE_HPP */