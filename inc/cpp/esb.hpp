#ifndef __INC_WHAD_BLE_HPP
#define __INC_WHAD_BLE_HPP

#ifdef __cplusplus

    #include <string>
    #include <vector>
    #include "message.hpp"
    #include "common.hpp"
    #include "../domains/esb.h"

    namespace whad
    {
        namespace esb
        {   
            typedef whad::Packet<255> Packet;

            enum MessageType {
                UnknownMsg = WHAD_ESB_UNKNOWN,
                SetNodeAddrMsg = WHAD_ESB_SET_NODE_ADDRESS,
                SniffMsg = WHAD_ESB_SNIFF,
                JamMsg = WHAD_ESB_JAM,
                SendMsg = WHAD_ESB_SEND,
                SendRawMsg = WHAD_ESB_SEND_RAW,
                PrxMsg = WHAD_ESB_PRX,
                PtxMsg = WHAD_ESB_PTX,
                StartMsg = WHAD_ESB_START,
                StopMsg = WHAD_ESB_STOP,
                JammedMsg = WHAD_ESB_JAMMED,
                RawPduReceivedMsg = WHAD_ESB_RAW_PDU_RECEIVED,
                PduReceivedMsg = WHAD_ESB_PDU_RECEIVED
            };


            class EsbAddress
            {
                private:

                    /* ESB address as a byte buffer. */
                    uint8_t m_address[5];
                    uint8_t m_size;

                public:
                    EsbAddress(void);
                    EsbAddress(uint8_t *pAddress, uint8_t size);

                    /* Getters. */
                    uint8_t *getAddressBuf(void);
                    uint8_t getLength(void);

                    /* Setters. */
                    void setAddress(uint8_t *pAddress, uint8_t size);
            };

            EsbAddress PromiscAddr;
            EsbAddress NullAddr;

            /* Default ESB message class. */
            class EsbMsg : public NanoPbMsg
            {
                public:

                    /* Constructor and destructor. */
                    EsbMsg();
                    EsbMsg(NanoPbMsg &pMessage);
                    ~EsbMsg();

                    /* Override getType() message. */
                    MessageType getType(void);
            };

            class SetNodeAddress : public EsbMsg
            {
                public:

                    /* Constructors. */
                    SetNodeAddress(EsbMsg &message);
                    SetNodeAddress(EsbAddress &address);

                    EsbAddress& getAddress();

                private:
                    EsbAddress m_address;

                    void pack();
                    void unpack();
            };

            class SniffMode : public EsbMsg
            {
                private:
                    bool parse(void);
                    uint32_t m_channel;
                    EsbAddress m_address;
                    bool m_showacks;

                public:
                    SniffMode(EsbMsg &message);
                    SniffMode();
                    SniffMode(uint32_t channel, EsbAddress &address, bool showAcks);
                    SniffMode(uint32_t channel);
                    SniffMode(uint32_t channel, EsbAddress &address);
                    SniffMode(EsbAddress &address);

                    uint32_t getChannel(void);
                    EsbAddress &getAddress(void);
                    bool mustShowAcks(void);
            };
             
            class JamMode : public EsbMsg
            {
                private:
                    bool parse(void);
                    uint32_t m_channel;

                public:
                    JamMode(EsbMsg &message);
                    JamMode(uint32_t channel);

                    uint32_t getChannel(void);
            };

            class SendPacket : public EsbMsg
            {
                protected:
                    bool parse();

                    uint32_t m_channel;
                    uint32_t m_retries;
                    Packet m_packet;

                public:
                    SendPacket(EsbMsg &message);
                    SendPacket(uint32_t channel, uint32_t retries, Packet &packet);

                    /* Getters. */
                    uint32_t getChannel();
                    uint32_t getRetrCount();
                    Packet &getPacket();
            };

            class SendPacketRaw : public SendPacket
            {
                public:
                    SendPacketRaw(EsbMsg &message);
                    SendPacketRaw(uint32_t channel, uint32_t retries, Packet &packet);

                private:
                    bool parse();
            };

            class PrxMode : public EsbMsg
            {
                public:
                    PrxMode(EsbMsg &message);
                    PrxMode(uint32_t channel);

                    uint32_t getChannel();
            };

            class PtxMode : public EsbMsg
            {
                public:
                    PtxMode(EsbMsg &message);
                    PtxMode(uint32_t channel);

                    uint32_t getChannel();
            };

            class Start : public EsbMsg
            {
                public:
                    Start(EsbMsg &message);
                    Start();
            };

            class Stop : public EsbMsg
            {
                public:
                    Stop(EsbMsg &message);
                    Stop();
            };

            class Jammed : public EsbMsg
            {
                public:
                    Jammed(EsbMsg &message);
                    Jammed(uint32_t timestamp);

                    uint32_t getTimestamp();
            };

            class RawPacketReceived : public EsbMsg
            {
                public:
                    RawPacketReceived(EsbMsg &message);
                    RawPacketReceived(uint32_t channel, Packet &packet);

                    /* Setters. */
                    void setChannel(uint32_t channel);
                    void setPacket(Packet& packet);
                    void setRssi(int32_t rssi);
                    void setTimestamp(uint32_t timestamp);
                    void setAddress(EsbAddress &address);
                    void setCrcValidity(bool validity);
                    

                    /* Getters. */
                    uint32_t getChannel();
                    bool hasRssi();
                    int32_t getRssi();
                    bool hasTimestamp();
                    uint32_t getTimestamp();
                    bool hasCrcValidity();
                    bool isCrcValid();
                    bool hasAddress();
                    EsbAddress& getAddress();
                    Packet& getPacket();


                protected:
                    void parse();
                    void update();

                    uint32_t m_channel;
                    
                    int32_t m_rssi;
                    bool m_hasRssi;
                    uint32_t m_timestamp;
                    bool m_hasTimestamp;
                    bool m_crcValidity;
                    bool m_hasCrcValidity;
                    EsbAddress m_address;
                    bool m_hasAddress;
                    Packet m_packet;
            };

            class PacketReceived : public RawPacketReceived
            {
                public:
                    /* Constructors. */
                    PacketReceived(EsbMsg &message);
                    PacketReceived(uint32_t channel, Packet &packet);

                private:
                    void parse();
                    void update();
            };
        }
    }

#endif /* _cplusplus */

#endif /* __INC_WHAD_BLE_HPP */