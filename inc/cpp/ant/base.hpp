#ifndef __INC_WHAD_ANT_HPP
#define __INC_WHAD_ANT_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/ant.h"

 

namespace whad
{
    namespace ant
    {   
        typedef whad::Packet<255> Packet;

        /*! ANT Message type */
        enum MessageType {
            UnknownMsg              = WHAD_ANT_UNKNOWN,
            SetDeviceNumberMsg      = WHAD_ANT_SET_DEVICE_NUMBER,
            SetDeviceTypeMsg        = WHAD_ANT_SET_DEVICE_TYPE,
            SetTransmissionTypeMsg  = WHAD_ANT_SET_TRANSMISSION_TYPE,
            SetChannelPeriodMsg     = WHAD_ANT_SET_CHANNEL_PERIOD,
            SetNetworkKeyMsg        = WHAD_ANT_SET_NETWORK_KEY,
            AssignChannelMsg        = WHAD_ANT_ASSIGN_CHANNEL,
            UnassignChannelMsg      = WHAD_ANT_UNASSIGN_CHANNEL,
            OpenChannelMsg          = WHAD_ANT_OPEN_CHANNEL,
            CloseChannelMsg         = WHAD_ANT_CLOSE_CHANNEL,
            SetRFChannelMsg         = WHAD_ANT_SET_RF_CHANNEL,
            SniffMsg                = WHAD_ANT_SNIFF,
            JamMsg                  = WHAD_ANT_JAM,
            SendMsg                 = WHAD_ANT_SEND,
            SendRawMsg              = WHAD_ANT_SEND_RAW,
            MasterModeMsg           = WHAD_ANT_MASTER_MODE,
            SlaveModeMsg            = WHAD_ANT_SLAVE_MODE,
            StartMsg                = WHAD_ANT_START,
            StopMsg                 = WHAD_ANT_STOP,
            ListChannelsMsg         = WHAD_ANT_LIST_CHANNELS,
            ListNetworksMsg         = WHAD_ANT_LIST_NETWORKS,
            JammedMsg               = WHAD_ANT_JAMMED,
            RawPduReceivedMsg       = WHAD_ANT_RAW_PDU_RECEIVED,
            PduReceivedMsg          = WHAD_ANT_PDU_RECEIVED, 
            AvailableChannelsMsg    = WHAD_ANT_AVAILABLE_CHANNELS,
            AvailableNetworksMsg    = WHAD_ANT_AVAILABLE_NETWORKS
        };
            
        /*! Channel type. */
        enum ChannelType {
            ReceiveOnlyChannel  = ANT_CHANNEL_TYPE_RECEIVE_ONLY_CHANNEL,
            TransmitOnlyChannel  = ANT_CHANNEL_TYPE_TRANSMIT_ONLY_CHANNEL,
            BidirectionalReceiveChannel = ANT_CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE_CHANNEL,
            BidirectionalTransmitChannel = ANT_CHANNEL_TYPE_BIDIRECTIONAL_TRANSMIT_CHANNEL, 
            SharedBidirectionalReceiveChannel = ANT_CHANNEL_TYPE_SHARED_BIDIRECTIONAL_RECEIVE_CHANNEL, 
            SharedBidirectionalTransmitChannel = ANT_CHANNEL_TYPE_SHARED_BIDIRECTIONAL_TRANSMIT_CHANNEL
        };


        /* Default ANT message class. */
        class AntMsg : public NanoPbMsg
        {
            public:

                /* Constructor and destructor. */
                AntMsg();
                AntMsg(NanoPbMsg &pMessage);
                ~AntMsg();

                /* Override getType() message. */
                MessageType getType(void);
        };
    }
}

#endif /* __INC_WHAD_ANT_HPP */