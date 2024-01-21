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

whad::phy::PhyMsg::PhyMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
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
 * @brief       Build an empty packet with a specific length
 * 
 * @param[in]   length          PDU length
 **/

Packet::Packet(int length)
{
    /* Allocate a new buffer. */
    this->m_length = length;
    if (this->m_length > 0)
    {
        this->m_buf = new uint8_t[length];
    }
    else
    {
        this->m_buf = NULL;
    }
}


/**
 * @brief       Build a packet with a specific length and fill with the provided bytes
 *
 * @param[in]   bytes           PDU bytes (byte array)
 * @param[in]   length          PDU length
 **/

Packet::Packet(uint8_t *bytes, int length) : Packet(length)
{
    /* Allocate a new buffer. */
    memcpy(this->m_buf, bytes, length);
}


/**
 * @brief       Packet destructor
 *
 * Free the allocated byte buffer.
 **/

Packet::~Packet()
{
    /* Free our byte buffer. */
    delete[] this->m_buf;
}


/**
 * @brief       Get a pointer to the packet byte buffer
 *
 * @return      Pointer to the PDU byte buffer
 **/

uint8_t *Packet::getBuf(void)
{
    return this->m_buf;
}


/**
 * @brief       Get Packet current length
 * 
 * @return      PDU byte buffer length
 **/

int Packet::getLength(void)
{
    return this->m_length;
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

SupportedFreqsResp::SupportedFreqsResp(NanoPbMsg message) : PhyMsg(message)
{
}


/** ASK modulation **/

/**
 * @brief       Create a SetAskMod message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetAskMod::SetAskMod(whad::NanoPbMsg message) : PhyMsg(message)
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

SetFskMod::SetFskMod(NanoPbMsg message) : PhyMsg(message)
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

Set4FskMod::Set4FskMod(NanoPbMsg message) : PhyMsg(message)
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

SetGfskMod::SetGfskMod(NanoPbMsg message) : PhyMsg(message)
{
}

SetGfskMod::SetGfskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_gfsk_mod(
        this->getRaw(),
        deviation
    );
}

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

SetBpskMod::SetBpskMod(NanoPbMsg message) : PhyMsg(message)
{
}

SetBpskMod::SetBpskMod()
{
}

/** QPSK modulation **/

SetQpskMod::SetQpskMod(NanoPbMsg message) : PhyMsg(message)
{
}

SetQpskMod::SetQpskMod(bool offset) : PhyMsg()
{
    whad_phy_set_qpsk_mod(
        this->getRaw(),
        offset
    );
}

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

SetMskMod::SetMskMod(NanoPbMsg message) : PhyMsg(message)
{
}

SetMskMod::SetMskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_msk_mod(
        this->getRaw(),
        deviation
    );
}

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

SetLoraMod::SetLoraMod(NanoPbMsg message) : PhyMsg(message)
{
}

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

uint32_t SetLoraMod::getBandwidth()
{
    if (this->parse())
    {
        return this->m_params.bandwidth;
    }
    
    /* Error. */
    return 0;
}

uint32_t SetLoraMod::getPreambleLength()
{
    if (this->parse())
    {
        return this->m_params.preamble_length;
    }
    
    /* Error. */
    return 0;
}

LoRaSpreadingFactor SetLoraMod::getSpreadingFactor()
{
    if (this->parse())
    {
        return (LoRaSpreadingFactor)this->m_params.sf;
    }

    /* Error. */
    return LoraSfError;
}

LoRaCodingRate SetLoraMod::getCodingRate()
{
    if (this->parse())
    {
        return (LoRaCodingRate)this->m_params.cr;
    }

    /* Error. */
    return LoraCrError; 
}

bool SetLoraMod::isCrcEnabled()
{
    if (this->parse())
    {
        return this->m_params.enable_crc;
    }

    /* Error. */
    return false;
}

bool SetLoraMod::isExplicitMode()
{
    if (this->parse())
    {
        return this->m_params.explicit_mode;
    }

    /* Error. */
    return false;
}

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

SetFreq::SetFreq(NanoPbMsg message) : PhyMsg(message)
{
}

SetFreq::SetFreq(uint32_t frequency) : PhyMsg()
{
    whad_phy_set_freq(
        this->getRaw(),
        frequency
    );
}

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

SetDatarate::SetDatarate(NanoPbMsg message) : PhyMsg(message)
{
}

SetDatarate::SetDatarate(uint32_t datarate)
{
    whad_phy_set_datarate(
        this->getRaw(),
        datarate
    );
}

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

SetEndianness::SetEndianness(NanoPbMsg message) : PhyMsg(message)
{
}

SetEndianness::SetEndianness(Endianness endian) : PhyMsg()
{
    whad_phy_set_endianness(
        this->getRaw(),
        (whad_phy_endian_t)endian
    );
}

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

SetTxPower::SetTxPower(NanoPbMsg message) : PhyMsg(message)
{
}

SetTxPower::SetTxPower(TxPower power) : PhyMsg()
{
    whad_phy_set_tx_power(
        this->getRaw(),
        (whad_phy_txpower_t)power
    );
}

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

SetPacketSize::SetPacketSize(NanoPbMsg message) : PhyMsg(message)
{
}

SetPacketSize::SetPacketSize(uint32_t size) : PhyMsg()
{
    whad_phy_set_packet_size(
        this->getRaw(),
        size
    );
}

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

SetSyncWord::SetSyncWord(NanoPbMsg message) : PhyMsg(message)
{
}

SetSyncWord::SetSyncWord(SyncWord syncWord) : PhyMsg()
{
    whad_phy_set_sync_word(
        this->getRaw(),
        syncWord.get(),
        syncWord.getSize()
    );
}

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

SniffMode::SniffMode(NanoPbMsg message) : PhyMsg(message)
{
}

SniffMode::SniffMode(bool iqMode) : PhyMsg()
{
    whad_phy_sniff_mode(
        this->getRaw(),
        iqMode
    );
}

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

JamMode::JamMode(NanoPbMsg message) : PhyMsg(message)
{
}

JamMode::JamMode(JammingMode mode) : PhyMsg()
{
    whad_phy_jam_mode(
        this->getRaw(),
        (whad_phy_jam_mode_t)mode
    );
}

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

MonitorMode::MonitorMode(NanoPbMsg message) : PhyMsg(message)
{
}

MonitorMode::MonitorMode() : PhyMsg()
{
    whad_phy_monitor_mode(
        this->getRaw()
    );
}

/** Start **/

Start::Start(NanoPbMsg message) : PhyMsg(message)
{
}

Start::Start() : PhyMsg()
{
    whad_phy_start(this->getRaw());
}

/** Stop **/

Stop::Stop(NanoPbMsg message) : PhyMsg(message)
{
}

Stop::Stop() : PhyMsg()
{
    whad_phy_stop(this->getRaw());
}

/** Send Packet **/

SendPacket::SendPacket(NanoPbMsg message) : PhyMsg(message)
{
}

SendPacket::SendPacket(Packet packet) : PhyMsg()
{
    whad_phy_send(
        this->getRaw(),
        packet.getBuf(),
        packet.getLength()
    );
}

Packet SendPacket::getPacket()
{
    whad_phy_packet_t packet;

    memset(packet.payload, 0, sizeof(packet.payload));

    whad_phy_send_parse(
        this->getRaw(),
        &packet
    );

    return Packet(packet.payload, packet.length);
}


/** Schedule Packet **/

SchedulePacket::SchedulePacket(NanoPbMsg message) : PhyMsg(message)
{
}

SchedulePacket::SchedulePacket(Packet packet, Timestamp timestamp) : PhyMsg()
{
    whad_phy_sched_packet(
        this->getRaw(),
        packet.getBuf(),
        packet.getLength(),
        timestamp.getSeconds(),
        timestamp.getMicroseconds()
    );
}

Packet SchedulePacket::getPacket()
{
    whad_phy_sched_packet_t sched_packet;

    whad_phy_sched_packet_parse(
        this->getRaw(),
        &sched_packet
    );

    return Packet(sched_packet.packet.payload, sched_packet.packet.length);
}

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

Jammed::Jammed(NanoPbMsg message) : PhyMsg(message)
{
}

Jammed::Jammed(Timestamp timestamp) : PhyMsg()
{
    whad_phy_jammed(
        this->getRaw(),
        timestamp.getSeconds(),
        timestamp.getMicroseconds()
    );
}

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

PacketReceived::PacketReceived(NanoPbMsg message) : PhyMsg(message)
{
}

PacketReceived::PacketReceived(uint32_t frequency, int32_t rssi, Timestamp ts, Packet packet)
{
    whad_phy_packet_received(
        this->getRaw(),
        frequency,
        rssi,
        ts.getSeconds(),
        ts.getMicroseconds(),
        packet.getBuf(),
        packet.getLength()
    );
}

bool PacketReceived::parse()
{
    return (whad_phy_packet_received_parse(this->getRaw(), &this->m_packet) == WHAD_SUCCESS);
}

uint32_t PacketReceived::getFrequency()
{
    if (this->parse())
    {
        return this->m_packet.freq;
    }

    return 0;
}

int32_t PacketReceived::getRssi()
{
    if (this->parse())
    {
        return this->m_packet.rssi;
    }

    return 0;   
}

Timestamp PacketReceived::getTimestamp()
{
    if (this->parse())
    {
        return Timestamp(this->m_packet.ts.ts_sec, this->m_packet.ts.ts_usec);
    }

    return Timestamp(0,0);       
}

Packet PacketReceived::getPacket()
{
    if (this->parse())
    {
        return Packet(this->m_packet.packet.payload, this->m_packet.packet.length);
    }

    /* Error. */
    return Packet(0);
}

/** Scheduled packet notification **/

PacketScheduled::PacketScheduled(NanoPbMsg message) : PhyMsg(message)
{
}

PacketScheduled::PacketScheduled(uint8_t packetId, bool full) : PhyMsg()
{
    whad_phy_packet_scheduled(
        this->getRaw(), packetId, full
    );
}

bool PacketScheduled::parse()
{
    return (whad_phy_packet_scheduled_parse(this->getRaw(), &this->m_packet) == WHAD_SUCCESS);
}

uint8_t PacketScheduled::getPacketId()
{
    if (this->parse())
    {
        return this->m_packet.id;
    }

    return 0;
}

bool PacketScheduled::isFull()
{
    if (this->parse())
    {
        return this->m_packet.full;
    }

    return false;
}

/** Scheduled packet sent notification **/

ScheduledPacketSent::ScheduledPacketSent(NanoPbMsg message) : PhyMsg(message)
{
}

ScheduledPacketSent::ScheduledPacketSent(uint32_t packetId) : PhyMsg()
{
    whad_phy_sched_packet_sent(this->getRaw(), packetId);
}

uint32_t ScheduledPacketSent::getPacketId()
{
    uint32_t packetId = 0;

    whad_phy_sched_packet_sent_parse(this->getRaw(), &packetId);

    return packetId;
}