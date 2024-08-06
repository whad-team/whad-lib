#ifndef __INC_WHAD_PHY_BASE_HPP
#define __INC_WHAD_PHY_BASE_HPP

#include <string>
#include <vector>
#include "message.hpp"
#include "common.hpp"
#include "../domains/phy.h"
#include <phy/syncword.hpp>
#include <phy/timestamp.hpp>

namespace whad::phy {

    typedef whad::Packet<255> Packet;

    enum ModulationType {
      ModulationASK  = MOD_ASK,
      ModulationFSK  = MOD_FSK,
      Modulation4FSK = MOD_4FSK,
      ModulationGFSK = MOD_GFSK,
      ModulationMSK  = MOD_MSK,
      ModulationBPSK = MOD_BPSK,
      ModulationQPSK = MOD_QPSK,
      ModulationLora = MOD_LORA
    };

    enum Endianness {
        PhyLittleEndian = PHY_LITTLE_ENDIAN,
        PhyBigEndian = PHY_BIG_ENDIAN
    };
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

    class PhyMsg : public NanoPbMsg
    {
        public:

            /* Constructor and destructor. */
            PhyMsg();
            PhyMsg(NanoPbMsg &pMessage);
            ~PhyMsg();

            /* Override getType() message. */
            whad::phy::MessageType getType(void);
    };
}

#endif /* __INC_WHAD_PHY_BASE_HPP */
