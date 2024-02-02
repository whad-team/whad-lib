#include "cpp/phy.hpp"

using namespace whad::phy;

/********************************
 * PHY message base class
 *******************************/

/**
 * @brief   PHY message base class.
 **/

whad::phy::PhyMsg::PhyMsg() : NanoPbMsg()
{
}


/**
 * @brief       PHY message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a PHY domain message 
 **/

whad::phy::PhyMsg::PhyMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   PHY message base class destructor.
 **/

whad::phy::PhyMsg::~PhyMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming PHY domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      PHY message type.
 **/

whad::phy::MessageType whad::phy::PhyMsg::getType(void)
{
    whad::phy::MessageType msgType = (whad::phy::MessageType)whad_phy_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}


/********************************
 * PHY helper classes
 *******************************/

SyncWord::SyncWord(uint8_t *syncword, uint8_t size)
{
    if (size <= 10)
    {
        memcpy(this->m_syncword, syncword, size);
        this->m_size = size;
    }
}

uint8_t *SyncWord::get()
{
    return this->m_syncword;
}

uint8_t SyncWord::getSize()
{
    return this->m_size;
}


/**
 * @brief       Create a timestamp with a precision to the microsecond
 * 
 * @param[in]   sec     Number of seconds
 * @param[in]   usec    Number of microseconds
 */

Timestamp::Timestamp(uint32_t sec, uint32_t usec)
{
    this->m_sec = sec;
    this->m_usec = usec;
}


/**
 * @brief   Get the number of seconds from a timestamp.
 * 
 * @retval  Number of seconds
 */

uint32_t Timestamp::getSeconds()
{
    return this->m_sec;
}


/**
 * @brief   Get the number of microseconds from a timestamp.
 * 
 * @retval  Number of microseconds
 */

uint32_t Timestamp::getMicroseconds()
{
    return this->m_usec;
}

/********************************
 * PHY messages classes
 *******************************/


/**
 * @brief       Create a SupportedFreqs message with the provided frequency ranges.
 * 
 * @param[in]   pFreqRanges     Pointer to an array containing the supported frequency ranges
 * @param[in]   nRanges         Number of supported frequency ranges
 **/

SupportedFreqsResp::SupportedFreqsResp(const whad_phy_frequency_range_t *pFreqRanges) : PhyMsg()
{
    int nRanges = 0;

    /* Count ranges (last range must be {0,0}). */
    for (nRanges=0; (pFreqRanges[nRanges].start != 0) && (pFreqRanges[nRanges].end != 0); nRanges++);

    whad_phy_supported_frequencies(
        this->getRaw(),
        (whad_phy_frequency_range_t *)pFreqRanges,
        nRanges
    );
}


/**
 * @brief       parse a supported frequency ranges message
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SupportedFreqsResp::SupportedFreqsResp(NanoPbMsg &message) : PhyMsg(message)
{
}


/** ASK modulation **/

/**
 * @brief       Create a SetAskMod message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetAskMod::SetAskMod(whad::NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetAskMod message.
 * 
 * @param[in]   ook     On/Off keying is enabled if set to true, disabled otherwise.
 **/

SetAskMod::SetAskMod(bool ook) : PhyMsg()
{
    whad_phy_set_ask_mod(
        this->getRaw(),
        ook
    );
}


/**
 * @brief       Determine if OnOff keying is enabled or not.
 * 
 * @retval      OOK is enabled if true, disabled otherwise.
 **/

bool SetAskMod::isOok()
{
    bool bIsOok = false;

    /* Parse message and extract OOK parameter. */
    whad_phy_set_ask_mod_parse(this->getRaw(), &bIsOok);
    return bIsOok;
}

/** FSK modulation **/

/**
 * @brief   Create a SetFskMod message from a NanoPbMessage.
 * 
 * @param[in]   message     NanoPb message
 */

SetFskMod::SetFskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a SetFskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 */

SetFskMod::SetFskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_fsk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief   Get the current deviation from a SetFskMod message.
 * 
 * @retval  Deviation in Hz.
 */

uint32_t SetFskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_fsk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}

/** 4FSK modulation **/

/**
 * @brief   Create a Set4FskMod message from a NanoPbMessage.
 * 
 * @param[in]   message     NanoPb message
 */

Set4FskMod::Set4FskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a Set4FskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 */

Set4FskMod::Set4FskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_4fsk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief   Get the current deviation from a Set4FskMod message.
 * 
 * @retval  Deviation in Hz.
 */

uint32_t Set4FskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_4fsk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}


/** GFSK modulation **/


/**
 * @brief   Create a SetGfskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetGfskMod::SetGfskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetGfskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 **/

SetGfskMod::SetGfskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_gfsk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief       Get the deviation
 * 
 * @retval      GFSK deviation in Hz
 **/

uint32_t SetGfskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_gfsk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}


/** BPSK modulation **/


/**
 * @brief   Create a SetBpskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetBpskMod::SetBpskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a SetBpskMod message.
 **/

SetBpskMod::SetBpskMod()
{
}


/** QPSK modulation **/


/**
 * @brief   Create a SetQpskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetQpskMod::SetQpskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetQpskMod message with a specific offset.
 * 
 * @param[in]   offset  Modulation offset
 **/

SetQpskMod::SetQpskMod(bool offset) : PhyMsg()
{
    whad_phy_set_qpsk_mod(
        this->getRaw(),
        offset
    );
}


/**
 * @brief       Get modulation offset.
 * 
 * @retval      Modulation offset
 **/

bool SetQpskMod::getOffset()
{
    bool offset = false;

    whad_phy_set_qpsk_mod_parse(
        this->getRaw(),
        &offset
    );

    return offset;
}


/** MSK modulation **/


/**
 * @brief       Create a SetMskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetMskMod::SetMskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetMskMod message with a specific deviation.
 * 
 * @param[in]   deviation   Deviation in Hz
 **/

SetMskMod::SetMskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_msk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief       Get current deviation.
 * 
 * @retval      Deviation in Hz
 **/

uint32_t SetMskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_msk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}


/** LoRa modulation **/


/**
 * @brief       Create a SetLoraMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetLoraMod::SetLoraMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetLoraMod message with specific parameters.
 * 
 * @param[in]   bandwidth       Modulation bandwidth in Hz
 * @param[in]   sf              Spreading factor
 * @param[in]   cr              Coding rate
 * @param[in]   enableCrc       If true, CRC will be enabled and checked by the hardware
 * @param[in]   preambleLength  Length of preamble, in number of symbols
 * @param[in]   explicitMode    If true, set explicit mode
 * @param[in]   invertIq        If true, invert I/Q (used in downstream channels)
 **/

SetLoraMod::SetLoraMod(uint32_t bandwidth, LoRaSpreadingFactor sf,
                               LoRaCodingRate cr, uint32_t preambleLength,
                               bool enableCrc, bool explicitMode, bool invertIq) : PhyMsg()
{
    whad_phy_set_lora_mod(
        this->getRaw(),
        bandwidth,
        (whad_phy_lora_sf_t)sf,
        (whad_phy_lora_cr_t)cr,
        preambleLength,
        enableCrc, explicitMode, invertIq
    );
}


/**
 * @brief       Parse the current message and extract its parameters.
 * 
 * @retval      True if parsing has been correctly performed, false otherwise.
 **/

bool SetLoraMod::parse()
{
    if (whad_phy_set_lora_mod_parse(this->getRaw(), &this->m_params) == WHAD_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * @brief       Get the message bandwidth modulation parameter
 * 
 * @retval      Bandwidth in Hz.
 **/

uint32_t SetLoraMod::getBandwidth()
{
    if (this->parse())
    {
        return this->m_params.bandwidth;
    }
    
    /* Error. */
    return 0;
}


/**
 * @brief       Get the message preamble length parameter.
 * 
 * @retval      Preamble length in number of symbols.
 **/

uint32_t SetLoraMod::getPreambleLength()
{
    if (this->parse())
    {
        return this->m_params.preamble_length;
    }
    
    /* Error. */
    return 0;
}


/**
 * @brief       Get the message spreading factor parameter.
 * 
 * @retval      Spreading factor
 **/

LoRaSpreadingFactor SetLoraMod::getSpreadingFactor()
{
    if (this->parse())
    {
        return (LoRaSpreadingFactor)this->m_params.sf;
    }

    /* Error. */
    return LoraSfError;
}


/**
 * @brief       Get the message coding rate parameter.
 * 
 * @retval      Coding rate
 **/

LoRaCodingRate SetLoraMod::getCodingRate()
{
    if (this->parse())
    {
        return (LoRaCodingRate)this->m_params.cr;
    }

    /* Error. */
    return LoraCrError; 
}


/**
 * @brief       Determine if CRC is enabled.
 * 
 * @retval      True if CRC should be enabled, false otherwise.
 **/

bool SetLoraMod::isCrcEnabled()
{
    if (this->parse())
    {
        return this->m_params.enable_crc;
    }

    /* Error. */
    return false;
}


/**
 * @brief       Determine if explicit mode is enabled.
 * 
 * @retval      True if explicit mode should be enabled, false otherwise.
 **/

bool SetLoraMod::isExplicitMode()
{
    if (this->parse())
    {
        return this->m_params.explicit_mode;
    }

    /* Error. */
    return false;
}


/**
 * @brief       Determine if IQ inversion is enabled.
 * 
 * @retval      True if IQ inversion should be enabled, false otherwise.
 **/

bool SetLoraMod::isIqInverted()
{
    if (this->parse())
    {
        return this->m_params.invert_iq;
    }

    /* Error. */
    return false;
}



/** Set frequency **/

/**
 * @brief       Create a SetFreq message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetFreq::SetFreq(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetFreq message with a specific frequency
 * 
 * @param[in]   frequency   Frequency in Hz
 **/

SetFreq::SetFreq(uint32_t frequency) : PhyMsg()
{
    whad_phy_set_freq(
        this->getRaw(),
        frequency
    );
}


/**
 * @brief       Get the frequency specified in this message
 * 
 * @retval      Frequency in Hz
 **/

uint32_t SetFreq::getFrequency()
{
    uint32_t freq = 0;

    whad_phy_set_freq_parse(
        this->getRaw(),
        &freq
    );

    return freq;
}


/** Set datarate **/

/**
 * @brief       Create a SetDatarate message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetDatarate::SetDatarate(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetDatarate message with specific data rate
 * 
 * @param[in]   datarate    Data rate to use in bits/second
 **/

SetDatarate::SetDatarate(uint32_t datarate)
{
    whad_phy_set_datarate(
        this->getRaw(),
        datarate
    );
}


/**
 * @brief       Get the data rate specified in this message
 * 
 * @retval      Datarate in bits/second
 **/

uint32_t SetDatarate::getDatarate()
{
    uint32_t datarate = 0;

    whad_phy_set_datarate_parse(
        this->getRaw(),
        &datarate
    );

    return datarate;
}


/** Set endianness **/

/**
 * @brief       Create a SetEndianness message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetEndianness::SetEndianness(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetEndianness message with specific endianness
 * 
 * @param[in]   endian  Endianness to use
 **/

SetEndianness::SetEndianness(Endianness endian) : PhyMsg()
{
    whad_phy_set_endianness(
        this->getRaw(),
        (whad_phy_endian_t)endian
    );
}


/**
 * @brief       Get the endianness specified in this message
 * 
 * @retval      Endianness to use
 **/

Endianness SetEndianness::getEndianness()
{
    whad_phy_endian_t endian;

    whad_phy_set_endianness_parse(
        this->getRaw(),
        &endian
    );

    return (Endianness)endian;
}


/** Set Tx power **/

/**
 * @brief       Create a SetTxPower message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetTxPower::SetTxPower(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetTxPower message with a specific power level.
 * 
 * @param[in]   power   Power level to use
 **/

SetTxPower::SetTxPower(TxPower power) : PhyMsg()
{
    whad_phy_set_tx_power(
        this->getRaw(),
        (whad_phy_txpower_t)power
    );
}


/**
 * @brief       Get the specified power level
 * 
 * @retval      Power level specified in this message
 **/

TxPower SetTxPower::getPower()
{
    whad_phy_txpower_t power;

    whad_phy_set_tx_power_parse(
        this->getRaw(),
        &power
    );

    return (TxPower)power;
}


/** Set Packet size **/

/**
 * @brief       Create a SetPacketSize message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetPacketSize::SetPacketSize(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetPacketSize message with a specific size
 * 
 * @param[in]   size     Packet size to use, in bytes
 **/

SetPacketSize::SetPacketSize(uint32_t size) : PhyMsg()
{
    whad_phy_set_packet_size(
        this->getRaw(),
        size
    );
}


/**
 * @brief       Get the specified packet size
 * 
 * @retval      Packet size specified, in bytes
 **/

uint32_t SetPacketSize::getSize()
{
    uint32_t size = 0;

    whad_phy_set_packet_size_parse(
        this->getRaw(),
        &size
    );

    return size;
}


/** Set Sync word **/

/**
 * @brief       Create a SetSyncWord message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetSyncWord::SetSyncWord(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetSyncWord message from a specified synchronization word.
 * 
 * @param[in]   syncWord    Synchronization word to use
 **/

SetSyncWord::SetSyncWord(SyncWord &syncWord) : PhyMsg()
{
    whad_phy_set_sync_word(
        this->getRaw(),
        syncWord.get(),
        syncWord.getSize()
    );
}


/**
 * @brief       Get the specified synchronization word
 * 
 * @retval      Synchronization word in use
 **/

SyncWord SetSyncWord::get()
{
    whad_phy_syncword_t syncword;

    whad_phy_set_sync_word_parse(
        this->getRaw(),
        &syncword
    );

    return SyncWord(syncword.syncword, syncword.length);
}


/** Sniff mode **/

/**
 * @brief       Create a SniffMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SniffMode::SniffMode(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SniffMode message.
 * 
 * @param[in]   iqMode  If set to true, will sniff IQ samples otherwise will sniff packets.
 **/

SniffMode::SniffMode(bool iqMode) : PhyMsg()
{
    whad_phy_sniff_mode(
        this->getRaw(),
        iqMode
    );
}

/**
 * @brief       Determine if IQ sniffing mode is enabled.
 * 
 * @retval      True if IQ sniffing is enabled, false otherwise.
 **/

bool SniffMode::isIqModeEnabled()
{
    bool enabled = false;

    whad_phy_sniff_mode_parse(
        this->getRaw(),
        &enabled
    );

    return enabled;
}


/** jam mode **/

/**
 * @brief       Create a JamMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

JamMode::JamMode(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a JamMode message with specified mode.
 * 
 * @param[in]   mode    Jamming mode to use
 **/

JamMode::JamMode(JammingMode mode) : PhyMsg()
{
    whad_phy_jam_mode(
        this->getRaw(),
        (whad_phy_jam_mode_t)mode
    );
}


/**
 * @brief       Get the specified jamming mode
 * 
 * @param[in]   mode    Jamming mode to use
 **/

JammingMode JamMode::getMode()
{
    whad_phy_jam_mode_t mode = PHY_JAM_MODE_CONTINUOUS;

    whad_phy_jam_mode_parse(
        this->getRaw(),
        &mode
    );

    return (JammingMode)mode;
}


/** Monitor mode **/

/**
 * @brief       Create a MonitorMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

MonitorMode::MonitorMode(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a MonitorMode message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

MonitorMode::MonitorMode() : PhyMsg()
{
    whad_phy_monitor_mode(
        this->getRaw()
    );
}


/** Start **/

/**
 * @brief       Create a Start message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Start::Start(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Start message.
 **/

Start::Start() : PhyMsg()
{
    whad_phy_start(this->getRaw());
}

/** Stop **/

/**
 * @brief       Create a Stop message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Stop::Stop(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Stop message.
 **/

Stop::Stop() : PhyMsg()
{
    whad_phy_stop(this->getRaw());
}


/** Send Packet **/

/**
 * @brief       Create a SendPacket message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SendPacket::SendPacket(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SendPacket message from a packet
 * 
 * @param[in]   packet  Packet to send
 **/

SendPacket::SendPacket(Packet &packet) : PhyMsg()
{
    whad_phy_send(
        this->getRaw(),
        packet.getBytes(),
        packet.getSize()
    );
}


/**
 * @brief       Get the packet to send
 * 
 * @retval      Packet object to send
 **/

Packet SendPacket::getPacket()
{
    memset(this->m_packet.payload, 0, sizeof(this->m_packet.payload));

    whad_phy_send_parse(
        this->getRaw(),
        &this->m_packet
    );

    return Packet(this->m_packet.payload, this->m_packet.length);
}


/** Schedule Packet **/

/**
 * @brief       Create a SchedulePacket message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SchedulePacket::SchedulePacket(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SchedulePacket message from timestamp and packet.
 * 
 * @param[in]   packet      Packet to schedule
 * @param[in]   timestamp   Timerstamp at which the provided packet must be sent
 **/

SchedulePacket::SchedulePacket(Packet &packet, Timestamp &timestamp) : PhyMsg()
{
    whad_phy_sched_packet(
        this->getRaw(),
        packet.getBytes(),
        packet.getSize(),
        timestamp.getSeconds(),
        timestamp.getMicroseconds()
    );
}


/**
 * @brief       Get the scheduled packet object
 * 
 * @retval      Scheduled packet
 **/

Packet SchedulePacket::getPacket()
{
    whad_phy_sched_packet_t sched_packet;

    whad_phy_sched_packet_parse(
        this->getRaw(),
        &sched_packet
    );

    return Packet(sched_packet.packet.payload, sched_packet.packet.length);
}


/**
 * @brief       Get the scheduled packet timestamp object
 * 
 * @retval      Scheduled packet timestamp
 **/

Timestamp SchedulePacket::getTimestamp()
{
    whad_phy_sched_packet_t sched_packet;

    whad_phy_sched_packet_parse(
        this->getRaw(),
        &sched_packet
    );

    return Timestamp(sched_packet.ts.ts_sec, sched_packet.ts.ts_usec);    
}


/** Jammed notification **/

/**
 * @brief       Create a Jammed message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

Jammed::Jammed(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a Jammed message with its associated timestamp.
 * 
 * @param[in]   timestamp   Timestamp at which the target has been successfully jammed
 **/

Jammed::Jammed(Timestamp &timestamp) : PhyMsg()
{
    whad_phy_jammed(
        this->getRaw(),
        timestamp.getSeconds(),
        timestamp.getMicroseconds()
    );
}


/**
 * @brief       Get message timestamp.
 * 
 * @param[in]   timestamp   Timestamp at which the target has been successfully jammed
 **/

Timestamp Jammed::getTimestamp()
{
    whad_phy_timestamp_t timestamp;

    whad_phy_jammed_parse(
        this->getRaw(),
        &timestamp
    );

    return Timestamp(timestamp.ts_sec, timestamp.ts_usec);
}


/** Received packet notification **/

/**
 * @brief       Create a PacketReceived message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

PacketReceived::PacketReceived(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a PacketReceived message with corresponding parameters.
 * 
 * @param[in]   frequency   Frequency on which this packet has been received
 * @param[in]   rssi        Received signal strength indicator
 * @param[in]   ts          Timestamp at which the packet has been received
 * @param[in]   packet      Packet received
 **/

PacketReceived::PacketReceived(uint32_t frequency, int32_t rssi, Timestamp &ts, Packet &packet)
{
    whad_phy_packet_received(
        this->getRaw(),
        frequency,
        rssi,
        ts.getSeconds(),
        ts.getMicroseconds(),
        packet.getBytes(),
        packet.getSize()
    );
}


/**
 * @brief       Parse the current message.
 * 
 * @retval      True if parsing is OK, false otherwise.
 **/

bool PacketReceived::parse()
{
    return (whad_phy_packet_received_parse(this->getRaw(), &this->m_packet) == WHAD_SUCCESS);
}


/**
 * @brief       Get the frequency parameter
 * 
 * @retval      Frequency in Hz
 **/

uint32_t PacketReceived::getFrequency()
{
    if (this->parse())
    {
        return this->m_packet.freq;
    }

    return 0;
}


/**
 * @brief       Get the RSSI parameter
 * 
 * @retval      Received signal strength indicator
 **/

int32_t PacketReceived::getRssi()
{
    if (this->parse())
    {
        return this->m_packet.rssi;
    }

    return 0;   
}


/**
 * @brief       Get the timetamp parameter
 * 
 * @retval      Timestamp at which the packet has been received
 **/

Timestamp PacketReceived::getTimestamp()
{
    if (this->parse())
    {
        return Timestamp(this->m_packet.ts.ts_sec, this->m_packet.ts.ts_usec);
    }

    return Timestamp(0,0);
}


/**
 * @brief       Get the received packet
 * 
 * @retval      Instance of Packet representing the received packet
 **/

Packet PacketReceived::getPacket()
{
    if (this->parse())
    {
        return Packet(this->m_packet.packet.payload, this->m_packet.packet.length);
    }
    else
    {
        /* Throw parsing error. */
        throw WhadMessageParsingError();
    }
}


/** Scheduled packet notification **/

/**
 * @brief       Create a PacketScheduled message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

PacketScheduled::PacketScheduled(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a PacketScheduled message with specific packet ID.
 * 
 * @param[in]   packetId    Packet identifier
 * @param[in]   full        Set to true to indicate the scheduled packets list is full.
 **/

PacketScheduled::PacketScheduled(uint8_t packetId, bool full) : PhyMsg()
{
    whad_phy_packet_scheduled(
        this->getRaw(), packetId, full
    );
}


/**
 * @brief       Parse the current message.
 * 
 * @retval      True if parsing is OK, false otherwise.
 **/

bool PacketScheduled::parse()
{
    return (whad_phy_packet_scheduled_parse(this->getRaw(), &this->m_packet) == WHAD_SUCCESS);
}


/**
 * @brief       Get the packet identifier.
 * 
 * @retval      Packet identifier
 **/

uint8_t PacketScheduled::getPacketId()
{
    if (this->parse())
    {
        return this->m_packet.id;
    }

    return 0;
}


/**
 * @brief       Determine if the scheduled packets list is full.
 * 
 * @retval      True if list is full, false otherwise.
 **/

bool PacketScheduled::isFull()
{
    if (this->parse())
    {
        return this->m_packet.full;
    }

    return false;
}


/** Scheduled packet sent notification **/


/**
 * @brief       Create a ScheduledPacketSent message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

ScheduledPacketSent::ScheduledPacketSent(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a ScheduledPacketSent message with a specific packet ID.
 * 
 * @param[in]   packetId    Packet identifier.
 **/

ScheduledPacketSent::ScheduledPacketSent(uint32_t packetId) : PhyMsg()
{
    whad_phy_sched_packet_sent(this->getRaw(), packetId);
}


/**
 * @brief       Get message packet ID.
 * 
 * @retval      Packet ID
 **/

uint32_t ScheduledPacketSent::getPacketId()
{
    uint32_t packetId = 0;

    whad_phy_sched_packet_sent_parse(this->getRaw(), &packetId);

    return packetId;
}