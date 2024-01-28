#ifndef __INC_WHAD_PHY_HPP
#define __INC_WHAD_PHY_HPP

#ifdef __cplusplus

    #include <string>
    #include <vector>
    #include "message.hpp"
    #include "../domains/phy.h"

    namespace whad
    {
        namespace phy
        {
            enum MessageType {
                UnknownMsg = WHAD_PHY_UNKNOWN,
                SetAskModMsg = WHAD_PHY_SET_ASK_MOD,
                SetFskModMsg = WHAD_PHY_SET_FSK_MOD,
                SetGfskModMsg = WHAD_PHY_SET_GFSK_MOD,
                SetBpskModMsg = WHAD_PHY_SET_BPSK_MOD,
                SetQpskModMsg = WHAD_PHY_SET_QPSK_MOD,
                Set4FskModMsg = WHAD_PHY_SET_4FSK_MOD,
                SetMskModMsg = WHAD_PHY_SET_MSK_MOD,
                SetLoRaModMsg = WHAD_PHY_SET_LORA_MOD,
                GetSupportedFreqsMsg = WHAD_PHY_GET_SUPPORTED_FREQS,
                SetFreqMsg = WHAD_PHY_SET_FREQ,
                SetDatarateMsg = WHAD_PHY_SET_DATARATE,
                SetEndiannessMsg = WHAD_PHY_SET_ENDIANNESS,
                SetTxPowerMsg = WHAD_PHY_SET_TX_POWER,
                SetPacketSizeMsg = WHAD_PHY_SET_PACKET_SIZE,
                SetSyncWordMsg = WHAD_PHY_SET_SYNC_WORD,
                SetSniffModeMsg = WHAD_PHY_SET_SNIFF_MODE,
                SendMsg = WHAD_PHY_SEND,
                SendRawMsg = WHAD_PHY_SEND_RAW,
                StartMsg = WHAD_PHY_START,
                StopMsg = WHAD_PHY_STOP,
                SetJamModeMsg = WHAD_PHY_SET_JAM_MODE,
                SetMonitorModeMsg = WHAD_PHY_SET_MONITOR_MODE,
                PacketReceivedMsg = WHAD_PHY_PACKET_RECEIVED,
                RawPacketReceivedMsg = WHAD_PHY_RAW_PACKET_RECEIVED,
                JammedMsg = WHAD_PHY_JAMMED,
                MonitorReportMsg = WHAD_PHY_MONITOR_REPORT,
                SupportedFreqsMsg = WHAD_PHY_SUPPORTED_FREQS,
                SendSchedPacketMsg = WHAD_PHY_SEND_SCHED_PACKET,
                SchedPacketRespMsg = WHAD_PHY_SCHED_PACKET_RESP,
                SchedPacketSentMsg = WHAD_PHY_SCHED_PACKET_SENT
            };

            enum LoRaSpreadingFactor {
                LoraSfError = -1,
                LoraSf7 = PHY_LORA_SF7,
                LoraSf8 = PHY_LORA_SF8,
                LoraSf9 = PHY_LORA_SF9,
                LoraSf10 = PHY_LORA_SF10,
                LoraSf11 = PHY_LORA_SF11,
                LoraSf12 = PHY_LORA_SF12
            };

            enum LoRaCodingRate {
                LoraCrError = -1,
                LoraCr45 = PHY_LORA_CR45,
                LoraCr46 = PHY_LORA_CR46,
                LoraCr47 = PHY_LORA_CR47,
                LoraCr48 = PHY_LORA_CR48
            };

            enum Endianness {
                PhyLittleEndian = PHY_LITTLE_ENDIAN,
                PhyBigEndian = PHY_BIG_ENDIAN
            };

            enum TxPower {
                PhyTxPowerLow = PHY_TXPOWER_LOW,
                PhyTxPowerMedium = PHY_TXPOWER_MEDIUM,
                PhyTxPowerHigh = PHY_TXPOWER_HIGH
            };

            enum JammingMode {
                PhyContinuousJamming = PHY_JAM_MODE_CONTINUOUS,
                PhyReactiveJamming = PHY_JAM_MODE_REACTIVE
            };

            /* Default PHY helper classes. */

            class SyncWord 
            {
                public:
                    SyncWord(uint8_t *syncword, uint8_t size);

                    uint8_t *get();
                    uint8_t getSize();

                private:
                    uint8_t m_syncword[10];
                    uint8_t m_size;
            };

            class Packet
            {
                private:
                    int m_length;
                    uint8_t *m_buf;
                
                public:
                    Packet(int length);
                    Packet(uint8_t *bytes, int length);
                    uint8_t *getBuf();
                    int getLength();
                    ~Packet();
            };

            class Timestamp
            {
                public:
                    Timestamp(uint32_t sec, uint32_t usec);

                    uint32_t getSeconds();
                    uint32_t getMicroseconds();

                private:
                    uint32_t m_sec;
                    uint32_t m_usec;
            };

            /* Default PHY message class. */

            class PhyMsg : public NanoPbMsg
            {
                public:

                    /* Constructor and destructor. */
                    PhyMsg();
                    PhyMsg(NanoPbMsg pMessage);
                    ~PhyMsg();

                    /* Override getType() message. */
                    whad::phy::MessageType getType(void);
            };

            class SupportedFreqsResp : public PhyMsg
            {
                public:
                    SupportedFreqsResp(NanoPbMsg message);
                    SupportedFreqsResp(const whad_phy_frequency_range_t *pFreqRanges);

                    //whad_phy_frequency_range_t *getFreqRanges();
            };

            class SetAskMod : public PhyMsg
            {
                public:
                    SetAskMod(NanoPbMsg message);
                    SetAskMod(bool ook);

                    bool isOok();
            };

            class SetFskMod : public PhyMsg
            {
                public:
                    SetFskMod(NanoPbMsg message);
                    SetFskMod(uint32_t deviation);

                    uint32_t getDeviation();
            };

            class Set4FskMod : public PhyMsg
            {
                public:
                    Set4FskMod(NanoPbMsg message);
                    Set4FskMod(uint32_t deviation);

                    uint32_t getDeviation();
            };

            class SetGfskMod : public PhyMsg
            {
                public:
                    SetGfskMod(NanoPbMsg message);
                    SetGfskMod(uint32_t deviation);

                    uint32_t getDeviation();
            };

            class SetBpskMod : public PhyMsg
            {
                public:
                    SetBpskMod(NanoPbMsg message);
                    SetBpskMod();
            };

            class SetQpskMod : public PhyMsg
            {
                public:
                    SetQpskMod(NanoPbMsg message);
                    SetQpskMod(bool offset);

                    bool getOffset();
            };

            class SetMskMod : public PhyMsg
            {
                public:
                    SetMskMod(NanoPbMsg message);
                    SetMskMod(uint32_t deviation);

                    uint32_t getDeviation();
            };

            class SetLoraMod : public PhyMsg
            {
                public:
                    SetLoraMod(NanoPbMsg message);
                    SetLoraMod(uint32_t bandwidth, LoRaSpreadingFactor sf,
                               LoRaCodingRate cr, uint32_t preambleLength,
                               bool enableCrc, bool explicitMode, bool invertIq);

                    uint32_t getBandwidth();
                    uint32_t getPreambleLength();
                    LoRaSpreadingFactor getSpreadingFactor();
                    LoRaCodingRate getCodingRate();
                    bool isCrcEnabled();
                    bool isExplicitMode();
                    bool isIqInverted();

                private:
                    bool parse();
                    whad_phy_lora_params_t m_params;
            };

            class SetFreq : public PhyMsg
            {
                public:
                    SetFreq(NanoPbMsg message);
                    SetFreq(uint32_t frequency);

                    uint32_t getFrequency();
            };

            class SetDatarate : public PhyMsg
            {
                public:
                    SetDatarate(NanoPbMsg message);
                    SetDatarate(uint32_t datarate);

                    uint32_t getDatarate();
            };

            class SetEndianness : public PhyMsg
            {
                public:
                    SetEndianness(NanoPbMsg message);
                    SetEndianness(Endianness endian);

                    Endianness getEndianness();
            };

            class SetTxPower : public PhyMsg
            {
                public:
                    SetTxPower(NanoPbMsg message);
                    SetTxPower(TxPower power);

                    TxPower getPower();
            };

            class SetPacketSize : public PhyMsg
            {
                public:
                    SetPacketSize(NanoPbMsg message);
                    SetPacketSize(uint32_t size);

                    uint32_t getSize();
            };

            class SetSyncWord : public PhyMsg
            {
                public:

                    SetSyncWord(NanoPbMsg message);
                    SetSyncWord(SyncWord syncWord);

                    SyncWord get();
            };

            class SniffMode : public PhyMsg
            {
                public:

                    SniffMode(NanoPbMsg message);
                    SniffMode(bool iqMode);

                    bool isIqModeEnabled();
            };

            class JamMode : public PhyMsg
            {
                public:
                    JamMode(NanoPbMsg message);
                    JamMode(JammingMode);

                    JammingMode getMode();
            };

            class MonitorMode : public PhyMsg
            {
                public:
                    MonitorMode(NanoPbMsg message);
                    MonitorMode();
            };

            class Start : public PhyMsg
            {
                public:
                    Start(NanoPbMsg message);
                    Start();
            };

            class Stop : public PhyMsg
            {
                public:
                    Stop(NanoPbMsg message);
                    Stop();
            };

            class SendPacket : public PhyMsg
            {
                public:
                    SendPacket(NanoPbMsg message);
                    SendPacket(Packet packet);

                    Packet getPacket();
                
                private:
                    whad_phy_packet_t m_packet;
            };

            class SchedulePacket : public PhyMsg
            {
                public:
                    SchedulePacket(NanoPbMsg message);
                    SchedulePacket(Packet packet, Timestamp timestamp);

                    Packet getPacket();
                    Timestamp getTimestamp();
            };

            class Jammed : public PhyMsg
            {
                public:
                    Jammed(NanoPbMsg message);
                    Jammed(Timestamp timestamp);

                    Timestamp getTimestamp();
            };

            class PacketReceived : public PhyMsg
            {
                public:
                    PacketReceived(NanoPbMsg message);
                    PacketReceived(uint32_t frequency, int32_t rssi, Timestamp ts, Packet packet);

                    uint32_t getFrequency();
                    int32_t getRssi();
                    Timestamp getTimestamp();
                    Packet getPacket();

                private:
                    bool parse();
                    whad_phy_received_packet_t m_packet;
            };

            class PacketScheduled : public PhyMsg
            {
                public:
                    PacketScheduled(NanoPbMsg message);
                    PacketScheduled(uint8_t packetId, bool full);

                    uint8_t getPacketId();
                    bool isFull();

                private:
                    bool parse();
                    whad_phy_scheduled_packet_t m_packet;
            };

            class ScheduledPacketSent : public PhyMsg
            {
                public:
                    ScheduledPacketSent(NanoPbMsg message);
                    ScheduledPacketSent(uint32_t packetId);

                    uint32_t getPacketId();
            };
        }
    }

#endif /* __cplusplus */
#endif /* __INC_WHAD_PHY_HPP */