#ifndef __INC_WHAD_BLE_HPP
#define __INC_WHAD_BLE_HPP

#ifdef __cplusplus

    #include <string>
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

            class BDAddress
            {
                private:

                    /* BD address as a byte buffer. */
                    uint8_t m_address[6];
                    AddressType m_type;

                public:
                    BDAddress(AddressType type, uint8_t *p_bdaddr);
                    AddressType getType(void);
                    uint8_t *getAddressBuf(void);
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

            class Pdu : public NanoPbMsg
            {
                public:
                    Pdu(uint32_t conn_handle, uint8_t *pdu, int length, Direction direction, bool processed, bool decrypted);
            };

            class RawPdu : public NanoPbMsg
            {
                public:
                    RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           uint8_t *p_pdu, int length, uint32_t crc, bool crc_validity, uint32_t timestamp,
                           uint32_t relative_timestamp, whad_ble_direction_t direction, bool processed,
                           bool decrypted);
                    RawPdu(uint32_t channel, int32_t rssi, uint32_t conn_handle, uint32_t access_address,
                           uint8_t *p_pdu, int length, uint32_t crc, bool crc_validity, whad_ble_direction_t direction,
                           bool processed, bool decrypted);
                    
            };

            class NotifyConnected : public NanoPbMsg
            {
                public:
                    NotifyConnected(uint32_t connHandle, BDAddress advAddr, BDAddress initAddr);
            };

            class NotifyDisconnected : public NanoPbMsg
            {
                public:
                    NotifyDisconnected(uint32_t conn_handle, uint32_t reason);
            };

            class SetBdAddress : public NanoPbMsg
            {
                public:
                    SetBdAddress(BDAddress address);
            };

            class SniffAdv : public NanoPbMsg
            {
                public:
                    SniffAdv(uint32_t channel, BDAddress targetAddr, bool useExtAdv);
            };

            class JamAdv : public NanoPbMsg
            {
                public:
                    JamAdv(void);
                    JamAdv(uint32_t channel);
            };

            class SniffConnReq : public NanoPbMsg
            {
                public:
                    SniffConnReq(uint32_t channel, BDAddress targetAddr, bool showAdv, bool showEmpty);
            };

            class SniffAccessAddress : public NanoPbMsg
            {
                public:
                    SniffAccessAddress(ChannelMap channelMap);
            };

            class SniffActiveConn : public NanoPbMsg
            {
                public:
                    SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels);
            };

            class JamActiveConn : public NanoPbMsg
            {
                public:
                    JamActiveConn(uint32_t accessAddress);
            };

            class ScanMode : public NanoPbMsg
            {
                public:
                    ScanMode(bool active);
            };

            class AdvMode : public NanoPbMsg
            {
                public:
                    AdvMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength);
            };

            class SetAdvData : public NanoPbMsg
            {
                public:
                    SetAdvData(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLengthv);
            };

            class CentralMode : public NanoPbMsg
            {
                public:
                    CentralMode(void);
            };

            class ConnectTo : public NanoPbMsg
            {
                public:
                    ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                              uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit);
            };
            
            class SendRawPdu : public NanoPbMsg
            {
                public:
                    SendRawPdu(Direction direction, uint32_t connHandle, uint32_t accessAddress, uint8_t *pPdu, int length, uint32_t crc, bool encrypt);
            };

            class SendPdu : public NanoPbMsg
            {
                public:
                    SendPdu(Direction direction, uint32_t connHandle, uint8_t *pPdu, int length, bool encrypt);
            };

            class Disconnect : public NanoPbMsg
            {
                public:
                    Disconnect(uint32_t connHandle);
            };

            class PeripheralMode : public NanoPbMsg
            {
                public:
                    PeripheralMode(uint8_t *pAdvData, int advDataLength, uint8_t *pScanRsp, int scanRspLength);
            };

            class Start : public NanoPbMsg
            {
                public:
                    Start(void);
            };

            class Stop : public NanoPbMsg
            {
                public:
                    Stop(void);
            };

            class HijackMaster : public NanoPbMsg
            {
                public:
                    HijackMaster(uint32_t accessAddress);
            };

            class HijackSlave : public NanoPbMsg
            {
                public:
                    HijackSlave(uint32_t accessAddress);
            };

            class HijackBoth : public NanoPbMsg
            {
                public:
                    HijackBoth(uint32_t accessAddress);
            };
        }
    }

#endif /* _cplusplus */

#endif /* __INC_WHAD_BLE_HPP */