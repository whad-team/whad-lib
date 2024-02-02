#include "cpp/esb.hpp"

using namespace whad::esb;


static EsbAddress PromiscAddr(WHAD_ESB_ADDR_ANY, 5);
static EsbAddress NullAddr((uint8_t *)"\x00\x00\x00\x00\x00", 5);


/**
 * @brief   BD Address default constructor.
 **/

EsbAddress::EsbAddress(void)
{
    memset(this->m_address, 0, 5);
    this->m_size = 0;
}


/**
 * @brief   ESB Address constructor.
 * 
 * @param[in]   pAddress    ESB address byte buffer (5 bytes max)
 * @param[in]   size        Address size in bytes
 **/

EsbAddress::EsbAddress(uint8_t *pAddress, uint8_t size)
{
    if (size <= 5)
    {
        this->m_size = size;
        memcpy(this->m_address, pAddress, size);
    }
}


/**
 * @brief   Get address length.
 * 
 * @retval  int   Address length in bytes
 **/

uint8_t EsbAddress::getLength(void)
{
    return this->m_size;
}


/**
 * @brief   Get address buffer.
 * 
 * @return  Pointer to the BD address byte buffer (6 bytes)
 **/

uint8_t *EsbAddress::getAddressBuf(void)
{
    return this->m_address;
}


/**
 * @brief   Set ESB address.
 * 
 * @param[in]   pAddress    Pointer to a 6-byte BD address buffer
 **/

void EsbAddress::setAddress(uint8_t *pAddress, uint8_t size)
{
    if (pAddress == NULL)
    {
        memset(this->m_address, 0, 5);
        this->m_size = 0;
    }

    if (size <= 5)
    {
        /* Copy BD address. */
        memcpy(this->m_address, pAddress, size);
    }
}


/********************************
 * ESB message base class
 *******************************/

/**
 * @brief   ESB message base class.
 **/

whad::esb::EsbMsg::EsbMsg() : NanoPbMsg()
{
}


/**
 * @brief       ESB message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::esb::EsbMsg::EsbMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   ESB message base class destructor.
 **/

whad::esb::EsbMsg::~EsbMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming Discovery domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      Discovery message type.
 **/

MessageType whad::esb::EsbMsg::getType(void)
{
    MessageType msgType = (whad::esb::MessageType)whad_esb_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}


/********************************
 * ESB messages classes
 *******************************/

SetNodeAddress::SetNodeAddress(EsbMsg &message) : EsbMsg(message)
{
}

SetNodeAddress::SetNodeAddress(EsbAddress &address) : EsbMsg()
{
    whad_esb_address_t addr;

    /* Prepare address. */
    addr.size = address.getLength();
    memcpy(addr.address, address.getAddressBuf(), addr.size);

    /* Craft message. */
    whad_esb_set_node_address(this->getRaw(), &addr);
}

EsbAddress& SetNodeAddress::getAddress(void)
{
    whad_esb_address_t addr;

    /* Parse message. */
    if (whad_esb_set_node_address_parse(this->getRaw(), &addr) == WHAD_SUCCESS)
    {
        this->m_address.setAddress(addr.address, addr.size);
    }
    else
        this->m_address.setAddress(NULL, 0);
    
    /* Success. */
    return this->m_address;
}

SniffMode::SniffMode(EsbMsg &message) : EsbMsg(message)
{
}

SniffMode::SniffMode(uint32_t channel, EsbAddress &address, bool showAcks)
{
    whad_esb_address_t addr;

    /* Convert address. */
    addr.size = address.getLength();
    memcpy(addr.address, address.getAddressBuf(), address.getLength());

    whad_esb_sniff(
        this->getRaw(),
        &addr,
        channel,
        showAcks
    );
}

SniffMode::SniffMode(uint32_t channel, EsbAddress &address) : SniffMode(channel, address, false)
{
}

SniffMode::SniffMode(EsbAddress &address) : SniffMode(WHAD_ESB_CHANNEL_AUTO, address, false)
{
}

SniffMode::SniffMode(uint32_t channel) : SniffMode(channel, PromiscAddr, false)
{
}

SniffMode::SniffMode() : SniffMode(WHAD_ESB_CHANNEL_AUTO, PromiscAddr, false)
{
}

bool SniffMode::parse(void)
{
    whad_result_t result;
    whad_esb_sniff_params_t params;

    result = whad_esb_sniff_parse(
        this->getRaw(),
        &params
    );

    if (result == WHAD_ERROR)
        return false;

    /* Saved parsed parameters. */
    this->m_channel = params.channel;
    this->m_address.setAddress(params.address.address, params.address.size);
    this->m_showacks = params.show_acks;

    /* Success. */
    return true;
}

uint32_t SniffMode::getChannel(void)
{
    if (this->parse())
    {
        return this->m_channel;
    }
    else
        return 0;
}

EsbAddress& SniffMode::getAddress(void)
{
    if (this->parse())
    {
        return this->m_address;
    }
    else
        return NullAddr;
}

bool SniffMode::mustShowAcks(void)
{
    if (this->parse())
    {
        return this->m_showacks;
    }
    else
        return false;
}

/** JamMode **/

JamMode::JamMode(EsbMsg &message) : EsbMsg(message)
{
}

JamMode::JamMode(uint32_t channel) : EsbMsg()
{
    this->m_channel = channel;

    whad_esb_jam(
        this->getRaw(),
        channel
    );
}

bool JamMode::parse(void)
{
    return (whad_esb_jam_parse(this->getRaw(), &this->m_channel) == WHAD_SUCCESS);
}

uint32_t JamMode::getChannel(void)
{
    if (this->parse())
    {
        return this->m_channel;
    }
    else
        return 0;
}

/** PacketSend **/

SendPacket::SendPacket(EsbMsg &message) : EsbMsg(message)
{
}

SendPacket::SendPacket(uint32_t channel, uint32_t retries, Packet &packet)
{
    /* Save properties. */
    this->m_channel = channel;
    this->m_retries = retries;
    this->m_packet.set(packet);

    /* Craft message. */
    whad_esb_send(
        this->getRaw(),
        channel,
        retries,
        packet.getBytes(),
        packet.getSize()
    );
}

bool SendPacket::parse()
{
    whad_result_t res;
    whad_esb_send_params_t params;
    Packet pkt;

    res = whad_esb_send_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_ERROR)
        return WHAD_ERROR;

    /* Set properties accordingly. */
    m_channel = params.channel;
    m_retries = params.retr_count;
    pkt = Packet(params.packet.bytes, params.packet.length);
    m_packet.set(pkt);

    /* Success. */
    return true;
}

uint32_t SendPacket::getChannel()
{
    if (this->parse())
    {
        return m_channel;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}

uint32_t SendPacket::getRetrCount()
{
    if (this->parse())
    {
        return m_retries;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}

Packet& SendPacket::getPacket()
{
    if (this->parse())
    {
        return m_packet;
    }
    else
    {
        throw whad::WhadMessageParsingError();
    }
}

SendPacketRaw::SendPacketRaw(EsbMsg &message) : SendPacket(message)
{
}

SendPacketRaw::SendPacketRaw(uint32_t channel, uint32_t retries, Packet &packet): SendPacket(channel, retries, packet)
{
    /* Save properties. */
    this->m_channel = channel;
    this->m_retries = retries;
    this->m_packet.set(packet);

    /* Craft message. */
    whad_esb_send_raw(
        this->getRaw(),
        channel,
        retries,
        packet.getBytes(),
        packet.getSize()
    );   
}

bool SendPacketRaw::parse()
{
    whad_result_t res;
    whad_esb_send_params_t params;
    Packet pkt;

    res = whad_esb_send_raw_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_ERROR)
        return WHAD_ERROR;

    /* Set properties accordingly. */
    m_channel = params.channel;
    m_retries = params.retr_count;
    pkt = Packet(params.packet.bytes, params.packet.length);
    m_packet.set(pkt);

    /* Success. */
    return true;
}

/** PrxMode **/

PrxMode::PrxMode(EsbMsg &message) : EsbMsg(message)
{
}

PrxMode::PrxMode(uint32_t channel) : EsbMsg()
{
    whad_esb_prx(
        this->getRaw(),
        channel
    );
}

uint32_t PrxMode::getChannel()
{
    uint32_t channel;

    if (whad_esb_prx_parse(this->getRaw(), &channel) == WHAD_SUCCESS)
    {
        return channel;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}


/** PtxMode **/

PtxMode::PtxMode(EsbMsg &message) : EsbMsg(message)
{
}

PtxMode::PtxMode(uint32_t channel) : EsbMsg()
{
    whad_esb_ptx(
        this->getRaw(),
        channel
    );
}

uint32_t PtxMode::getChannel()
{
    uint32_t channel;

    if (whad_esb_ptx_parse(this->getRaw(), &channel) == WHAD_SUCCESS)
    {
        return channel;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}


/** Start **/

Start::Start() : EsbMsg()
{
}

Start::Start(EsbMsg &message) : EsbMsg(message)
{
}


/** Stop **/

Stop::Stop() : EsbMsg()
{
}

Stop::Stop(EsbMsg &message) : EsbMsg(message)
{
}

/** Jammed **/

Jammed::Jammed(EsbMsg &message) : EsbMsg(message)
{
}

Jammed::Jammed(uint32_t timestamp) : EsbMsg()
{
    whad_esb_jammed(
        this->getRaw(),
        timestamp
    );
}

uint32_t Jammed::getTimestamp()
{
    uint32_t timestamp;

    if (whad_esb_jammed_parse(this->getRaw(), &timestamp) == WHAD_SUCCESS)
    {
        return timestamp;
    }
    else
    {
        throw WhadMessageParsingError();
    } 
}

/** RawPacketReceived **/

RawPacketReceived::RawPacketReceived(EsbMsg &message) : EsbMsg(message)
{
    /* Parse message. */
    this->parse();
}

RawPacketReceived::RawPacketReceived(uint32_t channel, Packet &packet) : EsbMsg()
{
    /* Save properties. */
    m_channel = channel;
    m_packet.set(packet);

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setChannel(uint32_t channel)
{
    m_channel = channel;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setPacket(Packet &packet)
{
    m_packet.set(packet);

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setRssi(int32_t rssi)
{
    m_rssi = rssi;
    m_hasRssi = true;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setTimestamp(uint32_t timestamp)
{
    m_timestamp = timestamp;
    m_hasTimestamp = true;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setAddress(EsbAddress &address)
{
    m_hasAddress = true;
    m_address = address;

    /* Save into message. */
    this->update();
}

void RawPacketReceived::setCrcValidity(bool validity)
{
    m_hasCrcValidity = true;
    m_crcValidity = validity;

    /* Save into message. */
    this->update();
}

uint32_t RawPacketReceived::getChannel()
{
    return m_channel;
}

bool RawPacketReceived::hasRssi()
{
    return m_hasRssi;
}

int32_t RawPacketReceived::getRssi()
{
    return m_rssi;
}

bool RawPacketReceived::hasTimestamp()
{
    return m_timestamp;
}

uint32_t RawPacketReceived::getTimestamp()
{
    return m_timestamp;
}

bool RawPacketReceived::hasCrcValidity()
{
    return m_hasCrcValidity;
}

bool RawPacketReceived::isCrcValid()
{
    return m_crcValidity;
}

bool RawPacketReceived::hasAddress()
{
    return m_hasAddress;
}

EsbAddress& RawPacketReceived::getAddress()
{
    return m_address;
}

Packet& RawPacketReceived::getPacket()
{
    return m_packet;
}



void RawPacketReceived::update()
{
    whad_esb_recvd_packet_t params;

    /* Set mandatory parameters. */
    params.channel = m_channel;
    params.packet.length = m_packet.getSize();
    memcpy(params.packet.bytes, m_packet.getBytes(), m_packet.getSize());

    /* Set optional parameters. */
    if (m_hasRssi)
    {
        params.has_rssi = true;
        params.rssi = m_rssi;
    }
    else
    {
        params.has_rssi = false;
    }

    if (m_hasTimestamp)
    {
        params.has_timestamp = true;
        params.timestamp = m_timestamp;
    }
    else
    {
        params.has_timestamp = false;
    }

    if (m_hasCrcValidity)
    {
        params.has_crc_validity = true;
        params.crc_validity = m_crcValidity;
    }
    else
    {
        params.has_crc_validity = false;
    }

    if (m_hasAddress)
    {
        params.has_address = true;
        params.address.size = m_address.getLength();
        memcpy(params.address.address, m_address.getAddressBuf(), m_address.getLength());
    }
    else
    {
        params.has_address = false;
    }

    whad_esb_raw_pdu_received(
        this->getRaw(),
        &params
    );
}

void RawPacketReceived::parse()
{
    whad_result_t res;
    whad_esb_recvd_packet_t params;

    res = whad_esb_raw_pdu_received_parse(
        this->getRaw(),
        &params
    );

    if (res == WHAD_SUCCESS)
    {
        /* Extract mandatory parameters. */
        m_channel = params.channel;
        m_packet.setBytes(params.packet.bytes, params.packet.length);

        /* Extract optional parameters. */
        if (params.has_rssi)
        {
            m_hasRssi = true;
            m_rssi = params.rssi;
        }
        else
            m_hasRssi = false;

        if (params.has_timestamp)
        {
            m_hasTimestamp = true;
            m_timestamp = params.timestamp;
        }
        else
            m_hasTimestamp = false;

        if (params.has_crc_validity)
        {
            m_hasCrcValidity = true;
            m_crcValidity = params.crc_validity;
        }
        else
            m_hasCrcValidity = false;

        if (params.has_address)
        {
            m_hasAddress = true;
            m_address.setAddress(params.address.address, params.address.size);
        }
        else
            m_hasAddress = false;
    }
    else
    {
        throw WhadMessageParsingError();
    }
}