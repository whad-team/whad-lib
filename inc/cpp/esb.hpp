#ifndef __INC_WHAD_BLE_HPP
#define __INC_WHAD_BLE_HPP

#ifdef __cplusplus

    #include <string>
    #include <vector>
    #include "message.hpp"
    #include "../domains/esb.h"

    namespace whad
    {
        namespace esb
        {
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
            };
        }
    }

#endif /* _cplusplus */

#endif /* __INC_WHAD_BLE_HPP */