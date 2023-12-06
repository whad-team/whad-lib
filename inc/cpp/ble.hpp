#ifndef __INC_WHAD_BLE_HPP
#define __INC_WHAD_BLE_HPP

#ifdef __cplusplus

    #include <string>
    #include <vector>
    #include "message.hpp"
    #include "../domains/ble.h"

    namespace whad
    {
        namespace ble
        {
            /* BLE direction. */
            enum Direction {
                DirectionUnknown = BLE_DIR_UNKNOWN,
                DirectionMasterToSlave = BLE_MASTER_TO_SLAVE,
                DirectionSlaveToMaster = BLE_SLAVE_TO_MASTER,
                DirectionInjectionToSlave = BLE_INJECTION_TO_SLAVE,
                DirectionInjectionToMaster = BLE_INJECTION_TO_MASTER
            };

            enum AddressType {
                AddressRandom = BLE_ADDR_RANDOM,
                AddressPublic = BLE_ADDR_PUBLIC
            };

            enum AdvType {
                AdvUnknown = BLE_ADV_UNKNOWN,
                AdvInd = BLE_ADV_IND,
                AdvDirectInd = BLE_ADV_DIRECT_IND,
                AdvNonConnInd = BLE_ADV_NONCONN_IND,
                AdvScanInd = BLE_ADV_SCAN_IND,
                AdvScanRsp = BLE_ADV_SCAN_RSP
            };

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

            class BDAddress
            {
                private:

                    /* BD address as a byte buffer. */
                    uint8_t m_address[6];
                    AddressType m_type;

                public:
                    BDAddress(void);
                    BDAddress(AddressType type, uint8_t *p_bdaddr);

                    /* Getters. */
                    AddressType getType(void);
                    uint8_t *getAddressBuf(void);

                    /* Setters. */
                    void setType(AddressType type);
                    void setAddress(uint8_t *pBdAddress);
            };

            class ChannelMap
            {
                private:

                    /* Channel map buffer. */
                    uint8_t m_map[5];

                public:
                    ChannelMap();
                    ChannelMap(uint8_t channelMap[5]);

                    /* Basic channel map operations. */
                    void enableChannel(int channel);
                    void disableChannel(int channel);
                    bool isChannelEnabled(int channel);

                    /* Channel map accessor. */
                    uint8_t *getChannelMapBuf(void);
            };

            class PDU
            {
                private:
                    int m_length;
                    uint8_t *m_buf;
                
                public:
                    PDU(int length);
                    PDU(uint8_t *bytes, int length);
                    uint8_t *getBuf();
                    int getLength();
                    ~PDU();
            };

            /* Default discovery message class. */
            class BleMsg : public NanoPbMsg
            {
                public:

                    /* Constructor and destructor. */
                    BleMsg();
                    BleMsg(NanoPbMsg pMessage);
                    ~BleMsg();

                    /* Override getType() message. */
                    whad::ble::MessageType getType(void);
            };

            class LinkLayerPdu : public BleMsg
            {
                public:
                    LinkLayerPdu(uint32_t conn_handle, PDU pdu, Direction direction, bool processed, bool decrypted);
            };

            class RawPdu : public BleMsg
            {
                public:
                    RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           PDU pdu, uint32_t crc, bool crc_validity, uint32_t timestamp,
                           uint32_t relative_timestamp, Direction direction, bool processed,
                           bool decrypted);
                    RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           PDU pdu, uint32_t crc, bool crc_validity, Direction direction,
                           bool processed, bool decrypted);
                    
            };

            class Connected : public BleMsg
            {
                public:
                    Connected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr);
            };

            class Disconnected : public BleMsg
            {
                public:
                    Disconnected(uint32_t conn_handle, uint32_t reason);
            };

            class SetBdAddress : public BleMsg
            {
                public:
                    SetBdAddress(NanoPbMsg message);
                    SetBdAddress(BDAddress address);

                    BDAddress *getAddress();
            };

            class SniffAdv : public BleMsg
            {
                private:
                    uint32_t m_channel;
                    BDAddress m_targetAddr;
                    bool m_useExtAdv;

                public:
                    SniffAdv(NanoPbMsg message);
                    SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv);

                    /* Getters. */
                    uint32_t getChannel();
                    BDAddress getAddress();
                    bool mustUseExtAdv();
            };

            class JamAdv : public BleMsg
            {
                public:
                    JamAdv(void);
                    JamAdv(uint32_t channel);
            };

            class SniffConnReq : public BleMsg
            {
                public:
                    SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty);
            };

            class SniffAccessAddress : public BleMsg
            {
                public:
                    SniffAccessAddress(ChannelMap channelMap);
            };

            class SniffActiveConn : public BleMsg
            {
                public:
                    SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels);
            };

            class JamActiveConn : public BleMsg
            {
                public:
                    JamActiveConn(uint32_t accessAddress);
            };

            class ScanMode : public BleMsg
            {
                public:
                    ScanMode(bool active);
            };

            class AdvMode : public BleMsg
            {
                public:
                    AdvMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength);
            };

            class SetAdvData : public BleMsg
            {
                public:
                    SetAdvData(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLengthv);
            };

            class CentralMode : public BleMsg
            {
                public:
                    CentralMode(void);
            };

            class ConnectTo : public BleMsg
            {
                public:
                    ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                              uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit);
            };
            
            class SendRawPdu : public BleMsg
            {
                public:
                    SendRawPdu(Direction direction, uint32_t connHandle, uint32_t accessAddress, uint8_t *pPdu, int length, uint32_t crc, bool encrypt);
            };

            class SendPdu : public BleMsg
            {
                public:
                    SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt);
            };

            class Disconnect : public BleMsg
            {
                public:
                    Disconnect(uint32_t connHandle);
            };

            class PeripheralMode : public BleMsg
            {
                public:
                    PeripheralMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength);
            };

            class Start : public BleMsg
            {
                public:
                    Start(void);
            };

            class Stop : public BleMsg
            {
                public:
                    Stop(void);
            };

            class HijackMaster : public BleMsg
            {
                public:
                    HijackMaster(uint32_t accessAddress);
            };

            class HijackSlave : public BleMsg
            {
                public:
                    HijackSlave(uint32_t accessAddress);
            };

            class HijackBoth : public BleMsg
            {
                public:
                    HijackBoth(uint32_t accessAddress);
            };

            class SetEncryption : public BleMsg
            {
                private:

                    uint32_t m_connHandle;
                    uint8_t m_LLKey[16];
                    uint8_t m_llIv[8];
                    uint8_t m_key[16];
                    uint8_t m_rand[8];
                    uint8_t m_eDiv[2];
                    bool m_enabled;

                public:
                    SetEncryption(NanoPbMsg message);
                    SetEncryption(uint32_t connHandle, uint8_t pLLKey[16],
                                  uint8_t llIv[8], uint8_t key[16], uint8_t rand[8],
                                  uint8_t eDiv[2], bool enabled);

                    /* Getters. */
                    uint32_t getConnHandle();
                    uint8_t *getLLKey();
                    uint8_t *getLLIv();
                    uint8_t *getKey();
                    uint8_t *getRand();
                    uint8_t *getEDiv();
                    bool isEnabled();
                    
            };

            class ReactiveJam : public BleMsg
            {
                public:
                    ReactiveJam(uint32_t channel, uint8_t *pPattern, int length, uint32_t position);
            };

            class PatternTrigger
            {
                private:
                    uint8_t *m_pattern;
                    uint8_t *m_mask;
                    uint32_t m_offset;
                    int m_length;

                public:
                    PatternTrigger(uint8_t *pPattern, uint8_t *pMask, int length, uint32_t offset);
                    int getLength(void);
                    uint8_t *getPattern(void);
                    uint8_t *getMask(void);
                    uint32_t getOffset(void);
            };

            class ConnEventTrigger
            {
                private:
                    uint32_t m_connEvent;

                public:
                    ConnEventTrigger(uint32_t connEvent);
                    uint32_t getConnEvent(void);
            };

            class PrepareSequence : public BleMsg
            {
                private:
                    whad_prepared_packet_t *buildPacketsArray(std::vector<PDU> packets);

                public:
                    /* Manual trigger */
                    PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets);

                    /* Pattern trigger */
                    PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets, PatternTrigger trigger);

                    /* Connection event trigger */
                    PrepareSequence(uint32_t id, Direction direction, std::vector<PDU> packets,
                                    ConnEventTrigger trigger);
            };

            class ManualTrigger : public BleMsg
            {
                public:
                    ManualTrigger(uint32_t id);
            };

            class DeleteSequence : public BleMsg
            {
                public:
                    DeleteSequence(uint32_t id);
            };

            class SequenceTriggered : public BleMsg
            {
                public:
                    SequenceTriggered(uint32_t id);
            };

            class AccessAddressDiscovered : public BleMsg
            {
                public:
                    AccessAddressDiscovered(uint32_t accessAddress);
                    AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp);
                    AccessAddressDiscovered(uint32_t accessAddress, int32_t rssi);
                    AccessAddressDiscovered(uint32_t accessAddress, uint32_t timestamp, int32_t rssi);

            };

            class AdvPdu : public BleMsg
            {
                public:
                    AdvPdu(AdvType advType, int32_t rssi, BDAddress address, uint8_t *pAdvData, int advDataLength);
            };

            class Synchronized : public BleMsg
            {
                public:
                    Synchronized(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval,
                                 uint32_t hopIncrement, ChannelMap channelMap);
            };

            class Desynchronized : public BleMsg
            {
                public:
                    Desynchronized(uint32_t accessAddress);
            };

            class Hijacked : public BleMsg
            {
                public:
                    Hijacked(uint32_t accessAddress, bool success);
            };

            class Injected : public BleMsg
            {
                public:
                    Injected(uint32_t accessAddress, uint32_t attempts, bool success);
            };
        }
    }

#endif /* _cplusplus */

#endif /* __INC_WHAD_BLE_HPP */