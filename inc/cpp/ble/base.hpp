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

    /* Advertisement type. */
    enum AdvType {
        AdvUnknown = BLE_ADV_UNKNOWN,
        AdvInd = BLE_ADV_IND,
        AdvDirectInd = BLE_ADV_DIRECT_IND,
        AdvNonConnInd = BLE_ADV_NONCONN_IND,
        AdvScanInd = BLE_ADV_SCAN_IND,
        AdvScanRsp = BLE_ADV_SCAN_RSP
    };

    /* BLE direction. */
    enum Direction {
        DirectionUnknown = BLE_DIR_UNKNOWN,
        DirectionMasterToSlave = BLE_MASTER_TO_SLAVE,
        DirectionSlaveToMaster = BLE_SLAVE_TO_MASTER,
        DirectionInjectionToSlave = BLE_INJECTION_TO_SLAVE,
        DirectionInjectionToMaster = BLE_INJECTION_TO_MASTER
    };

    /* BLE message types. */
    enum MessageType {
        UnknownMsg = WHAD_BLE_UNKNOWN,
        SetBdAddressMsg = WHAD_BLE_SET_BDADDRESS,
        SetAdvDataMsg = WHAD_BLE_SET_ADV_DATA,
        SetEncryptionMsg = WHAD_BLE_SET_ENCRYPTION,
        SniffAdvMsg = WHAD_BLE_SNIFF_ADV,
        SniffConnReqMsg = WHAD_BLE_SNIFF_CONN_REQ,
        SniffActConnMsg = WHAD_BLE_SNIFF_ACT_CONN,
        ScanModeMsg = WHAD_BLE_SCAN_MODE,
        AdvModeMsg = WHAD_BLE_ADV_MODE,
        PeriphModeMsg = WHAD_BLE_PERIPH_MODE,
        CentralModeMsg = WHAD_BLE_CENTRAL_MODE,
        StartMsg = WHAD_BLE_START,
        StopMsg = WHAD_BLE_STOP,
        ConnectToMsg = WHAD_BLE_CONNECT_TO,
        SendRawPduMsg = WHAD_BLE_SEND_RAW_PDU,
        SendPduMsg = WHAD_BLE_SEND_PDU,
        DisconnectMsg = WHAD_BLE_DISCONNECT,
        PrepareSeqMsg = WHAD_BLE_PREPARE_SEQ,
        PrepareSeqTriggerMsg = WHAD_BLE_PREPARE_SEQ_TRIGGER,
        PrepareSeqDeleteMsg = WHAD_BLE_PREPARE_SEQ_DELETE,
        JamAdvMsg = WHAD_BLE_JAM_ADV,
        JamAdvChannelMsg = WHAD_BLE_JAM_ADV_CHANNEL,
        JamActConnMsg = WHAD_BLE_JAM_ACT_CONN,
        HijackMasterMsg = WHAD_BLE_HIJACK_MASTER,
        HijackSlaveMsg = WHAD_BLE_HIJACK_SLAVE,
        HijackBothMsg = WHAD_BLE_HIJACK_BOTH,
        ReactiveJamMsg = WHAD_BLE_REACTIVE_JAM,
        NotifyConnectedMsg = WHAD_BLE_NOTIFY_CONNECTED,
        NotifyDisconnectedMsg = WHAD_BLE_NOTIFY_DISCONNECTED,
        RawPduMsg = WHAD_BLE_RAW_PDU,
        PduMsg = WHAD_BLE_PDU,
        TriggeredMsg = WHAD_BLE_TRIGGERED,
        AccessAddressDiscoveredMsg = WHAD_BLE_ACCESS_ADDRESS_DISCOVERED,
        AdvPduMsg = WHAD_BLE_ADV_PDU,
        SynchronizedMsg = WHAD_BLE_SYNCHRONIZED,
        DesynchronizedMsg = WHAD_BLE_DESYNCHRONIZED,
        HijackedMsg = WHAD_BLE_HIJACKED,
        InjectedMsg = WHAD_BLE_INJECTED
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