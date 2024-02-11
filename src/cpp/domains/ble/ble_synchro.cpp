#include <ble/synchro.hpp>

using namespace whad::ble;


/**
 * @brief   Parse a BleMsg as a Synchronized message.
 * 
 * @param[in]   message     Message to parse
 */

Synchronized::Synchronized(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Notify a successful connection synchronization
 * 
 * @param[in]   accessAddress       Connection access address
 * @param[in]   crcInit             Recovered CRC initial value (seed)
 * @param[in]   hopInterval         Recovered hop interval
 * @param[in]   hopIncrement        Recovered hop increment
 * @param[in]   channelMap          Recovered channel map
 **/

Synchronized::Synchronized(uint32_t accessAddress, uint32_t crcInit, uint32_t hopInterval,
                                 uint32_t hopIncrement, ChannelMap channelMap) : BleMsg()
{
    m_accessAddr = accessAddress;
    m_crcInit = crcInit;
    m_hopIncrement = hopIncrement;
    m_hopInterval = hopInterval;
    m_channelMap = channelMap;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void Synchronized::pack()
{
    whad_ble_synchronized(
        this->getMessage(),
        m_accessAddr,
        m_crcInit,
        m_hopInterval,
        m_hopIncrement,
        m_channelMap.getChannelMapBuf()
    );
}


/**
 * @brief   Get the access address
 * 
 * @retval  Access Address
 */

uint32_t Synchronized::getAccessAddress()
{
    return m_accessAddr;
}


/**
 * @brief   Get the CRC initial value
 * 
 * @retval  CRC initial value
 */

uint32_t Synchronized::getCrcInit()
{
    return m_crcInit;
}


/**
 * @brief   Get the connection hop interval
 * 
 * @retval  Hop interval value
 */

uint32_t Synchronized::getHopInterval()
{
    return m_hopInterval;
}


/**
 * @brief   Get the connection hop increment
 * 
 * @retval  Hop increment value
 */

uint32_t Synchronized::getHopIncrement()
{
    return m_hopIncrement;
}


/**
 * @brief   Get the connection channel map
 * 
 * @retval  Channel map
 */

ChannelMap& Synchronized::getChannelMap()
{
    return m_channelMap;
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void Synchronized::unpack()
{
    whad_result_t result;
    whad_ble_synchro_params_t params;

    result = whad_ble_synchronized_parse(
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
        m_hopIncrement = params.hop_increment;
        m_hopInterval = params.hop_interval;
        m_crcInit = params.crc_init;
        m_channelMap = ChannelMap(params.channelmap);
    }
}


/**
 * @brief   Parse a BleMsg as a Desynchronized message
 * 
 * @param[in]   message     Message to parse
 */

Desynchronized::Desynchronized(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       Notify a connection desynchronization
 * 
 * @param[in]   accessAddress       Connection access address
 **/

Desynchronized::Desynchronized(uint32_t accessAddress) : BleMsg()
{
    m_accessAddr = accessAddress;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void Desynchronized::pack()
{
    whad_ble_desynchronized(
        this->getMessage(),
        m_accessAddr
    );
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void Desynchronized::unpack()
{
    whad_result_t result;

    result = whad_ble_desynchronized_parse(
        this->getMessage(),
        &m_accessAddr
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Get the access address
 * 
 * @retval  Access Address
 */

uint32_t Desynchronized::getAccessAddress()
{
    return m_accessAddr;
}