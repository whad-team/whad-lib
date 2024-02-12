#include <ble/sniff_act_conn.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg as a SniffActiveConn message
 * 
 * @param[in]   message     Message to parse
 */

SniffActiveConn::SniffActiveConn(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       SniffActiveConn message constructor.
 * 
 * @param[in]   accessAddress   Connection access address
 * @param[in]   crcInit         Connection CRC init value (seed)
 * @param[in]   hopInterval     Hop interval
 * @param[in]   hopIncrement    Hop increment
 * @param[in]   channelMap      Connection channel map
 * @param[in]   channels        Channel map specifying the channels to use when recovering the
 *                              channel map (if multiple sniffers are used -- collaborative
 *                              channel map recovery).
 **/

SniffActiveConn::SniffActiveConn(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval, uint32_t hopIncrement, ChannelMap channelMap, ChannelMap channels) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_crcInit = crcInit;
    m_hopIncrement = hopIncrement;
    m_hopInterval = hopInterval;
    m_channelMap = channelMap;
    m_channels = channels;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void SniffActiveConn::pack()
{
    whad_ble_sniff_active_conn(
        this->getMessage(),
        m_accessAddr,
        m_crcInit,
        m_hopInterval,
        m_hopIncrement,
        m_channelMap.getChannelMapBuf(),
        m_channels.getChannelMapBuf()
    ); 
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void SniffActiveConn::unpack()
{
    whad_result_t result;
    whad_ble_sniff_conn_params_t params;

    result = whad_ble_sniff_active_conn_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Extract parameters. */
        m_accessAddr = params.access_address;
        m_crcInit = params.crc_init;
        m_hopIncrement = params.hop_increment;
        m_hopInterval = params.hop_interval;
        m_channelMap = ChannelMap(params.channelmap);
        m_channels = ChannelMap(params.channels);
    }
}

/**
 * @brief   Get the access address
 * 
 * @retval  Access Address
 */

uint32_t SniffActiveConn::getAccessAddress()
{
    return m_accessAddr;
}


/**
 * @brief   Get the CRC initial value
 * 
 * @retval  CRC initial value
 */

uint32_t SniffActiveConn::getCrcInit()
{
    return m_crcInit;
}


/**
 * @brief   Get the connection hop interval
 * 
 * @retval  Hop interval value
 */

uint32_t SniffActiveConn::getHopInterval()
{
    return m_hopInterval;
}


/**
 * @brief   Get the connection hop increment
 * 
 * @retval  Hop increment value
 */

uint32_t SniffActiveConn::getHopIncrement()
{
    return m_hopIncrement;
}


/**
 * @brief   Get the connection channel map
 * 
 * @retval  Channel map
 */

ChannelMap& SniffActiveConn::getChannelMap()
{
    return m_channelMap;
}


/**
 * @brief   Get the connection channels
 * 
 * @retval  Channels
 */

ChannelMap& SniffActiveConn::getChannels()
{
    return m_channels;
}