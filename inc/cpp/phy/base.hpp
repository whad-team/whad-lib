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

    /*! Modulation type. */
    enum ModulationType {
      ModulationASK  = MOD_ASK,     /*!< Amplitude-Shift Keying modulation. */
      ModulationFSK  = MOD_FSK,     /*!< Frequency Shift Keying modulation. */
      Modulation4FSK = MOD_4FSK,    /*!< Quadrature Frequency-Shift Keying modulation. */
      ModulationGFSK = MOD_GFSK,    /*!< Gaussian Frequency Shift Keying modulation. */
      ModulationMSK  = MOD_MSK,     /*!< Minimum-Shift Keying modulation. */
      ModulationBPSK = MOD_BPSK,    /*!< Binary Phase-Shift Keying modulation. */
      ModulationQPSK = MOD_QPSK,    /*!< Quadrature Phase-Shift Keying modulation. */
      ModulationLora = MOD_LORA     /*!< LoRa modulation. */
    };

    /*! PHY endianness. */
    enum Endianness {
        PhyLittleEndian = PHY_LITTLE_ENDIAN,    /*!< Little-endian. */
        PhyBigEndian = PHY_BIG_ENDIAN           /*! Big-endian. */
    };

    /*! PHY message type. */
    enum MessageType {
        UnknownMsg = WHAD_PHY_UNKNOWN,                          /*!< Unknown message. */
        SetAskModMsg = WHAD_PHY_SET_ASK_MOD,                    /*!< Set ASK modulation. */
        SetFskModMsg = WHAD_PHY_SET_FSK_MOD,                    /*!< Set FSK modulation. */
        SetGfskModMsg = WHAD_PHY_SET_GFSK_MOD,                  /*!< Set GFSK modulation. */
        SetBpskModMsg = WHAD_PHY_SET_BPSK_MOD,                  /*!< Set BPSK modulation. */
        SetQpskModMsg = WHAD_PHY_SET_QPSK_MOD,                  /*!< Set QPSK modulation. */
        Set4FskModMsg = WHAD_PHY_SET_4FSK_MOD,                  /*!< Set 4FSK modulation. */
        SetMskModMsg = WHAD_PHY_SET_MSK_MOD,                    /*!< Set MSK modulation. */
        SetLoRaModMsg = WHAD_PHY_SET_LORA_MOD,                  /*!< Set LoRa modulation. */
        GetSupportedFreqsMsg = WHAD_PHY_GET_SUPPORTED_FREQS,    /*!< Get supported frequency ranges. */
        SetFreqMsg = WHAD_PHY_SET_FREQ,                         /*!< Set interface frequency. */
        SetDatarateMsg = WHAD_PHY_SET_DATARATE,                 /*!< Set interface datarate. */
        SetEndiannessMsg = WHAD_PHY_SET_ENDIANNESS,             /*!< Set packet endianness. */
        SetTxPowerMsg = WHAD_PHY_SET_TX_POWER,                  /*!< Set transmitting power. */
        SetPacketSizeMsg = WHAD_PHY_SET_PACKET_SIZE,            /*!< Set packet size. */
        SetSyncWordMsg = WHAD_PHY_SET_SYNC_WORD,                /*!< Set synchronization word. */
        SetSniffModeMsg = WHAD_PHY_SET_SNIFF_MODE,              /*!< Set interface in sniffing mode. */
        SendMsg = WHAD_PHY_SEND,                                /*!< Send PDU. */
        SendRawMsg = WHAD_PHY_SEND_RAW,                         /*!< Send raw PDU. */
        StartMsg = WHAD_PHY_START,                              /*!< Start current mode. */
        StopMsg = WHAD_PHY_STOP,                                /*!< Stop current mode. */
        SetJamModeMsg = WHAD_PHY_SET_JAM_MODE,                  /*!< Set interface in jamming mode. */
        SetMonitorModeMsg = WHAD_PHY_SET_MONITOR_MODE,          /*!< Set interface in monitoring mode. */
        PacketReceivedMsg = WHAD_PHY_PACKET_RECEIVED,           /*!< PDU received notification. */
        RawPacketReceivedMsg = WHAD_PHY_RAW_PACKET_RECEIVED,    /*!< Raw PDU received notification. */
        JammedMsg = WHAD_PHY_JAMMED,                            /*!< Jamming result notification. */
        MonitorReportMsg = WHAD_PHY_MONITOR_REPORT,             /*!< Monitoring report. */
        SupportedFreqsMsg = WHAD_PHY_SUPPORTED_FREQS,           /*!< Supported frequency ranges. */
        SendSchedPacketMsg = WHAD_PHY_SEND_SCHED_PACKET,        /*!< Schedule a PDU for transmission. */
        SchedPacketRespMsg = WHAD_PHY_SCHED_PACKET_RESP,        /*!< Schedule response. */
        SchedPacketSentMsg = WHAD_PHY_SCHED_PACKET_SENT         /*!< Scheduled PDU sent notification. */
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
