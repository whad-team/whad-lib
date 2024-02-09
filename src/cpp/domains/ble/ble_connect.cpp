#include <ble/connect.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a message as a ConnectTo message.
*/
ConnectTo::ConnectTo(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       ConnectTo message constructor.
 * 
 * @param[in]   targetAddr      Target device BD address
 * @param[in]   accessAddress   Specify the access address to use for this connection, if supported
 *                              by the adapter
 * @param[in]   channelMap      Specify the channel map to use for this connection, if supported by
 *                              the adapter
 * @param[in]   hopInterval     Connection hop interval
 * @param[in]   hopIncrement    Connection hop increment
 * @param[in]   crcInit         CRC initial value (seed)
 **/

ConnectTo::ConnectTo(BDAddress targetAddr, uint32_t accessAddress, ChannelMap channelMap,
                              uint32_t hopInterval, uint32_t hopIncrement, uint32_t crcInit) : BleMsg()
{
    m_targetAddr = targetAddr;
    m_accessAddr = accessAddress;
    m_channelMap = channelMap;
    m_hopInterval = hopInterval;
    m_hopIncrement = hopIncrement;
    m_crcInit = crcInit;
}


/**
 * @brief   Pack parameters into a BleMsg object
 */

void ConnectTo::pack()
{
    whad_ble_connect_to(
        this->getMessage(),
        m_targetAddr.getAddressBuf(),
        (whad_ble_addrtype_t)m_targetAddr.getType(),
        m_accessAddr,
        m_channelMap.getChannelMapBuf(),
        m_hopInterval,
        m_hopIncrement,
        m_crcInit
    );
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void ConnectTo::unpack()
{
    whad_result_t result;
    whad_ble_connect_params_t params;

    result = whad_ble_connect_to_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_targetAddr = BDAddress((AddressType)params.addr_type, params.bdaddr);
        m_accessAddr = params.access_address;
        m_channelMap = ChannelMap(params.channelmap);
        m_hopIncrement = params.hop_increment;
        m_hopInterval = params.hop_interval;
        m_crcInit = params.crc_init;
    }
}


/**
 * @brief   Retrieve the target BD address
 * 
 * @retval  Target BD Address
 */

BDAddress& ConnectTo::getTargetAddr()
{
    return m_targetAddr;
}


/**
 * @brief   Retrieve the target Access Address
 * 
 * @retval  Target Access Address
 */

uint32_t ConnectTo::getAccessAddr()
{
    return m_accessAddr;
}


/**
 * @brief   Retrieve the channel map
 * 
 * @retval  Channel Map
 */

ChannelMap& ConnectTo::getChannelMap()
{
    return m_channelMap;
}


/**
 * @brief   Retrieve the hop increment
 * 
 * @retval  Hop increment value
 */

uint32_t ConnectTo::getHopIncrement()
{
    return m_hopIncrement;
}


/**
 * @brief   Retrieve the hop interval
 * 
 * @retval  Hop interval value
 */

uint32_t ConnectTo::getHopInterval()
{
    return m_hopInterval;
}


/**
 * @brief   Retrieve the CRC seed
 * 
 * @retval  CRC init value
 */

uint32_t ConnectTo::getCrcInit()
{
    return m_crcInit;
}