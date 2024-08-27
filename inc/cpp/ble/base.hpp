#ifndef __INC_WHAD_BLE_BASE_HPP
#define __INC_WHAD_BLE_BASE_HPP


#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/ble.h"
#include "ble/address.hpp"
#include "ble/channelmap.hpp"
#include "ble/pattern_trigger.hpp"
#include "ble/conn_evt_trigger.hpp"

namespace whad::ble {

    typedef whad::Packet<255> PDU;

    /*! Advertisement type. */
    enum AdvType {
        AdvUnknown = BLE_ADV_UNKNOWN,           /*!< Unknown advertisement type. */
        AdvInd = BLE_ADV_IND,                   /*!< Indirected advertisement. */
        AdvDirectInd = BLE_ADV_DIRECT_IND,      /*!< Directed advertisement. */
        AdvNonConnInd = BLE_ADV_NONCONN_IND,    /*!< Non-connectable indirected advertised. */
        AdvScanInd = BLE_ADV_SCAN_IND,          /*!< Scan request. */
        AdvScanRsp = BLE_ADV_SCAN_RSP           /*!< Scan response. */
    };

    /*! Indicate BLE direction. */
    enum Direction {
        DirectionUnknown = BLE_DIR_UNKNOWN,                     /*!< Direction is unknown. */
        DirectionMasterToSlave = BLE_MASTER_TO_SLAVE,           /*!< From "master" device to "slave" device. */
        DirectionSlaveToMaster = BLE_SLAVE_TO_MASTER,           /*!< From "slave" device to "master" device. */
        DirectionInjectionToSlave = BLE_INJECTION_TO_SLAVE,     /*!< Inject data towards "slave" device. */
        DirectionInjectionToMaster = BLE_INJECTION_TO_MASTER    /*!< Inject data towards "master" device. */
    };

    /*! BLE message types. */
    enum MessageType {
        UnknownMsg = WHAD_BLE_UNKNOWN,                                      /*<! Unknown message type. */
        SetBdAddressMsg = WHAD_BLE_SET_BDADDRESS,                           /*!< Set interface BD address. */
        SetAdvDataMsg = WHAD_BLE_SET_ADV_DATA,                              /*!< Set advertising data. */
        SetEncryptionMsg = WHAD_BLE_SET_ENCRYPTION,                         /*!< Set encryption. */
        SniffAAMsg = WHAD_BLE_SNIFF_AA,                                     /*!< Sniff BLE access address. */
        SniffAdvMsg = WHAD_BLE_SNIFF_ADV,                                   /*!< Sniff advertisements. */
        SniffConnReqMsg = WHAD_BLE_SNIFF_CONN_REQ,                          /*!< Sniff connection requests. */
        SniffActConnMsg = WHAD_BLE_SNIFF_ACT_CONN,                          /*!< Sniff active connection. */
        ScanModeMsg = WHAD_BLE_SCAN_MODE,                                   /*!< Set scanning mode. */
        AdvModeMsg = WHAD_BLE_ADV_MODE,                                     /*!< Set advertising mode. */
        PeriphModeMsg = WHAD_BLE_PERIPH_MODE,                               /*!< Set peripheral mode. */
        CentralModeMsg = WHAD_BLE_CENTRAL_MODE,                             /*!< Set central mode. */
        StartMsg = WHAD_BLE_START,                                          /*!< Start current mode. */
        StopMsg = WHAD_BLE_STOP,                                            /*!< Stop current mode. */
        ConnectToMsg = WHAD_BLE_CONNECT_TO,                                 /*!< Initiate a connection to a device. */
        SendRawPduMsg = WHAD_BLE_SEND_RAW_PDU,                              /*!< Send raw BLE PDU. */
        SendPduMsg = WHAD_BLE_SEND_PDU,                                     /*!< Send BLE PDU. */
        DisconnectMsg = WHAD_BLE_DISCONNECT,                                /*!< Disconnect from device. */
        PrepareSeqMsg = WHAD_BLE_PREPARE_SEQ,                               /*!< Prepare a sequence of packets. */
        PrepareSeqTriggerMsg = WHAD_BLE_PREPARE_SEQ_TRIGGER,                /*!< Manually trigger a prepared sequence. */
        PrepareSeqDeleteMsg = WHAD_BLE_PREPARE_SEQ_DELETE,                  /*!< Delete a prepared sequence. */
        JamAdvMsg = WHAD_BLE_JAM_ADV,                                       /*!< Set advertisement jamming mode. */
        JamAdvChannelMsg = WHAD_BLE_JAM_ADV_CHANNEL,                        /*!< Set single-channel advertisement jamming mode. */
        JamActConnMsg = WHAD_BLE_JAM_ACT_CONN,                              /*!< Set active connection jamming mode. */
        HijackMasterMsg = WHAD_BLE_HIJACK_MASTER,                           /*!< Hijack "master" device mode. */
        HijackSlaveMsg = WHAD_BLE_HIJACK_SLAVE,                             /*!< Hijack "slave" device mode*/
        HijackBothMsg = WHAD_BLE_HIJACK_BOTH,                               /*!< Hijack both "master" and "slave" devices. */
        ReactiveJamMsg = WHAD_BLE_REACTIVE_JAM,                             /*!< Set reactive jamming mode. */
        NotifyConnectedMsg = WHAD_BLE_NOTIFY_CONNECTED,                     /*!< Notify host about a successful connection. */
        NotifyDisconnectedMsg = WHAD_BLE_NOTIFY_DISCONNECTED,               /*!< Notify host of a disconnection. */
        RawPduMsg = WHAD_BLE_RAW_PDU,                                       /*!< Notify host about a received raw BLE PDU. */
        PduMsg = WHAD_BLE_PDU,                                              /*!< Notify host about a received BLE PDU. */
        TriggeredMsg = WHAD_BLE_TRIGGERED,                                  /*!< Notify host about a triggered prepared sequence. */
        AccessAddressDiscoveredMsg = WHAD_BLE_ACCESS_ADDRESS_DISCOVERED,    /*!< Notify host of a discovered access address. */
        AdvPduMsg = WHAD_BLE_ADV_PDU,                                       /*!< Notify host about a received advertising PDU. */
        SynchronizedMsg = WHAD_BLE_SYNCHRONIZED,                            /*!< Notify host of a connection sync. */
        DesynchronizedMsg = WHAD_BLE_DESYNCHRONIZED,                        /*!< Notify host of a connection desync. */
        HijackedMsg = WHAD_BLE_HIJACKED,                                    /*!< Notify host of an hijacking status update. */
        InjectedMsg = WHAD_BLE_INJECTED                                     /*!< Notify host of an injection status update. */
    };

    /* Default BLE message class. */
    class BleMsg : public NanoPbMsg
    {
        public:

            /* Constructor and destructor. */
            BleMsg();
            BleMsg(NanoPbMsg pMessage);
            ~BleMsg();

            /* Override getType() message. */
            MessageType getType(void);
    };           
}

#endif /* __INC_WHAD_BLE_BASE_HPP */