#ifndef __INC_WHAD_ZIGBEE_BASE_HPP
#define __INC_WHAD_ZIGBEE_BASE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "../domains/zigbee.h"

namespace whad::zigbee {

    typedef whad::Packet<255> PDU;

    /* ZigBee message types. */
    enum MessageType {
        UnknownMsg = WHAD_ZIGBEE_UNKNOWN,
        SetNodeAddressMsg = WHAD_ZIGBEE_SET_NODE_ADDRESS,
        SniffModeMsg = WHAD_ZIGBEE_SNIFF,
        JamModeMsg = WHAD_ZIGBEE_JAM,
        EnergyDetectionMsg = WHAD_ZIGBEE_NRG_DETECTION,
        SendMsg = WHAD_ZIGBEE_SEND,
        SendRawMsg = WHAD_ZIGBEE_SEND_RAW,
        EndDeviceModeMsg = WHAD_ZIGBEE_END_DEVICE_MODE,
        RouterModeMsg = WHAD_ZIGBEE_ROUTER_MODE,
        CoordModeMsg = WHAD_ZIGBEE_COORD_MODE,
        StartMsg = WHAD_ZIGBEE_START,
        StopMsg = WHAD_ZIGBEE_STOP,
        MitmModeMsg = WHAD_ZIGBEE_MITM_MODE,
        JammedMsg = WHAD_ZIGBEE_JAMMED,
        EnergyDetectionSampleMsg = WHAD_ZIGBEE_NRG_DETECTION_SAMPLE,
        RawPduReceivedMsg = WHAD_ZIGBEE_RAW_PDU_RECEIVED,
        PduReceivingMsg = WHAD_ZIGBEE_PDU_RECEIVED
    };

    /* ZigBee address type. */
    typedef enum {
        AddressShort = WHAD_ZIGBEE_ADDR_SHORT,
        AddressExtended = WHAD_ZIGBEE_ADDR_EXTENDED
    } AddressType;

    /* MitM role. */
    typedef enum {
        ReactiveRole = WHAD_ZIGBEE_MITM_REACTIVE,
        CorrectorRole = WHAD_ZIGBEE_MITM_CORRECTOR
    } MitmRole;


    /* Default BLE message class. */
    class ZigbeeMsg : public NanoPbMsg
    {
        public:

            /* Constructor and destructor. */
            ZigbeeMsg();
            ZigbeeMsg(NanoPbMsg pMessage);
            ~ZigbeeMsg();

            /* Override getType() message. */
            MessageType getType(void);
    };           
}

#endif /* __INC_WHAD_ZIGBEE_BASE_HPP */