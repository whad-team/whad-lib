#ifndef __INC_WHAD_DOT15D4_BASE_HPP
#define __INC_WHAD_DOT15D4_BASE_HPP

#include <string>
#include "message.hpp"
#include "common.hpp"
#include "../domains/dot15d4.h"

namespace whad::dot15d4 {

    typedef whad::Packet<255> PDU;

    /*! Dot15d4 message types. */
    enum MessageType {
        UnknownMsg = WHAD_DOT15D4_UNKNOWN,                              /*!< Unknown message. */
        SetNodeAddressMsg = WHAD_DOT15D4_SET_NODE_ADDRESS,              /*!< Set interface address message.*/
        SniffModeMsg = WHAD_DOT15D4_SNIFF,                              /*!< Set interface in sniffing mode. */
        JamModeMsg = WHAD_DOT15D4_JAM,                                  /*!< Set interface in jamming mode. */
        EnergyDetectionMsg = WHAD_DOT15D4_NRG_DETECTION,                /*!< Set interface in energy detection mode. */
        SendMsg = WHAD_DOT15D4_SEND,                                    /*!< Send a PDU. */
        SendRawMsg = WHAD_DOT15D4_SEND_RAW,                             /*!< Send a raw PDU. */
        EndDeviceModeMsg = WHAD_DOT15D4_END_DEVICE_MODE,                /*!< Set interface in end device mode. */
        RouterModeMsg = WHAD_DOT15D4_ROUTER_MODE,                       /*!< Set interface in router mode. */
        CoordModeMsg = WHAD_DOT15D4_COORD_MODE,                         /*!< Set interface in coordinator mode. */
        StartMsg = WHAD_DOT15D4_START,                                  /*!< Start current mode.*/
        StopMsg = WHAD_DOT15D4_STOP,                                    /*!< Stop current mode. */
        MitmModeMsg = WHAD_DOT15D4_MITM_MODE,                           /*!< Set interface in Man-in-the-Middle mode. */
        JammedMsg = WHAD_DOT15D4_JAMMED,                                /*!< Jamming result notification. */
        EnergyDetectionSampleMsg = WHAD_DOT15D4_NRG_DETECTION_SAMPLE,   /*!< Energy detection sample notification message. */
        RawPduReceivedMsg = WHAD_DOT15D4_RAW_PDU_RECEIVED,              /*!< Raw PDU received notification message. */
        PduReceivingMsg = WHAD_DOT15D4_PDU_RECEIVED                     /*!< PDU received notification message. */
    };

    /*! Dot15d4 address type. */
    typedef enum {
        AddressShort = WHAD_DOT15D4_ADDR_SHORT,         /*!< Short (16-bit) node address. */
        AddressExtended = WHAD_DOT15D4_ADDR_EXTENDED    /*!< Extended (64-bit) node address. */
    } AddressType;

    /*! MitM role. */
    typedef enum {
        ReactiveRole = WHAD_DOT15D4_MITM_REACTIVE,      /*!< Reactive role. */
        CorrectorRole = WHAD_DOT15D4_MITM_CORRECTOR     /*!< Corrector role. */
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